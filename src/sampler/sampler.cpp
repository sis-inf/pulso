#include "sampler.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

namespace pulso::sampler {

Sampler::Sampler(
    std::vector<std::shared_ptr<pulso::collectors::ICollector>> collectors,
    pulso::storage::Storage& storage,
    int intervaloSegundos)
    : collectors_(std::move(collectors)),
      storage_(storage),
      intervaloSegundos_(intervaloSegundos) {}

Sampler::~Sampler() {
    detener();
}

void Sampler::iniciar() {
    if (corriendo_) {
        return;
    }

    corriendo_ = true;

    thread_ = std::thread([this]() {
        while (corriendo_) {

            auto timestamp =
                static_cast<std::int64_t>(std::time(nullptr));

            pulso::core::Snapshot snapshot;
            snapshot.timestamp = timestamp;

            for (const auto& collector : collectors_) {

                try {

                    auto metricas =
                        collector->recolectar();

                    snapshot.metrics.insert(
                        snapshot.metrics.end(),
                        metricas.begin(),
                        metricas.end());

                } catch (const std::exception& e) {

                    std::cerr
                        << "Error en collector "
                        << collector->nombre()
                        << ": "
                        << e.what()
                        << std::endl;
                }
            }

            try {

                storage_.save(snapshot);

            } catch (const std::exception& e) {

                std::cerr
                    << "Error al guardar snapshot: "
                    << e.what()
                    << std::endl;
            }

            std::unique_lock<std::mutex> lock(mutex_);

            cv_.wait_for(
                lock,
                std::chrono::seconds(intervaloSegundos_),
                [this]() {
                    return !corriendo_;
                });
        }
    });
}

void Sampler::detener() {

    if (!corriendo_) {
        return;
    }

    corriendo_ = false;

    cv_.notify_all();

    if (thread_.joinable()) {
        thread_.join();
    }
}

bool Sampler::corriendo() const {
    return corriendo_;
}

} // namespace pulso::sampler
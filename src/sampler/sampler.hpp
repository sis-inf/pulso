#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "../collectors/icollector.hpp"
#include "../core/types.hpp"
#include "../storage/storage.hpp"

namespace pulso::sampler {

class Sampler {
public:
    Sampler(
        std::vector<std::shared_ptr<pulso::collectors::ICollector>> collectors,
        pulso::storage::Storage& storage,
        int intervaloSegundos);

    ~Sampler();

    /// Inicia el thread de muestreo. No bloquea.
    void iniciar();

    /// Solicita la detención y espera a que el thread termine.
    void detener();

    /// Devuelve true si el sampler está corriendo.
    bool corriendo() const;

private:
    std::vector<std::shared_ptr<pulso::collectors::ICollector>> collectors_;
    pulso::storage::Storage& storage_;
    int intervaloSegundos_;

    std::thread thread_;
    std::atomic<bool> corriendo_{false};
    std::condition_variable cv_;
    std::mutex mutex_;
};

} // namespace pulso::sampler
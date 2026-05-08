#include "system_monitor.h"
#include <chrono>

/// @brief Inicia el monitoreo registrando el tiempo de inicio.
void SystemMonitor::start() {
    running_ = true;
    last_time_ = std::chrono::steady_clock::now();
}

/// @brief Detiene el monitoreo.
void SystemMonitor::stop() {
    running_ = false;
}

/// @brief Retorna la última lectura de métricas almacenada.
/// @return Mapa con nombre de métrica y su valor.
std::map<std::string, double> SystemMonitor::getLastReading() const {
    return last_reading_;
}

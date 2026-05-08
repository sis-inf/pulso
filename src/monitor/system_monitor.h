#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include <chrono>
#include <map>
#include <string>

/// @brief Clase que coordina la lectura de métricas del sistema
/// y almacena la última lectura de forma temporal.
class SystemMonitor {
public:
    /// @brief Inicia el monitoreo del sistema.
    void start();

    /// @brief Detiene el monitoreo del sistema.
    void stop();

    /// @brief Retorna la última lectura de métricas.
    /// @return Mapa con nombre de métrica y su valor double.
    std::map<std::string, double> getLastReading() const;

private:
    bool running_{false};
    std::map<std::string, double> last_reading_{};
    std::chrono::steady_clock::time_point last_time_{};
};

#endif // SYSTEM_MONITOR_H

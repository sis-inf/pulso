#include "uptime_collector.h"
#include <fstream>
#include <stdexcept>

UptimeInfo getUptime() {
    // 1. Abrir el archivo /proc/uptime
    std::ifstream file("/proc/uptime");
    
    // 2. Criterio de aceptación: Lanzar error si no se puede acceder
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo acceder a /proc/uptime");
    }

    // 3. Leer el primer campo (tiempo en segundos como float/double)
    double uptime_seconds_float;
    if (!(file >> uptime_seconds_float)) {
        throw std::runtime_error("Error al leer el formato de /proc/uptime");
    }
    file.close();

    // 4. Convertir a entero (uint64_t)
    uint64_t total_seconds = static_cast<uint64_t>(uptime_seconds_float);

    // 5. Criterio de aceptación: Calcular días, horas, minutos y segundos
    uint32_t days = total_seconds / 86400;
    uint32_t remaining_after_days = total_seconds % 86400;

    uint32_t hours = remaining_after_days / 3600;
    uint32_t remaining_after_hours = remaining_after_days % 3600;

    uint32_t minutes = remaining_after_hours / 60;
    uint32_t seconds = remaining_after_hours % 60;

    // 6. Criterio de aceptación: Formatear el string "5d 3h 12m 44s"
    std::string formatted = std::to_string(days) + "d " + 
                            std::to_string(hours) + "h " + 
                            std::to_string(minutes) + "m " + 
                            std::to_string(seconds) + "s";

    // 7. Retornar la estructura con los datos llenos
    return {
        total_seconds,
        days,
        hours,
        minutes,
        seconds,
        formatted
    };
}
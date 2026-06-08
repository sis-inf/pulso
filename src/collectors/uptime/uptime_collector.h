#ifndef UPTIME_COLLECTOR_H
#define UPTIME_COLLECTOR_H

#include <cstdint>
#include <string>

// Estructura requerida por los criterios de aceptación
struct UptimeInfo {
    uint64_t total_seconds;
    uint32_t days;
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
    std::string formatted; // Debe tener el formato '5d 3h 12m 44s'
};

// Declaración de la función principal
UptimeInfo getUptime();

#endif // UPTIME_COLLECTOR_H 
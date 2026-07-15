#pragma once
/**
 * @file rutas_proc.hpp
 * @brief Constantes centralizadas para las rutas de archivos virtuales del
 *        kernel Linux (/proc/*, /sys/*).
 *
 * Centralizar estas rutas permite:
 * 1. Evitar strings literales repetidos en múltiples collectors.
 * 2. Inyectar rutas alternativas en tests sin modificar el código de producción.
 * 3. Facilitar futuros cambios si alguna ruta necesita configurarse.
 */

namespace pulso::platform::linux_platform {

/// Ruta al archivo de estadísticas de CPU del kernel.
inline constexpr const char* RUTA_PROC_STAT       = "/proc/stat";

/// Ruta al archivo de información de memoria del kernel.
inline constexpr const char* RUTA_PROC_MEMINFO    = "/proc/meminfo";

/// Ruta al archivo de estadísticas de red del kernel.
inline constexpr const char* RUTA_PROC_NET_DEV    = "/proc/net/dev";

/// Ruta al archivo de carga promedio del sistema.
inline constexpr const char* RUTA_PROC_LOADAVG    = "/proc/loadavg";

/// Ruta al archivo de tiempo de actividad del sistema.
inline constexpr const char* RUTA_PROC_UPTIME     = "/proc/uptime";

}  // namespace pulso::platform::linux_platform
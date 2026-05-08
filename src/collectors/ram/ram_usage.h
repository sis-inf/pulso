#ifndef RAM_USAGE_H
#define RAM_USAGE_H

#include <string>

/// @brief Obtiene el uso de RAM en porcentaje leyendo /proc/meminfo.
/// @param ruta Ruta al archivo (por defecto "/proc/meminfo").
/// @return Porcentaje de uso de RAM (0.0 - 100.0).
/// @throws std::runtime_error Si el archivo no existe o no se puede leer.
double getRAMUsage(const std::string& ruta = "/proc/meminfo");

#endif // RAM_USAGE_H

#ifndef DISK_USAGE_H
#define DISK_USAGE_H
#include <cstdint>
#include <string>

/// @brief Estructura que representa el uso de disco del sistema.
struct DiskUsage {
    uint64_t total{}; ///< Espacio total del sistema de archivos
    uint64_t usado{}; ///< Espacio actualmente utilizado
    uint64_t libre{}; ///< Espacio disponible para el usuario
};

/// @brief Obtiene las métricas de uso de disco usando statvfs.
/// @param ruta Ruta del punto de montaje a consultar (por defecto "/").
/// @return Estructura DiskUsage con total, usado y libre en bytes.
/// @throws std::runtime_error si statvfs falla, con el errno correspondiente.
DiskUsage ObtenerUsoDisco(const std::string& ruta = "/");

#endif // DISK_USAGE_H
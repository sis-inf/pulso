#include "disk_usage.h"
#include <sys/statvfs.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>

/// @brief Obtiene las métricas de uso de disco del sistema de archivos raíz.
/// @param ruta Ruta del punto de montaje a consultar (por defecto "/").
/// @return Estructura DiskUsage con total, usado y libre en bytes.
/// @throws std::runtime_error si statvfs falla.
DiskUsage ObtenerUsoDisco(const std::string& ruta) {
    struct statvfs buf;

    if (statvfs(ruta.c_str(), &buf) != 0) {
        throw std::runtime_error(
            std::string("Error al leer métricas de disco: ") + std::strerror(errno)
        );
    }

    DiskUsage uso{};

    uso.total = static_cast<uint64_t>(buf.f_blocks) * buf.f_frsize;
    uso.libre  = static_cast<uint64_t>(buf.f_bavail) * buf.f_frsize;
    uso.usado  = uso.total - uso.libre;

    return uso;
}
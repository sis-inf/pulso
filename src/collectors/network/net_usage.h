#ifndef NET_USAGE_H
#define NET_USAGE_H

#include <cstdint>
#include <string>

/// @brief Estructura que representa el uso de red del sistema.
/// Acumula los bytes recibidos y enviados de todas las interfaces
/// activas, excluyendo la interfaz de loopback (lo).
struct UsoRed {
    uint64_t rx_bytes_total{}; ///< Total de bytes recibidos por todas las interfaces
    uint64_t tx_bytes_total{}; ///< Total de bytes enviados por todas las interfaces
};

/// @brief Obtiene los bytes recibidos y enviados por la red.
/// Lee /proc/net/dev, salta las dos primeras líneas de encabezado,
/// parsea cada interfaz y excluye la interfaz lo.
/// @param ruta Ruta al archivo (por defecto "/proc/net/dev").
/// @return Estructura UsoRed con rx_bytes_total y tx_bytes_total.
/// @throws std::runtime_error si el archivo no es accesible.
UsoRed ObtenerUsoRed(const std::string& ruta = "/proc/net/dev");

#endif 
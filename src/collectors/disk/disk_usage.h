#pragma once

#include <cstdint>

/// @brief Estructura con información de uso de disco.
struct DiskInfo {
  uint64_t total{};  ///< Espacio total en bytes
  uint64_t used{};   ///< Espacio usado en bytes
  uint64_t free{};   ///< Espacio libre en bytes
};

/// @brief Obtiene información del uso de disco.
/// @return Estructura DiskInfo con espacio total, usado y libre.
DiskInfo GetDiskUsage();
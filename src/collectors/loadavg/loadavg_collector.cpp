#include "loadavg_collector.h"
#include <fstream>
#include <stdexcept>

LoadAvgInfo getLoadAverage() {
    // Abrir el archivo virtual del sistema operativo Linux
    std::ifstream file("/proc/loadavg");
    
    // Criterio de aceptación: Lanzar std::runtime_error si no existe o no se puede abrir
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir o no existe el archivo /proc/loadavg");
    }
    
    LoadAvgInfo info{0.0f, 0.0f, 0.0f};
    
    // Leer y parsear los primeros 3 valores float separados por espacios en blanco
    if (!(file >> info.load1 >> info.load5 >> info.load15)) {
        throw std::runtime_error("Error: El formato de /proc/loadavg es invalido");
    }
    
    return info;
}

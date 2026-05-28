#include "ram_usage.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

namespace pulso::collectors::memory {

RamInfo getRamUsage() {
    std::ifstream file("/proc/meminfo");

    if (!file.is_open()) {
        throw std::runtime_error(
            "No se pudo abrir el archivo /proc/meminfo: "
            "verifique permisos y disponibilidad del sistema"
        );
    }

    std::string line;
    long long memTotal     = 0;
    long long memAvailable = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        long long value;

        iss >> key >> value;

        if (key == "MemTotal:") {
            memTotal = value;
        }

        if (key == "MemAvailable:") {
            memAvailable = value;
        }
    }

    if (memTotal == 0 || memAvailable == 0) {
        throw std::runtime_error(
            "No se encontraron las claves MemTotal o MemAvailable en /proc/meminfo"
        );
    }

    // Convertir de kB a bytes
    memTotal     *= 1024;
    memAvailable *= 1024;

    // Calcular memoria usada: MemTotal - MemAvailable
    long long memUsed = memTotal - memAvailable;

    return {
        static_cast<uint64_t>(memTotal),
        static_cast<uint64_t>(memUsed),
        static_cast<uint64_t>(memAvailable)
    };
}

} // namespace pulso::collectors::memory
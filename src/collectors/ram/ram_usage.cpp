#include "ram_usage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

/// @brief Obtiene el uso de RAM en porcentaje leyendo /proc/meminfo.
/// @param ruta Ruta al archivo de información de memoria.
/// @return Porcentaje de uso de RAM (0.0 - 100.0).
/// @throws std::runtime_error Si el archivo no existe o no se puede leer.
double getRAMUsage(const std::string& ruta) {
    // Abrir archivo
    std::ifstream archivo(ruta);

    // Verificar si el archivo existe y se puede abrir
    if (!archivo.is_open()) {
        throw std::runtime_error("No se puede abrir el archivo: " + ruta);
    }

    uint64_t mem_total = 0;
    uint64_t mem_available = 0;
    bool encontro_total = false;
    bool encontro_available = false;

    std::string linea;

    // Parsear línea por línea con std::getline
    while (std::getline(archivo, linea)) {
        std::istringstream flujo(linea);
        std::string clave;
        uint64_t valor;

        flujo >> clave >> valor;

        if (clave == "MemTotal:") {
            mem_total = valor;
            encontro_total = true;
        } else if (clave == "MemAvailable:") {
            mem_available = valor;
            encontro_available = true;
        }

        // Terminar cuando se encontraron ambos valores
        if (encontro_total && encontro_available) {
            break;
        }
    }

    // Verificar que se encontraron los valores necesarios
    if (!encontro_total || !encontro_available) {
        return 0.0;
    }

    // Evitar división por cero
    if (mem_total == 0) {
        return 0.0;
    }

    // Aplicar fórmula: (total - available) / total * 100
    return static_cast<double>(mem_total - mem_available) / mem_total * 100.0;
}

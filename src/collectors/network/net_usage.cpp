#include "net_usage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

/// @brief Obtiene los bytes recibidos y enviados por la red desde /proc/net/dev.
/// Salta las dos primeras líneas de encabezado, parsea cada interfaz extrayendo
/// el nombre (antes de ':'), columna 1 = rx_bytes y columna 9 = tx_bytes.
/// Excluye la interfaz lo y suma el resto de interfaces.
/// @param ruta Ruta al archivo de estadísticas de red.
/// @return Estructura UsoRed con rx_bytes_total y tx_bytes_total.
/// @throws std::runtime_error si el archivo no es accesible.
UsoRed ObtenerUsoRed(const std::string& ruta) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        throw std::runtime_error(
            "Error al acceder a " + ruta + ": archivo no accesible"
        );
    }

    UsoRed uso{};
    std::string linea;

    std::getline(archivo, linea); 
    std::getline(archivo, linea); 

    while (std::getline(archivo, linea)) {
        std::istringstream flujo(linea);

        std::string nombre_interfaz;
        std::getline(flujo, nombre_interfaz, ':');

        size_t inicio = nombre_interfaz.find_first_not_of(" \t");
        if (inicio != std::string::npos) {
            nombre_interfaz = nombre_interfaz.substr(inicio);
        }

        if (nombre_interfaz == "lo") {
            continue;
        }

        uint64_t rx_bytes = 0;
        uint64_t ignorado = 0;
        uint64_t tx_bytes = 0;

        flujo >> rx_bytes;  

        for (int i = 0; i < 7; ++i) {
            flujo >> ignorado;
        }

        flujo >> tx_bytes;    
        uso.rx_bytes_total += rx_bytes;
        uso.tx_bytes_total += tx_bytes;
    }

    return uso;
}
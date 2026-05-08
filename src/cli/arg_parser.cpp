#include "arg_parser.h"
#include <iostream>
#include <stdexcept>
#include <string>

/// @brief Parsea los argumentos de línea de comandos manualmente.
/// @param argc Cantidad de argumentos.
/// @param argv Arreglo de argumentos.
/// @return Estructura CliArgs con los valores parseados.
CliArgs parseArgs(int argc, char* argv[]) {
    CliArgs args;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            args.help = true;
            return args;
        } else if (arg == "--interval") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--interval requiere un valor");
            }
            int val = std::stoi(argv[++i]);
            if (val <= 0) {
                throw std::invalid_argument("--interval debe ser mayor a 0");
            }
            args.interval_ms = val;
        } else if (arg == "--metrics") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--metrics requiere un valor");
            }
            args.metrics = argv[++i];
        }
    }

    // Validar que interval_ms sea mayor a 100ms
    if (args.interval_ms < 100) {
        throw std::invalid_argument("--interval debe ser mayor o igual a 100ms");
    }

    return args;
}

/// @brief Imprime el mensaje de ayuda en consola.
void printHelp() {
    std::cout << "Uso: pulso [opciones]\n\n"
              << "Opciones:\n"
              << "  --interval <ms>   Intervalo de lectura en ms (default: 1000)\n"
              << "  --metrics <list>  Metricas a monitorear (cpu, ram, disk)\n"
              << "  -h, --help        Mostrar esta ayuda\n";
}

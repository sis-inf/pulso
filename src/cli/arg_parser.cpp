#include "arg_parser.h"

#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Procesa la lista de métricas y actualiza la configuración.
 *
 * Ejemplo:
 * --metrics cpu,ram
 */
static void parse_metrics(const std::string& metrics, MonitorConfig& config)
{
    /**
     * Primero deshabilitamos todas las métricas.
     * Luego habilitamos únicamente las indicadas.
     */
    config.cpu = false;
    config.ram = false;
    config.disk = false;

    std::stringstream ss(metrics);

    std::string item;

    while (std::getline(ss, item, ','))
    {
        if (item == "cpu")
        {
            config.cpu = true;
        }
        else if (item == "ram")
        {
            config.ram = true;
        }
        else if (item == "disk")
        {
            config.disk = true;
        }
    }
}

void print_help()
{
    std::cout << "Uso:\n";
    std::cout << "  monitor [opciones]\n\n";

    std::cout << "Opciones:\n";
    std::cout << "  --interval <ms>      Intervalo de lectura\n";
    std::cout << "  --metrics <lista>    cpu,ram,disk\n";
    std::cout << "  -h, --help           Mostrar ayuda\n";
}

bool parse_arguments(int argc, char* argv[], MonitorConfig& config)
{
    /**
     * Recorremos argv manualmente.
     */
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        /**
         * Mostrar ayuda.
         */
        if (arg == "-h" || arg == "--help")
        {
            print_help();
            return false;
        }

        /**
         * Procesar intervalo.
         */
        else if (arg == "--interval")
        {
            /**
             * Verificar que exista un valor después.
             */
            if (i + 1 >= argc)
            {
                std::cerr << "Error: falta valor para --interval\n";
                return false;
            }

            int interval = std::stoi(argv[++i]);

            /**
             * Validación requerida por la issue.
             */
            if (interval <= 100)
            {
                std::cerr << "Error: interval debe ser mayor a 100ms\n";
                return false;
            }

            config.interval_ms = interval;
        }

        /**
         * Procesar métricas.
         */
        else if (arg == "--metrics")
        {
            /**
             * Validar existencia del valor.
             */
            if (i + 1 >= argc)
            {
                std::cerr << "Error: falta valor para --metrics\n";
                return false;
            }

            parse_metrics(argv[++i], config);
        }

        /**
         * Argumento desconocido.
         */
        else
        {
            std::cerr << "Error: argumento desconocido -> "
                      << arg << "\n";

            return false;
        }
    }

    return true;
}
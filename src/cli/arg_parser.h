#ifndef CLI_ARG_PARSER_H
#define CLI_ARG_PARSER_H

#include <string>

/// @brief Resultado del parseo de argumentos CLI.
struct CliArgs {
    int interval_ms{1000};  ///< Intervalo en ms (--interval)
    std::string metrics{};  ///< Métricas a monitorear (--metrics)
    bool help{false};       ///< Mostrar ayuda (-h / --help)
};

/// @brief Parsea los argumentos de línea de comandos.
/// @param argc Cantidad de argumentos.
/// @param argv Arreglo de argumentos.
/// @return Estructura CliArgs con los valores parseados.
CliArgs parseArgs(int argc, char* argv[]);

/// @brief Imprime el mensaje de ayuda.
void printHelp();

#endif // CLI_ARG_PARSER_H

#pragma once

#include "../config.hpp"

/**
 * @brief Procesa argumentos de línea de comandos.
 *
 * Permite sobrescribir valores dentro de MonitorConfig.
 *
 * Argumentos soportados:
 * - --interval <ms>
 * - --metrics <lista>
 * - -h | --help
 *
 * @param argc Cantidad de argumentos.
 * @param argv Vector de argumentos.
 * @param config Configuración a modificar.
 *
 * @return true si la ejecución puede continuar.
 * @return false si ocurrió un error o se mostró ayuda.
 */
bool parse_arguments(int argc, char* argv[], MonitorConfig& config);

/**
 * @brief Muestra la ayuda del programa.
 */
void print_help();
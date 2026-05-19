#include <atomic>
#include <chrono>
#include <map>
#include <string>
#include <thread>
#include <iostream>

#include "config/config.hpp"
#include "cli/arg_parser.h"

// --- Declaraciones de funciones existentes en otros archivos ---

// collectors/cpu/cpu_usage.cpp
double ObtenerUsoCPU();

// utils/disk_usage.cpp
double getDiskUsage();

// collectors/network/network_io.cpp
struct NetworkIO { long rx; long tx; };
NetworkIO getNetworkIO();

// utils/console_formatter.cpp
void printMetrics(const std::map<std::string, double>& data);

// utils/signal_handler.cpp
void setupSignalHandler();
extern std::atomic<bool> isRunning;

// --------------------------------------------------------------

/**
 * @brief Ejecuta el loop de monitoreo hasta que isRunning sea false.
 *
 * En cada iteración:
 *  1. Recolecta métricas de CPU, disco y red en un mapa.
 *  2. Llama al formateador para mostrarlas por consola.
 *  3. Duerme `intervalo_ms` milisegundos antes del siguiente ciclo.
 *
 * @param intervalo_ms Tiempo de espera entre lecturas, en milisegundos.
 */
void start(int intervalo_ms) {
    while (isRunning) {
        // 1. Actualizar el mapa con las lecturas de cada collector
        std::map<std::string, double> metricas;
        metricas["cpu"]    = ObtenerUsoCPU();
        metricas["disk"]   = getDiskUsage();

        NetworkIO net      = getNetworkIO();
        metricas["net.rx"] = static_cast<double>(net.rx);
        metricas["net.tx"] = static_cast<double>(net.tx);

        // 2. Llamar al formateador
        printMetrics(metricas);

        // 3. Esperar X ms antes del siguiente ciclo
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalo_ms));
    }
}



/**
 * @brief Punto de entrada principal.
 */
int main(int argc, char* argv[])
{
    /**
     * Configuración con valores por defecto.
     */
    MonitorConfig config;

    /**
     * Procesar argumentos CLI.
     */
    if (!parse_arguments(argc, argv, config))
    {
        return 1;
    }

    /**
     * Configurar manejo de señales.
     */
    setupSignalHandler();

    /**
     * Iniciar monitoreo.
     */
    start(config.interval_ms);

    return 0;
}
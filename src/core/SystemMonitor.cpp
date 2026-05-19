#include "SystemMonitor.hpp"

#include <chrono>
#include <map>
#include <string>

// Declaraciones de funciones existentes
double ObtenerUsoCPU();
double getDiskUsage();
double getRAMUsage();

struct NetworkIO {
    long rx;
    long tx;
};

NetworkIO getNetworkIO();

SystemMonitor::SystemMonitor()
    : running(false) {
}

void SystemMonitor::start() {

    running = true;

    auto inicio = std::chrono::steady_clock::now();

    metrics["cpu"] = ObtenerUsoCPU();
    metrics["ram"] = getRAMUsage();
    metrics["disk"] = getDiskUsage();

    NetworkIO net = getNetworkIO();

    metrics["net.rx"] = static_cast<double>(net.rx);
    metrics["net.tx"] = static_cast<double>(net.tx);

    auto fin = std::chrono::steady_clock::now();

    auto duracion = fin - inicio;
}

void SystemMonitor::stop() {

    running = false;
}

std::map<std::string, double> SystemMonitor::getMetrics() const {

    return metrics;
}
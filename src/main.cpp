#include "core/SystemMonitor.hpp"

int main() {

    SystemMonitor monitor;

    monitor.start();

    auto metrics = monitor.getMetrics();

    return 0;
}
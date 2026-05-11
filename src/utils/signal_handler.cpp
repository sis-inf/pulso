#include <csignal>
#include <atomic>
#include <iostream>

std::atomic<bool> isRunning = true;

void handler(int signal) {
    isRunning = false;
    std::cout << "\nMonitor detenido." << std::endl;
}

void setupSignalHandler() {
    signal(SIGINT, handler);
}
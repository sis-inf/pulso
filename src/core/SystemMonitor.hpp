#pragma once

#include <map>
#include <string>

class SystemMonitor {

private:

    bool running;

    std::map<std::string, double> metrics;

public:

    SystemMonitor();

    void start();

    void stop();

    std::map<std::string, double> getMetrics() const;
};
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

void printMetrics(const std::map<std::string, double>& data) {
    for (const auto& entry : data) {
        if (entry.second >= 0) {
            std::cout << std::left << std::setw(6) << entry.first + ":"
                      << std::setw(8) << entry.second << "%" << std::endl;
        }
    }
}
#include "cpu_usage.h"
#include <fstream>
#include <string>
#include <sstream>

double ObtenerUsoCPU() {
    static unsigned long long prev_idle = 0;
    static unsigned long long prev_total = 0;
    
    std::ifstream file("/proc/stat");
    std::string line;
    
    if (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string cpu;
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
        
        ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
        
        unsigned long long idle_time = idle + iowait;
        unsigned long long total_time = user + nice + system + idle + iowait + irq + softirq + steal;
        
        double uso = 0.0;
        if (prev_total > 0) {
            unsigned long long total_diff = total_time - prev_total;
            unsigned long long idle_diff = idle_time - prev_idle;
            uso = 100.0 * (1.0 - (double)idle_diff / total_diff);
        }
        
        prev_idle = idle_time;
        prev_total = total_time;
        
        return uso;
    }
    return 0.0;
}

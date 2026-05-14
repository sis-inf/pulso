#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;
struct RamUsage {
    long long total;
    long long used;
    long long available;
};

RamUsage getRamUsage() {
    ifstream file("/proc/meminfo");

    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir /proc/meminfo");
    }

    string line;
    long long memTotal = 0;
    long long memAvailable = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        string key;
        long long value;

        iss >> key >> value;

        if (key == "MemTotal:") {
            memTotal = value;
        }

        if (key == "MemAvailable:") {
            memAvailable = value;
        }
    }

    if (memTotal == 0 || memAvailable == 0) {
        throw runtime_error("No se pudieron leer los datos de memoria");
    }

    memTotal *= 1024;
    memAvailable *= 1024;

    long long memUsed = memTotal - memAvailable;

    return {memTotal, memUsed, memAvailable};
}
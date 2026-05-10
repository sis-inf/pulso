#include <fstream>
#include <sstream>
#include <string>

struct NetworkIO {
    long rx;
    long tx;
};

NetworkIO getNetworkIO() {
   
    NetworkIO result = {-1, -1};
    std::ifstream file("/proc/net/dev");
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("eth0") != std::string::npos ||
            line.find("wlan0") != std::string::npos) {

            std::istringstream ss(line);
            std::string iface;
            long rx, tx;
            long skip;

            ss >> iface >> rx;
            for (int i = 0; i < 7; i++) ss >> skip;
            ss >> tx;

            result.rx = rx;
            result.tx = tx;
            return result;
        }
    }
    return result;
}
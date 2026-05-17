#include "formatter_prometheus.hpp"

#include <sstream>

namespace pulso::formatters {

std::string FormatterPrometheus::formato() const {
    return "prometheus";
}

std::string FormatterPrometheus::contentType() const {
    return "text/plain; version=0.0.4";
}

std::string FormatterPrometheus::formatear(
    const pulso::core::Snapshot& snapshot) const {

    std::ostringstream output;

    output << "# HELP pulso_cpu_usage Porcentaje de uso de CPU\n";
    output << "# TYPE pulso_cpu_usage gauge\n";
    output << "pulso_cpu_usage " << snapshot.cpu << "\n\n";

    output << "# HELP pulso_memory_usage Uso de memoria RAM\n";
    output << "# TYPE pulso_memory_usage gauge\n";
    output << "pulso_memory_usage " << snapshot.ram << "\n\n";

    output << "# HELP pulso_disk_usage Uso de disco\n";
    output << "# TYPE pulso_disk_usage gauge\n";
    output << "pulso_disk_usage " << snapshot.disk << "\n\n";

    output << "# HELP pulso_rx_bytes Trafico recibido\n";
    output << "# TYPE pulso_rx_bytes gauge\n";
    output << "pulso_rx_bytes " << snapshot.rx_bytes << "\n\n";

    output << "# HELP pulso_tx_bytes Trafico enviado\n";
    output << "# TYPE pulso_tx_bytes gauge\n";
    output << "pulso_tx_bytes " << snapshot.tx_bytes << "\n";

    return output.str();
}

std::string FormatterPrometheus::formatearHistorial(
    const std::vector<pulso::core::Snapshot>& snapshots) const {

    if (snapshots.empty()) {
        return "";
    }

    return formatear(snapshots.back());
}

} // namespace pulso::formatters
#include "storage.hpp"
#include "schema.hpp"
 
namespace pulso::storage {
 
Storage::Storage(const std::string& dbPath)
    : db_(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    // Activar modo WAL para mejorar rendimiento en escrituras concurrentes
    db_.exec("PRAGMA journal_mode=WAL;");
 
    // Inicializar esquema (idempotente)
    inicializarEsquema(db_);
}
 
void Storage::save(const pulso::core::Snapshot& snapshot) {
    // Extraer métricas del snapshot por nombre
    auto getMetricValue = [&](const std::string& name) -> double {
        for (const auto& m : snapshot.metrics) {
            if (m.name == name) return m.value;
        }
        return 0.0;
    };
 
    SQLite::Statement query(db_,
        "INSERT INTO snapshots "
        "(timestamp, cpu_usage, cpu_cores, memory_total, memory_used, memory_available, "
        " disk_total, disk_used, disk_free, network_rx_bytes, network_tx_bytes) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);"
    );
 
    query.bind(1,  snapshot.timestamp);
    query.bind(2,  getMetricValue("cpu.usage"));
    query.bind(3,  static_cast<int>(getMetricValue("cpu.cores")));
    query.bind(4,  static_cast<int64_t>(getMetricValue("memory.total")));
    query.bind(5,  static_cast<int64_t>(getMetricValue("memory.used")));
    query.bind(6,  static_cast<int64_t>(getMetricValue("memory.available")));
    query.bind(7,  static_cast<int64_t>(getMetricValue("disk.total")));
    query.bind(8,  static_cast<int64_t>(getMetricValue("disk.used")));
    query.bind(9,  static_cast<int64_t>(getMetricValue("disk.free")));
    query.bind(10, static_cast<int64_t>(getMetricValue("network.rx_bytes")));
    query.bind(11, static_cast<int64_t>(getMetricValue("network.tx_bytes")));
 
    query.exec();
}
 
// Convierte una fila de la query en un Snapshot
static pulso::core::Snapshot rowToSnapshot(SQLite::Statement& query) {
    pulso::core::Snapshot snapshot;
    snapshot.timestamp = query.getColumn(0).getInt64();
 
    // Mapeo de columnas a métricas
    auto addMetric = [&](const std::string& name, const std::string& unit, double value) {
        pulso::core::Metrica m;
        m.name      = name;
        m.value     = value;
        m.unit      = unit;
        m.timestamp = snapshot.timestamp;
        snapshot.metrics.push_back(m);
    };
 
    addMetric("cpu.usage",          "percent",  query.getColumn(1).getDouble());
    addMetric("cpu.cores",          "cores",    query.getColumn(2).getInt());
    addMetric("memory.total",       "bytes",    query.getColumn(3).getInt64());
    addMetric("memory.used",        "bytes",    query.getColumn(4).getInt64());
    addMetric("memory.available",   "bytes",    query.getColumn(5).getInt64());
    addMetric("disk.total",         "bytes",    query.getColumn(6).getInt64());
    addMetric("disk.used",          "bytes",    query.getColumn(7).getInt64());
    addMetric("disk.free",          "bytes",    query.getColumn(8).getInt64());
    addMetric("network.rx_bytes",   "bytes",    query.getColumn(9).getInt64());
    addMetric("network.tx_bytes",   "bytes",    query.getColumn(10).getInt64());
 
    return snapshot;
}
 
std::optional<pulso::core::Snapshot> Storage::last() const {
    SQLite::Statement query(db_,
        "SELECT timestamp, cpu_usage, cpu_cores, memory_total, memory_used, memory_available, "
        "disk_total, disk_used, disk_free, network_rx_bytes, network_tx_bytes "
        "FROM snapshots ORDER BY timestamp DESC LIMIT 1;"
    );
 
    if (!query.executeStep()) {
        return std::nullopt;
    }
 
    return rowToSnapshot(query);
}
 
std::vector<pulso::core::Snapshot> Storage::history(
    std::int64_t from,
    std::int64_t until,
    std::size_t  limit) const
{
    std::string sql =
        "SELECT timestamp, cpu_usage, cpu_cores, memory_total, memory_used, memory_available, "
        "disk_total, disk_used, disk_free, network_rx_bytes, network_tx_bytes "
        "FROM snapshots WHERE timestamp >= ?";
 
    if (until != 0) {
        sql += " AND timestamp <= ?";
    }
 
    sql += " ORDER BY timestamp ASC LIMIT ?;";
 
    SQLite::Statement query(db_, sql);
 
    int bindIndex = 1;
    query.bind(bindIndex++, from);
    if (until != 0) {
        query.bind(bindIndex++, until);
    }
    query.bind(bindIndex, static_cast<int64_t>(limit));
 
    std::vector<pulso::core::Snapshot> results;
    while (query.executeStep()) {
        results.push_back(rowToSnapshot(query));
    }
 
    return results;
}
 
std::size_t Storage::total() const {
    SQLite::Statement query(db_, "SELECT COUNT(*) FROM snapshots;");
    query.executeStep();
    return static_cast<std::size_t>(query.getColumn(0).getInt64());
}
 
} // namespace pulso::storage
 
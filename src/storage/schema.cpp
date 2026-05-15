#include "schema.hpp"

namespace pulso::storage {

void inicializarEsquema(SQLite::Database& db) {

    db.exec(
        "CREATE TABLE IF NOT EXISTS snapshots ("
        "    id                 INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    timestamp          INTEGER NOT NULL,"
        "    cpu_usage          REAL,"
        "    cpu_cores          INTEGER,"
        "    memory_total       INTEGER,"
        "    memory_used        INTEGER,"
        "    memory_available   INTEGER,"
        "    disk_total         INTEGER,"
        "    disk_used          INTEGER,"
        "    disk_free          INTEGER,"
        "    network_rx_bytes   INTEGER,"
        "    network_tx_bytes   INTEGER"
        ");"
    );

    db.exec(
        "CREATE INDEX IF NOT EXISTS idx_snapshots_timestamp "
        "ON snapshots(timestamp);"
    );
}

} // namespace pulso::storage
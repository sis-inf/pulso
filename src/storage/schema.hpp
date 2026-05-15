#pragma once

#include <SQLiteCpp/Database.h>

namespace pulso::storage {

/**
 * @brief Inicializa el esquema de la base de datos SQLite.
 *
 * Crea la tabla `snapshots` y el índice `idx_snapshots_timestamp`
 * si no existen. La función es idempotente: puede invocarse
 * múltiples veces sobre la misma base de datos sin producir errores.
 *
 * @param db Referencia a la base de datos SQLite ya abierta.
 */
void inicializarEsquema(SQLite::Database& db);

} // namespace pulso::storage
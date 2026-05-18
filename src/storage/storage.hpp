#pragma once
 
#include <string>
#include <vector>
#include <optional>
#include <cstdint>
#include <cstddef>
#include <SQLiteCpp/SQLiteCpp.h>
#include "../core/types.hpp"
 
namespace pulso::storage {
 
/**
 * @brief Encapsula todas las operaciones de persistencia contra la base de datos SQLite.
 *
 * La clase Storage es responsable de abrir o crear la base de datos,
 * inicializar el esquema y proveer operaciones CRUD sobre los snapshots.
 * El resto del código no debe manipular SQL directamente.
 */
class Storage {
public:
    /**
     * @brief Abre o crea la base de datos en la ruta indicada.
     *
     * Activa el modo WAL para mejorar el rendimiento en escrituras concurrentes.
     * @param dbPath Ruta al archivo de base de datos SQLite.
     * @throws ErrorStorage si la apertura falla.
     */
    explicit Storage(const std::string& dbPath);
 
    /**
     * @brief Inserta un snapshot en la base de datos.
     * @param snapshot Snapshot a persistir.
     */
    void save(const pulso::core::Snapshot& snapshot);
 
    /**
     * @brief Devuelve el snapshot más reciente almacenado.
     * @return El snapshot más reciente, o std::nullopt si no hay datos.
     */
    std::optional<pulso::core::Snapshot> last() const;
 
    /**
     * @brief Devuelve snapshots en el rango de timestamps indicado.
     *
     * @param from  Timestamp Unix de inicio del rango (inclusive).
     * @param until Timestamp Unix de fin del rango (inclusive). Si es 0, no se aplica límite superior.
     * @param limit Cantidad máxima de snapshots a retornar. Por defecto 1000.
     * @return Vector de snapshots que cumplen el filtro.
     */
    std::vector<pulso::core::Snapshot> history(
        std::int64_t from,
        std::int64_t until = 0,
        std::size_t  limit = 1000) const;
 
    /**
     * @brief Cuenta el total de snapshots almacenados en la base de datos.
     * @return Cantidad total de snapshots.
     */
    std::size_t total() const;
 
private:
    SQLite::Database db_;
};
 
} // namespace pulso::storage
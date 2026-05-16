#include "config.hpp"

// toml++ — header-only, incluir una sola vez en la TU que lo necesite.
// Si el proyecto usa la variante multi-header, reemplaza por <toml++/toml.hpp>.
#define TOML_EXCEPTIONS 1
#include <toml++/toml.hpp>

#include <filesystem>
#include <format>      // C++23; usa fmt:: o snprintf si el compilador es C++17
#include <string>

namespace pulso::config {

// ---------------------------------------------------------------------------
// Helpers internos
// ---------------------------------------------------------------------------

namespace {

/// Lee un valor escalar del nodo TOML; si no existe devuelve `porDefecto`.
template <typename T>
T leer(const toml::table& tabla,
       std::string_view   seccion,
       std::string_view   clave,
       T                  porDefecto)
{
    if (auto* sec = tabla[seccion].as_table()) {
        if (auto nodo = (*sec)[clave]) {
            if (auto val = nodo.value<T>()) {
                return *val;
            }
        }
    }
    return porDefecto;
}

/// Sobrecarga sin sección (claves en la raíz del documento).
template <typename T>
T leer(const toml::table& tabla,
       std::string_view   clave,
       T                  porDefecto)
{
    if (auto nodo = tabla[clave]) {
        if (auto val = nodo.value<T>()) {
            return *val;
        }
    }
    return porDefecto;
}

/// Construye un Config a partir de un toml::table ya parseado.
Config mapear(const toml::table& doc)
{
    Config cfg;

    // [servidor]
    cfg.servidor.host  = leer<std::string>(doc, "servidor", "host",  cfg.servidor.host);
    cfg.servidor.puerto = leer<int64_t>   (doc, "servidor", "puerto", cfg.servidor.puerto);

    // [sampler]
    cfg.sampler.intervalo_segundos =
        leer<int64_t>(doc, "sampler", "intervalo_segundos", cfg.sampler.intervalo_segundos);

    // [storage]
    cfg.storage.ruta_db = leer<std::string>(doc, "storage", "ruta_db", cfg.storage.ruta_db);

    // nivel_log (clave raíz)
    cfg.nivel_log = leer<std::string>(doc, "nivel_log", cfg.nivel_log);

    return cfg;
}

} // namespace anónimo

// ---------------------------------------------------------------------------
// API pública
// ---------------------------------------------------------------------------

Config cargar(const std::string& ruta)
{
    // 1. Verificar existencia antes de intentar parsear para un mensaje claro.
    if (!std::filesystem::exists(ruta)) {
        throw ErrorConfig(
            std::format("El archivo de configuración no existe: '{}'", ruta));
    }

    // 2. Parsear; toml++ lanza toml::parse_error si la sintaxis es inválida.
    try {
        const toml::table doc = toml::parse_file(ruta);
        return mapear(doc);
    }
    catch (const toml::parse_error& e) {
        throw ErrorConfig(
            std::format("Error al parsear '{}': {} (línea {}, columna {})",
                        ruta,
                        std::string_view{e.description()},
                        e.source().begin.line,
                        e.source().begin.column));
    }
}

Config porDefecto()
{
    return Config{};   // Todos los campos usan sus inicializadores por defecto.
}

} // namespace pulso::config
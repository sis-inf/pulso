#include "config.hpp"

// toml++ — header-only, incluir una sola vez en la TU que lo necesite.
// Si el proyecto usa la variante multi-header, reemplaza por <toml++/toml.hpp>.
#define TOML_EXCEPTIONS 1
#include <toml++/toml.hpp>

#include <filesystem>
#include <format>      // C++23; usa fmt:: o snprintf si el compilador es C++17
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

    // output_format (clave raíz)
    cfg.output_format = leer<std::string>(doc, "output_format", cfg.output_format);

    return cfg;
}

} // namespace anónimo

// ---------------------------------------------------------------------------
// API pública
// ---------------------------------------------------------------------------

Config cargar(const std::string& ruta)
{
    // Si el archivo no existe:
    // usar valores por defecto sin excepcion
    if (!std::filesystem::exists(ruta)) {
        return porDefecto();
    }

    try {
        toml::table doc = toml::parse_file(ruta);

        Config cfg = mapear(doc);


        // Validar nivel_log
        if (cfg.nivel_log != "debug" &&
            cfg.nivel_log != "info" &&
            cfg.nivel_log != "warn" &&
            cfg.nivel_log != "error") {

            throw std::invalid_argument(
                "Valor inválido para nivel_log: " + cfg.nivel_log
            );
        }


        // Validar output_format
        if (cfg.output_format != "json" &&
            cfg.output_format != "csv" &&
            cfg.output_format != "prometheus") {

            throw std::invalid_argument(
                "Valor inválido para output_format: " + cfg.output_format
            );
        }


        // Validar puerto
        if (cfg.servidor.puerto < 1 ||
            cfg.servidor.puerto > 65535) {

            throw std::invalid_argument(
                "Valor inválido para puerto: " +
                std::to_string(cfg.servidor.puerto)
            );
        }


        // Validar intervalo
        if (cfg.sampler.intervalo_segundos <= 0) {

            throw std::invalid_argument(
                "Valor inválido para intervalo_segundos: " +
                std::to_string(cfg.sampler.intervalo_segundos)
            );
        }


        return cfg;

    }
    catch (const toml::parse_error& e) {

        throw ErrorConfig(
            "Error parseando '" + ruta + "': " +
            std::string(e.description())
        );

    }
    catch (const std::invalid_argument&) {

        throw;

    }
    catch (const std::exception& e) {

        throw ErrorConfig(e.what());

    }
}

Config porDefecto()
{
    return Config{};   // Todos los campos usan sus inicializadores por defecto.
}

} // namespace pulso::config

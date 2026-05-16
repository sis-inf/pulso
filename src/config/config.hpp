#pragma once

#include <stdexcept>
#include <string>

namespace pulso::config {

// ---------------------------------------------------------------------------
// Excepción
// ---------------------------------------------------------------------------

/// Lanzada cuando el archivo de configuración no existe o contiene errores.
class ErrorConfig : public std::runtime_error {
public:
    explicit ErrorConfig(const std::string& mensaje)
        : std::runtime_error(mensaje) {}
};

// ---------------------------------------------------------------------------
// Estructuras de configuración
// ---------------------------------------------------------------------------

struct ConfigServidor {
    std::string host  = "0.0.0.0";
    int         puerto = 8080;
};

struct ConfigSampler {
    int intervalo_segundos = 10;
};

struct ConfigStorage {
    std::string ruta_db = "pulso.db";
};

struct Config {
    ConfigServidor servidor;
    ConfigSampler  sampler;
    ConfigStorage  storage;
    std::string    nivel_log = "info";
};

// ---------------------------------------------------------------------------
// API pública
// ---------------------------------------------------------------------------

/// Carga el archivo TOML ubicado en `ruta`.
/// Lanza ErrorConfig si la ruta no existe o el archivo es inválido.
Config cargar(const std::string& ruta);

/// Devuelve una Config construida con todos los valores por defecto.
Config porDefecto();

} // namespace pulso::config
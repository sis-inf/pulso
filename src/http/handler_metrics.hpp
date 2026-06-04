#pragma once

#include <httplib.h>
#include "storage/storage.hpp"
#include "formatters/iformatter.hpp"

namespace pulso::http {

/**
 * @brief Registra el handler del endpoint GET /metrics en el servidor HTTP.
 *
 * El handler devuelve el snapshot más reciente almacenado en la base de datos,
 * formateado según el formatter proporcionado.
 *
 * - Si hay datos: responde con HTTP 200 y el body producido por el formatter.
 * - Si no hay datos: responde con HTTP 503 y un JSON de error.
 *
 * Cada request se registra en el log con nivel INFO incluyendo
 * método, ruta y código de respuesta.
 *
 * @param servidor  Referencia al servidor httplib donde se registra el handler.
 * @param storage   Referencia al almacenamiento para obtener el último snapshot.
 * @param formatter Referencia al formatter que serializa el snapshot.
 */

void registrarMetrics(
    httplib::Server&                       servidor,
    const pulso::storage::Storage&         storage,
    const pulso::formatters::IFormatter&   formatter);

} // namespace pulso::http
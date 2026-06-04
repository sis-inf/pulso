#include "handler_metrics.hpp"
#include "utils/logging/logger.hpp"

#include <string>

namespace pulso::http {


void registrarMetrics(
    httplib::Server&                       servidor,
    const pulso::storage::Storage&         storage,
    const pulso::formatters::IFormatter&   formatter)
{
    servidor.Get("/metrics", [&storage, &formatter](
        const httplib::Request&  req,
        httplib::Response&       res)
    {
        auto& logger = pulso::utils::logging::Logger::instancia();

        // Obtener el snapshot más reciente
        auto snapshot = storage.last();

        int statusCode = 0;

        if (snapshot.has_value()) {
            // Hay datos: responder con 200 y el body del formatter
            std::string body        = formatter.formatear(snapshot.value());
            std::string contentType = formatter.contentType();

            res.set_content(body, contentType);
            res.status = 200;
            statusCode = 200;
        } else {
            // No hay datos: responder con 503
            res.set_content(
                R"({ "error": "sin datos disponibles" })",
                "application/json"
            );
            res.status = 503;
            statusCode = 503;
        }

        // Registrar la request en el log con nivel INFO
        logger.info(
            req.method + " " + req.path +
            " -> " + std::to_string(statusCode)
        );
    });
}

} // namespace pulso::http
#include "handler_health.hpp"

namespace pulso::http {

void registrarHealth(httplib::Server& servidor) {
    servidor.Get("/health", [](const httplib::Request&, httplib::Response& res) {

        res.set_content(
            R"({
  "status": "ok",
  "service": "pulso",
  "version": "0.1.0"
})",
            "application/json"
        );

        res.status = 200;
    });
}

} // namespace pulso::http
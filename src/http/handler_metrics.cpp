#include "handler_metrics.hpp"
#include "utils/logging/logger.hpp"

#include <string>

namespace pulso::http {

void HandleMetrics(
  httplib::Server& servidor,
  SystemMonitor&   system_monitor)
{
  servidor.Get("/metrics", [&system_monitor](
    const httplib::Request& req,
    httplib::Response&      res)
  {
    auto& logger = pulso::utils::logging::Logger::instancia();

    auto metrics = system_monitor.getMetrics();

    int status_code = 0;

    if (!metrics.empty()) {
      pulso::formatters::FormatterJSON formatter;

      std::string body         = formatter.formatear(metrics);
      std::string content_type = formatter.contentType();

      res.set_content(body, content_type);
      res.status = 200;
      status_code = 200;
    } else {
      res.set_content(
        R"({ "error": "no data available" })",
        "application/json"
      );
      res.status = 503;
      status_code = 503;
    }

    logger.info(
      req.method + " " + req.path +
      " -> " + std::to_string(status_code)
    );
  });
}

} // namespace pulso::http
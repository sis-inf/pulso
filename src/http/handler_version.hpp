#ifndef HTTP_HANDLER_VERSION_HPP
#define HTTP_HANDLER_VERSION_HPP

#include <httplib.h>
#include <string>

namespace pulso {
namespace http {

    /**
     * @brief Maneja la petición GET /version retornando un JSON con la versión de la app.
     */
    std::string handleVersion();

} // namespace http
} // namespace pulso

#endif 
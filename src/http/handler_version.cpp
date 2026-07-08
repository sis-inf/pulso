#include "handler_version.hpp"
#include "../core/version.hpp"

namespace pulso {
namespace http {

    std::string handleVersion() {
        return "{\"version\": \"" + pulso::APP_VERSION + "\"}";
    }

} // namespace http
} // namespace pulso
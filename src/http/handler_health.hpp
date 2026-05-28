#pragma once

#include <httplib.h>

namespace pulso::http {

/// Registra el handler de /health en el servidor httplib.
void registrarHealth(httplib::Server& servidor);

} // namespace pulso::http
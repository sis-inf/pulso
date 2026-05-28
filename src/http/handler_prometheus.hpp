#pragma once

#include <httplib.h>
#include "storage/storage.hpp"

namespace pulso::http {

/// Registra el handler de /metrics/prometheus en el servidor httplib.
void registrarPrometheus(
    httplib::Server& servidor,
    const pulso::storage::Storage& storage);

} // namespace pulso::http
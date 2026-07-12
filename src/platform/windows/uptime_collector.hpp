#pragma once

#include "../../collectors/uptime/uptime_collector.hpp"

#ifdef _WIN32

namespace pulso::platform::windows {

UptimeInfo getUptimeWindows();

}

#endif

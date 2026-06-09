add_executable(pulso main.cpp)

target_sources(pulso PRIVATE
    cli/arg_parser.cpp
    collectors/cpu/cpu_usage.cpp
    collectors/disk/disk_usage.cpp
    collectors/memory/ram_usage.cpp
    collectors/network/network_io.cpp
    collectors/network/net_usage.cpp
    collectors/temperatura/temp_collector.cpp
    config/config.cpp
    core/SystemMonitor.cpp
    formatters/formatter_json.cpp
    formatters/formatter_prometheus.cpp
    http/handler_history.cpp
    collectors/loadavg/loadavg_collector.cpp
    collectors/procesos/proc_collector.cpp
    platform/linux/collector_cpu.cpp
    sampler/sampler.cpp
    storage/schema.cpp
    storage/storage.cpp
    utils/console_formatter.cpp
    utils/disk_usage.cpp
    utils/logging/logger.cpp
    utils/signal_handler.cpp
)

target_compile_features(pulso PRIVATE cxx_std_17)

target_include_directories(pulso PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pulso PRIVATE
    httplib
    nlohmann_json
    tomlplusplus
    SQLiteCpp
    sqlite3
)

target_compile_options(pulso PRIVATE -Wall -Wextra -Wpedantic -O2)
#ifndef PULSO_CONFIG_HPP
#define PULSO_CONFIG_HPP

namespace pulso {

/// @brief Configuración del sistema de monitoreo.
/// Almacena los parámetros de qué métricas monitorear y con qué frecuencia.
struct MonitorConfig {
    int interval_ms{1000};  ///< Intervalo entre lecturas en milisegundos
    bool cpu{true};         ///< Monitorear uso de CPU
    bool ram{true};         ///< Monitorear uso de RAM
    bool disk{false};       ///< Monitorear uso de disco
};

} // namespace pulso

#endif // PULSO_CONFIG_HPP

# Integración de Pulso con Prometheus y Grafana

Esta guía explica cómo configurar Pulso para exponer métricas en formato Prometheus, cómo configurar Prometheus para hacer scraping de estas métricas y cómo crear dashboards en Grafana para visualizarlas.

## Requisitos previos

- Pulso instalado y configurado
- Prometheus instalado (versión 2.x o superior)
- Grafana instalado (versión 8.x o superior)
- Acceso a la terminal para verificar configuraciones

## 1. Activar formato Prometheus en Pulso

Para que Pulso exponga métricas en el formato que Prometheus puede consumir, debes configurar el parámetro `output_format=prometheus` en el archivo `pulso.toml`:

```toml
# Configuración principal de Pulso
[output]
# Formato de salida: json, text o prometheus
format = "prometheus"

# Puerto del servidor HTTP para métricas (opcional, default 9090)
port = 9090

# Endpoint donde se expondrán las métricas
endpoint = "/metrics"

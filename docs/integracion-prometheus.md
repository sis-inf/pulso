# Integración con Prometheus y Grafana

## Activar formato Prometheus

En `pulso.toml` configurar:

```toml
output_format = "prometheus"
```

## Configurar Prometheus scraping

En `prometheus.yml`:

```yaml
scrape_configs:
  - job_name: pulso
    static_configs:
      - targets: ['localhost:9090']
```

## Métricas expuestas

| Métrica | Tipo | Descripción |
|---|---|---|
| pulso_cpu_usage_percent | gauge | Uso de CPU en porcentaje |
| pulso_memory_used_bytes | gauge | Memoria RAM usada en bytes |
| pulso_memory_total_bytes | gauge | Memoria RAM total en bytes |
| pulso_disk_used_bytes | gauge | Espacio en disco usado |
| pulso_disk_total_bytes | gauge | Espacio en disco total |
| pulso_network_rx_bytes | counter | Bytes recibidos por interfaz |
| pulso_network_tx_bytes | counter | Bytes enviados por interfaz |

## Dashboard de Grafana

Paneles recomendados:

- **CPU Usage** — `pulso_cpu_usage_percent`
- **Memoria disponible** — `pulso_memory_used_bytes / pulso_memory_total_bytes * 100`
- **Disco usado %** — `pulso_disk_used_bytes / pulso_disk_total_bytes * 100`
- **Tráfico de red entrada** — `rate(pulso_network_rx_bytes[5m])`
- **Tráfico de red salida** — `rate(pulso_network_tx_bytes[5m])`

## Verificar la integración

Verificar que pulso expone métricas:

```bash
curl http://localhost:9090/metrics
```

Validar configuración de Prometheus:

```bash
promtool check config prometheus.yml
```

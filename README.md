# Pulso

Agente de monitoreo de sistemas en C++ para recolección de métricas y exposición vía HTTP.

## ¿Qué es?

Pulso es un agente ligero escrito en C++ que recolecta métricas del sistema (CPU, RAM, disco, red, procesos, carga) y las expone a través de endpoints HTTP. Ofrece almacenamiento histórico en SQLite y formatos de salida compatibles con Prometheus.

## ¿Para quién es?

- Administradores de servidores que necesitan monitoreo en tiempo real
- Equipos de operaciones que requieren métricas históricas
- Integradores con Prometheus para alertas y dashboards

## ¿Qué problema resuelve?

Pulso ofrece una alternativa ligera a soluciones de monitoreo pesadas. Al estar implementado en C++, consume menos recursos que agentes basados en Python o Java, ideal para servidores con recursos limitados o entornos donde cada MB de RAM cuenta.

## Requisitos

- Sistema operativo: Linux
- Compilador C++17 (g++ o clang++)
- CMake 3.16 o superior
- Git
- Dependencias del sistema: libsqlite3-dev, libcurl4-openssl-dev

## Compilación

```bash
git clone https://github.com/sis-inf/pulso.git
cd pulso
cmake -S . -B build
cmake --build build
```

## Uso rápido

Arrancar el agente con la configuración por defecto:

```bash
./build/bin/pulso --config pulso.toml
```

Realizar una primera consulta:

```bash
curl http://localhost:8080/health
curl http://localhost:8080/metrics
```

## Endpoints disponibles

| Endpoint | Método | Parámetros | Descripción | Ejemplo de respuesta |
|----------|--------|------------|-------------|---------------------|
| `/health` | GET | Ninguno | Estado del agente y uptime | `{"status":"ok","uptime_seconds":123,"version":"0.1.0","hostname":"server01"}` |
| `/metrics` | GET | Ninguno | Métricas actuales en JSON | `{"cpu_usage":23.5,"memory_used":3.2,...}` |
| `/metrics/history` | GET | `desde`, `hasta`, `limite` | Histórico de métricas | `[{"timestamp":"2024-01-01T00:00:00Z","cpu_usage":20.0,...},...]` |
| `/metrics/prometheus` | GET | Ninguno | Métricas en formato Prometheus | `pulso_cpu_usage 23.5\npulso_memory_used 3.2\n...` |

## Configuración

El archivo `pulso.toml` controla el comportamiento del agente. Secciones principales:

- `[servidor]`: host y puerto del servidor HTTP (default: 0.0.0.0:8080)
- `[sampler]`: intervalo de muestreo en segundos (default: 10)
- `[storage]`: ruta de la base de datos SQLite y nivel de log

## Integración con Prometheus

Ejemplo de configuración para Prometheus (ver `examples/prometheus.yml`):

```yaml
scrape_configs:
  - job_name: pulso
    metrics_path: /metrics/prometheus
    static_configs:
      - targets:
          - localhost:8080
```

## Ejecución de pruebas

```bash
cmake --build build && ctest --test-dir build
```

## Documentación adicional

Ver la carpeta `docs/` para documentación detallada.

## Contribuir

Ver `CONTRIBUTING.md` para guías de desarrollo.

## Licencia

Ver `LICENSE` para detalles de la licencia.


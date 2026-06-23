# Pulso

## Descripción

Pulso es un agente ligero de monitoreo en C++17 que expone métricas del sistema a través de una API HTTP local. Permite consultar el estado del sistema y sus métricas en tiempo real de forma simple y eficiente.

---

## ¿Qué es?

Pulso es un agente de monitoreo que recopila métricas del sistema y las expone mediante endpoints HTTP.

### Métricas disponibles:
- Estado del sistema
- Uso de CPU
- Memoria
- Historial de métricas

### Endpoints disponibles:
- `/health`
- `/metrics`
- `/metrics/history`
- `/metrics/prometheus`

---

## ¿Para quién es?

Pulso está diseñado para:

- Administradores de servidores Linux
- Equipos de operaciones (DevOps)
- Integradores de Prometheus
- Sistemas que requieren monitoreo ligero

---

## ¿Qué problema resuelve?

Pulso evita la complejidad de soluciones de monitoreo pesadas al ofrecer:

- Un agente liviano en C++
- Exposición directa de métricas vía HTTP
- Fácil integración con Prometheus
- Bajo consumo de recursos

Es ideal para entornos donde se necesita observabilidad sin infraestructura compleja.

---

## Requisitos

- Sistema operativo Linux
- Compilador compatible con C++17 (g++ o clang++)
- CMake >= 3.16
- Dependencias del sistema necesarias para compilación

---

## Compilación

```bash
git clone <URL_DEL_REPOSITORIO>
cd pulso
cmake -S . -B build
cmake --build build
Uso rápido
./build/bin/pulso --config pulso.toml

En otra terminal:

curl http://localhost:8080/health
curl http://localhost:8080/metrics
Endpoints disponibles
Endpoint	Descripción	Ejemplo
/health	Estado del agente	{ "status": "ok" }
/metrics	Métricas actuales del sistema	JSON con métricas del sistema
/metrics/history	Historial de métricas	Lista temporal de datos
/metrics/prometheus	Formato compatible con Prometheus	Texto en formato Prometheus
Configuración

Pulso utiliza el archivo:

pulso.toml

Este archivo permite configurar:

Puerto del servidor
Intervalo de recolección de métricas
Parámetros del sistema de monitoreo
Integración con Prometheus

Ejemplo básico en:

examples/prometheus.yml

Ejemplo:

scrape_configs:
  - job_name: "pulso"
    static_configs:
      - targets: ["localhost:8080"]
Ejecución de pruebas
cmake --build build && ctest --test-dir build
Documentación adicional

Ver carpeta:

docs/
Contribuir

Ver:

CONTRIBUTING.md
Licencia

Ver:

LICENSE
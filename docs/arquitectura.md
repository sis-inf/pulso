# Arquitectura del Sistema Pulso

## Módulos principales

| Módulo | Responsabilidad |
|--------|----------------|
| **Core** | Gestión central del sistema, orquestación de módulos |
| **Métricas** | Recolección de métricas del sistema (CPU, memoria, disco) |
| **Monitor** | Evaluación continua de métricas y generación de alertas |
| **API** | Exposición de datos vía HTTP para consultas externas |
| **Logger** | Registro de eventos y errores del sistema |

## Diagrama de componentes (Mermaid)

```mermaid
graph TD
    A[Sistema Pulso] --> B[CORE]
    B --> C[Métricas]
    B --> D[Monitor]
    B --> E[API]
    B --> F[Logger]
    C --> G[Linux /proc]
    D --> H[Alertas]
    E --> I[Cliente HTTP]

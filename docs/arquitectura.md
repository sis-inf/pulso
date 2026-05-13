# Arquitectura del Sistema Pulso

## Módulos principales

| Módulo | Responsabilidad |
|--------|----------------|
| **Collector** | Recolecta métricas del sistema (CPU, RAM, disco, red) desde `/proc` y `/sys` |
| **Storage** | Almacena las métricas en memoria o disco para análisis histórico |
| **Analyzer** | Procesa las métricas y detecta anomalías o tendencias |
| **API** | Expone las métricas vía HTTP para consultas externas |
| **Alert Manager** | Genera alertas cuando las métricas superan umbrales definidos |
| **Logger** | Registra eventos, errores y actividad del sistema |

## Diagrama de componentes (Mermaid)

```mermaid
graph TD
    A[Sistema Pulso] --> B[Collector]
    A --> C[Storage]
    A --> D[Analyzer]
    A --> E[API]
    A --> F[Alert Manager]
    A --> G[Logger]

    B --> H[/proc/stat, /proc/meminfo]
    C --> I[Métricas históricas]
    D --> J[Detección de anomalías]
    E --> K[Cliente HTTP]
    F --> L[Notificaciones]
    G --> M[pulso.log]

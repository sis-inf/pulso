# Colectores

## ¿Qué es un collector?
Un collector es un componente encargado de recolectar métricas del sistema operativo a partir de fuentes de datos bien definidas, como archivos en `/proc` o llamadas al sistema. Su función es leer esa información en crudo, interpretarla y transformarla en valores numéricos que puedan ser almacenados, analizados o expuestos para monitorización.

Cada collector se especializa en un tipo de recurso (CPU, memoria, red, disco, etc.) y devuelve un conjunto concreto de métricas. De esta manera, la arquitectura del sistema de monitoreo se mantiene modular: agregar un nuevo recurso solo requiere implementar un collector que sepa leer la fuente correspondiente.

Internamente, un collector sigue siempre la misma interfaz: un método que ejecuta la recolección y retorna las métricas en un formato estructurado. Esto permite que el resto del sistema los trate de manera uniforme, sin preocuparse por los detalles de cada fuente de datos.

## Collectors implementados

| Nombre | Archivo           | Métricas que devuelve                  |
|--------|-------------------|----------------------------------------|
| CPU    | `cpu_collector`   | `cpu_user`, `cpu_system`, `cpu_idle`  |
| RAM    | `ram_collector`   | `ram_total`, `ram_usada`, `ram_libre` |
| Disco  | `disco_collector` | `disco_total`, `disco_usado`, `disco_libre` |

## Cómo agregar un nuevo collector

1. Identifica la fuente de datos que expone la métrica deseada (por ejemplo, un archivo en `/proc` o una syscall).
2. Crea un nuevo archivo en el directorio de collectors con un nombre descriptivo, como `red_collector.c`.
3. Define la función principal del collector (ej. `int recolectar_red(metricas_t *metricas)`) que lea la fuente y complete la estructura de métricas.
4. Implementa la lectura y parseo de la fuente de datos, convirtiendo los valores al formato que espera el sistema.
5. Registra el nuevo collector en la tabla de collectors del sistema para que sea invocado automáticamente.
6. Agrega las métricas nuevas a la estructura global de métricas y a cualquier sistema de reporte o almacenamiento.
7. Prueba el collector manualmente ejecutándolo y verificando que los valores recolectados sean correctos.

## Fuentes de datos en Linux

| Fuente              | Información que provee                                      |
|---------------------|-------------------------------------------------------------|
| `/proc/stat`        | Tiempos de CPU (usuario, sistema, idle, iowait, etc.)       |
| `/proc/meminfo`     | Estadísticas detalladas de memoria (total, libre, buffers)  |
| `/proc/net/dev`     | Contadores de tráfico de red por interfaz (bytes, paquetes) |
| `statvfs`           | Información de sistemas de archivos (espacio total, libre)  |
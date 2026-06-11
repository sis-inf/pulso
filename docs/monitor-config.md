# Propuesta: struct MonitorConfig

## ¿Qué se propone?

Se propone la creación de la estructura MonitorConfig para almacenar la configuración del monitoreo del sistema.

## ¿Para qué sirve?

Esta estructura permitirá definir parámetros como el intervalo de lectura y qué métricas del sistema se desean monitorear, facilitando la configuración del comportamiento del sistema de monitoreo.

## Estructura propuesta

Se sugiere que la estructura contenga:

- interval_ms (int): intervalo de tiempo en milisegundos entre lecturas
- cpu (bool): indica si se monitorea el uso de CPU
- ram (bool): indica si se monitorea el uso de memoria RAM
- disk (bool): indica si se monitorea el uso de disco

## Comportamiento esperado

- Contar con un constructor con valores por defecto
- Ubicarse en include/pulso/config.hpp
- Incluir documentación mediante comentarios en el código

## Nota

Esta es solo una propuesta en documentación. No se está implementando código fuente aún.

---

## Configuración de alertas
Pulso permite definir umbrales para generar advertencias cuando se superan los límites establecidos en el uso de recursos. Esta configuración se define en el archivo `pulso.toml` dentro de la sección `[alerts]`.

### Ejemplo completo de archivo `pulso.toml`
```toml
```
# Configuración general del monitoreo
[general]
collect_interval = 5          # Intervalo entre lecturas en segundos
log_level = "info"           # Nivel de detalle de los registros: debug, info, warn, error

# Configuración de alertas
[alerts]
enabled = true               # Habilitar o deshabilitar el sistema de alertas
check_interval = 60          # Verificar condiciones cada 60 segundos

# Umbrales para CPU
[alerts.cpu]
max_percent = 90             # Alerta si el uso supera el 90%
consecutive_readings = 3     # Activar alerta después de 3 mediciones seguidas

# Umbrales para memoria RAM
[alerts.memory]
max_percent = 85             # Alerta si el uso supera el 85%

# Umbrales para disco
[alerts.disk]
max_percent = 90             # Alerta si el uso supera el 90%
path = "/"                    # Ruta del disco a monitorear

### Parámetros de línea de comandos
Pulso acepta los siguientes argumentos al ejecutarlo, para modificar su comportamiento sin editar el archivo de configuración:

| Parámetro               | Descripción                                                                 | Ejemplo de uso                          |
|-------------------------|-----------------------------------------------------------------------------|-----------------------------------------|
| `--port <número>`       | Define el puerto para exponer el servicio web                               | `./pulso --port 8080`                  |
| `--once`                | Ejecuta una sola recolección de métricas y finaliza                         | `./pulso --once`                        |
| `--format <formato>`    | Define el formato de salida: `text`, `json`, `csv`                         | `./pulso --format json`                |
| `--config <ruta>`       | Especifica una ruta personalizada para el archivo `pulso.toml`              | `./pulso --config ./mi-config.toml`    |
| `--log-level <nivel>`   | Cambia el nivel de detalle de los registros: `debug`, `info`, `warn`, `error` | `./pulso --log-level debug`            |
| `--export <formato>`    | Exporta el historial de métricas a un archivo (`csv`, `json`)              | `./pulso --export csv --output datos.csv` |
| `--help`                | Muestra la ayuda con todos los comandos disponibles                         | `./pulso --help`                        |
| `--version`             | Muestra la versión actual de Pulso                                          | `./pulso --version`                    |


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

## Configuración de alertas

Se propone agregar una sección de alertas en el archivo de configuración para definir umbrales máximos de uso de recursos.

Ejemplo:

[alertas]

- cpu.max = 90
- ram.max = 80
- disco.max = 85

Donde:

- cpu.max: porcentaje máximo permitido de uso de CPU
- ram.max: porcentaje máximo permitido de uso de memoria RAM
- disco.max: porcentaje máximo permitido de uso de disco

Cuando una métrica supera el valor configurado, el sistema puede generar una alerta para notificar al usuario.

## Modo de ejecución única

El parámetro `--once` permite ejecutar una única lectura de métricas y finalizar inmediatamente después de completar la ejecución.

Ejemplo:

- pulso --once

## Opciones de línea de comandos

### --port

Permite especificar el puerto utilizado por el servicio.

Ejemplo:

- pulso --port 8080

### --format

Permite seleccionar el formato de salida.

Ejemplo:

- pulso --format json

### --config

Permite indicar un archivo de configuración personalizado.

Ejemplo:

- pulso --config pulso.toml

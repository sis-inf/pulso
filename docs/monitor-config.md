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

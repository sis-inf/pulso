# Casos de Uso Avanzados

Escenarios completos end-to-end para uso de pulso en entornos de produccion.

## Escenario 1: Alertar al equipo por Slack cuando el disco supera el 90%

Combina: monitoreo de disco + webhook de alertas.

Configuracion en pulso.toml:

    [collectors]
    disk = true

    [alertas]
    habilitadas = true

    [[alertas.reglas]]
    metrica = "disk.used_percent"
    umbral = 90.0
    operador = ">"
    webhook = "https://hooks.slack.com/services/TU/WEBHOOK/URL"
    mensaje = "Disco supero el 90% en {hostname}"

Ejecutar pulso:

    ./pulso --config pulso.toml

Cuando el disco supere el 90%, pulso enviara automaticamente un mensaje al canal de Slack configurado.

## Escenario 2: Mantener 90 dias de historial sin que la base de datos crezca sin control

Combina: retencion de datos + downsampling.

Configuracion en pulso.toml:

    [storage]
    habilitado = true
    ruta = "/var/lib/pulso/datos.db"
    retencion_dias = 90
    downsampling = true
    downsampling_intervalo = "1h"

Con esta configuracion:
- Los datos de los ultimos 90 dias se conservan completos
- Los datos mas antiguos se comprimen a una muestra por hora
- La base de datos no crece indefinidamente

Verificar el tamano de la base de datos:

    du -sh /var/lib/pulso/datos.db

## Escenario 3: Exportar metricas a un pipeline de Telegraf usando Influx Line Protocol

Combina: formato de exportacion InfluxDB + integracion con Telegraf.

Configuracion en pulso.toml:

    [output]
    formato = "influx"
    destino = "http://localhost:8186/write"

Configuracion en Telegraf (telegraf.conf):

    [[inputs.http]]
    urls = ["http://localhost:8186/write"]
    data_format = "influx"

    [[outputs.influxdb_v2]]
    urls = ["http://localhost:8086"]
    token = "TU_TOKEN"
    organization = "mi-org"
    bucket = "pulso"

Ejecutar pulso y Telegraf:

    ./pulso --config pulso.toml &
    telegraf --config telegraf.conf

Las metricas de pulso llegaran automaticamente a InfluxDB via Telegraf.

## Escenario 4: Monitorear una maquina de desarrollo sin exponer el agente a la red

Combina: modo watch local + sin servidor HTTP.

Configuracion en pulso.toml:

    [servidor]
    habilitado = false

    [output]
    formato = "texto"
    destino = "stdout"

Ejecutar en modo watch local:

    ./pulso --watch --config pulso.toml

Con esta configuracion:
- pulso muestra las metricas en la terminal en tiempo real
- No abre ningun puerto de red
- No expone el agente a conexiones externas
- Util para depuracion en maquinas de desarrollo

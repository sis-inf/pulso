# Casos de Falla

Comportamiento del agente Pulso ante condiciones de error y como recuperarse.

## 1. Disco lleno — Storage no puede escribir

### Que ocurre

Cuando el disco donde se encuentra pulso.db se llena, la clase Storage lanza ErrorStorage al intentar insertar un nuevo snapshot. El agente registra el error en el log y continua ejecutandose, pero los datos nuevos no se persisten.

El agente se degrada parcialmente: sigue recolectando metricas y sirviendo el endpoint /metrics con datos en memoria, pero el historial no se actualiza.

### Como diagnosticarlo

Buscar en el log:

    [ERROR] Storage: fallo al insertar snapshot — disk full

Verificar espacio en disco:

    df -h

### Como recuperarse

1. Liberar espacio en disco eliminando archivos innecesarios
2. Reiniciar pulso para que Storage vuelva a intentar abrir la base de datos:

    ./pulso --config pulso.toml

## 2. /proc inaccesible — collector de red o CPU falla

### Que ocurre

En Linux, los collectors de CPU y red leen de /proc/stat y /proc/net/dev. Si estos archivos no son accesibles por permisos insuficientes o por estar en un entorno restringido (contenedor sin privilegios), el collector correspondiente falla y devuelve cero o un valor invalido.

El agente continua ejecutandose. Los otros collectors no se ven afectados.

### Como diagnosticarlo

Buscar en el log:

    [WARN] collector_cpu: no se pudo leer /proc/stat — permission denied
    [WARN] collector_network: no se pudo leer /proc/net/dev — permission denied

Verificar acceso:

    cat /proc/stat
    cat /proc/net/dev

### Como recuperarse

1. Ejecutar pulso con permisos suficientes:

    sudo ./pulso --config pulso.toml

2. O ajustar los permisos del contenedor si se ejecuta en Docker:

    docker run --privileged ...

## 3. Base de datos corrupta o bloqueada

### Que ocurre

Si el archivo pulso.db esta corrupto (por ejemplo por un cierre forzado durante una escritura) o bloqueado por otro proceso, Storage lanza ErrorStorage al intentar abrirlo. Pulso no inicia y muestra el error en el log.

### Como diagnosticarlo

Buscar en el log al iniciar:

    [ERROR] Storage: no se pudo abrir la base de datos — database disk image is malformed
    [ERROR] Storage: no se pudo abrir la base de datos — database is locked

Verificar integridad de la base de datos:

    sqlite3 pulso.db "PRAGMA integrity_check;"

### Como recuperarse

Si la base de datos esta corrupta:

1. Hacer un respaldo del archivo actual
2. Eliminar pulso.db
3. Reiniciar pulso — creara una base de datos nueva vacia

Si la base de datos esta bloqueada:

1. Identificar que proceso la tiene bloqueada:

    lsof pulso.db

2. Detener ese proceso y reiniciar pulso

## 4. Puerto HTTP ya en uso

### Que ocurre

Si el puerto configurado (por defecto 8080) ya esta en uso por otro proceso cuando pulso intenta iniciar el servidor HTTP, pulso no puede iniciar el servidor y termina con un error.

### Como diagnosticarlo

Buscar en el log:

    [ERROR] servidor HTTP: no se pudo enlazar al puerto 8080 — address already in use

Identificar que proceso usa el puerto:

    lsof -i :8080
    ss -tlnp | grep 8080

### Como recuperarse

Opcion 1: cambiar el puerto en pulso.toml:

    [servidor]
    puerto = 9090

Opcion 2: detener el proceso que usa el puerto y reiniciar pulso.

## 5. Permisos insuficientes para leer metricas del sistema

### Que ocurre

Algunos collectors requieren permisos especiales para leer ciertas metricas del sistema operativo. Si pulso se ejecuta como usuario sin privilegios, algunos valores pueden ser 0 o no estar disponibles.

### Como diagnosticarlo

Buscar en el log:

    [WARN] collector_disk: no se pudo leer estadisticas de E/S — permission denied

### Como recuperarse

Ejecutar pulso con el usuario adecuado o agregar capacidades especificas:

    sudo ./pulso --config pulso.toml

O usar setcap para dar permisos especificos sin ejecutar como root:

    sudo setcap cap_sys_ptrace+ep ./pulso

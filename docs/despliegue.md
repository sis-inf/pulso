# Guía de Despliegue

## Prerrequisitos

- Sistema operativo Linux (Ubuntu 22.04 LTS o superior recomendado).
- Compilador C++17 (GCC 11+ o Clang 14+).
- CMake 3.16 o superior.
- Acceso `sudo` en el servidor de destino (para instalar el binario y configurar systemd).
- Puerto HTTP disponible (por defecto `8080`) accesible desde la red donde se monitoreará.

## Entornos

### Local

```bash
# Clonar el repositorio
git clone https://github.com/sis-inf/pulso.git
cd pulso

# Configurar y compilar en modo Debug (incluye símbolos de depuración)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j$(nproc)

# Ejecutar localmente usando el pulso.toml de ejemplo del repositorio
./build/bin/pulso --config pulso.toml
```

### Producción

```bash
# 1. Compilación en modo Release (optimizada, sin símbolos de depuración)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# 2. Instalación del binario en el sistema
sudo install -m 755 build/bin/pulso /usr/local/bin/pulso

# 3. Crear el directorio y archivo de configuración
sudo mkdir -p /etc/pulso
sudo cp pulso.toml /etc/pulso/pulso.toml
sudo chown root:root /etc/pulso/pulso.toml
sudo chmod 644 /etc/pulso/pulso.toml

# 4. Verificar la instalación
pulso --version
```

#### Archivo de configuración (`/etc/pulso/pulso.toml`)

El agente lee su configuración desde un archivo TOML. Ejemplo con los valores por defecto:

```toml
[servidor]
host = "0.0.0.0"
puerto = 8080

[sampler]
intervalo_segundos = 10

[storage]
ruta_db = "/var/lib/pulso/pulso.db"
nivel_log = "info"
```

> 👉 En producción, usa una ruta absoluta para `ruta_db` (por ejemplo `/var/lib/pulso/pulso.db`)
> en lugar de una ruta relativa, para evitar depender del directorio desde el que se inicia el proceso.

```bash
# Crear el directorio de datos para SQLite
sudo mkdir -p /var/lib/pulso
sudo chown pulso:pulso /var/lib/pulso
```

#### Despliegue como servicio systemd

Crear el archivo de unidad `/etc/systemd/system/pulso.service`:

```ini
[Unit]
Description=Pulso - Agente de monitoreo de sistema
After=network.target

[Service]
Type=simple
User=pulso
Group=pulso
ExecStart=/usr/local/bin/pulso --config /etc/pulso/pulso.toml
Restart=on-failure
RestartSec=5
WorkingDirectory=/var/lib/pulso

[Install]
WantedBy=multi-user.target
```

Crear el usuario de sistema dedicado y habilitar el servicio:

```bash
# Crear usuario de sistema sin shell de login, dueño de los archivos del agente
sudo useradd --system --no-create-home --shell /usr/sbin/nologin pulso
sudo chown -R pulso:pulso /var/lib/pulso

# Recargar systemd, habilitar e iniciar el servicio
sudo systemctl daemon-reload
sudo systemctl enable pulso
sudo systemctl start pulso
```

#### Verificación del servicio

```bash
# Ver el estado del servicio
sudo systemctl status pulso

# Ver los logs en tiempo real
sudo journalctl -u pulso -f

# Verificar que el servidor HTTP responde correctamente
curl http://localhost:8080/health
```

Una respuesta exitosa de `/health` debe verse similar a:

```json
{
  "status": "ok",
  "uptime_seconds": 42,
  "version": "0.1.0",
  "hostname": "servidor-produccion"
}
```

#### Actualización sin downtime

Pulso es un único binario estático sin estado en memoria persistente entre reinicios (las métricas históricas se guardan en SQLite), por lo que actualizar consiste en reemplazar el binario y reiniciar el servicio:

```bash
# 1. Compilar la nueva versión en un entorno de build (no en el servidor de producción
#    si se quiere evitar instalar herramientas de compilación allí)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# 2. Respaldar el binario actual antes de sobreescribirlo
sudo cp /usr/local/bin/pulso /usr/local/bin/pulso.bak

# 3. Instalar el nuevo binario
sudo install -m 755 build/bin/pulso /usr/local/bin/pulso

# 4. Reiniciar el servicio para que tome el nuevo binario
sudo systemctl restart pulso

# 5. Verificar que el servicio levantó correctamente con la nueva versión
sudo systemctl status pulso
curl http://localhost:8080/health
```

> 👉 El tiempo de interrupción real corresponde solo al `restart` (típicamente menos de un segundo,
> ya que `pulso` no requiere migraciones de esquema en cada arranque). Para monitoreo crítico de
> alta disponibilidad, se recomienda ejecutar dos instancias en hosts distintos detrás de un balanceador.

#### Rollback si falla

Si tras la actualización el servicio no levanta o `/health` no responde correctamente:

```bash
# 1. Revisar los logs para entender la falla
sudo journalctl -u pulso -n 50 --no-pager

# 2. Restaurar el binario anterior desde el respaldo
sudo cp /usr/local/bin/pulso.bak /usr/local/bin/pulso

# 3. Reiniciar el servicio con el binario anterior
sudo systemctl restart pulso

# 4. Confirmar que el rollback restauró el servicio
sudo systemctl status pulso
curl http://localhost:8080/health
```

> 👉 Conserva siempre al menos un binario `.bak` de la última versión estable conocida.
> Si se usan múltiples versiones, nombra los respaldos con la versión incluida
> (por ejemplo `pulso.bak-0.1.0`) para poder elegir a cuál revertir.

## Variables de entorno

Pulso se configura principalmente mediante el archivo `pulso.toml`. Las siguientes variables de entorno permiten sobreescribir o complementar esa configuración en el entorno de despliegue:

| Variable | Descripción | Ejemplo |
|---|---|---|
| `PULSO_CONFIG_PATH` | Ruta al archivo de configuración TOML, si se desea usar una distinta a `/etc/pulso/pulso.toml` | `/etc/pulso/pulso.toml` |
| `PULSO_LOG_LEVEL` | Sobrescribe el nivel de log definido en `[storage].nivel_log` del TOML | `debug` |
| `PULSO_HTTP_PORT` | Sobrescribe el puerto HTTP definido en `[servidor].puerto` del TOML | `8080` |

> 👉 Si una variable de entorno y el archivo TOML definen el mismo valor, revisa la documentación de ello
> de `config.cpp` en el código fuente para confirmar el orden de precedencia antes de depender de ambos mecanismos a la vez.

## Solución de problemas comunes

**El servicio no inicia (`systemctl status pulso` muestra `failed`)**
- Revisa `sudo journalctl -u pulso -n 50` para ver el error exacto.
- Verifica que `/etc/pulso/pulso.toml` exista y tenga sintaxis TOML válida.
- Confirma que el usuario `pulso` tiene permisos de escritura sobre `/var/lib/pulso`.

**`curl http://localhost:8080/health` no responde**
- Verifica que el puerto configurado en `[servidor].puerto` no esté en uso por otro proceso: `sudo ss -tlnp | grep 8080`.
- Revisa que el valor de `host` en el TOML permita conexiones desde donde estás probando (`0.0.0.0` acepta cualquier interfaz; `127.0.0.1` solo acepta conexiones locales).

**Error de permisos al escribir en la base de datos SQLite**
- Confirma que `ruta_db` en el TOML apunta a un directorio existente y con permisos de escritura para el usuario `pulso`.
- Verifica el propietario del archivo: `ls -l /var/lib/pulso/pulso.db`.

**La compilación falla por dependencias faltantes**
- Asegúrate de tener instalado un compilador compatible con C++17 y CMake 3.16+.
- Las dependencias (`httplib`, `nlohmann_json`, `tomlplusplus`, `SQLiteCpp`, `sqlite3`) se gestionan según lo definido en `cmake/Dependencies.cmake`; revisa ese archivo si el paso de configuración falla al resolverlas.
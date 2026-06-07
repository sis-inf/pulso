# Diagnóstico de Problemas Comunes en Producción

> Este documento cubre los problemas más frecuentes al desplegar **pulso** como agente de monitoreo en servidores Linux.
> Cada entrada sigue el formato: **Síntoma → Causa → Solución**.

---

## 1. Permission denied al leer `/proc/stat`

**Síntoma:** El agente falla al iniciar con errores como `Permission denied` al acceder a `/proc/stat`, `/proc/meminfo` u otros archivos de `/proc`.

**Causa:** El proceso del agente no tiene permisos suficientes para leer los archivos virtuales del kernel. Esto ocurre cuando el agente se ejecuta como usuario no privilegiado.

**Solución:** Ejecutar el agente con permisos de root o agregar el usuario al grupo adecuado:
```bash
# Opción A: ejecutar con sudo (recomendado para producción)
sudo systemctl start pulso

# Opción B: agregar usuario al grupo adm (permite lectura de /proc)
sudo usermod -aG adm $USER

# Verificar permisos:
ls -l /proc/stat
```

---

## 2. Puerto ya en uso

**Síntoma:** El agente no inicia y muestra `Address already in use` o `bind: address already in use` al intentar levantar el servidor HTTP.

**Causa:** Otro proceso ya está escuchando en el puerto configurado (por defecto `8080` o el definido en `config.json`).

**Solución:** Identificar y liberar el puerto:
```bash
# Identificar qué proceso usa el puerto (ejemplo puerto 8080)
sudo ss -tlnp | grep 8080
# o
sudo lsof -i :8080

# Opción A: detener el proceso conflictivo
sudo kill <PID>

# Opción B: cambiar el puerto en config.json
# Editar config.json y cambiar "port": 8080 a otro valor libre
```

---

## 3. CPU siempre reportada como 0%

**Síntoma:** Las métricas de CPU muestran consistentemente `0%` de utilización, independientemente de la carga real del sistema.

**Causa:** El cálculo de uso de CPU en Linux requiere dos lecturas de `/proc/stat` con un intervalo de tiempo. Si el intervalo es demasiado corto o la primera lectura es inválida, el cálculo retorna 0.

**Solución:**
```bash
# Verificar que /proc/stat sea legible
cat /proc/stat | head -1

# Aumentar el intervalo de muestreo en config.json
# Cambiar "interval_ms" de 1000 a 5000 o superior
# El cálculo necesita al menos 1-2 segundos entre lecturas para ser preciso

# Reiniciar el agente tras el cambio
sudo systemctl restart pulso
```

---

## 4. RAM reportada incorrectamente

**Síntoma:** La memoria RAM reportada no coincide con `free -m` o con los valores esperados del sistema.

**Causa:** Diferencias en cómo se interpreta `/proc/meminfo`. Linux reporta "MemAvailable" que incluye caché y buffers reutilizables, mientras que algunos cálculos usan "MemFree" que excluye estos valores.

**Solución:**
```bash
# Comparar con lo que reporta el kernel
cat /proc/meminfo | grep -E "MemTotal|MemFree|MemAvailable|Buffers|Cached"

# Verificar qué métrica usa pulso en su configuración
# Si es posible, cambiar de MemFree a MemAvailable para una medida más realista

# free -m como referencia externa
free -m
```

---

## 5. El agente no inicia como servicio systemd

**Síntoma:** `systemctl start pulso` falla con `Job for pulso.service failed` o `Unit pulso.service not found`.

**Causa:** El archivo de servicio no está instalado correctamente, o el binario no es ejecutable, o la ruta al binario en el unit file es incorrecta.

**Solución:**
```bash
# Verificar que el archivo de servicio existe
ls -l /etc/systemd/system/pulso.service

# Si no existe, crearlo:
sudo tee /etc/systemd/system/pulso.service << 'EOF'
[Unit]
Description=Pulso System Monitor Agent
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/pulso
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target
EOF

# Asegurar que el binario es ejecutable
sudo chmod +x /usr/local/bin/pulso

# Recargar y reiniciar
sudo systemctl daemon-reload
sudo systemctl enable pulso
sudo systemctl start pulso

# Verificar estado
sudo systemctl status pulso
sudo journalctl -u pulso -n 50 --no-pager
```

---

## 6. Memory leak: ¿cuánto consumo de RAM es normal?

**Síntoma:** El uso de memoria del agente crece gradualmente con el tiempo y no disminuye.

**Causa:** Pulso usa almacenamiento en memoria (ver [docs/storage.md](./storage.md)). La política de rotación limita el número máximo de entradas, pero si el intervalo de muestreo es muy corto, el buffer puede llenarse rápidamente.

**Solución:**
```bash
# Monitorear el uso de memoria del agente
ps aux | grep pulso
# o con top/htop
top -p $(pgrep pulso)

# Verificar que la rotación está configurada
# En config.json, asegurar que haya un límite máximo de entradas en storage
# Ejemplo: "max_entries": 10000

# Si el consumo supera 50MB persistentemente, revisar logs:
sudo journalctl -u pulso --since "1 hour ago" | grep -i "memory\|leak\|storage"

# Como mitigación temporal, reiniciar el servicio:
sudo systemctl restart pulso
```

---

## 7. `/sys/class/thermal` no existe

**Síntoma:** El colector de temperatura falla o reporta valores nulos.

**Causa:** No todos los sistemas exponen sensores térmicos en `/sys/class/thermal/`. Esto es común en máquinas virtuales, contenedores, o hardware sin sensores ACPI térmicos.

**Solución:**
```bash
# Verificar si existen zonas térmicas
ls /sys/class/thermal/

# Si está vacío, el hardware no expone temperatura
# Opciones:
# 1. Desactivar el colector de temperatura en config.json
# 2. Usar lm-sensors como alternativa:
sudo apt install lm-sensors
sudo sensors-detect  # responder YES a todo
sensors

# 3. En VMs/contenedores, es esperado no tener datos térmicos — no es un error
```

---

## 8. El agente consume demasiado CPU

**Síntoma:** El propio agente de monitoreo consume más del 5% de CPU de forma sostenida.

**Causa:** Intervalo de muestreo demasiado agresivo (ej. `interval_ms: 100`), o demasiados colectores activos simultáneamente.

**Solución:**
```bash
# Medir consumo actual del agente
pidstat -p $(pgrep pulso) 5 3

# Ajustar intervalo de muestreo (recomendado: 5000ms o superior)
# Editar config.json:
# "interval_ms": 5000

# Desactivar colectores innecesarios en config.json:
# "collectors": { "cpu": true, "ram": true, "disk": true, "temperature": false }

# Un agente de monitoreo no debe consumir >2% CPU en reposo
# Si persiste, abrir un issue con el output de:
strace -p $(pgrep pulso) -c -s 100
```

---

## 9. Logs excesivos o sin información útil

**Síntoma:** Los logs crecen rápidamente o solo muestran mensajes genéricos sin detalles de diagnóstico.

**Causa:** Nivel de log configurado en `DEBUG` o `TRACE`, o falta de contexto en los mensajes de error.

**Solución:**
```bash
# Revisar nivel de log en config.json
# Cambiar de "debug" a "info" o "warn" para producción:
# "log_level": "info"

# Ver logs recientes
sudo journalctl -u pulso -n 100 --no-pager

# Rotar logs manualmente si es necesario
sudo journalctl --rotate
sudo journalctl --vacuum-time=7d  # mantener solo 7 días

# Para diagnóstico temporal, habilitar debug:
# "log_level": "debug"
# Reproducir el problema, luego volver a "info"
```

---

## 10. El agente no reporta métricas al endpoint HTTP

**Síntoma:** El agente está corriendo (`systemctl status pulso` muestra activo) pero `curl localhost:8080/metrics` no responde o retorna error.

**Causa:** Firewall bloqueando el puerto, agente escuchando solo en `127.0.0.1` cuando se accede desde otra IP, o el servidor HTTP no inició correctamente.

**Solución:**
```bash
# Verificar que el agente escucha en el puerto esperado
sudo ss -tlnp | grep pulso
# o
sudo lsof -i :8080

# Probar acceso local
curl -v http://127.0.0.1:8080/metrics
curl -v http://127.0.0.1:8080/health

# Si funciona localmente pero no remotamente, verificar:
# 1. bind_address en config.json (cambiar de "127.0.0.1" a "0.0.0.0")
# 2. Firewall:
sudo ufw status
sudo ufw allow 8080/tcp

# Verificar logs del servicio
sudo journalctl -u pulso --since "10 minutes ago"
```

---

## 11. Colector de disco reporta valores inconsistentes

**Síntoma:** El uso de disco reportado no coincide con `df -h`, o ciertos montajes no aparecen.

**Causa:** Pulso puede estar leyendo `/proc/diskstats` o usando `statvfs` con filtros diferentes. Sistemas de archivos virtuales (tmpfs, procfs, sysfs) pueden estar incluidos o excluidos según la configuración.

**Solución:**
```bash
# Comparar con df
df -h

# Verificar qué sistemas de archivos está leyendo pulso
cat /proc/diskstats | head -5

# Si hay montajes NFS o remotos, pueden causar timeouts
# Excluir montajes problemáticos en config.json si es soportado

# Para debugging:
lsblk
mount | grep -E "nfs|cifs|fuse"
```

---

## 12. `uptime` o `loadavg` reportan 0 en contenedores

**Síntoma:** Las métricas de uptime y load average muestran 0 o valores incorrectos cuando el agente corre dentro de un contenedor Docker/LXC.

**Causa:** Los contenedores comparten el kernel del host. `/proc/uptime` y `/proc/loadavg` reflejan los valores del host, no del contenedor. Algunos runtimes de contenedores restringen el acceso a estos archivos.

**Solución:**
```bash
# Verificar qué ve el contenedor
cat /proc/uptime
cat /proc/loadavg

# Si son 0 o inaccesibles, es una limitación del runtime
# Opciones:
# 1. Ejecutar el agente directamente en el host (no en contenedor)
# 2. Configurar el contenedor con --privileged (no recomendado en producción)
# 3. Desactivar estos colectores en entornos containerizados
```

---

## Resumen rápido de comandos útiles

```bash
# Estado del agente
sudo systemctl status pulso

# Logs recientes
sudo journalctl -u pulso -n 50 --no-pager

# Consumo de recursos del agente
ps aux | grep pulso
top -p $(pgrep pulso)

# Probar endpoints HTTP
curl http://127.0.0.1:8080/health
curl http://127.0.0.1:8080/metrics

# Reiniciar el agente
sudo systemctl restart pulso
```

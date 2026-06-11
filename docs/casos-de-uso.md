# Casos de Uso - Proyecto Pulso

Este documento define los actores y las funcionalidades principales del agente de monitoreo **Pulso**.

## 1. Actores del Sistema
- **Administrador de Sistemas (SysAdmin):** Responsable de configurar el agente y visualizar las métricas consolidadas.
- **Agente Pulso:** Actor automatizado que recolecta y envía datos de rendimiento en segundo plano.

## 2. Casos de Uso Principales

### CU-01: Registro de Métricas de CPU
- **Actor:** Agente Pulso
- **Descripción:** El agente captura el porcentaje de uso de la CPU en intervalos definidos.
- **Flujo Principal:**
  1. El agente inicia el ciclo de captura.
  2. Consulta el estado del procesador mediante llamadas al sistema.
  3. Almacena temporalmente el valor capturado para su envío.

### CU-02: Consulta del Estado General del Sistema
- **Actor:** Administrador de Sistemas
- **Descripción:** Permite al administrador obtener un resumen completo del estado actual del sistema desde la terminal.
- **Flujo Principal:**
  1. El administrador ejecuta `./pulso --status` desde la terminal.
  2. El Agente Pulso consulta las métricas actuales al sistema operativo.
  3. Se muestra el estado general: procesos activos, uso de recursos y estado de la red.

### CU-03: Visualización de Estado de Red
- **Actor:** Administrador de Sistemas
- **Descripción:** Permite ver la velocidad de descarga, subida y el estado de la conexión de red del sistema.
- **Flujo Principal:**
  1. El administrador solicita ver el estado del sistema vía menú o `--status`.
  2. El Agente Pulso consulta las métricas de red al sistema operativo.
  3. Se muestra la velocidad de descarga, subida en Mbps y el estado de conexión.

### CU-04: Navegación por el Menú Interactivo
- **Actor:** Administrador de Sistemas
- **Descripción:** Permite al administrador interactuar con Pulso a través de un menú de opciones en la terminal.
- **Flujo Principal:**
  1. El administrador ejecuta `./pulso` sin argumentos.
  2. Pulso presenta el menú con las opciones: Ver estado, Actualizar datos, Salir.
  3. El administrador selecciona una opción ingresando el número correspondiente.
  4. Pulso ejecuta la acción y muestra el resultado.

### CU-05: Recolección de Métricas de Memoria RAM
- **Actor:** Agente Pulso
- **Descripción:** El agente captura el estado actual de la memoria RAM del sistema, incluyendo uso total y disponible.
- **Flujo Principal:**


---

### CU-Alert-01: Configuración de alerta por uso elevado de CPU
- **Actor:** Administrador de Sistemas
- **Descripción:** Permite definir un umbral de uso de CPU para generar notificaciones automáticas cuando se supere.
- **Flujo Principal:**
  1. El administrador abre el archivo de configuración `config.toml`.
  2. Localiza la sección `[alerts.cpu]`.
  3. Establece el valor `threshold_percent = 90`.
  4. Configura el intervalo de revisión: `check_interval_seconds = 60`.
  5. Guarda el archivo y reinicia el servicio:
     ```bash
     sudo systemctl restart pulso
     ```
- **Postcondición:** El sistema genera una alerta cuando el uso de CPU supera el 90% durante 3 mediciones consecutivas.

---

### CU-Export-01: Exportación de historial de métricas a CSV
- **Actor:** Administrador de Sistemas
- **Descripción:** Permite extraer el historial de métricas almacenado y guardarlo en formato CSV para análisis externo.
- **Flujo Principal:**
  1. El administrador abre la terminal en la carpeta del proyecto.
  2. Ejecuta el comando de exportación:
     ```bash
     ./build/bin/pulso --export csv --output metricas.csv --last-hours 24
     ```
  3. El sistema procesa los datos y genera el archivo de salida.
- **Postcondición:** Se crea el archivo `metricas.csv` con los valores de CPU, memoria, disco y red de las últimas 24 horas.

---

### CU-Once-01: Recolección puntual de métricas
- **Actor:** Administrador de Sistemas
- **Descripción:** Ejecuta una sola captura de métricas sin dejar el servicio en segundo plano.
- **Flujo Principal:**
  1. El administrador abre la terminal en la carpeta del proyecto.
  2. Ejecuta el modo de captura única:
     ```bash
     ./build/bin/pulso --once
     ```
  3. El agente obtiene los valores actuales y los muestra en pantalla.
- **Postcondición:** Se muestran las métricas del momento y el proceso finaliza automáticamente.

  1. El agente consulta la memoria RAM al sistema operativo.
  2. Obtiene la memoria total, en uso y disponible.
  3. Almacena temporalmente los valores para mostrarlos al administrador.

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
  1. El agente consulta la memoria RAM al sistema operativo.
  2. Obtiene la memoria total, en uso y disponible.
  3. Almacena temporalmente los valores para mostrarlos al administrador.
# Casos de Prueba Funcionales

| ID | Requerimiento Asociado | Descripción del Caso | Precondiciones | Pasos | Resultado Esperado |
|---|---|---|---|---|---|
| CP-001 | RF-001 | Validar monitoreo de disponibilidad mediante ping y chequeos HTTP. | Servidor activo y accesible. | 1. Ejecutar monitoreo. 2. Verificar respuesta de ping/HTTP. | El sistema muestra estado “Disponible” si responde correctamente. |
| CP-002 | RF-002 | Validar recolección y visualización de métricas CPU, memoria y red. | Servidor con agente instalado. |  1. Iniciar agente. 2. Consultar panel de métricas. | El sistema muestra valores en tiempo real de CPU, memoria y red.  |
| CP-003 | RF-003 | Validar generación de alertas ante caída de servicio. | Servicio configurado con umbral crítico. | 1. Simular caída del servicio. 2. Revisar alertas. | El sistema genera alerta inmediata indicando el fallo. |
| CP-004 | RF-004 | Validar visualización en panel web. | Usuario autenticado en el sistema. | 1. Acceder al panel web. 2. Consultar estado de infraestructura. | El panel muestra estado actualizado de servidores y servicios. |
| CP-005 | RF-005 | Validar almacenamiento de métricas históricas por 24 horas. | Métricas recolectadas durante el día. | 1. Consultar métricas del día anterior. | El sistema muestra datos históricos disponibles hasta 24 horas atrás. |
| CP-006 | RF-006 | Validar instalación y configuración de agentes en servidores monitoreados. | Servidor destino disponible y con permisos de instalación. | 1. Ejecutar instalador del agente. 2. Configurar parámetros básicos (IP, puerto, credenciales). 3. Iniciar agente. | El agente queda instalado y comienza a reportar métricas al sistema. |
| CP-007 | RF-007 | | | | |
| CP-008 | RF-008 | | | | |
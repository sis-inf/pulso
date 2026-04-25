# Casos de Prueba Funcionales

| ID | Requerimiento Asociado | Descripción del Caso | Precondiciones | Pasos | Resultado Esperado |
|---|---|---|---|---|---|
| CP-001 | RF-001 | Validar monitoreo de disponibilidad mediante ping y chequeos HTTP. | Servidor activo y accesible. | 1. Ejecutar monitoreo. 2. Verificar respuesta de ping/HTTP. | El sistema muestra estado “Disponible” si responde correctamente. |
| CP-002 | RF-002 | Validar recolección y visualización de métricas CPU, memoria y red. | Servidor con agente instalado. |  1. Iniciar agente. 2. Consultar panel de métricas. | El sistema muestra valores en tiempo real de CPU, memoria y red.  |
| CP-003 | RF-003 | Validar generación de alertas ante caída de servicio. | Servicio configurado con umbral crítico. | 1. Simular caída del servicio. 2. Revisar alertas. | El sistema genera alerta inmediata indicando el fallo. |
| CP-004 | RF-004 | Validar visualización en panel web. | Usuario autenticado en el sistema. | 1. Acceder al panel web. 2. Consultar estado de infraestructura. | El panel muestra estado actualizado de servidores y servicios. |
| CP-005 | RF-005 | | | | |
| CP-006 | RF-006 | | | | |
| CP-007 | RF-007 | | | | |
| CP-008 | RF-008 | | | | |
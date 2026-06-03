# Guía de Integración de pulso con Prometheus y Grafana

Esta guía proporciona las instrucciones detalladas para configurar la exportación de métricas desde **pulso** hacia un servidor de monitoreo **Prometheus** y su posterior visualización en paneles de tiempo real utilizando **Grafana**. El sistema aprovecha el componente interno `FormatterPrometheus` para exponer datos compatibles con el estándar de la Cloud Native Computing Foundation (CNCF).

---

## Activar formato Prometheus

Por defecto, **pulso** puede estar configurado para emitir métricas en formatos de consola o texto plano estructurado. Para habilitar la exposición de datos compatible con el ecosistema de Prometheus, es necesario modificar el archivo de configuración global del agente.

Abra el archivo `pulso.toml` ubicado en el directorio raíz o de configuración de la aplicación y asegúrese de definir el formato de salida de la siguiente manera:

```toml
# Configuración global del agente pulso
[agent]
interval = "10s"
output_format = "prometheus"
listen_address = "0.0.0.0:8080"

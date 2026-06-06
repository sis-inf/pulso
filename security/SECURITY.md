# Política de Seguridad

## Reportar una vulnerabilidad

Si encuentras una vulnerabilidad de seguridad:

1. **No** crees un issue público
2. Contacta directamente al mantenedor del proyecto
3. Incluye descripción detallada del problema
4. Espera confirmación antes de divulgar

## Análisis de seguridad

Este proyecto ejecuta análisis automático de seguridad
en cada PR mediante GitHub Actions.

## Versiones soportadas

| Versión | Soportada |
|---|---|
| latest | ✅ |

## Modelo de amenazas del servidor HTTP

El proyecto expone un servidor HTTP con endpoints que actualmente no requieren autenticación.

### Amenazas identificadas

- Acceso no autorizado a métricas internas del servidor si el puerto está expuesto.
- Posibles ataques de denegación de servicio (DoS) mediante múltiples requests masivos que saturen el servidor.

### Mitigaciones recomendadas

- Configurar el servidor para que haga bind únicamente a `localhost` en entornos de desarrollo.
- Implementar rate limiting en el futuro para limitar requests por IP.
- Usar firewall o reglas de red para restringir el acceso a los endpoints HTTP.

### Advertencia

Actualmente no existe autenticación en el servidor HTTP, por lo que cualquier endpoint expuesto puede ser accesible si el servicio es público.

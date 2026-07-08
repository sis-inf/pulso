# Consideraciones de seguridad en Pulso

Pulso es un monitor de infraestructura ligero que accede a información sensible del sistema.
Por ello, es fundamental considerar aspectos de seguridad durante su desarrollo para evitar
riesgos potenciales en los entornos donde se ejecute.

A continuación se describen las principales consideraciones de seguridad:

## 1. Acceso a datos del sistema

- **Riesgo:** Pulso accede a información sensible como uso de CPU, memoria, procesos y red.
  Un mal manejo podría exponer datos internos del sistema o del usuario.
- **Mitigación:**
  - Limitar la recolección de datos únicamente a lo necesario.
  - Evitar almacenar información sensible innecesaria.
  - No registrar datos que puedan comprometer la privacidad del usuario.

## 2. Permisos de ejecución

- **Riesgo:** Ejecutar Pulso con privilegios elevados (root/administrador) puede aumentar
  el impacto de posibles vulnerabilidades.
- **Mitigación:**
  - Diseñar el sistema para funcionar con privilegios mínimos.
  - Solicitar permisos elevados solo cuando sea estrictamente necesario.
  - Documentar claramente los permisos requeridos.

## 3. Exposición de información

- **Riesgo:** Mostrar métricas del sistema sin control puede exponer información crítica,
  especialmente si se integra con interfaces web o APIs.
- **Mitigación:**
  - Evitar exponer datos sensibles en interfaces públicas.
  - Implementar mecanismos de control de acceso.

## 4. Manejo de errores

- **Riesgo:** Mensajes de error detallados pueden revelar información interna del sistema,
  como rutas, configuraciones o fallos específicos.
- **Mitigación:**
  - Mostrar mensajes de error genéricos al usuario final.
  - Registrar detalles técnicos solo en logs internos controlados.
  - Evitar exponer stack traces en producción.

## 5. Consumo de recursos y denegación de servicio

- **Riesgo:** Un monitoreo demasiado frecuente puede consumir recursos excesivos y afectar
  el rendimiento del sistema.
- **Mitigación:**
  - Definir frecuencias de muestreo razonables.
  - Optimizar el uso de CPU y memoria.
  - Permitir configuración de intervalos de monitoreo.

## 6. Compatibilidad y diferencias entre sistemas operativos

- **Riesgo:** Diferencias entre Linux y Windows pueden generar comportamientos inesperados
  o vulnerabilidades si no se manejan correctamente.
- **Mitigación:**
  - Implementar capas de abstracción para cada sistema operativo.
  - Validar el comportamiento en ambos entornos.
  - Evitar dependencias inseguras o específicas sin validación.


---

## 7 Seguridad del Servidor HTTP

### Amenazas específicas
Con la incorporación de múltiples endpoints (como `/metrics`, `/health`, `/alerts`) se identifican los siguientes riesgos:

1. **Acceso no autorizado a métricas y datos**
   - Actualmente el servicio no incluye sistema de autenticación ni autorización. Cualquier usuario con acceso a la red puede consultar métricas internas, estados y configuración.

2. **Ataques de tipo DoS (Denegación de Servicio)**
   - Un atacante podría enviar un volumen elevado de peticiones de forma rápida para saturar el servidor y reducir su rendimiento o detenerlo.

---

### Medidas de mitigación recomendadas

🔹 **Vincular el servidor solo a `localhost`**
Configurar el puerto HTTP para que solo sea accesible desde el mismo equipo donde se ejecuta Pulso:
```toml
http.bind = "127.0.0.1"
http.port = 8080
```

Esto evita que el servicio sea accesible desde redes externas.
 
🔹 Protección mediante cortafuegos (Firewall)
Restringir el acceso al puerto usado por Pulso mediante reglas de firewall:
 
- Permitir conexiones solo desde IPs confiables o dentro de la red local.
​
- Bloquear intentos de acceso desde direcciones desconocidas.
 
🔹 Control de tasa de peticiones (futura mejora)
Se planea implementar limitación de velocidad para evitar abusos y ataques DoS.
 
  
Nota importante: En la versión actual no existe autenticación para los endpoints HTTP. No se recomienda exponer el servicio directamente a internet público sin capas adicionales de seguridad.

## Notas finales

- La seguridad es un proceso continuo y debe revisarse constantemente.
- Estas consideraciones pueden ampliarse a medida que el proyecto evolucione.
- Pulso prioriza un enfoque seguro sin comprometer su ligereza y rendimiento.

  

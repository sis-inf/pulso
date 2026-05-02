# Documentación de API

## Base URL
http://localhost:8080

## Endpoints

### GET /
*Descripción:* Obtiene información general del sistema Pulso.  
*Parámetros:* No requiere parámetros.  
*Respuesta:*
json
{
  "status": "ok",
  "message": "Sistema funcionando correctamente"
}


---

### GET /metrics
*Descripción:* Obtiene métricas del sistema.  
*Parámetros:* No requiere parámetros.  
*Respuesta:*
json
{
  "cpu": "20%",
  "memory": "512MB",
  "status": "normal"
}


---

### POST /alert
*Descripción:* Envía una alerta del sistema.  
*Parámetros:*
json
{
  "message": "string",
  "level": "string"
}

*Respuesta:*
json
{
  "status": "alert sent"
}


---

## Códigos de error

| Código | Descripción |
|---|---|
| 200 | OK |
| 400 | Bad Request |
| 500 | Internal Server Error |

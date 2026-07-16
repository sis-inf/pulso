# Historial de alertas

## Introducción

El historial de alertas permite consultar las alertas que fueron disparadas por el sistema y registradas de forma persistente. A diferencia del endpoint `GET /alerts`, que muestra únicamente las alertas activas en el momento de la consulta, el endpoint `GET /alerts/historial` permite recuperar alertas registradas anteriormente mediante filtros por rango de tiempo.

Este documento describe la estructura de la tabla `alertas_disparadas`, los parámetros disponibles para consultar el historial y un ejemplo del formato de respuesta devuelto por la API.

---

## Tabla `alertas_disparadas`

Las alertas disparadas se registran en la tabla `alertas_disparadas`. Cada registro conserva la información necesaria para consultar eventos ocurridos previamente, incluso cuando la alerta ya no se encuentra activa.

### Estructura

| Campo | Descripción |
|--------|-------------|
| `id` | Identificador único del registro. |
| `timestamp` | Marca de tiempo Unix correspondiente al momento en que se registró la alerta. |
| `metrica` | Nombre de la métrica que originó la alerta. |
| `umbral` | Valor configurado como límite para la alerta. |
| `operador` | Operador utilizado para evaluar la condición de la alerta. |
| `valor_en_el_momento` | Valor observado cuando la alerta fue disparada. |
| `mensaje` | Mensaje descriptivo asociado a la alerta. |

---

## Consultar el historial de alertas

El historial de alertas puede consultarse mediante el siguiente endpoint:

```http
GET /alerts/historial
```

### Parámetros opcionales

| Parámetro | Descripción |
|-----------|-------------|
| `from` | Timestamp Unix que indica el inicio del rango de tiempo que se desea consultar. |
| `until` | Timestamp Unix que indica el final del rango de tiempo que se desea consultar. |

Los parámetros pueden utilizarse para limitar la consulta a un intervalo específico de tiempo.

---

## Ejemplo de consulta

El siguiente ejemplo consulta las alertas registradas entre dos marcas de tiempo Unix:

```bash
curl "http://localhost:8080/alerts/historial?from=1719900000&until=1719903600"
```

---

## Ejemplo de respuesta JSON

Una respuesta del endpoint puede tener el siguiente formato:

```json
{
  "alerts": [
    {
      "id": 1,
      "timestamp": 1719900123,
      "metrica": "cpu",
      "umbral": 90,
      "operador": ">",
      "valor_en_el_momento": 94.8,
      "mensaje": "Uso de CPU superior al umbral configurado."
    },
    {
      "id": 2,
      "timestamp": 1719901480,
      "metrica": "ram",
      "umbral": 85,
      "operador": ">",
      "valor_en_el_momento": 87.1,
      "mensaje": "Uso de memoria superior al umbral configurado."
    }
  ]
}
```

---

## Consideraciones

- El historial de alertas permite consultar eventos registrados previamente, incluso si la alerta ya no se encuentra activa.
- Los parámetros `from` y `until` permiten filtrar las alertas por un rango de tiempo específico.
- La respuesta del endpoint utiliza el formato JSON, manteniendo el mismo estilo que el resto de los endpoints HTTP del proyecto.

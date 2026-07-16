# Postman y herramientas de cliente

## Importar la colección de Postman

El proyecto dispone de un endpoint que permite exportar una colección de Postman lista para importar.

### Pasos

1. Abrir Postman.
2. Seleccionar **Import**.
3. Elegir la opción **Link**.
4. Introducir la siguiente URL:

```text
http://localhost:PUERTO/export/postman-collection
```

5. Confirmar la importación para que la colección quede disponible en Postman.

---

## Uso con curl

Además de utilizar Postman, es posible consumir los principales endpoints del proyecto desde la línea de comandos mediante `curl`.

### Estado del servicio

Permite verificar que el servicio está funcionando correctamente.

```bash
curl http://localhost:PUERTO/health
```

### Historial de métricas

Obtiene el historial de métricas almacenadas.

```bash
curl http://localhost:PUERTO/metrics/history
```

También es posible filtrar los resultados utilizando parámetros:

```bash
curl "http://localhost:PUERTO/metrics/history?desde=1700000000&hasta=1700003600&limite=100"
```

### Métricas en formato Prometheus

Obtiene las métricas en formato compatible con Prometheus.

```bash
curl http://localhost:PUERTO/metrics/prometheus
```

### Exportar la colección de Postman

La colección también puede descargarse desde la línea de comandos.

```bash
curl http://localhost:PUERTO/export/postman-collection
```

---

## Herramientas alternativas

Si no deseas utilizar Postman, también puedes interactuar con la API utilizando otras herramientas compatibles con HTTP, por ejemplo:

- curl
- HTTPie
- Insomnia

Estas herramientas permiten realizar solicitudes HTTP directamente desde la terminal o mediante una interfaz gráfica.

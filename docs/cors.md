# Configuración de CORS

## ¿Qué es CORS?

CORS (Cross-Origin Resource Sharing) permite que aplicaciones web alojadas en un origen diferente puedan realizar solicitudes HTTP al servidor.

Esta configuración es útil cuando se desea consumir la API desde un dashboard web externo.

## Configuración

Configure el parámetro `cors_origin` con el origen que tendrá permiso para acceder al servidor.

Ejemplo:

```toml
cors_origin = "http://localhost:3000"
```

En este ejemplo, únicamente la aplicación ejecutándose en `http://localhost:3000` podrá realizar solicitudes al servidor.

## Ejemplo desde JavaScript

Una vez configurado `cors_origin`, es posible realizar solicitudes desde otro origen utilizando `fetch`.

```javascript
fetch("http://localhost:8000/api/status")
  .then((response) => response.json())
  .then((data) => {
    console.log(data);
  })
  .catch((error) => {
    console.error(error);
  });
```

Si el origen desde el que se ejecuta este código coincide con el valor configurado en `cors_origin`, la solicitud será aceptada correctamente.

## Limitaciones

Actualmente solo se admite un único origen mediante la opción `cors_origin`.

No es posible configurar una lista de múltiples orígenes autorizados. Si se requiere permitir otro origen, debe reemplazarse el valor existente por el nuevo origen autorizado.

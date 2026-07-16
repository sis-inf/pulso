# Modelo de datos

## Resumen

Pulso almacena la información recolectada en una base de datos SQLite. El esquema está definido en `storage/schema.cpp` y organiza las métricas, los resúmenes históricos y las alertas generadas por el sistema.

Aunque SQLite no utiliza claves foráneas formales en este esquema, existen relaciones lógicas entre las tablas que permiten reconstruir el historial de monitoreo.

---

# Diagrama del modelo de datos

```text
                   +--------------------+
                   |     snapshots      |
                   +--------------------+
                   | id                 |
                   | timestamp          |
                   | hostname           |
                   | metric             |
                   | value              |
                   +--------------------+
                            |
                            |
                            | Resumen horario
                            |
                            ▼
                 +--------------------------+
                 | snapshots_horarios       |
                 +--------------------------+
                 | id                       |
                 | hora                     |
                 | hostname                 |
                 | metric                   |
                 | promedio                 |
                 | minimo                   |
                 | maximo                   |
                 +--------------------------+

                            |
                            |
                            | Genera alertas
                            |
                            ▼

                 +--------------------------+
                 | alertas_disparadas       |
                 +--------------------------+
                 | id                       |
                 | timestamp                |
                 | hostname                 |
                 | alerta                   |
                 | valor                    |
                 | umbral                   |
                 +--------------------------+
```

---

# Tabla `snapshots`

Contiene las métricas recolectadas en cada ciclo de monitoreo.

## Columnas

| Columna | Tipo | Descripción |
|---------|------|-------------|
| id | INTEGER | Identificador del registro |
| timestamp | INTEGER | Momento de captura |
| hostname | TEXT | Equipo monitoreado |
| metric | TEXT | Nombre de la métrica |
| value | REAL | Valor registrado |

## Índices

- Índice por `timestamp`.
- Índice por `hostname`.
- Índice por nombre de métrica.

---

# Tabla `snapshots_horarios`

Almacena resúmenes horarios obtenidos a partir de los datos almacenados en `snapshots`.

## Columnas

| Columna | Tipo | Descripción |
|---------|------|-------------|
| id | INTEGER | Identificador |
| hora | INTEGER | Hora resumida |
| hostname | TEXT | Equipo monitoreado |
| metric | TEXT | Métrica resumida |
| promedio | REAL | Promedio horario |
| minimo | REAL | Valor mínimo |
| maximo | REAL | Valor máximo |

## Índices

- Índice por hora.
- Índice por hostname.
- Índice por métrica.

---

# Tabla `alertas_disparadas`

Registra las alertas generadas cuando una métrica supera el umbral configurado.

## Columnas

| Columna | Tipo | Descripción |
|---------|------|-------------|
| id | INTEGER | Identificador |
| timestamp | INTEGER | Momento de la alerta |
| hostname | TEXT | Equipo afectado |
| alerta | TEXT | Nombre de la alerta |
| valor | REAL | Valor observado |
| umbral | REAL | Umbral configurado |

## Índices

- Índice por timestamp.
- Índice por hostname.

---

# Relaciones lógicas

Aunque SQLite no define claves foráneas explícitas, las tablas mantienen relaciones conceptuales:

- `snapshots` contiene las mediciones originales.
- `snapshots_horarios` resume la información almacenada en `snapshots`.
- `alertas_disparadas` registra eventos generados a partir de los datos almacenados en `snapshots`.

Todas las tablas utilizan el campo `hostname` para identificar el origen de la información y permiten consultar el historial completo de un equipo monitoreado.

---

# Referencias

- `storage/schema.cpp`
- `storage/storage.cpp`
- `storage/storage.hpp`
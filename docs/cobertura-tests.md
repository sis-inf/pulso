# Cobertura de Tests

## Estado actual

La compilación del proyecto no pudo completarse debido a que la estructura de directorios del proyecto base está pendiente de corrección por parte del equipo de mantenimiento. Esta situación fue comunicada por el ingeniero responsable.

Por esta razón, los porcentajes de cobertura no pudieron obtenerse ejecutando el comando de tests. El presente documento identifica los módulos existentes y su estado de cobertura basado en el análisis del código fuente disponible.

## Tabla de cobertura por módulo

| Módulo | Archivo de test | Cobertura estimada | Estado |
|---|---|---|---|
| formatters/formatter_json | tests/formatters/test_formatter_json.cpp | ~80% | Con tests |
| formatters/formatter_prometheus | — | 0% | Sin tests |
| core/types | — | 0% | Sin tests |
| collectors/cpu | — | 0% | Sin tests |
| collectors/memory | — | 0% | Sin tests |
| collectors/disk | — | 0% | Sin tests |
| collectors/network | — | 0% | Sin tests |
| storage | — | 0% | Sin tests |

## Módulos con cobertura menor al 60%

Todos los módulos excepto `formatters/formatter_json` tienen cobertura del **0%** por ausencia de tests:

- `formatters/formatter_prometheus`
- `core/types`
- `collectors/cpu`
- `collectors/memory`
- `collectors/disk`
- `collectors/network`
- `storage`

## Nota

La cobertura real deberá medirse una vez que la estructura base del proyecto sea corregida y la compilación pueda completarse exitosamente.

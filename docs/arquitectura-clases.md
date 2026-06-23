# Arquitectura de clases de Pulso

## Introducción

Este documento describe la arquitectura de clases principal del proyecto Pulso, incluyendo interfaces, relaciones de herencia, relaciones de uso y estructuras de datos utilizadas para la recolección, procesamiento y formateo de métricas.

---

## Clases principales

### Recolectores (Collectors)

Los recolectores obtienen información del sistema operativo y exponen una interfaz común mediante `ICollector`.

* ICollector
* CpuUsage
* RamUsage
* DiskUsage
* NetUsage

### Formateadores (Formatters)

Los formateadores convierten los datos recolectados a distintos formatos de salida.

* IFormatter
* FormatterJson
* FormatterCsv
* FormatterPrometheus

### Núcleo del sistema

* SystemMonitor
* MetricSnapshot

---

## Estructura MetricSnapshot

`MetricSnapshot` almacena una instantánea de las métricas del sistema.

Campos principales:

* cpu
* ram
* disk
* rx_bytes
* tx_bytes
* timestamp

Métodos principales:

* MetricSnapshot()
* MetricSnapshot(...)
* isValid()

---

## Clase SystemMonitor

Responsable de coordinar la recolección y consulta de métricas.

Métodos principales:

* SystemMonitor()
* start()
* stop()
* getMetrics()

Atributos:

* metrics : std::map<std::string, double>

---

## Relaciones de herencia

```mermaid
classDiagram

class ICollector {
    +nombre()
    +recolectar()
}

class CpuUsage
class RamUsage
class DiskUsage
class NetUsage

ICollector <|-- CpuUsage
ICollector <|-- RamUsage
ICollector <|-- DiskUsage
ICollector <|-- NetUsage
```

---

## Relaciones de herencia de formateadores

```mermaid
classDiagram

class IFormatter {
    +formato()
    +contentType()
    +formatear()
    +formatearHistorial()
}

class FormatterJson
class FormatterCsv
class FormatterPrometheus

IFormatter <|-- FormatterJson
IFormatter <|-- FormatterCsv
IFormatter <|-- FormatterPrometheus
```

---

## Relaciones de uso

```mermaid
classDiagram

class SystemMonitor
class ICollector
class MetricSnapshot
class IFormatter

SystemMonitor --> ICollector : utiliza
IFormatter --> MetricSnapshot : formatea
```

---

## Arquitectura general

```mermaid
classDiagram

class SystemMonitor {
    +start()
    +stop()
    +getMetrics()
}

class MetricSnapshot {
    +cpu
    +ram
    +disk
    +rx_bytes
    +tx_bytes
    +timestamp
    +isValid()
}

class ICollector
class CpuUsage
class RamUsage
class DiskUsage
class NetUsage

class IFormatter
class FormatterJson
class FormatterCsv
class FormatterPrometheus

ICollector <|-- CpuUsage
ICollector <|-- RamUsage
ICollector <|-- DiskUsage
ICollector <|-- NetUsage

IFormatter <|-- FormatterJson
IFormatter <|-- FormatterCsv
IFormatter <|-- FormatterPrometheus

SystemMonitor --> ICollector
IFormatter --> MetricSnapshot
```

---

## Configuración

El proyecto utiliza estructuras de configuración definidas en los módulos de configuración para controlar el comportamiento del monitor, frecuencia de muestreo y parámetros de ejecución.

---

## Alertas

La carpeta `src/alertas` está reservada para la implementación del sistema de alertas. Actualmente no contiene clases concretas implementadas.

Las futuras implementaciones podrán incluir componentes como:

* GestorAlertas
* AlertaUmbral

para la evaluación y notificación de eventos basados en métricas.

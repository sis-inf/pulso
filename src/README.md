# 📁 Estructura de la carpeta src

```bash
src/
├── core/
├── monitor/
├── collectors/
├── platform/
├── config/
├── logging/
└── utils/
```

---

## 📂 Descripción de Directorios

### 🧠 `core/`

Contiene el núcleo del sistema.

Responsabilidades:

* Planificación de tareas (scheduler)
* Manejo de hilos (threads)
* Flujo principal de ejecución

---

### 📊 `monitor/`

Lógica de monitoreo a alto nivel.

Responsabilidades:

* Definir qué se monitorea
* Coordinar los *collectors*
* Gestionar los ciclos de monitoreo

---

### 📡 `collectors/`

Módulos encargados de recolectar métricas.

Cada subcarpeta representa un tipo de recurso:

Ejemplos:

* CPU
* Memoria
* Disco
* Red

Este diseño permite agregar nuevos *collectors* fácilmente sin afectar el resto del sistema.

---

### 🖥️ `platform/`

Implementaciones específicas del sistema operativo.

Se utiliza para aislar código dependiente de la plataforma:

Ejemplo:

```bash
platform/
├── linux/
└── windows/
```

Responsabilidades:

* Llamadas al sistema
* Acceso a métricas del hardware
* Diferencias entre sistemas operativos

---

### ⚙️ `config/`

Gestión de configuración del sistema.

Responsabilidades:

* Lectura de archivos de configuración (JSON, YAML, variables de entorno)
* Proveer parámetros en tiempo de ejecución

---

### 🪵 `logging/`

Sistema de registro (logs).

Responsabilidades:

* Registro en consola y/o archivo
* Manejo de niveles de log (INFO, WARN, ERROR)

---

### 🧰 `utils/`

Funciones utilitarias reutilizables.

Ejemplos:

* Manejo de tiempo
* Manipulación de strings
* Operaciones con archivos

---

## 🧩 Principios de Diseño

* **Modularidad**: Cada componente tiene una única responsabilidad
* **Extensibilidad**: Se pueden agregar nuevos *collectors* sin modificar el núcleo
* **Portabilidad**: El código dependiente del sistema está aislado
* **Simplicidad**: Diseño ligero y fácil de entender
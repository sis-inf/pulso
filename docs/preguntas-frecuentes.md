# Preguntas frecuentes
 
Respuestas a las dudas más comunes sobre Pulso.
 
---
 
## ¿Qué es Pulso?

Pulso es una herramienta de línea de comandos desarrollada en C++ que permite recolectar y visualizar métricas del sistema en tiempo real. Monitorea recursos como CPU, memoria RAM, disco y red, y está diseñada para ofrecer alto rendimiento con bajo consumo de recursos.

---
 
## ¿En qué plataformas funciona Pulso?

Pulso es compatible con los siguientes sistemas operativos:
 
- **Linux** — Kernel 5.4 o superior
- **Windows** — Windows 10 u 11
- **macOS** — macOS 12 o superior

---
 
## ¿Qué métricas puede monitorear Pulso?

Pulso monitorea las siguientes métricas del sistema:
 
| Métrica | Unidad | Frecuencia |
|---|---|---|
| CPU | Porcentaje (%) | Cada 1 segundo |
| Memoria RAM | MB / % | Cada 1 segundo |
| Disco | GB / % | Cada 5 segundos |
| Red (entrada/salida) | Bytes/segundo | Cada 1 segundo |
| Procesos activos | Cantidad | Cada 2 segundos |
| Carga del sistema | Load average | Cada 5 segundos |
 
Las frecuencias de muestreo pueden ajustarse según el entorno de ejecución.

---
 
## ¿Cómo se instala Pulso?

Para instalar Pulso se necesita un compilador C++ (GCC, Clang o MSVC), CMake 3.16 o superior y Git. Los pasos básicos son:
 
```bash
# Clonar el repositorio
git clone https://github.com/sis-inf/pulso.git
cd pulso
 
# Compilar
cmake -B build
cmake --build build
```  

Para instrucciones detalladas por plataforma, consulte [instalacion.md](instalacion.md).

---
 
## ¿Cómo se ejecuta Pulso?

Una vez compilado, el binario se encuentra en `build/bin/`. Para ejecutarlo:
 
**Linux y macOS:**
```bash
./build/bin/pulso
```
 
**Windows:**
```bash
build\bin\Release\pulso.exe
```

---
 
## ¿Cómo puedo contribuir al proyecto?

El proyecto usa el **Forking Workflow**. Los pasos básicos son:
 
1. Haz un fork del repositorio en tu cuenta de GitHub.
2. Clona tu fork y agrega el repositorio original como `upstream`.
3. Sincroniza con `upstream/dev` antes de empezar a trabajar.
4. Crea una rama siguiendo la convención `tipo/descripcion-corta`.
5. Realiza tus cambios con commits descriptivos siguiendo la convención del proyecto.
6. Abre un Pull Request hacia `dev` referenciando el issue con `Closes #N`.

Para más detalles, consulte [CONTRIBUTING.md](../CONTRIBUTING.md).

---
 
## ¿Qué compilador necesito para usar Pulso?

Pulso requiere un compilador compatible con el estándar **C++17**. Las opciones soportadas según el sistema operativo son:
 
- **Linux** — GCC 11 o superior
- **macOS** — Clang 13 o superior (incluido con las herramientas de Xcode)
- **Windows** — MSVC 2019 o superior (incluido con Visual Studio)
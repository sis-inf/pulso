# Guía de instalación de Pulso

Este documento describe los pasos necesarios para instalar y ejecutar Pulso en un entorno local.

---

## Requisitos previos

Antes de instalar Pulso, asegúrese de contar con lo siguiente:

| Requisito | Versión mínima | Notas |
|---|---|---|
| Sistema operativo | — | Linux, Windows o macOS |
| Compilador C++ | C++17 | GCC, Clang o MSVC |
| CMake | 3.16 | |
| Git | — | Para clonar el repositorio |

### Instalar dependencias
 
**Linux (Debian/Ubuntu)**
```bash
sudo apt install g++ cmake git
```
 
**macOS**
```bash
brew install cmake git
```
> El compilador Clang viene incluido con las herramientas de línea de comandos de Xcode. Si no lo tiene, ejecute `xcode-select --install`.
 
**Windows**
 
- Instale [CMake](https://cmake.org/download/) y marque la opción para agregarlo al PATH durante la instalación.
- Instale [Git](https://git-scm.com/download/win).
- Instale [Visual Studio](https://visualstudio.microsoft.com/) con la carga de trabajo **"Desarrollo de escritorio con C++"**, que incluye el compilador MSVC.

---

## Clonar el repositorio

Ejecute el siguiente comando para clonar el proyecto:

```bash
git clone https://github.com/sis-inf/pulso.git
cd pulso
```

---

## Compilar el proyecto
 
### Linux y macOS
 
```bash
# Configurar el proyecto y crear la carpeta build
cmake -B build
 
# Compilar
cmake --build build
```
 
### Windows
 
Abra el **Developer Command Prompt** de Visual Studio y ejecute:
 
```bash
# Configurar el proyecto y crear la carpeta build
cmake -B build
 
# Compilar
cmake --build build --config Release
```
 
> El binario resultante se encuentra en `build/bin/`.
 
---
 
## Ejecutar el programa
 
### Linux y macOS
 
```bash
./build/bin/pulso
```
 
### Windows
 
```bash
build\bin\Release\pulso.exe
```
 
---
 
## Notas adicionales
 
- En Linux, si aparecen errores de permisos al acceder a `/proc`, verifique que el usuario tenga los permisos necesarios. No se recomienda modificar permisos del sistema sin conocer su impacto.
- Para compilar sin ejecutar los tests, agregue `-DPULSO_BUILD_TESTS=OFF` al comando de configuración:

```bash
cmake -B build -DPULSO_BUILD_TESTS=OFF
```
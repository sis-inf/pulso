# Compilación en Linux

Este documento describe los pasos básicos para instalar las herramientas necesarias y compilar el proyecto en Linux.

## 1. Instalar dependencias

En distribuciones basadas en Debian o Ubuntu, ejecutar:

```bash
sudo apt install g++ cmake
```

`g++` permite compilar código C++, mientras que `cmake` permite configurar el proceso de compilación del proyecto.

## 2. Configurar el proyecto

Desde la raíz del proyecto, ejecutar:

```bash
cmake -B build
```

Este comando crea la carpeta `build` y genera los archivos necesarios para la compilación.

## 3. Nota sobre permisos en `/proc`

En Linux, algunos programas pueden acceder a información del sistema mediante `/proc`.

Si aparecen errores relacionados con permisos en `/proc`, se debe verificar que el programa tenga los permisos necesarios. No se recomienda modificar permisos del sistema sin conocer su impacto, ya que `/proc` contiene información sensible del sistema operativo y de los procesos en ejecución.
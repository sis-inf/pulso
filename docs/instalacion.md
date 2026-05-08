# Guía de instalación de Pulso

## Descripción

Pulso es una herramienta de monitoreo de infraestructura desarrollada en C++.

---

## Requisitos previos

Antes de instalar el proyecto, asegúrese de contar con:

- Sistema operativo Windows, Linux o macOS
- Compilador compatible con C++17
- CMake 3.15 o superior
- Git

Verificar herramientas instaladas:

```bash
g++ --version
cmake --version
git --version
```

---

## Clonar el repositorio

Ejecute el siguiente comando:

```bash
git clone https://github.com/sis-inf/pulso.git
```

Luego ingrese al proyecto:

```bash
cd pulso
```

---

## Compilar el proyecto

Crear carpeta de compilación:

```bash
mkdir build
cd build
```

Generar archivos de compilación:

```bash
cmake ..
```

Compilar el proyecto:

```bash
cmake --build .
```

---

## Verificar instalación

Si la compilación finaliza sin errores, la instalación fue exitosa.

También puede ejecutar:

```bash
./pulso
```

o en Windows:

```bash
pulso.exe
```

---

## Ejecución básica

Ejemplo de ejecución desde terminal:

```bash
./pulso
```
# Flujo de datos en el sistema Pulso

Este documento describe cómo fluye la información dentro del sistema Pulso desde la recolección hasta la visualización.

---

## 1. Recolección de datos

Se obtienen métricas del sistema como CPU, memoria, red y procesos.

**Componentes:**
- Módulo de recolección
- APIs del sistema operativo

---

## 2. Procesamiento

Los datos se transforman y organizan para su uso interno.

**Componentes:**
- Parser de métricas
- Normalización de datos

---

## 3. Almacenamiento

Los datos procesados se almacenan temporalmente.

**Componentes:**
- Gestor de datos en memoria

---

## 4. Visualización

Los datos se muestran al usuario.

**Componentes:**
- Interfaz / consola

---

## Diagrama
Recolección → Procesamiento → Almacenamiento → Visualización
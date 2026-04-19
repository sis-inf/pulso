# Cómo contribuir a este proyecto

Gracias por tu interés en contribuir. Este proyecto usa
el **Forking Workflow**. Lee este documento antes de empezar.

---

## Flujo de trabajo

### 1. Haz fork del repositorio
Botón **Fork** en la esquina superior derecha de GitHub.

### 2. Clona tu fork
```bash
git clone https://github.com/TU-USUARIO/PROYECTO.git
cd PROYECTO
```

### 3. Agrega el repo original como upstream
```bash
git remote add upstream https://github.com/sis-inf/PROYECTO.git
```

### 4. Sincroniza antes de trabajar
```bash
git checkout dev
git pull upstream dev
```

### 5. Crea tu rama de trabajo
```bash
git checkout -b tipo/descripcion-corta
```

Ejemplos de nombres de rama:

feat/endpoint-metricas-cpu
docs/readme-instalacion
fix/calculo-ram-incorrecto
test/pruebas-unitarias-cpu
chore/configurar-github-actions
security/analisis-dependencias

### 6. Trabaja y haz commits pequeños
```bash
git add .
git commit -m "tipo: descripción corta en presente"
```

### 7. Sube tu rama a tu fork
```bash
git push origin tipo/descripcion-corta
```

### 8. Abre un Pull Request
- Base: `sis-inf/PROYECTO` → rama `dev`
- Compare: `TU-USUARIO/PROYECTO` → tu rama

---

## Convención de commits

| Tipo | Cuándo usarlo |
|---|---|
| `feat:` | Nueva funcionalidad |
| `fix:` | Corrección de error |
| `docs:` | Documentación |
| `test:` | Pruebas |
| `chore:` | Configuración o CI/CD |
| `refactor:` | Mejora sin cambiar comportamiento |
| `security:` | Mejora de seguridad |
| `data:` | Análisis de datos |

### Ejemplos

feat: agregar endpoint /metrics para CPU
fix: corregir cálculo de porcentaje de RAM
docs: agregar guía de instalación en Windows
test: agregar pruebas unitarias para módulo de disco
chore: configurar GitHub Actions para CI

---

## Reglas importantes

- ❌ Nunca hagas push directo a `main` o `dev`
- ❌ Nunca trabajes directamente en `main` o `dev`
- ✅ Un issue = una rama = un PR
- ✅ Todo PR debe referenciar su issue con `Closes #N`
- ✅ El PR debe pasar el CI antes de ser mergeado
- ✅ Todo PR necesita al menos una revisión

---

## Ramas del proyecto

| Rama | Propósito |
|---|---|
| `main` | Versión estable — solo recibe merges desde `dev` |
| `dev` | Rama de desarrollo principal |
| `feat/*` | Nuevas funcionalidades |
| `fix/*` | Correcciones |
| `docs/*` | Documentación |
| `test/*` | Pruebas |
| `chore/*` | Configuración |

---

## ¿No sabes por dónde empezar?

1. Revisa los issues abiertos con la etiqueta `good first issue`
2. Comenta en el issue que quieres trabajarlo
3. Espera confirmación antes de empezar
4. Sigue los pasos de este documento
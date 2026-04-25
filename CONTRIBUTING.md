# Cómo contribuir a este proyecto

Gracias por tu interés en contribuir. Este proyecto usa
el **Forking Workflow**. Lee este documento antes de empezar.

---

## Flujo de trabajo

### 1. Haz fork del repositorio
Botón **Fork** en la esquina superior derecha de GitHub.  

Asegúrate que el **owner** sea tu cuenta de GithHub, luego click al botón de color verde: "**Create Fork**".
Ahora deberías tener un repositorio en tu **cuenta personal** de GitHub llamado **tu_nombre_usuario/nombre_repositorio**. 

*Ejemplo.-* **Atoxny/pulso**

### 2. Clona tu fork
Desde el apartado **Code** del repositorio en tu cuenta personal realiza la clonación con los siguientes pasos:
1.   Click al botón de color verde **"<> Code"**.
2.   Selecciona Local -> HTTPS.
3.   Copia la URL.
4.   Desde tu computadora (portátil o de escritorio), en la carpeta donde quieres clonar el repositorio, abre la terminal de GitBash haciendo click derecho dentro la carpeta.
5.   En la terminal de GitBash escribe los siguientes comandos:

```bash
# Clonar el repositorio
# Recuerda PEGAR la URL que copiaste en lugar del URL de ejemplo :D
git clone https://github.com/TU-USUARIO/PROYECTO.git

# Moverte dentro la carpeta donde se clonó el repositorio
cd PROYECTO
```

### 3. Agrega el repo original como upstream 
Para estar al tanto de las modificaciones que se realicen en el **repositorio original (sis-inf/pulso)** debes agregar el repositorio original como un upstream de la siguiente manera en la terminal de GitBash, puedes **copiar** el siguiente comando:
```bash
git remote add upstream https://github.com/sis-inf/pulso.git
```
Revisa si se agregó de manera exitosa el repositorio como upstream.
```bash
git remote -v
# Deberia salirte como resultado, luego de ingresar ese comando, lo siguiente:
origin https://github.com/TU-USUARIO/pulso.git (fetch)
origin https://github.com/TU-USUARIO/pulso.git (push)
upstream https://github.com/sis-inf/pulso.git (fetch)
upstream https://github.com/sis-inf/puslo.git (push)
```
Asegúrate de que te aparezca en **origin** tu nombre de usuario en el apartado ***TU-USUARIO***, mientras que en **upstream** el nombre de ***sis-inf***. 

En caso de existir algún error revisar el apartado [Errores comunes](#errores-comunes).

### 4. Sincroniza antes de trabajar
**Realiza** este paso **SIEMPRE ANTES** de empezar a trabajar en un nuevo Issue para tener tu repositorio al dia :D
```bash
# Moverte a la rama dev
git checkout dev
# Trae los cambios del repositorio original a tu repositorio local
git pull upstream dev
```

### 5. Crea tu rama de trabajo
Recuerda trabajar con ramas. El nombre de la rama que debes utilizar para tu Issue esta siempre en la descripcion del mismo, ya sea en el apartado **"Rama sugerida"** o simplemente **"Rama"**.

***tipo/descripcion-corta = el nombre de la Rama sugerida***
```bash
# Crear y moverte a la rama que crearás
git checkout -b tipo/descripcion-corta
```

Ejemplos de nombres de rama:
```
feat/endpoint-metricas-cpu
docs/readme-instalacion
fix/calculo-ram-incorrecto
test/pruebas-unitarias-cpu
chore/configurar-github-actions
security/analisis-dependencias
```

### 6. Trabaja y haz commits pequeños
*"Un cambio, un commit".*

Trabajar con commits permite tener "Checkpoints" y mantener un historial del trabajo que haz realizado. Normalmente llevan una descripcion corta tal y como se muestra en el ejemplo de abajo. 

La descripcion del commit debe ser de forma imperativa y concisa: *"docs: actualizar guía de instalación", "fix: corregir error en validación de usuario"*, entre otros.

El commit debe responder a la pregunta: *"¿Qué hace este cambio?"*
```bash
git add .
git commit -m "tipo: descripción corta en presente"
```
Para saber de que *tipo* debes realizar el commit revisa el apartado de [convención de commits](#convención-de-commits).
### 7. Sube tu rama a tu fork

***tipo/descripcion-corta = el nombre de la rama donde trabajaste.***
```bash
git push origin tipo/descripcion-corta
```

### 8. Abre un Pull Request
1. Ve a tu Fork en GitHub, aquel repositorio que está en tu cuenta personal.
2. Click en el banner de color amarillo: "Compare & pull request"
   En caso de que no aparezca: 
     * Dirígete a la pestaña `Pull Requests`-> `New Pull Request`
3. Verifica el  destino del PR
   - Base repository: `sis-inf/pulso` → base `dev`
   - Head repository: `TU-USUARIO/pulso` → compare `tu-rama`
4. Edita la descripción y el título del PR según los cambios que hayas realizado sin olvidarte de agregar al `Closes #` el numero del Issue que realizaste.
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

## Errores comunes

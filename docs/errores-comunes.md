# Errores comunes en Pulso

## 1. undefined reference to `ICollector::collect()`

**Causa:** El método fue declarado en una interfaz o clase base, pero no tiene implementación o no se compiló el archivo correspondiente.

**Solución:**

```bash
Verificar que collect() esté implementado y que el archivo .cpp sea incluido en CMakeLists.txt.
```

## 2. fatal error: no such file or directory

**Causa:** El compilador no encuentra un archivo de cabecera incluido con `#include`.

**Solución:**

```bash
Verificar la ruta del archivo y los directorios de inclusión.
```

## 3. cmake: command not found

**Causa:** CMake no está instalado en el sistema.

**Solución:**

```bash
sudo apt install cmake
```

## 4. make: command not found

**Causa:** GNU Make no está instalado.

**Solución:**

```bash
sudo apt install build-essential
```

## 5. make: No rule to make target

**Causa:** El objetivo especificado no existe en el Makefile.

**Solución:**

```bash
make help
```

## 6. ctest: Test not found

**Causa:** El test solicitado no existe o no fue compilado.

**Solución:**

```bash
ctest --output-on-failure
```

## 7. SIGSEGV en tests

**Causa:** Acceso a un puntero nulo o memoria inválida.

**Solución:**

```bash
gdb ./test_program
```

## 8. clang-format: unknown argument

**Causa:** Se utilizó una opción no soportada por la versión instalada.

**Solución:**

```bash
clang-format --version
```

## 9. undefined reference to `main`

**Causa:** La función `main()` no existe o no está siendo compilada.

**Solución:**

```bash
Verificar que main.cpp forme parte de la compilación.
```

## 10. Permission denied

**Causa:** El ejecutable no tiene permisos de ejecución.

**Solución:**

```bash
chmod +x pulso
```

## 11. CMake Error: The source directory does not exist

**Causa:** Se indicó una ruta incorrecta al ejecutar CMake.

**Solución:**

```bash
cmake ..
```

## 12. ld returned 1 exit status

**Causa:** Error de enlazado debido a bibliotecas faltantes o símbolos sin resolver.

**Solución:**

```bash
Revisar target_link_libraries en CMakeLists.txt.
```

# 📘 Guía de Estilo C++ (Basada en Google)
## 🎯 Objetivo

Esta guía define convenciones para escribir código C++ legible, mantenible y consistente, ya que la consistencia es más importante que preferencias personales.

## 🧾 1. Nombres de variables
- Usar `snake_case` (minúsculas con `_`).
- Los nombres deben ser descriptivos.
- Parámetros de funciones también siguen esta regla.
- Miembros de clase llevan guión bajo al final.

### ✅ Ejemplos:

```cpp
int user_age;
double total_price;
bool is_valid;

class User {
 private:
  int user_id_;
};
```

## ⚙️ 2. Nombres de funciones

- Usar `PascalCase` (UpperCamelCase).
- Deben representar acciones claras.
- Evitar nombres genéricos.

### ✅ Ejemplos:

```cpp
int CalculateTotal(int price, int quantity);
bool IsValidInput(const std::string& input);
void PrintReport();
```

## 📁 3. Nombres de archivos

- Usar minúsculas.
- Separar palabras con `_` o `-`.
- Archivos C++ usan `.cc` y headers `.h`.

### ✅ Ejemplos:

```bash
user_service.cc
user_service.h
math_utils.cc
```

> [!NOTE] 
> Los nombres deben ser específicos (evitar cosas como utils.h).

## 📐 4. Indentación y formato

- Usar 2 espacios por nivel.
- No usar tabs.
- Máximo recomendado: 80 caracteres por línea.
- Llaves `{}` en la misma línea.

### ✅ Ejemplo:

```cpp
if (is_valid) {
  ProcessData();
}
```

## 🧠 5. Reglas importantes de funciones

- Preferir return en lugar de parámetros de salida.
- Usar const cuando sea posible.

**Parámetros:**
- Entrada → valor o const&
- Salida → referencia
- Mantener funciones cortas (~40 líneas o menos).

## 🏗️ 6. Clases

* Orden recomendado:

```cpp
class MyClass {
 public:
  MyClass();
  void DoSomething();

 protected:

 private:
  int value_;
};
```

- public primero, luego protected, luego private.
- Variables privadas por defecto.

## 💬 7. Comentarios

- Explicar el por qué, no el qué.
- Preferir `//` en lugar de `/* */`.
- El código debe ser lo más autoexplicativo posible.

## 🚫 8. Buenas prácticas clave

- Evitar macros (#define) cuando sea posible.
- Preferir `const`, `enum` o funciones inline.
- Evitar `long double` salvo que sea estrictamente necesario.
- Escribir código portable (no dependiente de hardware).

> [!IMPORTANT]
> Una buena práctica es escribir el código en inglés  
> y la documentación en tu idioma nativo.

### 🧠 ¿Código en español o en inglés?

✅ Se puede usar español si:
- Es un proyecto académico
- Todo el equipo habla español

⚠️ Pero en la práctica profesional:
- Se usa inglés casi siempre
- Librerías, documentación y comunidad están en inglés
- Facilita colaborar con otros en proyectos Open Source

👉 Conclusión:
Puedes usar español para aprender, pero intenta acostumbrarte al inglés.

## 💻 9. Ejemplo completo

```cpp
#include <iostream>
#include <string>

// Calcula el precio total
int CalculateTotal(int price, int quantity) {
  return price * quantity;
}

// Verifica disponibilidad
bool IsAvailable(int stock) {
  return stock > 0;
}

class Product {
 public:
  Product(int price, int stock)
      : price_(price), stock_(stock) {}

  int GetPrice() const {
    return price_;
  }

  bool IsAvailable() const {
    return stock_ > 0;
  }

 private:
  int price_;
  int stock_;
};

int main() {
  Product product(10, 5);

  int total = CalculateTotal(product.GetPrice(), 3);

  if (product.IsAvailable()) {
    std::cout << "Total: " << total << std::endl;
  } else {
    std::cout << "No disponible" << std::endl;
  }

  return 0;
}
```
## 🔥 Conclusión rápida
- snake_case → variables
- PascalCase → funciones y tipos
- 2 espacios → indentación
- .cc / .h → archivos
- Consistencia > preferencias personales
- Código → Español
#pragma once

#include <string>
#include <vector>

#include "core/types.hpp"

namespace pulso::collectors {

/**
 * @brief Interfaz abstracta común para todos los recolectores de métricas.
 *
 * Cada categoría de métrica (CPU, memoria, disco, red) se implementa como
 * un collector distinto que hereda de esta interfaz. Esto permite al sampler
 * iterar sobre todos los collectors sin conocer sus detalles internos.
 */
class ICollector {
 public:
  /**
   * @brief Destructor virtual para permitir la destrucción polimórfica.
   */
  virtual ~ICollector() = default;

  /**
   * @brief Devuelve el nombre identificador del collector.
   *
   * Identifica el subsistema que gestiona este collector.
   * Ejemplos: "cpu", "memory", "disk", "network".
   *
   * @return Nombre del collector como cadena de texto.
   */
  virtual std::string nombre() const = 0;

  /**
   * @brief Ejecuta una medición y devuelve las métricas obtenidas.
   *
   * Cada implementación concreta debe capturar las métricas propias
   * de su subsistema y devolverlas como una colección de Metrica.
   *
   * @return Vector de pulso::core::Metrica con las métricas recolectadas.
   * @throws pulso::core::ErrorRecoleccion si la medición falla.
   */
  virtual std::vector<pulso::core::Metrica> recolectar() = 0;
};

}  // namespace pulso::collectors
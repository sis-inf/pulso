#pragma once

#include <string>
#include <vector>

#include "iformatter.hpp"

namespace pulso::formatters {

class FormatterPrometheus : public IFormatter {
public:
    std::string formato() const override;

    std::string contentType() const override;

    std::string formatear(
        const pulso::core::Snapshot& snapshot) const override;

    std::string formatearHistorial(
        const std::vector<pulso::core::Snapshot>& snapshots) const override;
};

} // namespace pulso::formatters
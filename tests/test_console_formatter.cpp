#include <gtest/gtest.h>

#include <sstream>
#include <map>
#include <string>
#include <iostream>

// Declaración de la función
void printMetrics(const std::map<std::string, double>& data);

TEST(ConsoleFormatterTest, OutputContainsMetrics) {
    std::map<std::string, double> data = {
        {"CPU", 25.5},
        {"RAM", 40.0}
    };

    std::ostringstream output;

    // Redirigir std::cout
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    // Llamar formateador con datos mock
    printMetrics(data);

    // Limpiar/restaurar stream
    std::cout.rdbuf(oldCout);

    std::string result = output.str();

    EXPECT_NE(result.find("CPU:"), std::string::npos);
    EXPECT_NE(result.find("RAM:"), std::string::npos);
}
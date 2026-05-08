#include <gtest/gtest.h>
#include "pulso/config.hpp"

/// @brief Verifica que MonitorConfig tiene valores por defecto correctos.
TEST(MonitorConfigTest, ValoresPorDefecto) {
    pulso::MonitorConfig config;
    ASSERT_EQ(config.interval_ms, 1000);
    ASSERT_TRUE(config.cpu);
    ASSERT_TRUE(config.ram);
    ASSERT_FALSE(config.disk);
}

#include <gtest/gtest.h>
#include "config/config.hpp"

namespace pulso::config {

TEST(ConfigSamplerTest, DefaultValues) {
    Config config;

    ASSERT_EQ(config.sampler.intervalo_segundos, 10);
    ASSERT_EQ(config.servidor.host,              "0.0.0.0");
    ASSERT_EQ(config.servidor.puerto,            8080);
    ASSERT_EQ(config.storage.ruta_db,            "pulso.db");
    ASSERT_EQ(config.nivel_log,                  "info");
}

} // namespace pulso::config
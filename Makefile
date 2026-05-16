# ==============================================================================
# Makefile simple — Issue #34
# Compilación sin CMake para entornos ligeros
# ==============================================================================

CXX     ?= g++
CXXFLAGS = -std=c++17 -Wall

SRC_DIR  = src
TEST_DIR = tests
BUILD_DIR = build

# Recopilar fuentes automáticamente
SRCS     = $(wildcard $(SRC_DIR)/*.cpp)
OBJS     = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test_%.o, $(TEST_SRCS))

TARGET      = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/run_tests

# ------------------------------------------------------------------------------
# Target por defecto
# ------------------------------------------------------------------------------
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar cada .cpp → .o solo si hubo cambios (regla implícita con prereqs)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------
# Directorio de build
# ------------------------------------------------------------------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ------------------------------------------------------------------------------
# Limpieza
# ------------------------------------------------------------------------------
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
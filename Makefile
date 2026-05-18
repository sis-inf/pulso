# Compilador y flags
CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2 -I/usr/include
LDFLAGS ?= -lSQLiteCpp -lsqlite3 -lpthread -ldl

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = .
TESTS_DIR = tests

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/collectors/*.cpp) \
          $(wildcard $(SRC_DIR)/collectors/cpu/*.cpp) \
          $(wildcard $(SRC_DIR)/collectors/disk/*.cpp) \
          $(wildcard $(SRC_DIR)/collectors/memory/*.cpp) \
          $(wildcard $(SRC_DIR)/collectors/network/*.cpp) \
          $(wildcard $(SRC_DIR)/config/*.cpp) \
          $(wildcard $(SRC_DIR)/formatters/*.cpp) \
          $(wildcard $(SRC_DIR)/storage/*.cpp) \
          $(wildcard $(SRC_DIR)/utils/*.cpp)

# Archivos objeto
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Nombre del ejecutable
TARGET = $(BIN_DIR)/pulso

# Archivos de prueba
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_TARGET = $(BIN_DIR)/run_tests

# Regla principal
all: $(TARGET)

# Crear directorio de build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/collectors
	mkdir -p $(BUILD_DIR)/collectors/cpu
	mkdir -p $(BUILD_DIR)/collectors/disk
	mkdir -p $(BUILD_DIR)/collectors/memory
	mkdir -p $(BUILD_DIR)/collectors/network
	mkdir -p $(BUILD_DIR)/config
	mkdir -p $(BUILD_DIR)/formatters
	mkdir -p $(BUILD_DIR)/storage
	mkdir -p $(BUILD_DIR)/utils

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linkear ejecutable principal
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compilar pruebas
$(TEST_TARGET): $(TEST_SOURCES) $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS)) -o $(TEST_TARGET)

# Ejecutar pruebas
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)

# Limpieza más agresiva
distclean: clean
	rm -rf $(BIN_DIR)/pulso
	rm -rf $(BIN_DIR)/run_tests

# Verificar compilación sin warnings
check:
	$(CXX) $(CXXFLAGS) -fsyntax-only $(SOURCES)

# Ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make         - Compilar pulso"
	@echo "  make test    - Compilar y ejecutar pruebas"
	@echo "  make clean   - Limpiar archivos objeto"
	@echo "  make check   - Verificar sintaxis sin warnings"
	@echo "  make help    - Mostrar esta ayuda"

# Declarar phony targets
.PHONY: all test clean distclean check help

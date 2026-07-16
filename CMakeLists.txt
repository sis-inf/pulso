cmake_minimum_required(VERSION 3.16)
project(pulso VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Criterio de aceptación: Desactivado (OFF) por defecto para compilaciones limpias
option(BUILD_TESTS "Build tests" OFF)
option(PULSO_BUILD_TESTS "Build tests (Legacy)" OFF)
option(BUILD_WITH_ASAN "Build tests with AddressSanitizer" OFF)
# Enlace estático: OFF por defecto para no cambiar el comportamiento estándar de build.
# Activar con -DPULSO_STATIC_LINK=ON para producir un binario standalone sin dependencias dinámicas.
option(PULSO_STATIC_LINK "Link statically against libgcc, libstdc++ and system libs" OFF)

if(PULSO_STATIC_LINK)
    target_link_options(pulso PRIVATE -static-libgcc -static-libstdc++)
endif()

# Si el usuario activa cualquiera de las dos opciones, sincronizamos el estado
if(BUILD_TESTS OR PULSO_BUILD_TESTS)
    set(BUILD_TESTS ON CACHE BOOL "Build tests" FORCE)
    set(PULSO_BUILD_TESTS ON CACHE BOOL "Build tests (Legacy)" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(cmake/Dependencies.cmake)
add_subdirectory(src)

# Los siguientes subdirectorios están vacíos o pendientes de implementación.
# Se comentan para evitar advertencias de CMake sobre directorios sin archivos fuente.
# Descomentar cuando se agreguen archivos fuente en cada directorio.
# add_subdirectory(src/collectors/disk)
# add_subdirectory(src/collectors/network)
# add_subdirectory(src/alertas)
# add_subdirectory(src/config)
# add_subdirectory(src/collectors/temperatura)   # pendiente: sin archivos fuente aún
# add_subdirectory(src/collectors/uptime)        # pendiente: sin archivos fuente aún

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
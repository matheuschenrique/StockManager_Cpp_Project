cmake_minimum_required(VERSION 3.12)
project(StockManager_Cpp_Project "CXX")

# Definir o diretório de saída dos arquivos binários
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set (CMAKE_CXX_STANDARD 14)

# Adicionar os arquivos de origem
set(SOURCES
    src/main.cpp
    src/product.cpp
    src/current_time.cpp
    src/menu.cpp
)

# Adicionar o executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Definir o diretório de inclusão
target_include_directories(${PROJECT_NAME} PUBLIC include)
cmake_minimum_required(VERSION 3.10)
project(3d_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raccogliere tutti i file sorgente
file(GLOB SOURCES "*.cpp")

# Creare l'eseguibile
add_executable(3d_engine ${SOURCES})

# Include directories
target_include_directories(3d_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Opzioni specifiche per piattaforme
if(APPLE)
    target_compile_options(3d_engine PRIVATE -Wall -Wextra)
    target_compile_options(3d_engine PRIVATE -stdlib=libc++)
    target_link_options(3d_engine PRIVATE -stdlib=libc++)
else()
    target_compile_options(3d_engine PRIVATE -Wall -Wextra)
endif()

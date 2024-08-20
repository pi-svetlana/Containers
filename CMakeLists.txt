cmake_minimum_required(VERSION 3.16.3)

project(Containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Werror -pedantic-errors -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wextra-semi -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo)

set(CMAKE_BUILD_TYPE Debug)


add_subdirectory(src)
# add_subdirectory(tests)

enable_testing()

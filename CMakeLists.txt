cmake_minimum_required(VERSION 3.16)

project(
    Cogsworth
    DESCRIPTION "Assembly code for DX8-based animated Cogsworth"
    HOMEPAGE_URL "https://github.com/hnkb/Cogsworth"
    LANGUAGES CXX ASM_MASM
)

add_subdirectory("third-party")
add_subdirectory("src")
add_subdirectory("src/cpp-blueprint")

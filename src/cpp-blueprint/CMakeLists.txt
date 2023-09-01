
add_executable(cogsworth-cpp WIN32
    "assets.rc"
    "scene.cpp"
    "main.cpp"
)

target_precompile_headers(cogsworth-cpp PRIVATE pch.h)
target_link_libraries(cogsworth-cpp PRIVATE dx8 Shlwapi legacy_stdio_definitions)
set_target_properties(cogsworth-cpp
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

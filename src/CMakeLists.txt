
add_executable(cogsworth WIN32
    "Assets.rc"
    "Cogsworth.asm"
)

target_link_libraries(cogsworth PRIVATE kernel32 user32 gdi32 advapi32 Shlwapi dx8 masm32)
set_target_properties(cogsworth
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LINKER_LANGUAGE ASM_MASM
)

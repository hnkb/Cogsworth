
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
add_custom_command(TARGET cogsworth POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:cogsworth> $<TARGET_RUNTIME_DLLS:cogsworth>
  COMMAND_EXPAND_LISTS
)

install(
    TARGETS
        cogsworth
    RUNTIME
        DESTINATION bin
)
install(
	FILES $<TARGET_RUNTIME_DLLS:cogsworth>
	TYPE BIN
)

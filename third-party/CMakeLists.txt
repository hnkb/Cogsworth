

add_library(dx8 INTERFACE)

target_include_directories(dx8
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/dx8/include
        ${CMAKE_CURRENT_SOURCE_DIR}/dx8/include-asm
)
target_link_directories(dx8 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/dx8/lib)
target_link_libraries(dx8 INTERFACE d3d8.lib d3dx8.lib)
target_link_options(dx8 INTERFACE "/SAFESEH:NO")



add_library(masm32 INTERFACE)

target_include_directories(masm32 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/masm32/include)
target_link_directories(masm32 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/masm32/lib)
target_link_libraries(masm32 INTERFACE msvcrt.lib)

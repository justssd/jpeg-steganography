add_compile_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fsanitize=memory)
    add_link_options(-fsanitize=memory)
endif()

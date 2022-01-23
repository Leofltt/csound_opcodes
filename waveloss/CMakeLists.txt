make_plugin(waveloss waveloss.cpp)
target_include_directories(waveloss PRIVATE
${CSOUND_INCLUDE_DIRS})

target_link_libraries(waveloss ${clang_libs})
target_compile_options(waveloss PRIVATE "-std=c++17")
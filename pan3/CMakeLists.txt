make_plugin(pan3 pan3.cpp)
target_include_directories(pan3 PRIVATE
${CSOUND_INCLUDE_DIRS})

target_link_libraries(pan3 ${clang_libs})
target_compile_options(pan3 PRIVATE "-std=c++17")
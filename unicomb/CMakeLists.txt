make_plugin(unicomb unicomb.cpp)
target_include_directories(unicomb PRIVATE
${CSOUND_INCLUDE_DIRS})

target_link_libraries(unicomb ${clang_libs})
target_compile_options(unicomb PRIVATE "-std=c++17")
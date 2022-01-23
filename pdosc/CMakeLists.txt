make_plugin(pdosc pdosc.cpp)
target_include_directories(pdosc PRIVATE
${CSOUND_INCLUDE_DIRS})

target_link_libraries(pdosc ${clang_libs})
target_compile_options(pdosc PRIVATE "-std=c++17")
make_plugin(wavefolder wavefolder.cpp)
target_include_directories(wavefolder PRIVATE
${CSOUND_INCLUDE_DIRS})

target_link_libraries(wavefolder ${clang_libs})
target_compile_options(wavefolder PRIVATE "-std=c++17")
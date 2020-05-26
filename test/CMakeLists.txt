set(SOURCES main_test.cpp rubik_engine.cpp rubik_engine.h)

add_executable(rubik_cube_test ${SOURCES})
target_link_libraries(rubik_cube_test rubik_engine CONAN_PKG::Catch2)
add_test(NAME rubik_cube_test COMMAND $<TARGET_FILE:rubik_cube_test>)

set(SOURCES main.cpp rubik_cube.h rubik_cube.cpp cubie.cpp cubie.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 3d_engine rubik_engine rubik_detector)

set(SOURCES rubik.h rubik.cpp cubie_data.cpp cubie_data.h face_data.cpp face_data.h)

add_library(rubik_engine ${SOURCES})
target_link_libraries(rubik_engine CONAN_PKG::glm)
target_include_directories(rubik_engine INTERFACE ..)

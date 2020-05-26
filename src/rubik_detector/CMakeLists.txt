set(SOURCES rubik_detector.h rubik_detector.cpp)

add_library(rubik_detector ${SOURCES})
target_link_libraries(rubik_detector CONAN_PKG::opencv)

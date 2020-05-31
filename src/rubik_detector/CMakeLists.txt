set(SOURCES rubik_detector.h rubik_detector.cpp custom_contour.cpp custom_contour.h utils.cpp utils.h viewer.cpp viewer.h)

add_library(rubik_detector ${SOURCES})
target_link_libraries(rubik_detector CONAN_PKG::opencv)

set(SOURCES
        rubik_detector.cpp
        rubik_detector.h

        custom_contour.cpp
        custom_contour.h

        utils.cpp
        utils.h

        viewer.cpp
        viewer.h

        image.cpp
        image.h

        vendor/imgui_impl_glfw.cpp
        vendor/imgui_impl_glfw.h

        vendor/imgui_impl_opengl3.cpp
        vendor/imgui_impl_opengl3.h)

add_library(rubik_detector ${SOURCES})
target_link_libraries(rubik_detector CONAN_PKG::opencv CONAN_PKG::glfw CONAN_PKG::glew CONAN_PKG::imgui CONAN_PKG::soil2 CONAN_PKG::nlohmann_json)

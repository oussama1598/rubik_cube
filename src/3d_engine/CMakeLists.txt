set(SOURCES core/window.h core/window.cpp core/engine.h core/engine.cpp renderer/camera.h renderer/camera.cpp core/scene.cpp core/scene.h renderer/shader.cpp renderer/shader.h renderer/object.cpp renderer/object.h renderer/vertex.h renderer/mesh.cpp renderer/mesh.h renderer/material.h primitives/plane.cpp primitives/plane.h core/mouse_controller.cpp core/mouse_controller.h events/mouse_moved.h core/keyboard_controller.cpp core/keyboard_controller.h)

add_library(3d_engine ${SOURCES})
target_link_libraries(3d_engine CONAN_PKG::glm CONAN_PKG::glew CONAN_PKG::glfw)
target_include_directories(3d_engine INTERFACE ..)

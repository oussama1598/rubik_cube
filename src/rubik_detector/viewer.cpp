#include "viewer.h"

Viewer::Viewer(std::map<std::string, bool> *windows_states) : _windows_states{windows_states} {
    glfwSetErrorCallback(_handle_errors);

    if (!glfwInit())
        std::runtime_error("Couldn't initialize glfw.");

    // configure glfw to use the OPENGL version 4.4 with the core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

    if (!_window) {
        std::runtime_error("Couldn't create a window.");
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::runtime_error("Couldn't initialize glew.");
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 440");
}

void Viewer::_build_gui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos({(float) (_width - 200), 0});
    ImGui::SetNextWindowSize({200, (float) _height});

    {
        ImGui::Begin(
                "Render options");

        if (ImGui::CollapsingHeader("Debug")) {
            ImGui::Checkbox("Output Image", &_windows_states->at("output"));
            ImGui::Checkbox("Gray Image", &_windows_states->at("gray"));
            ImGui::Checkbox("Filtered Image", &_windows_states->at("no_noise"));
            ImGui::Checkbox("Canny Image", &_windows_states->at("canny"));
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("OpenGL version supported by this platform: %s, %s",
                    glGetString(GL_VERSION), glGetString(GL_VENDOR));
        ImGui::End();
    }

    for (auto &image: _images) {
        std::pair<int, int> size = image.second->get_size();

//        ImGui::SetNextWindowSize(ImVec2(size.first, (float)(size.second + 35)));

        ImGui::Begin(image.first.c_str());
        ImGui::Image(image.second->get_id(), ImVec2(size.first, size.second));
        ImGui::End();
    }
}

void Viewer::_clear_gui() {
    for (auto &image: _images) {
        delete image.second;
    }

    _images.clear();
}

void Viewer::add_frame(const std::string &title, cv::Mat &frame) {
    _images.insert({title, new Image(frame)});
}

void Viewer::render() {
    glfwPollEvents();
    _build_gui();

    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    _clear_gui();

    glfwSwapBuffers(_window);
    glFlush();
}

void Viewer::_handle_errors(int, const char *description) {
    std::cout << "Error" << " " << description << std::endl;
}

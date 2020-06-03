#include "viewer.h"

Viewer::Viewer(std::map<std::string, bool> *windows_states,
               std::string *calibrate_color,
               std::map<std::string, int> *blur_settings,
               std::map<std::string, int> *canny_settings,
               std::map<std::string, int> *dilated_settings,
               std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> *color_ranges,
               std::unordered_map<char, std::array<std::string, 9>> *data,
               char *current_face,
               bool *save_settings,
               float *resize_ratio)
        : _windows_states(windows_states),
          _calibrate_color(calibrate_color),
          _blur_settings(blur_settings),
          _canny_settings(canny_settings),
          _dilated_settings(dilated_settings),
          _color_ranges(color_ranges),
          _data(data),
          _current_face(current_face),
          _save_settings(save_settings),
          _resize_ratio(resize_ratio) {
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

    {
        ImGui::Begin(
                "Render options");

        ImGui::Text("FPS: %.1f", 1000.0f / ImGui::GetIO().Framerate);

        if (ImGui::CollapsingHeader("Debug", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Checkbox("Output Image", &_windows_states->at("output"));
            ImGui::Checkbox("Gray Image", &_windows_states->at("gray"));
            ImGui::Checkbox("Filtered Image", &_windows_states->at("no_noise"));
            ImGui::Checkbox("Canny Image", &_windows_states->at("canny"));
            ImGui::Checkbox("Dilated Image", &_windows_states->at("dilated"));
        }

        if (ImGui::CollapsingHeader("Faces Data", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Indent();

            ImGui::Text("Current Face: %c", *_current_face);
            ImGui::Spacing();
            ImGui::Spacing();

            for (auto &face: *_data) {
                ImGui::Text("%c: ", face.first);

                bool is_done{true};

                for (auto &color: face.second) {
                    if (color.empty()) is_done = false;
                }

                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(!is_done, is_done, 0, 1));
                ImGui::Text("%s", is_done ? "Done" : "Not enough data");
                ImGui::PopStyleColor();
            }

            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Unindent();

            auto el = std::find(_faces.begin(), _faces.end(), *_current_face);
            int index = std::distance(_faces.data(), el);

            if (index >= 5) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }
            if (ImGui::Button("Save Current Face")) {
                *_current_face = _faces[index + 1];
            }
            if (index >= 5) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }


            ImGui::SameLine();

            if (ImGui::Button("Reset Current Face")) {
                _data->at(*_current_face) = {};
            }

            if (index == 0) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }
            if (ImGui::Button("Reset Previous Face")) {
                *_current_face = _faces[index - 1];
            }
            if (index == 0) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }

            ImGui::SameLine();

            if (ImGui::Button("Reset All")) {
                for (auto &color: *_data) {
                    _data->at(color.first) = {};
                }

                *_current_face = 'U';
            }
        }

        if (ImGui::CollapsingHeader("Calibrate", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (!_calibrate_color->empty()) ImGui::Text("Currently Recording Face colors ...");

            if (ImGui::BeginCombo("Color", _c_color.c_str())) {
                for (auto &color: *_color_ranges) {
                    bool is_selected = (color.first == _c_color);

                    if (ImGui::Selectable(color.first.c_str(), is_selected))
                        _c_color = color.first;

                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (_calibrate_color->empty() && ImGui::Button(
                    "Start Calibration")) {
                *_calibrate_color = _c_color;
            }

            if (!_calibrate_color->empty() && ImGui::Button("Stop Calibration")) {
                *_calibrate_color = "";
            }

        }

        if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("Image resize ratio");
            ImGui::InputFloat("s", _resize_ratio, .1f);

            *_resize_ratio = std::clamp(*_resize_ratio, .1f, 1.5f);

            if (ImGui::TreeNode("Gaussian Blur")) {
                ImGui::Text("Kernel Size x");
                ImGui::InputInt("kx", &_blur_settings->at("kernel_x"), 2);

                ImGui::Text("Kernel Size y");
                ImGui::InputInt("ky", &_blur_settings->at("kernel_y"), 2);

                ImGui::Text("Sigma x");
                ImGui::SliderInt("sx", &_blur_settings->at("sigma_x"), 1, 30);

                ImGui::Text("Sigma y");
                ImGui::SliderInt("sy", &_blur_settings->at("sigma_y"), 1, 30);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Canny")) {
                ImGui::Text("Threshold 1");
                ImGui::SliderInt("x", &_canny_settings->at("threshold1"), 1, 20);

                ImGui::Text("Threshold 2");
                ImGui::SliderInt("y", &_canny_settings->at("threshold2"), 1, 20);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Dilated")) {
                ImGui::Text("Kernel Size x");
                ImGui::SliderInt("x", &_dilated_settings->at("kernel_x"), 1, 10);

                ImGui::Text("Kernel Size y");
                ImGui::SliderInt("y", &_dilated_settings->at("kernel_y"), 1, 10);

                ImGui::Text("Iterations");
                ImGui::SliderInt("i", &_dilated_settings->at("iterations"), 1, 10);

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Color Ranges")) {
                for (auto &color: *_color_ranges) {
                    if (ImGui::TreeNode(color.first.c_str())) {
                        cv::Scalar from_color_cv = color.second.first;
                        ImVec4 from_color = ImVec4((float) from_color_cv[0] / 255,
                                                   (float) from_color_cv[1] / 255,
                                                   (float) from_color_cv[2] / 255,
                                                   1.f);

                        ImGui::Text("From");
                        ImGui::ColorEdit4("f", (float *) &from_color,
                                          ImGuiColorEditFlags__PickerMask);

                        color.second.first = cv::Scalar(from_color.x * 255, from_color.y * 255,
                                                        from_color.z * 255);

                        cv::Scalar to_color_cv = color.second.second;
                        ImVec4 to_color = ImVec4((float) to_color_cv[0] / 255,
                                                 (float) to_color_cv[1] / 255,
                                                 (float) to_color_cv[2] / 255, 1.f);

                        ImGui::Text("To");
                        ImGui::ColorEdit4("t", (float *) &to_color);

                        color.second.second = cv::Scalar(to_color.x * 255, to_color.y * 255,
                                                         to_color.z * 255);

                        ImGui::TreePop();
                    }
                }

                ImGui::TreePop();
            }
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Save Settings")) {
            *_save_settings = true;

            ImGui::Text("Settings Saved.");
        } else {
            *_save_settings = false;
        }

        ImGui::End();
    }

    for (auto &image: _images) {
        std::pair<int, int> size = image.second->get_size();

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

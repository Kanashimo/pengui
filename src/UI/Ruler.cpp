#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <imgui.h>
#include <string>
#include <algorithm>

#include "src/UI/Ruler.h"
#include "src/Application.h"
#include "src/Config/Config.h"
#include "src/ScreenCapture/ScreenCapture.h"
#include "src/UI/Toolbar.h"

namespace UI {

    void Ruler::on_update(Instance &instance)
    {
        if (Application::application().module<Toolbar>()->get_current_option() != OPTION_RULER) return;

        pos = ImGui::GetMousePos();

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !dragging && !ImGui::GetIO().WantCaptureMouse)
        {
            dragging = true;
            start_pos = pos;
            glfwSetInputMode(instance.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            Application::application().module<Toolbar>()->set_busy(true);
            current_window = instance.window;
        }

        if (dragging && instance.window == current_window)
        {
            process_alignment();

            auto width = Application::application().module<Config::Config>()->get().ruler.border.width;
            auto color = Application::application().module<Config::Config>()->get().ruler.border.color;

            ImGui::GetForegroundDrawList()->AddLine(start_pos, pos, IM_COL32(color.r, color.g, color.b, 255), width);
            ImGui::GetForegroundDrawList()->AddCircleFilled(start_pos, width / 2.0f, IM_COL32(color.r, color.g, color.b, 255));
            ImGui::GetForegroundDrawList()->AddCircleFilled(pos, width / 2.0f, IM_COL32(color.r, color.g, color.b, 255));

            int dist = static_cast<int>(std::hypot(pos.x - start_pos.x, pos.y - start_pos.y)) + 1;
            std::string dist_text = std::to_string(dist) + "px";
            draw_box(dist_text);
        }

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && dragging)
        {
            dragging = false;
            Application::application().module<Toolbar>()->set_busy(false);
            current_window = nullptr;
        }
    }

    void Ruler::process_alignment()
    {
        if (!ImGui::IsKeyDown(ImGuiKey_LeftShift)) return;

        const Monitor *monitor = Application::application().get_active_instance()->monitor;

        constexpr float pi = 3.14159265359f;
        constexpr float snap = pi / 4.0f;

        ImVec2 dist = ImVec2(
            pos.x - start_pos.x,
            pos.y - start_pos.y
        );

        float len = std::hypot(dist.x, dist.y);

        if (len < 15.0f) return;

        float angle = std::atan2(dist.y, dist.x);
        float result = std::round(angle / snap) * snap;

        ImVec2 dist_final = ImVec2(
            std::cos(result),
            std::sin(result)
        );

        float max_len = len;

        if (dist_final.x > 0.0f) {
            max_len = std::min(max_len, (monitor->width - start_pos.x) / dist_final.x);
        } else if (dist_final.x < 0.0f) {
            max_len = std::min(max_len, (0.0f - start_pos.x) / dist_final.x);
        }

        if (dist_final.y > 0.0f) {
            max_len = std::min(max_len, (monitor->height - start_pos.y) / dist_final.y);
        } else if (dist_final.y < 0.0f) {
            max_len = std::min(max_len, (0.0f - start_pos.y) / dist_final.y);
        }

        max_len = std::max(0.0f, max_len);

        pos = ImVec2(
            start_pos.x + dist_final.x * max_len,
            start_pos.y + dist_final.y * max_len
        );

    }

    void Ruler::draw_box(std::string text)
    {
        const Monitor *monitor = Application::application().get_active_instance()->monitor;
        ImVec2 size = ImGui::CalcTextSize(text.c_str());

        int padding = 10;
        ImVec2 padding_pos = ImVec2(pos.x + padding, pos.y + padding);
        ImVec2 padding_size = ImVec2(size.x + padding, size.y + padding);

        float x = std::clamp(padding_pos.x, 0.0f, (float)monitor->width - padding_size.x);
        float y = std::clamp(padding_pos.y, 0.0f, (float)monitor->height - padding_size.y);

        ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + size.x, y + size.y), IM_COL32(15, 15, 15, 150));
        ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), IM_COL32(255, 255, 255, 255), text.c_str());
    }
}

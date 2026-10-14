#include <GLFW/glfw3.h>
#include <imgui.h>
#include <string>

#include "src/Module.h"

namespace UI {

    class Ruler : public Module
    {
        public:
            void on_update(Instance &instance) override;

        private:
            ImVec2 pos;
            ImVec2 start_pos;
            bool dragging;
            GLFWwindow *current_window;

            void process_alignment();
            void draw_box(std::string text);
    };
}

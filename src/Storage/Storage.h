#pragma once

#include <filesystem>
#include <glib.h>

#include "src/Module.h"
#include "src/ScreenCapture/ScreenCapture.h"

namespace Storage {

    class Storage : public Module
    {
        public:
            ~Storage();
            std::filesystem::path save_image(const Monitor &m, int x, int y, int w, int h);

        private:
            GdkPixbuf *pixbuf = nullptr;
            GdkPixbuf *cropped = nullptr;
            GError *error = nullptr;

            std::filesystem::path screenshot_path();
    };

}

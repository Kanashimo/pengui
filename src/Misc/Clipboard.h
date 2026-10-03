#include "src/Module.h"
#include "glib.h"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace Misc {

    class Clipboard : public Module
    {
        public:
            void copy_text(std::string text)
            {
                std::string cmd;

                if (getenv("WAYLAND_DISPLAY")) {
                    cmd = "wl-copy";
                } else if (getenv("DISPLAY")) {
                    cmd = "xclip -selection clipboard";
                } else {
                    throw std::runtime_error("Cannot get wl-copy/xclip");
                }

                FILE* pipe = popen(cmd.c_str(), "w");

                if (!pipe)
                {
                    throw std::runtime_error("Cannot get wl-copy/xclip");
                }

                fwrite(text.data(), 1, text.size(), pipe);
                pclose(pipe);
            }

            void copy_image(guchar *framebuffer)
            {

            }

    };

}

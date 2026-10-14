#include "src/Module.h"
#include "glib.h"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace Clipboard {

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

                size_t write = fwrite(text.data(), 1, text.size(), pipe);
                int status = pclose(pipe);

                if (write != text.size()) throw std::runtime_error("Failet to write clipboard");
                if (status == -1) throw std::runtime_error("Something went wrong with clipboard, check if wl-copy or xclip is installed");
                if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) throw std::runtime_error("Something went wrong with clipboard, check if wl-copy or xclip is installed");
            }

            void copy_image(guchar *framebuffer)
            {

            }

    };

}

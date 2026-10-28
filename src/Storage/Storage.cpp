#include <chrono>
#include <filesystem>
#include <stdexcept>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib-object.h>
#include <glib.h>

#include "Storage.h"
#include "src/ScreenCapture/ScreenCapture.h"
#include "src/Application.h"
#include "src/Config/Config.h"

namespace Storage {

    std::filesystem::path Storage::save_image(const Monitor &monitor, int x, int y, int w, int h)
    {
        pixbuf = gdk_pixbuf_new_from_data(
            monitor.framebuffer,
            GDK_COLORSPACE_RGB,
            monitor.alpha,
            8,
            monitor.width,
            monitor.height,
            monitor.stride,
            nullptr,
            nullptr
        );

        cropped = gdk_pixbuf_new_subpixbuf(pixbuf, x, y, w, h);

        auto image_path = screenshot_path();

        if (!gdk_pixbuf_save(cropped, image_path.c_str(), "png", &error, NULL))
        {
            throw std::runtime_error("An error occurred while trying to save the screenshot: " + std::string(error->message));
        }

        g_clear_object(&cropped);
        g_clear_object(&pixbuf);

        return image_path;
    }

    std::filesystem::path Storage::screenshot_path()
    {
        auto config = Application::application().module<Config::Config>()->get();
        std::filesystem::create_directories(config.screenshot.save_location);

        auto now = std::chrono::system_clock::now();
        auto local_time = floor<std::chrono::seconds>(std::chrono::current_zone()->to_local(now));
        auto filename = std::format("screenshot_{:%Y%m%d_%H%M%S}.png", local_time);
        auto image_path = config.screenshot.save_location / filename;

        return image_path;
    }

    Storage::~Storage()
    {
        g_clear_error(&error);
        g_clear_object(&cropped);
        g_clear_object(&pixbuf);
    }

}

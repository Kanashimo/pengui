#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <toml++/toml.hpp>

#include "src/Config/Config.h"

namespace Config {

    Config::Config()
    {
        const char* xdg = std::getenv("XDG_CONFIG_HOME");
        const char* home = std::getenv("HOME");

        if (xdg && *xdg) {
            config_dir = std::filesystem::path(xdg) / "pengui";
        } else if (home && *home) {
            config_dir = std::filesystem::path(xdg) / ".config" / "pengui";
        } else {
            throw std::runtime_error("Could not initialize config, check if XDG_CONFIG_HOME or HOME is set");
        }

        std::filesystem::create_directories(config_dir);

        config_path = config_dir / "config.toml";

        std::ofstream cfg(config_path, std::ios::app);
        cfg.close();

        config.screenshot.save_location = default_save_location();

        auto toml = toml::parse_file(config_path.string());

        if (auto value = toml["screenshot"]["save_location"].value<std::string>())
            config.screenshot.save_location = *value;

        if (auto value = toml["crop"]["glow"]["enabled"].value<decltype(config.crop.glow.enabled)>())
            config.crop.glow.enabled = *value;

        if (auto arr = toml["crop"]["glow"]["color"].as_array())
            if (arr->size() == 3)
            {
                auto r = (*arr)[0].value<unsigned int>();
                auto g = (*arr)[1].value<unsigned int>();
                auto b = (*arr)[2].value<unsigned int>();

                if (r && g && b)
                {
                    unsigned int min = 0;
                    unsigned int max = 255;

                    unsigned int R = std::clamp(*r, min, max);
                    unsigned int G = std::clamp(*g, min, max);
                    unsigned int B = std::clamp(*b, min, max);

                    config.crop.glow.color = {R, G, B};
                }
            }

        if (auto value = toml["crop"]["border"]["width"].value<decltype(config.crop.border.width)>())
            config.crop.border.width = *value;

        if (auto arr = toml["crop"]["border"]["color"].as_array())
            if (arr->size() == 3)
            {
                auto r = (*arr)[0].value<unsigned int>();
                auto g = (*arr)[1].value<unsigned int>();
                auto b = (*arr)[2].value<unsigned int>();

                if (r && g && b)
                {
                    unsigned int min = 0;
                    unsigned int max = 255;

                    unsigned int R = std::clamp(*r, min, max);
                    unsigned int G = std::clamp(*g, min, max);
                    unsigned int B = std::clamp(*b, min, max);

                    config.crop.border.color = {R, G, B};
                }
            }

        if (auto value = toml["ruler"]["border"]["width"].value<decltype(config.ruler.border.width)>())
            config.ruler.border.width = *value;

        if (auto arr = toml["ruler"]["border"]["color"].as_array())
            if (arr->size() == 3)
            {
                auto r = (*arr)[0].value<unsigned int>();
                auto g = (*arr)[1].value<unsigned int>();
                auto b = (*arr)[2].value<unsigned int>();

                if (r && g && b)
                {
                    unsigned int R = std::clamp(*r, 0u, 255u);
                    unsigned int G = std::clamp(*g, 0u, 255u);
                    unsigned int B = std::clamp(*b, 0u, 255u);

                    config.ruler.border.color = {R, G, B};
                }
            }
    }

    void Config::save_config()
    {
        toml::table toml;

        toml::table screenshot;
        screenshot.insert("save_location", config.screenshot.save_location.string());
        toml.insert("screenshot", std::move(screenshot));

        toml::table glow;
        glow.insert("enabled", config.crop.glow.enabled);
        glow.insert("color", toml::array{
            config.crop.glow.color.r,
            config.crop.glow.color.g,
            config.crop.glow.color.b,
        });

        toml::table crop_border;
        crop_border.insert("width", config.crop.border.width);
        crop_border.insert("color", toml::array{
            config.crop.border.color.r,
            config.crop.border.color.g,
            config.crop.border.color.b,
        });

        toml::table crop;
        crop.insert("glow", std::move(glow));
        crop.insert("border", std::move(crop_border));
        toml.insert("crop", std::move(crop));

        toml::table ruler_border;
        ruler_border.insert("width", config.ruler.border.width);
        ruler_border.insert("color", toml::array{
            config.ruler.border.color.r,
            config.ruler.border.color.g,
            config.ruler.border.color.b,
        });

        toml::table ruler;
        ruler.insert("border", std::move(ruler_border));
        toml.insert("ruler", std::move(ruler));

        std::ofstream cfg(config_path);

        if (!cfg)
        {
            throw std::runtime_error("Cannot save config file");
        }

        cfg << toml;
        cfg << "\n";
    }

    std::filesystem::path Config::default_save_location()
    {
        char buffer[256];
        FILE* pipe = popen("xdg-user-dir PICTURES", "r");

        if (!pipe)
        {
            throw std::runtime_error("Failed to open xdg-user-dir");
        }

        if (!fgets(buffer, sizeof(buffer), pipe))
        {
            pclose(pipe);
            throw std::runtime_error("Failed to read xdg-user-dir");
        }

        int status = pclose(pipe);

        if (status == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0)
        {
            throw std::runtime_error("xdg-user-dir exited with an error");
        }

        std::string path(buffer);

        if (!path.empty() && path.back() == '\n')
        {
            path.pop_back();
        }

        if (path.empty() || path == "")
        {
            throw std::runtime_error("xdg-user-dir returned an empty path");
        }

        return std::filesystem::path(path) / "PenguiScreenshots";
    }

    Config::~Config()
    {
        save_config();
    }

}

#pragma once

#include <filesystem>
#include <toml++/toml.hpp>

#include "src/Module.h"

namespace Config {

    struct PenguiConfigRGBColor
    {
        unsigned int r = 255;
        unsigned int g = 255;
        unsigned int b = 255;
    };

    struct PenguiConfig
    {
        struct Screenshot {
            std::filesystem::path save_location;
        } screenshot;

        struct Crop {
            struct Glow {
                bool enabled = false;
                PenguiConfigRGBColor color = {90, 200, 255};
            } glow;

            struct Border {
                float width = 2.0f;
                PenguiConfigRGBColor color = {90, 200, 255};
            } border;
        } crop;

        struct Ruler {
            struct Border {
                float width = 5.0f;
                PenguiConfigRGBColor color = {90, 200, 255};
            } border;
        } ruler;
    };

    class Config : public Module
    {
        public:
            Config();
            ~Config();

            PenguiConfig &get()
            {
                return config;
            }

            const PenguiConfig &get() const
            {
                return config;
            }

            void save_config();

        private:
            PenguiConfig config;

            std::filesystem::path config_dir;
            std::filesystem::path config_path;

            std::filesystem::path default_save_location();

    };

}

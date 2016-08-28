#pragma once

namespace jeti
{

struct Config
{
    public:
        int width = 800;
        int height = 600;
        int bpp = 32;
        int fps_limit = 60;
        bool vsync = 0;

        Config();
        ~Config();
};

}

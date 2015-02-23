#pragma once

namespace jeti
{

struct Config
{
    public:
        int width;
        int height;
        int bpp;
        int fps_limit;
        bool vsync;

        Config();
        ~Config();
};

}

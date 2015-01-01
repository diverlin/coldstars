#pragma once

namespace jeti
{

struct Video {
        int width;
        int height;
        int bpp;
        int fps_limit;
        bool vsync;

        Video()
            :
            width(800),
            height(600),
            bpp(32),
            fps_limit(60),
            vsync(true)
        {}
};

struct ConfigV
{
    public:
        static ConfigV& instance();
        Video& video() { return m_video; }

    private:
        ConfigV();
        ConfigV(const ConfigV&) = delete;
        ~ConfigV();
        ConfigV& operator=(const ConfigV&) = delete;

        Video m_video;
};

}

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

struct Config
{
    public:
        static Config& instance();
        Video& video() { return m_video; }

    private:
        Config();
        Config(const Config&) = delete;
        ~Config();
        Config& operator=(const Config&) = delete;

        Video m_video;
};

}

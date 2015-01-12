#pragma once

#include <SFML/Graphics.hpp>
#include <meti/VectorUtils.hpp>

#include <MyGl.hpp>
//#include <FreeType.h>

namespace jeti {

class SFMLWrapper
{
    public:
        SFMLWrapper();
        ~SFMLWrapper();

        void wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, int fps_limit, const std::string& title);

        int GetWidth() const { return window.getSize().x; };
        int GetHeight() const { return window.getSize().y; };

        sf::Font& GetFont() { return font; };
        sf::RenderWindow& GetWindow() { return window; };

        float GetElapsedTimeInSeconds() { return clock.getElapsedTime().asSeconds(); };

        void wrResizeSpecific(int width, int height);

        void wrDrawSpecific();

        void DrawText(const std::string& str, int font_size, const glm::vec2& pos);
        void DrawText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color);

    private:
        int bpp;
        bool vert_sync;

        //freetype::font_data ftfont;

        sf::Text text12;
        sf::Clock clock;
        sf::Font font;
        sf::View view;
        sf::RenderWindow window;
};

}

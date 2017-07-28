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

    void wrCreateWindowSpecific(int width, int height, int m_bpp, bool m_vsync, int fps_limit, const std::string& title);

    int width() const { return m_window.getSize().x; }
    int height() const { return m_window.getSize().y; }

    sf::Font& font() { return m_font; }
    sf::RenderWindow& window() { return m_window; }

    float elapsedSeconds() { return m_clock.getElapsedTime().asSeconds(); }

    void wrResizeSpecific(int width, int height);

    void wrDrawSpecific();

    void drawText(const std::string& str, int font_size, const glm::vec2& pos);
    void drawText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color);

private:
    int m_bpp = 32;
    bool m_vsync = false;

    //freetype::font_data ftfont;

    sf::Text m_text12;
    sf::Clock m_clock;
    sf::Font m_font;
    sf::View m_view;
    sf::RenderWindow m_window;
};

}


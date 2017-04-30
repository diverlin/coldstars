/*
    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#pragma once

#include "SFMLWrapper.hpp"

#include <MyGl.hpp>

#include <meti/VectorUtils.hpp>
#include <ceti/rect.hpp>

namespace jeti {

class Screen : public SFMLWrapper
{
    const float SCALE_MIN = 0.2;
    const float SCALE_MAX = 50.0;
    const float SCALE_STEP = 0.05;

public:
    class Data {
    public:
        int width = 0;
        int height = 0;
        int radius = 0;
        glm::vec3 worldcoolds;
        float scale = 1.0f;
        Data() = default;
       ~Data() = default;
        void resize(int w, int h) {
            width = w;
            height = h;
            radius = std::sqrt(w*w + h*h);
        }
        float scaledRadius() const { return radius / scale; }
    };

    Screen();
    ~Screen();

    void init();

    const ceti::Rect& rect() const { return m_rect; }

    void setBottomLeftScreenWC(const glm::vec2& bl)    { m_rect.SetBottomLeft(bl); }

    glm::vec2 bottomLeftScreenWC()    { return m_rect.GetBottomLeft(); }
    glm::vec2 topRightScreenWC()    { return (m_rect.GetBottomLeft()+glm::vec2(m_rect.width()*m_data.scale, m_rect.height()*m_data.scale)); }

    const glm::vec2& bottomLeft() const    { return m_rect.GetBottomLeft(); }
    const glm::vec2& topRight()    const    { return m_rect.GetTopRight(); }

    void move(const glm::vec2&);
    void initiateScrollTo(const glm::vec2& scroll_coord) { m_targetCenter = scroll_coord; m_autoScroll = true; };
    void updateInSpace();

    void resize(int, int);
    void draw();

    int framesCounter() const { return m_framesCounter; }

    float scale() const { return m_data.scale; }
    void increaseScale();
    void decreaseScale();

private:
    Data m_data;
    bool m_autoScroll;

    int m_fps = 0;
    int m_framesCounter = 0;
    float m_lastTime = 0;

    float m_deltaScale = 0.0;
    ceti::Rect m_rect;
    glm::vec2 m_targetCenter;

    void __drawFps();
};

} // namespace jeti


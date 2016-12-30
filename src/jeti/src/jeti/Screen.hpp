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
public:
    Screen();
    ~Screen();

    void init();

    const ceti::Rect& rect() const { return m_rect; }
    //glm::vec2 GetBottomLeftScreenWC()    { return m_rect.GetBottomLeft()*scale; }
    //glm::vec2 GetTopRightScreenWC()    { return m_rect.GetTopRight()*scale; }

    void setBottomLeftScreenWC(const glm::vec2& bl)    { m_rect.SetBottomLeft(bl); }

    glm::vec2 bottomLeftScreenWC()    { return m_rect.GetBottomLeft(); }
    glm::vec2 topRightScreenWC()    { return (m_rect.GetBottomLeft()+glm::vec2(m_rect.GetWidth()*m_scale, m_rect.GetHeight()*m_scale)); }

    const glm::vec2& bottomLeft() const    { return m_rect.GetBottomLeft(); }
    const glm::vec2& topRight()    const    { return m_rect.GetTopRight(); }

    void move(const glm::vec2&);
    void initiateScrollTo(const glm::vec2& scroll_coord) { m_targetCenter = scroll_coord; m_autoScroll = true; };
    void updateInSpace();

    void resize(int, int);
    void draw();

    int framesCounter() const { return m_framesCounter; }

    float scale() const { return m_scale; }
    void increaseScale();
    void decreaseScale();

private:
    bool m_autoScroll;

    int m_fps;
    int m_framesCounter;
    float m_lastTime;

    float m_scale;
    float m_deltaScale;
    ceti::Rect m_rect;
    glm::vec2 m_targetCenter;

    void __drawFps();
};

} // namespace jeti


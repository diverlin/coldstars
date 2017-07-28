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
    class Data {
    public:
        ceti::Rect rect;
        int radius = 0;
        Data() = default;
       ~Data() = default;
        void resize(int w, int h) {
            rect.setSize(w, h);
            radius = std::sqrt(w*w + h*h);
        }
    };

    Screen() = default;
    ~Screen() = default;

    void init();

    void initiateScrollTo(const glm::vec2& scroll_coord) { m_targetCenter = scroll_coord; m_autoScroll = true; }
    void updateInSpace();

    void resize(int, int);
    void draw();

    int framesCounter() const { return m_framesCounter; }

    const Data& data() const { return m_data; }

    int fps() const { return m_fps; }

    void setPosition(const glm::vec2& position) { m_data.rect.setBottomLeft(position); }
    const glm::vec2& position() const { return m_data.rect.bottomLeft(); }

private:
    Data m_data;
    bool m_autoScroll;

    int m_fps = 0;
    int m_framesCounter = 0;
    float m_lastTime = 0;

    float m_deltaScale = 0.0;
    glm::vec2 m_targetCenter;

    void __drawFps();
};

} // namespace jeti


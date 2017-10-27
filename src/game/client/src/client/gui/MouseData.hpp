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

#include <glm/glm.hpp>

class MouseData
{
public:
    enum class Event: int { None, LeftButtonPress, LeftButtonRelease, RightButtonPress, RightButtonRelease };

    MouseData()=default;
    ~MouseData()=default;

    void reset() {
        m_screenCoord = glm::vec3(0.0f);
        m_worldCoord = glm::vec3(0.0f);

        m_event = Event::None;
    }

    void setScreenCoord(const glm::vec3& coord) { m_screenCoord = coord; }
    void setWorldCoord(const glm::vec3& coord) { m_worldCoord = coord; }

    void setEvent(const Event& event) { m_event = event; }

    const glm::vec3& screenCoord() const { return m_screenCoord; }
    const glm::vec3& worldCoord() const { return m_worldCoord; }

    const Event& event() const { return m_event; }

private:
    glm::vec3 m_screenCoord;
    glm::vec3 m_worldCoord;

    Event m_event = Event::None;
};



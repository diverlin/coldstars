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

namespace client {
class Player;
} // naemspace client

namespace gui {

class UserInputInSpace
{
public:
    UserInputInSpace();
    ~UserInputInSpace();

    bool nextTurnReady() const { return m_nextTurnReady; }
    bool runSession() const { return m_runSession; }

    void update(client::Player*);

    const glm::vec3& scrollAccel() const { return m_scrollAccel; }
    const glm::vec3& mouseCliclPos() const { return m_scrollAccel; }

private:
    bool m_nextTurnReady = false;
    bool m_runSession = true;

    float m_scrollStep = 0.0;
    glm::vec3 m_scrollAccel;
    glm::vec3 m_mouseClickPos;

    void __reset(client::Player*);
    
    void __manageInputsInSpace(client::Player*);

    void __mouseButtonPressed(client::Player*);

    void __manageRealTimeInputsInSpace(client::Player*);
};

} // namespace gui

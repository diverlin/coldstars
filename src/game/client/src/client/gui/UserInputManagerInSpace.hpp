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

class Player;

class UserInputInSpace
{
public:
    UserInputInSpace();
    ~UserInputInSpace();

    bool nextTurnReady() const { return m_nextTurnReady; }
    bool runSession() const { return m_runSession; }

    void update(Player*);

    const glm::vec3& scrollAccel() const { return m_scrollAccel; }

private:
    bool m_nextTurnReady = false;
    bool m_runSession = true;

    float m_scrollStep = 0.0;
    glm::vec3 m_scrollAccel;

    void __reset();
    
    void __manageInputsInSpace(Player*);

    void __mouseButtonPressed(Player*);

    void __manageRealTimeInputsInSpace(Player*);
};



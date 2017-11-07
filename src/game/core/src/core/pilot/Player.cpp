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


#include "Player.hpp"

#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

namespace core {

Player::Player(int_t id)
    : m_id(id)
{ 
}
    
Player::~Player()
{}  

place::Type
Player::place() const
{
    return m_npc->vehicle()->place();
}

const meti::vec3&
Player::position() const {
    assert(m_npc);
    assert(m_npc->vehicle());
    return m_npc->vehicle()->position();
}


float
Player::radius() const {
    assert(m_npc);
    assert(m_npc->vehicle());
    return m_npc->vehicle()->properties().radar;
}

} // namespace core

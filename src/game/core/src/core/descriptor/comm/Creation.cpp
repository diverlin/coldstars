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

#include "Creation.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace comm {

// BulletShoot
CreateBullet::CreateBullet(int_t owner, int_t item, int_t target)
    :
    m_owner(owner)
  , m_item(item)
  , m_target(target)
{}

CreateBullet::CreateBullet(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
CreateBullet::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}
//


namespace effect {

Explosion::Explosion(float size, const glm::vec3& position)
    :
      m_size(size)
    , m_position(position)
{
}

Explosion::Explosion(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Explosion::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace effect

//////////////////////

Object::Object(int_t object)
    :
      m_object(object)
{
}

Object::Object(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Object::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}


//////////////////////


CreatePlayer::CreatePlayer(int_t player, int_t npc)
    :
      m_player(player)
    , m_npc(npc)
{
}

CreatePlayer::CreatePlayer(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
CreatePlayer::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

////////////////////////
/// \brief CreateGoodsPack::CreateGoodsPack
/// \param object
/// \param descriptor
/// \param mass
///
CreateGoodsPack::CreateGoodsPack(int_t descriptor, int_t object, int mass)
    :
      Creation(descriptor, object)
    , m_mass(mass)
{
}

CreateGoodsPack::CreateGoodsPack(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
CreateGoodsPack::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}


//////////////////////////

CreateContainer::CreateContainer(int_t descriptor, int_t object, int_t item)
    :
      Creation(descriptor, object)
    , m_item(item)
{
}

CreateContainer::CreateContainer(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
CreateContainer::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

////////////////////////////////////////
StarSystemTransition::StarSystemTransition(int_t object, int_t starsystem)
    :
      m_object(object)
    , m_starsystem(starsystem)
{
}

StarSystemTransition::StarSystemTransition(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
StarSystemTransition::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace comm
} // namespace descriptor


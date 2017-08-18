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

Explosion::Explosion(int size, const glm::vec3& position)
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


Creation::Creation(int_t obId, int_t obDescriptor)
    :
      m_object(obId)
    , m_descriptor(obDescriptor)
{
}

Creation::Creation(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Creation::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

////////////////////////

CreateMineral::CreateMineral(int_t obId, int_t obDescriptor, int mass)
    :
      Creation(obId, obDescriptor)
    , m_mass(mass)
{
}

CreateMineral::CreateMineral(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
CreateMineral::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}


} // namespace comm
} // namespace descriptor


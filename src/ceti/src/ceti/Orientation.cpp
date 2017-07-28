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

#include "Orientation.hpp"
#include <ceti/serialization/macro.hpp>

namespace ceti {

namespace model {

Orientation::Orientation(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Orientation::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace model

namespace control {

Orientation::Orientation(model::Orientation* model)
    :
      m_model_orientation(model)
{
    __updateCollisionRadius();
}

/* virtual */
Orientation::~Orientation()
{
    //    LOG("___::~Orientation("+std::to_string(id())+")");
}

void Orientation::setPosition(float x, float y, float z) {
    model()->setPosition(meti::vec3(x, y, z));
    m_isUpdated = false;
}

void Orientation::setPosition(const meti::vec3& position) {
    model()->setPosition(position);
    m_isUpdated = false;
}

void Orientation::setPosition(const Position& position)   {
    model()->setPosition(position.center);
    model()->setDirection(position.direction);
    m_isUpdated = false;
}

void Orientation::setSize(float x, float y, float z) {
    setSize(meti::vec3(x, y, z));
}

void Orientation::setSize(const meti::vec3& size) {
    model()->setSize(size);

    __updateCollisionRadius();
    m_isUpdated = false;
}

void Orientation::__updateCollisionRadius() {
    m_collisionRadius = (model()->size().x + model()->size().y) / 2.0f;
}

} // namespace control

} // namespace ceti

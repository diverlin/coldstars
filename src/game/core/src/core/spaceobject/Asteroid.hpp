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

#include <core/spaceobject/Planetoid.hpp>

#include <core/descriptor/spaceobject/Asteroid.hpp>

namespace model {
class Asteroid;
} // namespace model

namespace core {
namespace control {

class Asteroid : public Planetoid
{
public:
    Asteroid(AsteroidDescr*, model::Asteroid*);
    virtual ~Asteroid();

    int damage() const { return mass()*10; }

    void updateInSpace(int);
    void collisionEvent();

    AsteroidDescr* descriptor() const { return m_descriptor_asteroid; }
    model::Asteroid* model() const { return m_model_asteroid; }

private:
    void _postDeathUniqueEvent(bool);

    AsteroidDescr* m_descriptor_asteroid = nullptr;
    model::Asteroid* m_model_asteroid = nullptr;
};

} // namespace control
} // namespace core


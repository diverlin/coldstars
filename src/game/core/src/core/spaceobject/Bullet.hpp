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

#include <core/spaceobject/SpaceObject.hpp>

namespace descriptor {
class Bullet;
} // namespace descriptor

namespace model {
class Bullet;
} // namespace model

namespace control {

class Bullet : public SpaceObject
{
public:
    Bullet(descriptor::Bullet*, model::Bullet*);
    virtual ~Bullet();

    void update(int);

    bool collideable() const { return true; }
    void collisionEvent();

    void setTarget(SpaceObject* target) { m_target = target; }

    void hit(int, SpaceObject* agresor = nullptr) override final;
    void _postDeathUniqueEvent(bool) override final;

    int damage() const;

    descriptor::Bullet* descriptor() const { return m_descriptor_rocket; }
    model::Bullet* model() const { return m_model_rocket; }

private:
    descriptor::Bullet* m_descriptor_rocket = nullptr;
    model::Bullet* m_model_rocket = nullptr;

    control::SpaceObject* m_target = nullptr;

    bool __checkTarget() const;
};

} // namespace control


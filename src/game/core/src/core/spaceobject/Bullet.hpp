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

namespace core {
class BulletDescr;
} // namespace core

namespace core {
class BulletModel;
} // namespace core

namespace core {
namespace control {

class Bullet : public SpaceObject
{
public:
    Bullet(BulletDescr*, BulletModel*);
    virtual ~Bullet();

    void setOwnerId(int_t) const;

    int_t ownerId() const;
    void update(int);

    bool collideable() const { return true; }
    void collisionEvent();

    void setTarget(SpaceObject* target) { m_target = target; }

    void hit(int, SpaceObject* agresor = nullptr) override final;
    void _postDeathUniqueEvent(bool) override final;

    int damage() const;

    BulletDescr* descriptor() const { return m_descriptor_bullet; }
    BulletModel* model() const { return m_model_bullet; }

private:
    BulletDescr* m_descriptor_bullet = nullptr;
    BulletModel* m_model_bullet = nullptr;

    core::control::SpaceObject* m_target = nullptr;

    bool __checkTarget() const;
};

} // namespace control
} // namespace core

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

#include "BulletBuilder.hpp"

#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/descriptor/spaceobject/Bullet.hpp>
#include <core/model/spaceobject/Bullet.hpp>
#include <core/spaceobject/Bullet.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Bullet*
Bullet::gen(int damage)
{
    descriptor::Bullet* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::CONTAINER)) {
        descr = descriptor::genBullet();
    } else {
        descr = core::shortcuts::descriptors()->randBullet();
    }
    assert(descr);
    return gen(descr, damage);
}

control::Bullet*
Bullet::gen(descriptor::Bullet* descriptor, int damage)
{
    control::Bullet* bullet = __genTemplate(descriptor);
    createInternals(bullet, descriptor, damage);

    return bullet;
}

control::Bullet*
Bullet::__genTemplate(descriptor::Bullet* descr)
{
    model::Bullet* model = new model::Bullet();
    assert(model);

    control::Bullet* bullet = new control::Bullet(descr, model);
    assert(bullet);

    return bullet;
}

void
Bullet::createInternals(control::Bullet* bullet, descriptor::Bullet* descriptor, int damage)
{
    bullet->model()->setArmor(descriptor->armor());
    bullet->model()->setDamage(damage);
}

} // namespace builder

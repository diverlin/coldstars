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

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Bullet*
Bullet::gen()
{
    descriptor::Bullet* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::CONTAINER)) {
        descr = descriptor::genBullet();
    } else {
        descr = descriptor::Manager::get().randBullet();
    }
    assert(descr);
    return gen(descr);
}

control::Bullet*
Bullet::gen(descriptor::Bullet* descriptor)
{
    control::Bullet* bullet = __genTemplate(descriptor);
    createInternals(bullet, descriptor);

    return bullet;
}

control::Bullet*
Bullet::__genTemplate(descriptor::Bullet* descr)
{
    model::Bullet* model = new model::Bullet();
    assert(model);

    control::Bullet* bullet = new control::Bullet(descr, model);
    assert(bullet);

    manager::Entity::get().add(bullet);

    return bullet;
}

void
Bullet::createInternals(control::Bullet* bullet, descriptor::Bullet* descriptor)
{
    LifeData data_life;
    data_life.armor = descriptor->armor();
    bullet->model()->setLifeData(data_life);
}

} // namespace builder

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
#include <core/spaceobject/Bullet.hpp>

namespace builder {

control::Bullet*
Bullet::gen(const BulletData& data_bullet)
{
    assert(false);
    control::Bullet* rocket_bullet = __genTemplate(nullptr);
    createInternals(rocket_bullet, data_bullet);

    return rocket_bullet;
}

control::Bullet*
Bullet::__genTemplate(descriptor::Bullet* descr)
{
    model::Bullet* model = new model::Bullet();
    assert(false);
    //model::Bullet* model = new model::Bullet(descr->id());
    assert(model);

    control::Bullet* bullet = new control::Bullet(descr, model);
    assert(bullet);

    manager::Entity::get().add(bullet);

    return bullet;
}

void
Bullet::createInternals(control::Bullet* rocket_bullet, const BulletData& data_bullet)
{
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);

    LifeData data_life;
    data_life.armor = data_bullet.armor();

    rocket_bullet->model()->setLifeData(data_life);
    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ROCKET_BULLET);
    //alpitodorender rocket_bullet->SetRenderData(mesh, texOb, texOb->size());

    assert(false);
    //rocket_bullet->CreateDriveComplexTextureDependedStuff();
}

} // namespace builder

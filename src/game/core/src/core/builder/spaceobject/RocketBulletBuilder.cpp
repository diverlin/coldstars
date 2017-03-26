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

#include "RocketBulletBuilder.hpp"

#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/spaceobject/RocketBullet.hpp>

namespace builder {

control::RocketBullet*
Rocket::gen(const BulletData& data_bullet)
{
    control::RocketBullet* rocket_bullet = __genTemplate();
    createInternals(rocket_bullet, data_bullet);

    return rocket_bullet;
}

control::RocketBullet*
Rocket::__genTemplate(int_t id)
{
    model::RocketBullet* model = new model::RocketBullet;
    descriptor::RocketBullet* descr = nullptr;
    assert(descr);
    control::RocketBullet* rocket_bullet = new control::RocketBullet(model, descr);
    assert(rocket_bullet);

    EntityManager::get().reg(rocket_bullet);

    return rocket_bullet;
}

void
Rocket::createInternals(control::RocketBullet* rocket_bullet, const BulletData& data_bullet)
{
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);

    LifeData data_life;
    data_life.armor = data_bullet.armor;

    rocket_bullet->model()->setBulletData(data_bullet);
    
    rocket_bullet->model()->setLifeData(data_life);
    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ROCKET_BULLET);
    //alpitodorender rocket_bullet->SetRenderData(mesh, texOb, texOb->size());

    assert(false);
    //rocket_bullet->CreateDriveComplexTextureDependedStuff();
}

} // namespace builder

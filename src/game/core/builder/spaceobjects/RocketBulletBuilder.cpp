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
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/RocketBullet.hpp"


RocketBulletBuilder::RocketBulletBuilder()
{}

RocketBulletBuilder::~RocketBulletBuilder()
{}

RocketBullet* RocketBulletBuilder::createTemplate(INTLONGEST id) const
{
    RocketBullet* rocket_bullet = new RocketBullet(id);
    assert(rocket_bullet);

    global::get().entitiesManager().RegisterEntity(rocket_bullet);
    
    return rocket_bullet;
}

RocketBullet* RocketBulletBuilder::create(const BulletData& data_bullet) const
{
    RocketBullet* rocket_bullet = createTemplate();
    createInternals(rocket_bullet, data_bullet);
        
    return rocket_bullet;
}

void RocketBulletBuilder::createInternals(RocketBullet* rocket_bullet, const BulletData& data_bullet) const
{
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);

    LifeData data_life;    
    data_life.armor = data_bullet.armor;        

    rocket_bullet->SetBulletData(data_bullet);
    
    rocket_bullet->setLifeData(data_life);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ROCKET_BULLET_ID);
    //alpitodorender rocket_bullet->SetRenderData(mesh, texOb, texOb->size());

    rocket_bullet->CreateDriveComplexTextureDependedStuff();       
}

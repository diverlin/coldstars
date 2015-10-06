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

#include "BombBuilder.hpp"
#include <items/others/Bomb.hpp>
#include <managers/EntitiesManager.hpp>

#include <ceti/Logger.hpp>
#include <common/IdGenerator.hpp>
#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <boost/property_tree/info_parser.hpp>

BombBuilder::BombBuilder()
{}

BombBuilder::~BombBuilder()
{}

Bomb* BombBuilder::createTemplate(IDTYPE id) const
{
    Bomb* bomb = new Bomb(id);
    assert(bomb);

    global::get().entitiesManager().registerEntity(bomb);
    
    return bomb;
} 

Bomb* BombBuilder::create(int damage, int radius) const
{
    Bomb* bomb = createTemplate();
    createInternals(bomb, damage, radius);

    return bomb;
} 

void BombBuilder::createInternals(Bomb* bomb, int damage, int radius) const
{     
    //    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BOMB_ID);

    //alpitodorender bomb->SetRenderData(mesh, texOb, texOb->size());
    bomb->setDamage(damage);
    bomb->setRadius(radius);
    bomb->setParentSubTypeId(TYPE::ENTITY::CARGO_SLOT_ID);
}

void BombBuilder::write(const std::string& fpath, Bomb* bomb)
{
    boost::property_tree::ptree ptree;

//    ptree.put("title",  bomb->title());
//    ptree.put("race",   bomb->race());
    ptree.put("damage", bomb->damage());
    ptree.put("radius", bomb->radius());
//    ptree.put("mass",   bomb->mass());

    write_info("fpath", ptree);
}



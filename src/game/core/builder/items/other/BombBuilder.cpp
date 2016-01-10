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
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>
#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

//#include <boost/property_tree/info_parser.hpp>
#include <descriptors/Descriptor.hpp>

BombBuilder::BombBuilder()
{}

BombBuilder::~BombBuilder()
{}

Bomb* BombBuilder::create(const Descriptor& descriptor) const
{
    Bomb* bomb = new Bomb(descriptor.get<id_type>(KEY_ID));
    assert(bomb);
    global::get().entityManager().reg(bomb);
    createInternals(bomb, descriptor);
    return bomb;
} 

void BombBuilder::createInternals(Bomb* bomb, const Descriptor& descriptor) const
{     
    //    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //    jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BOMB_ID);

    //alpitodorender bomb->SetRenderData(mesh, texOb, texOb->size());
    bomb->setDamage(descriptor.get<int>(KEY_DAMAGE));
    bomb->setRadius(descriptor.get<int>(KEY_RADIUS));
    bomb->setParentSubTypeId(TYPE::ENTITY::CARGO_SLOT_ID);
}

//void BombBuilder::write(const std::string& fpath, Bomb* bomb)
//{
//    boost::property_tree::ptree ptree;

////    ptree.put("title",  bomb->title());
////    ptree.put("race",   bomb->race());
//    ptree.put("damage", bomb->damage());
//    ptree.put("radius", bomb->radius());
////    ptree.put("mass",   bomb->mass());

//    write_info("fpath", ptree);
//}



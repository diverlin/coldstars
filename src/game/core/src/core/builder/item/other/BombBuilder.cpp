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
#include <item/others/Bomb.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>
#include <common/Global.hpp>

//#include <client/resources/TextureCollector.hpp>
//#include <client/resources/MeshCollector.hpp>
//#include <jeti/Material.hpp>

//#include <boost/property_tree/info_parser.hpp>

#include <descriptor/Base.hpp>
#include <descriptor/DescriptorManager.hpp>

BombBuilder::BombBuilder()
{}

BombBuilder::~BombBuilder()
{}

Bomb* BombBuilder::getNew()
{
    const descriptor::BaseOLD& descriptor = core::global::get().descriptors().getRand(descriptor::Type::BOMB);
    return getNew(descriptor);
}

Bomb* BombBuilder::getNew(const descriptor::BaseOLD& descriptor)
{
    Bomb* bomb = new Bomb;
    assert(bomb);

    assert(false);
//    core::global::get().entityManager().reg(bomb);

    __createInternals(bomb, descriptor);

    return bomb;
} 

void BombBuilder::__createInternals(Bomb* bomb, const descriptor::BaseOLD& descriptor)
{     
    //    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE_ID);
    //    jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BOMB_ID);

    //alpitodorender bomb->SetRenderData(mesh, texOb, texOb->size());
    bomb->setDamage(descriptor.damage());
    bomb->setRadius(descriptor.radius());
    bomb->setParentSubTypeId(entity::type::CARGO_SLOT_ID);
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


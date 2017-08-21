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

#include "Goods.hpp"

#include <core/descriptor/item/other/Goods.hpp>
#include <core/model/item/other/Goods.hpp>

namespace control {
namespace item {

Goods::Goods(descriptor::item::Goods* descriptor, model::item::Goods* model)
    :
      Base(descriptor, model)
    , m_descriptor_goods(descriptor)
    , m_model_goods(model)
{
}

Goods::~Goods()
{}

void Goods::increase(int amount) { m_model_goods->setAmount(m_model_goods->amount()+amount); }
void Goods::decrease(int amount) { m_model_goods->setAmount(m_model_goods->amount()-amount); }

           
//void Goods::addUniqueInfo()
//{
////    info.addTitleStr("GOODS");
////    switch(subTypeId())
////    {
////        case entity::Type::MINERALS:     { info.addNameStr("mineral:"); info.addValueStr(std::to_string(data_item.mass)); break; }
////        case entity::Type::FOOD:         { info.addNameStr("food:"); info.addValueStr(std::to_string(data_item.mass)); break; }
////        case entity::Type::MEDICINE:     { info.addNameStr("medicine:"); info.addValueStr(std::to_string(data_item.mass)); break; }
////        case entity::Type::MILITARY:     { info.addNameStr("military:"); info.addValueStr(std::to_string(data_item.mass)); break; }
////        case entity::Type::DRUG:         { info.addNameStr("drug:"); info.addValueStr(std::to_string(data_item.mass)); break; }
////        case entity::Type::EXCLUSIVE:     { info.addNameStr("exclusive:"); info.addValueStr(std::to_string(data_item.mass)); break; }
        
////        default: { info.addNameStr("UNKNOWN:"); info.addValueStr("fix the bug"); break; }
////    }
//}
     
//void Goods::AddCommonInfo()
//{
//    //info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
//}
 
} // namespace item
} // namespace control


//Goods* GetNewGoodsPack(entity::Type group, int_t id)
//{
////    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
////    jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::CONTAINER);
    
//    GoodsPack* goodsPack = new GoodsPack(id, group);
//    //alpitodorender goodsPack->SetRenderData(mesh, texOb, texOb->size());

//    assert(false);
//    //manager::EntityManager::get().reg(goodsPack);
            
//    return goodsPack;
//}

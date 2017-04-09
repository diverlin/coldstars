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

#include "GoodsPack.hpp"
//#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

//#include <ceti/IdGenerator.hpp>
#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/model/item/Item.hpp>

//#include <client/resources/TextureCollector.hpp>
//#include <client/resources/MeshCollector.hpp>
//#include <jeti/Material.hpp>

GoodsPack::GoodsPack(int id, entity::Type subtype_id)
    :
      control::Item(nullptr, nullptr)
{
    assert(false);
//    setId(id);
//    setTypeId(entity::Type::GOODS);
//    setSubTypeId(subtype_id);
}

/* virtual */
GoodsPack::~GoodsPack() 
{}

void GoodsPack::Increase(int amount) { m_mass += amount; }
void GoodsPack::Decrease(int amount) { m_mass -= amount; }

           
/* virtual */
void GoodsPack::UpdateOwnerAbilities() { /* do nothing*/ }
                    

/* virtual */
void GoodsPack::addUniqueInfo() 
{
//    info.addTitleStr("GOODS");
//    switch(subTypeId())
//    {
//        case entity::Type::MINERALS:     { info.addNameStr("mineral:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case entity::Type::FOOD:         { info.addNameStr("food:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case entity::Type::MEDICINE:     { info.addNameStr("medicine:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case entity::Type::MILITARY:     { info.addNameStr("military:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case entity::Type::DRUG:         { info.addNameStr("drug:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case entity::Type::EXCLUSIVE:     { info.addNameStr("exclusive:"); info.addValueStr(std::to_string(data_item.mass)); break; }
        
//        default: { info.addNameStr("UNKNOWN:"); info.addValueStr("fix the bug"); break; }
//    }
}
     
/* virtual */    
void GoodsPack::AddCommonInfo()
{
    //info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
}

 
///*virtual*/
//void GoodsPack::Save(boost::property_tree::ptree& save_ptree) const
//{
////    std::string root = "goods_pack." + std::to_string(id()) + ".";
////    Base::SaveData(save_ptree, root);
////    Base::SaveData(save_ptree, root);
////    GoodsPack::SaveData(save_ptree, root);
//}

///*virtual*/
//void GoodsPack::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    Base::LoadData(load_ptree);
////    GoodsPack::LoadData(load_ptree);
//}
    
///*virtual*/
//void GoodsPack::Resolve()
//{
////    Base::ResolveData();
////    Base::ResolveData();
////    GoodsPack::ResolveData();
//}

//void GoodsPack::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
////    LOG(" GoodsPack::SaveData()  id=" + std::to_string(id()) + " START");
//}
         
//void GoodsPack::LoadData(const boost::property_tree::ptree& load_ptree)
//{
////    LOG(" GoodsPack::LoadData()  id=" + std::to_string(id()) + " START");
//}

//void GoodsPack::ResolveData()
//{
////    LOG(" GoodsPack::ResolveData()  id=" + std::to_string(id()) + " START");
//}


GoodsPack* GetNewGoodsPack(entity::Type subtype_id, int_t id)
{
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::CONTAINER);
    
    GoodsPack* goodsPack = new GoodsPack(id, subtype_id);
    //alpitodorender goodsPack->SetRenderData(mesh, texOb, texOb->size());

    assert(false);
    //EntityManager::get().reg(goodsPack);
            
    return goodsPack;
}

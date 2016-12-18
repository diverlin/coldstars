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
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <ceti/IdGenerator.hpp>
#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

GoodsPack::GoodsPack(int id, type::entity subtype_id)
{
    setId(id); 
    setTypeId(type::entity::GOODS_ID);
    setSubTypeId(subtype_id);
}

/* virtual */
GoodsPack::~GoodsPack() 
{}

           
/* virtual */
void GoodsPack::UpdateOwnerAbilities() { /* do nothing*/ }
                    

/* virtual */
void GoodsPack::addUniqueInfo() 
{
//    info.addTitleStr("GOODS");
//    switch(subTypeId())
//    {
//        case type::entity::MINERALS_ID:     { info.addNameStr("mineral:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case type::entity::FOOD_ID:         { info.addNameStr("food:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case type::entity::MEDICINE_ID:     { info.addNameStr("medicine:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case type::entity::MILITARY_ID:     { info.addNameStr("military:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case type::entity::DRUG_ID:         { info.addNameStr("drug:"); info.addValueStr(std::to_string(data_item.mass)); break; }
//        case type::entity::EXCLUSIVE_ID:     { info.addNameStr("exclusive:"); info.addValueStr(std::to_string(data_item.mass)); break; }
        
//        default: { info.addNameStr("UNKNOWN:"); info.addValueStr("fix the bug"); break; }
//    }
}
     
/* virtual */    
void GoodsPack::AddCommonInfo()
{
    //info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
}

 
/*virtual*/
void GoodsPack::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "goods_pack." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    GoodsPack::SaveData(save_ptree, root);
}

/*virtual*/
void GoodsPack::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    GoodsPack::LoadData(load_ptree);
}
    
/*virtual*/
void GoodsPack::Resolve()
{
    Base::ResolveData();
    Base::ResolveData();
    GoodsPack::ResolveData();
}

void GoodsPack::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" GoodsPack::SaveData()  id=" + std::to_string(id()) + " START");
}
         
void GoodsPack::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" GoodsPack::LoadData()  id=" + std::to_string(id()) + " START");
}

void GoodsPack::ResolveData()
{
    LOG(" GoodsPack::ResolveData()  id=" + std::to_string(id()) + " START");
}


GoodsPack* GetNewGoodsPack(type::entity subtype_id, int_t id)
{
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::CONTAINER_ID);
    
    GoodsPack* goodsPack = new GoodsPack(id, subtype_id);
    //alpitodorender goodsPack->SetRenderData(mesh, texOb, texOb->size());
    
    global::get().entityManager().reg(goodsPack);
            
    return goodsPack;
}

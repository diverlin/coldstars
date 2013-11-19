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
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

#include "../../common/IdGenerator.hpp"
#include "../../world/EntityManager.hpp"
#include "../../resources/TextureManager.hpp"

GoodsPack::GoodsPack(int id, TYPE::ENTITY subtype_id)
{
    SetId(id); 
    SetTypeId(TYPE::ENTITY::GOODS_ID);
    SetSubTypeId(subtype_id);
}

/* virtual */
GoodsPack::~GoodsPack() 
{}

           
/* virtual */
void GoodsPack::UpdateOwnerAbilities() { /* do nothing*/ }
                    

/* virtual */
void GoodsPack::AddUniqueInfo() 
{
        info.addTitleStr("GOODS");
        switch(GetSubTypeId())
        {
            case TYPE::ENTITY::MINERALS_ID:     { info.addNameStr("mineral:"); info.addValueStr(int2str(data_item.mass)); break; }
            case TYPE::ENTITY::FOOD_ID:         { info.addNameStr("food:"); info.addValueStr(int2str(data_item.mass)); break; }
            case TYPE::ENTITY::MEDICINE_ID:     { info.addNameStr("medicine:"); info.addValueStr(int2str(data_item.mass)); break; }
            case TYPE::ENTITY::MILITARY_ID:     { info.addNameStr("military:"); info.addValueStr(int2str(data_item.mass)); break; }
            case TYPE::ENTITY::DRUG_ID:         { info.addNameStr("drug:"); info.addValueStr(int2str(data_item.mass)); break; }
            case TYPE::ENTITY::EXCLUSIVE_ID:     { info.addNameStr("exclusive:"); info.addValueStr(int2str(data_item.mass)); break; }
            
            default: { info.addNameStr("UNKNOWN:"); info.addValueStr("fix the bug"); break; }
        }
}
     
/* virtual */    
void GoodsPack::AddCommonInfo()
{
        //info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

 
/*virtual*/
void GoodsPack::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "goods_pack." + int2str(GetId()) + ".";
    Base::SaveData(save_ptree, root);
        BaseItem::SaveData(save_ptree, root);
    SaveDataUniqueGoodsPack(save_ptree, root);
}

/*virtual*/
void GoodsPack::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
        BaseItem::LoadData(load_ptree);
    LoadDataUniqueGoodsPack(load_ptree);
}
    
/*virtual*/
void GoodsPack::Load()
{
    Base::ResolveData();
        BaseItem::ResolveData();
    ResolveDataUniqueGoodsPack();
}

void GoodsPack::SaveDataUniqueGoodsPack(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SaveDataUniqueGoodsPack()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
         
void GoodsPack::LoadDataUniqueGoodsPack(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" LoadDataUniqueGoodsPack()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}

void GoodsPack::ResolveDataUniqueGoodsPack()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ResolveDataUniqueGoodsPack()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


GoodsPack* GetNewGoodsPack(TYPE::ENTITY subtype_id, INTLONGEST id)
{
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }
        
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::CONTAINER_ID); 
    
    GoodsPack* goodsPack = new GoodsPack(id, subtype_id);
    goodsPack->BindData2D(texOb);
    
    EntityManager::Instance().RegisterEntity(goodsPack);
            
    return goodsPack;
}

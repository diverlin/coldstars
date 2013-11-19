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

#include "Bomb.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

Bomb::Bomb(int id)
:
damage(0),
radius(0)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::BOMB_ID);
}

 /* virtual */
Bomb::~Bomb() 
{}

/* virtual */    
void Bomb::UpdateOwnerAbilities() {} 

       
/* virtual */         
void Bomb::AddCommonInfo()
{
        info.addNameStr("mass:");        info.addValueStr(int2str(data_item.mass));
}

/* virtual */
void Bomb::AddUniqueInfo()
{
        info.addTitleStr("BOMB");

        //info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
        info.addNameStr("id:");          info.addValueStr(int2str(GetId()));
        info.addNameStr("damage:");      info.addValueStr(int2str(damage));
        //info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
}         

/*virtual*/
void Bomb::SaveData(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "bomb." + int2str(GetId()) + ".";
    Base::Save(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
    SaveDataUniqueBomb(save_ptree, root);
}

/*virtual*/
void Bomb::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
    LoadDataUniqueBomb(load_ptree);
}
    
/*virtual*/
void Bomb::ResolveData()
{
    Base::Resolve();
        ResolveDataUniqueBaseItem();
    ResolveDataUniqueBomb();
}

void Bomb::SaveDataUniqueBomb(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SaveDataUniqueBomb()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        save_ptree.put(root+"damage", damage);
        save_ptree.put(root+"radius", radius);
}
         
void Bomb::LoadDataUniqueBomb(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" LoadDataUniqueBomb()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        damage = load_ptree.get<int>("damage");
        radius = load_ptree.get<int>("radius");
}

void Bomb::ResolveDataUniqueBomb()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ResolveDataUniqueBomb()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}



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
//#include <ceti/StringUtils.hpp>
#include "../../common/Logger.hpp"

Bomb::Bomb(int id)
:
damage(0),
radius(0)
{ 
    setId(id);
    setTypeId(TYPE::ENTITY::BOMB_ID);
}

 /* virtual */
Bomb::~Bomb() 
{}

/* virtual */    
void Bomb::UpdateOwnerAbilities() {} 

       
/* virtual */         
void Bomb::AddCommonInfo()
{
    info.addNameStr("mass:");        info.addValueStr(std::to_string(data_item.mass));
}

/* virtual */
void Bomb::AddUniqueInfo()
{
    info.addTitleStr("BOMB");

    //info.addNameStr("id/ss_id:");    info.addValueStr(std::to_string(data_id.id) + " / " + std::to_string(starsystem->id()));
    info.addNameStr("id:");          info.addValueStr(std::to_string(id()));
    info.addNameStr("damage:");      info.addValueStr(std::to_string(damage));
    //info.addNameStr("armor:");       info.addValueStr(std::to_string(data_life.armor));
}         

/*virtual*/
void Bomb::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "bomb." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    Bomb::SaveData(save_ptree, root);
}

/*virtual*/
void Bomb::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    LoadData(load_ptree);
}
    
/*virtual*/
void Bomb::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    Bomb::ResolveData();
}

void Bomb::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Bomb::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"damage", damage);
    save_ptree.put(root+"radius", radius);
}
         
void Bomb::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Bomb::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    damage = load_ptree.get<int>("damage");
    radius = load_ptree.get<int>("radius");
}

void Bomb::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Bomb::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}



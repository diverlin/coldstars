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

#include "EnergizerEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items/modules/EnergizerModule.hpp"

#include "../../slots/ItemSlot.hpp"
#include "../../spaceobjects/Vehicle.hpp"

EnergizerEquipment::EnergizerEquipment(INTLONGEST id)
:
energy_max_orig(0),
energy(0),
restoration_orig(0) 
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::EQUIPMENT_ID);           
    SetSubTypeId(TYPE::ENTITY::ENERGIZER_EQUIPMENT_ID);
}

/* virtual */
EnergizerEquipment::~EnergizerEquipment() 
{}

/* virtual */
void EnergizerEquipment::UpdateProperties()
{
    energy_max_add   = 0;
    restoration_add  = 0;
    
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        energy_max_add  += ((EnergizerModule*)modules_vec[i])->GetEnergyMaxAdd();
        restoration_add += ((EnergizerModule*)modules_vec[i])->GetRestorationAdd();        
    }
    
    energy_max  = energy_max_orig  + energy_max_add;
    restoration = restoration_orig + restoration_add;
}


/* virtual */
void EnergizerEquipment::UpdateInStatic()
{
    if (GetFunctioning() == true)    
    {
        if (item_slot->GetOwnerVehicle()->TryToGenerateEnergy(restoration) == true)
        {
            DeteriorationEvent();
        }
    }
    
    UpdateLock();
}

void EnergizerEquipment::CountPrice()
{
    float energy_rate          = (float)energy_max_orig / EQUIPMENT::ENERGIZER::ENERGY_MIN;
    float restoration_rate     = (float)restoration_orig / EQUIPMENT::ENERGIZER::RESTORATION_MIN;
    float modules_num_rate     = (float)data_item.modules_num_max / EQUIPMENT::ENERGIZER::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::ENERGIZER::ENERGY_WEIGHT * energy_rate + EQUIPMENT::ENERGIZER::RESTORATION_WEIGHT * restoration_rate + EQUIPMENT::ENERGIZER::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)data_item.mass / EQUIPMENT::ENERGIZER::MASS_MIN;
    float condition_rate     = (float)condition / data_item.condition_max;

    price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void EnergizerEquipment::AddUniqueInfo()
{
    info.addTitleStr("ENERGYBLOCK");
    info.addNameStr("energy:");      info.addValueStr(GetEnergyStr());
    info.addNameStr("restoration:"); info.addValueStr(GetRestorationStr());
}

std::string EnergizerEquipment::GetEnergyStr()
{
    if (energy_max_add == 0)
        return int2str(energy) + "/" + int2str(energy_max_orig);
    else
        return int2str(energy) + "/" + int2str(energy_max_orig) + "+" + int2str(energy_max_add);
}

std::string EnergizerEquipment::GetRestorationStr()
{
    if (restoration_add == 0)
        return int2str(restoration_orig);
    else
        return int2str(restoration_orig) + "+" + int2str(restoration_add);
}

/*virtual*/
void EnergizerEquipment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "energizer_equipment." + int2str(GetId()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseEquipment::SaveData(save_ptree, root);
    EnergizerEquipment::SaveData(save_ptree, root);
}

/*virtual*/
void EnergizerEquipment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseEquipment::LoadData(load_ptree);
    EnergizerEquipment::LoadData(load_ptree);
}

/*virtual*/
void EnergizerEquipment::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseEquipment::ResolveData();
    EnergizerEquipment::ResolveData();
}

void EnergizerEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerEquipment::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"energy_max_orig", energy_max_orig);
    save_ptree.put(root+"restoration_orig", restoration_orig);
}
                
void EnergizerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerEquipment::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    energy_max_orig = load_ptree.get<int>("energy_max_orig");
    restoration_orig = load_ptree.get<int>("restoration_orig");        
}                

void EnergizerEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerEquipment::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}



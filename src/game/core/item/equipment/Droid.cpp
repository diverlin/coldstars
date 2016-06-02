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

#include "Droid.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/DroidModule.hpp>
#endif
#include "../../spaceobjects/Vehicle.hpp"
#include "../../slots/ItemSlot.hpp"

namespace item {
namespace equipment {

Droid::Droid(const id_type& id)
    :
      repair_orig(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::EQUIPMENT_ID);
    setSubTypeId(TYPE::ENTITY::DROID_EQUIPMENT_ID);
}

/* virtual */
Droid::~Droid()
{}

/* virtual */
void Droid::updateProperties()
{
    repair_add = 0;
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++)
    {
        repair_add += ((DroidModule*)modules_vec[i])->GetRepairAdd();
    }
#endif
    repair = repair_orig + repair_add;
}

/* virtual */
void Droid::updateInStatic()
{
    if (isFunctioning()) {
        if (!itemSlot()->GetOwnerVehicle()->IsArmorFull()) {
            itemSlot()->GetOwnerVehicle()->IncreaseArmor(repair);
            deteriorationEvent();
        }
    }
    updateLock();
}

void Droid::CountPrice()
{
    float repair_rate        = (float)repair_orig / EQUIPMENT::DROID::REPAIR_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::DROID::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::DROID::REPAIR_WEIGHT * repair_rate +
            EQUIPMENT::DROID::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data_item.mass / EQUIPMENT::DROID::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data_item.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Droid::addUniqueInfo()
{
    //    info.addTitleStr("DROID");
    //    info.addNameStr("repair:");     info.addValueStr(GetRepairStr());
}


std::string Droid::GetRepairStr()
{
    if (repair_add == 0)
        return std::to_string(repair_orig);
    else
        return std::to_string(repair_orig) + "+" + std::to_string(repair_add);
}

/*virtual*/
void Droid::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "droid_equipment." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Base::SaveData(save_ptree, root);
    Droid::SaveData(save_ptree, root);
}

/*virtual*/
void Droid::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Base::LoadData(load_ptree);
    Droid::LoadData(load_ptree);
}

/*virtual*/
void Droid::Resolve()
{
    Base::ResolveData();
    Base::ResolveData();
    Base::ResolveData();
    Droid::ResolveData();
}

void Droid::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" DroidEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"repair_orig", repair_orig);
}

void Droid::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" DroidEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
    repair_orig = load_ptree.get<int>("repair_orig");
}                

void Droid::ResolveData()
{
    LOG(" DroidEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
}

} // namespace equipment
} // namespace item

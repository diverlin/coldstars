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

#include "Bak.hpp"
#include <core/common/constants.hpp>
#ifdef USE_MODULES
#include <core/item/modules/BakModule.hpp>
#endif // USE_MODULES

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace model {
namespace item {

Bak::Bak()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::BAK_EQUIPMENT_ID);
}

Bak::Bak(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Bak::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model



namespace control {
namespace item {

Bak::Bak(int_t id)
{
//    setId(id);
}
   
/* virtual */
Bak::~Bak()
{}
        
void Bak::increaseFuel(int fuel)
{
    fuel += model()->fuel();
    if (fuel > model()->fuelMax()) {
        fuel = model()->fuelMax();
    }
    model()->setFuel(fuel);
}    
                                    
/* virtual */            
void Bak::updateProperties()
{
    int fuelMaxAdd = 0;
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        fuelMaxAdd += ((BakModule*)modules_vec[i])->GetFuelMaxAdd();
    }
#endif
    model()->setFuelMax(model()->fuelMaxOrig() + fuelMaxAdd);
}

void Bak::countPrice()
{
    float fuel_rate          = (float)model()->fuelMaxOrig() / EQUIPMENT::BAK::FUEL_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::BAK::MODULES_NUM_MAX;
    
    float effectiveness_rate = EQUIPMENT::BAK::FUEL_WEIGHT * fuel_rate + 
                               EQUIPMENT::BAK::MODULES_NUM_WEIGHT * modules_num_rate;
    
    float mass_rate          = (float)m_data.mass / EQUIPMENT::BAK::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;
    
    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Bak::addUniqueInfo()
{
//    info.addTitleStr("BAK");
//    info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}


std::string Bak::getFuelStr()
{
    if (model()->fuelMaxAdd()) {
        return std::to_string(model()->fuelMaxOrig()) + "+" + std::to_string(model()->fuelMaxAdd()) + "/" + std::to_string(model()->fuel());
    } else {
        return std::to_string(model()->fuelMaxOrig()) + "/" + std::to_string(model()->fuel());
    }
}

///*virtual*/
//void Bak::Save(boost::property_tree::ptree& save_ptree) const
//{
////    std::string root = "bak_equipment." + std::to_string(id()) + ".";

////    Base::SaveData(save_ptree, root);
////    Base::SaveData(save_ptree, root);
////    Base::SaveData(save_ptree, root);
////    Bak::SaveData(save_ptree, root);
//}

///*virtual*/
//void Bak::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    Base::LoadData(load_ptree);
////    Base::LoadData(load_ptree);
////    Bak::LoadData(load_ptree);
//}

///*virtual*/
//void Bak::Resolve()
//{
////    Base::ResolveData();
////    Base::ResolveData();
////    Base::ResolveData();
////    Bak::ResolveData();
//}

//void Bak::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
////    LOG(" BakEquipment::SaveData()  id=" + std::to_string(id()) + " START");
    
////    save_ptree.put(root+"fuel_max_orig", m_fuelMaxOrig);
////    save_ptree.put(root+"fuel", m_fuel);
//}
                
//void Bak::LoadData(const boost::property_tree::ptree& load_ptree)
//{
////    LOG(" BakEquipment::LoadData()  id=" + std::to_string(id()) + " START");
    
////    m_fuelMaxOrig = load_ptree.get<int>("fuel_max_orig");
////    m_fuel = load_ptree.get<int>("fuel");
//}

//void Bak::ResolveData()
//{
////    LOG(" BakEquipment::ResolveData()  id=" + std::to_string(id()) + " START");
//}

} // namespace item
} // namespace control

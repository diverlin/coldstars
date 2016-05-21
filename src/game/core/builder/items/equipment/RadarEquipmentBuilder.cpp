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


#include <builder/items/equipment/RadarEquipmentBuilder.hpp>
#include <items/equipment/RadarEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>
         
#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

RadarBuilder::RadarBuilder()
{}

RadarBuilder::~RadarBuilder()
{}

item::equipment::Radar* RadarBuilder::createTemplate(id_type id) const
{
    item::equipment::Radar* radar_equipment = new item::equipment::Radar(id);
    assert(radar_equipment);

    global::get().entityManager().reg(radar_equipment);
    
    return radar_equipment;
} 
  
item::equipment::Radar* RadarBuilder::create(const descriptor::Base& descriptor) const
{
    item::equipment::Radar* radar_equipment = createTemplate();
    createInternals(radar_equipment, descriptor);
        
    return radar_equipment;
} 
        
void RadarBuilder::createInternals(item::equipment::Radar* radar_equipment, const descriptor::Base& descriptor) const
{     
    ItemCommonData common_data = extractCommonData(descriptor);

    radar_equipment->SetRadiusOrig(descriptor.radius());
    radar_equipment->setParentSubTypeId(TYPE::ENTITY::RADAR_SLOT_ID);
    radar_equipment->setItemCommonData(common_data);

    radar_equipment->updateProperties();
    radar_equipment->CountPrice();
}



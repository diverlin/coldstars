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


#include <builder/items/equipment/DroidEquipmentBuilder.hpp>
#include <items/equipment/DroidEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>


DroidEquipmentBuilder::DroidEquipmentBuilder()
{}

DroidEquipmentBuilder::~DroidEquipmentBuilder()
{}

DroidEquipment* DroidEquipmentBuilder::createTemplate(id_type id) const
{
    DroidEquipment* droid_equipment = new DroidEquipment(id);
    assert(droid_equipment);

    global::get().entityManager().reg(droid_equipment);
    
    return droid_equipment;
} 

DroidEquipment* DroidEquipmentBuilder::create(const Descriptor& descriptor) const
{
    DroidEquipment* droid_equipment = createTemplate();
    createInternals(droid_equipment, descriptor);
        
    return droid_equipment;
}  
            
void DroidEquipmentBuilder::createInternals(DroidEquipment* droid_equipment, const Descriptor& descriptor) const
{     
    ItemCommonData common_data;
    common_data.race            = (TYPE::RACE)descriptor.race();
    common_data.tech      = (TYPE::TECH)descriptor.tech();
    common_data.modules_num = descriptor.modules();
    common_data.mass            = descriptor.mass();
    common_data.condition   = descriptor.condition();
    common_data.deterioration = descriptor.deteoration();
   
    droid_equipment->SetRepairOrig(descriptor.repair());
    //alpitodorender droid_equipment->SetRenderData(mesh, texOb_item, texOb_item->size());
    droid_equipment->setParentSubTypeId(TYPE::ENTITY::DROID_SLOT_ID);
    droid_equipment->setItemCommonData(common_data);
    droid_equipment->setCondition(common_data.condition);
            
    droid_equipment->updateProperties();
    droid_equipment->CountPrice();
}



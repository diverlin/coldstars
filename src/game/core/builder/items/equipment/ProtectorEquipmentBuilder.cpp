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


#include <builder/items/equipment/ProtectorEquipmentBuilder.hpp>
#include <items/equipment/ProtectorEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

ProtectorBuilder::ProtectorBuilder()
{}

ProtectorBuilder::~ProtectorBuilder()
{}

ProtectorEquipment* ProtectorBuilder::createTemplate(id_type id) const
{
    ProtectorEquipment* protector_equipment = new ProtectorEquipment(id);
    assert(protector_equipment);

    global::get().entityManager().reg(protector_equipment);
    
    return protector_equipment;
} 
   
ProtectorEquipment* ProtectorBuilder::create(const Descriptor& descriptor) const
{
    ProtectorEquipment* protector_equipment = createTemplate();
    createInternals(protector_equipment, descriptor);
        
    return protector_equipment;
} 
         
void ProtectorBuilder::createInternals(ProtectorEquipment* protector_equipment, const Descriptor& descriptor) const
{     
    ItemCommonData common_data = extractCommonData(descriptor);

    protector_equipment->SetProtectionOrig(descriptor.protection());
    protector_equipment->setParentSubTypeId(TYPE::ENTITY::PROTECTOR_SLOT_ID);
    protector_equipment->setItemCommonData(common_data);
            
    protector_equipment->updateProperties();
    protector_equipment->CountPrice();
}

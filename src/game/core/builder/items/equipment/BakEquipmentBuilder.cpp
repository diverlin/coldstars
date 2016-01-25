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


#include <builder/items/equipment/BakEquipmentBuilder.hpp>
#include <items/equipment/BakEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

BakEquipmentBuilder::BakEquipmentBuilder()
{
}

BakEquipmentBuilder::~BakEquipmentBuilder()
{}

BakEquipment* BakEquipmentBuilder::createTemplate(id_type id) const
{
    BakEquipment* bak_equipment = new BakEquipment(id);
    assert(bak_equipment);

    global::get().entityManager().reg(bak_equipment);
    
    return bak_equipment;
} 
       
BakEquipment* BakEquipmentBuilder::create(const Descriptor& descriptor) const
{
    BakEquipment* bak_equipment = createTemplate();
    createInternals(bak_equipment, descriptor);
    
    return bak_equipment;
}
                          
void BakEquipmentBuilder::createInternals(BakEquipment* bak_equipment, const Descriptor& descriptor) const
{
    ItemCommonData common_data;
    common_data.race            = (TYPE::RACE)descriptor.race();
    common_data.tech             = (TYPE::TECHLEVEL)descriptor.tech();
    common_data.modules_num        = descriptor.modules();
    common_data.mass                   = descriptor.mass();
    common_data.condition          = descriptor.condition();
    common_data.deterioration   = descriptor.deteoration();

    bak_equipment->setFuelMaxOrig(descriptor.fuel());
    bak_equipment->setFuel(descriptor.fuel());
    bak_equipment->setParentSubTypeId(TYPE::ENTITY::BAK_SLOT_ID);
    bak_equipment->setItemCommonData(common_data);
    bak_equipment->setCondition(common_data.condition);
                                    
    bak_equipment->updateProperties();
    bak_equipment->countPrice();
}



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

BakBuilder::BakBuilder()
{
}

BakBuilder::~BakBuilder()
{}

item::equipment::BakEquipment* BakBuilder::createTemplate(id_type id) const
{
    item::equipment::BakEquipment* bak_equipment = new item::equipment::BakEquipment(id);
    assert(bak_equipment);

    global::get().entityManager().reg(bak_equipment);
    
    return bak_equipment;
} 
       
item::equipment::BakEquipment* BakBuilder::create(const descriptor::Base& descriptor) const
{
    item::equipment::BakEquipment* bak_equipment = createTemplate();
    createInternals(bak_equipment, descriptor);
    
    return bak_equipment;
}
                          
void BakBuilder::createInternals(item::equipment::BakEquipment* bak_equipment, const descriptor::Base& descriptor) const
{
    ItemCommonData data = extractCommonData(descriptor);

    bak_equipment->setFuelMaxOrig(descriptor.fuel());
    bak_equipment->setFuel(descriptor.fuel());
    bak_equipment->setParentSubTypeId(TYPE::ENTITY::BAK_SLOT_ID);
    bak_equipment->setItemCommonData(data);
                                    
    bak_equipment->updateProperties();
    bak_equipment->countPrice();
}



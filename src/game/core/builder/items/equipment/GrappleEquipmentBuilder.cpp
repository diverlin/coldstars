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


#include <builder/items/equipment/GrappleEquipmentBuilder.hpp>
#include <items/equipment/GrappleEquipment.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>
#include <meti/RandUtils.hpp>

GrappleBuilder::GrappleBuilder()
{}

GrappleBuilder::~GrappleBuilder()
{}

GrappleEquipment* GrappleBuilder::createTemplate(id_type id) const
{
    GrappleEquipment* grapple_equipment = new GrappleEquipment(id);
    assert(grapple_equipment);

    global::get().entityManager().reg(grapple_equipment);
    
    return grapple_equipment;
} 

GrappleEquipment* GrappleBuilder::create(const Descriptor& descriptor) const
{
    GrappleEquipment* grapple_equipment = createTemplate();
    createInternals(grapple_equipment, descriptor);

    return grapple_equipment;
} 

void GrappleBuilder::createInternals(GrappleEquipment* grapple_equipment, const Descriptor& descriptor) const
{
    ItemCommonData data = extractCommonData(descriptor);

    grapple_equipment->SetStrengthOrig(descriptor.strength());
    grapple_equipment->SetRadiusOrig(descriptor.radius());
    grapple_equipment->SetSpeedOrig(descriptor.speed());

    grapple_equipment->setParentSubTypeId(TYPE::ENTITY::GRAPPLE_SLOT_ID);
    grapple_equipment->setItemCommonData(data);
    
    grapple_equipment->updateProperties();
    grapple_equipment->CountPrice();
}

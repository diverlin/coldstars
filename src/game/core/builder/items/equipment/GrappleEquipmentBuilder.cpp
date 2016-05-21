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
#include <item/equipment/Grapple.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>
#include <meti/RandUtils.hpp>

using namespace item::equipment;

GrappleBuilder::GrappleBuilder()
{}

GrappleBuilder::~GrappleBuilder()
{}

Grapple* GrappleBuilder::createTemplate(id_type id) const
{
    Grapple* grapple_equipment = new Grapple(id);
    assert(grapple_equipment);

    global::get().entityManager().reg(grapple_equipment);
    
    return grapple_equipment;
} 

Grapple* GrappleBuilder::create(const descriptor::Base& descriptor) const
{
    Grapple* grapple_equipment = createTemplate();
    createInternals(grapple_equipment, descriptor);

    return grapple_equipment;
} 

void GrappleBuilder::createInternals(Grapple* grapple_equipment, const descriptor::Base& descriptor) const
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

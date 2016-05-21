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


#include "GrappleBuilder.hpp"
#include <item/equipment/Grapple.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>
#include <meti/RandUtils.hpp>

namespace item {
namespace equipment {

GrappleBuilder::GrappleBuilder()
{}

GrappleBuilder::~GrappleBuilder()
{}

Grapple* GrappleBuilder::createTemplate(id_type id) const
{
    Grapple* grapple = new Grapple(id);
    assert(grapple);

    global::get().entityManager().reg(grapple);
    
    return grapple;
} 

Grapple* GrappleBuilder::create(const descriptor::Base& descriptor) const
{
    Grapple* grapple = createTemplate();
    createInternals(grapple, descriptor);

    return grapple;
} 

void GrappleBuilder::createInternals(Grapple* grapple, const descriptor::Base& descriptor) const
{
    ItemCommonData data = extractCommonData(descriptor);

    grapple->SetStrengthOrig(descriptor.strength());
    grapple->SetRadiusOrig(descriptor.radius());
    grapple->SetSpeedOrig(descriptor.speed());

    grapple->setParentSubTypeId(TYPE::ENTITY::GRAPPLE_SLOT_ID);
    grapple->setItemCommonData(data);
    
    grapple->updateProperties();
    grapple->CountPrice();
}

} // namespace equipment
} // namespace item

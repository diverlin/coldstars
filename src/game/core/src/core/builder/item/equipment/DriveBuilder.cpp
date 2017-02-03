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

#include "DriveBuilder.hpp"
#include <item/equipment/Drive.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace builder {
namespace item {
namespace equipment {

model::item::equipment::Drive*
DriveBuilder::createTemplate(int_t id)
{
    model::item::equipment::Drive* drive = new model::item::equipment::Drive();
    assert(drive);

    assert(false);
//    core::global::get().entityManager().reg(drive);
    
    return drive;
} 

model::item::equipment::Drive*
DriveBuilder::getNew()
{
    const descriptor::BaseOLD& descriptor = core::global::get().descriptors().getRand(descriptor::Type::DRIVE);
    model::item::equipment::Drive* drive = createTemplate();
    createInternals(drive, descriptor);

    return drive;
}

model::item::equipment::Drive*
DriveBuilder::getNew(const descriptor::BaseOLD& descriptor)
{
    model::item::equipment::Drive* drive = createTemplate();
    createInternals(drive, descriptor);

    return drive;
}        

void DriveBuilder::createInternals(model::item::equipment::Drive* drive, const descriptor::BaseOLD& descriptor)
{
    assert(false);
//    ItemCommonData data = extractCommonData(descriptor);

//    drive->SetSpeedOrig(descriptor.speed());
//    drive->SetHyperOrig(descriptor.hyper());
//    drive->setParentSubTypeId(type::entity::DRIVE_SLOT_ID);
//    drive->setItemCommonData(data);
    
//    drive->updateProperties();
//    drive->CountPrice();
}

} // namespace equipment
} // namespace item
} // namespace builder

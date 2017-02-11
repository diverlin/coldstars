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
#include <core/model/item/equipment/Drive.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/common/Global.hpp>

namespace builder {
namespace item {

model::item::Drive*
Drive::__createTemplate()
{
    model::item::Drive* drive = new model::item::Drive;
    assert(drive);

    assert(false);
//    core::global::get().entityManager().reg(drive);
    
    return drive;
} 

model::item::Drive*
Drive::getNew()
{
    const descriptor::item::Drive& descr = core::global::get().descriptors().drive().random();
    model::item::Drive* drive = __createTemplate();
    __createInternals(drive, descr);

    return drive;
}

model::item::Drive*
Drive::getNew(const std::string& data)
{
    descriptor::item::Drive descr(data);
    assert(descr.descriptor() != descriptor::type::DRIVE_EQUIPMENT);
    return getNew(descr);
}

model::item::Drive*
Drive::getNew(const descriptor::item::Drive& descr)
{
    model::item::Drive* drive = __createTemplate();
    __createInternals(drive, descr);

    return drive;
}        

void Drive::__createInternals(model::item::Drive* drive, const descriptor::item::Drive& descr)
{
    assert(false);
//    ItemCommonData data = extractCommonData(descriptor);

//    drive->SetSpeedOrig(descriptor.speed());
//    drive->SetHyperOrig(descriptor.hyper());
//    drive->setParentSubTypeId(entity::Type::DRIVE_SLOT_ID);
//    drive->setItemCommonData(data);
    
//    drive->updateProperties();
//    drive->CountPrice();
}

} // namespace item
} // namespace builder
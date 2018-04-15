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
#include <core/item/equipment/Drive.hpp>
#include <core/descriptor/item/equipment/Drive.hpp>
#include <core/common/Global.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::item::Drive*
DriveItemBuilder::gen()
{
    descriptor::item::Drive* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::DRIVE_EQUIPMENT)) {
        descr = descriptor::item::genDrive();
    } else {
        descr = core::shortcuts::descriptors()->randDrive();
    }
    assert(descr);
    return gen(descr);
}

core::control::item::Drive*
DriveItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Drive* descr = core::shortcuts::descriptors()->drive(descriptor_id);
    core::control::item::Drive* drive = __genTemplate(descr, ob_id);
    __createInternals(drive, descr);
    return drive;
}

core::control::item::Drive*
DriveItemBuilder::gen(descriptor::item::Drive* descr)
{
    core::control::item::Drive* drive = __genTemplate(descr);
    __createInternals(drive, descr);
    return drive;
}        

core::control::item::Drive*
DriveItemBuilder::__genTemplate(descriptor::item::Drive* descriptor, int_t id)
{
    model::item::Drive* model = new model::item::Drive(descriptor->id(), id);
    assert(model);
    core::control::item::Drive* drive = new core::control::item::Drive(descriptor, model);
    assert(drive);
    return drive;
}

void DriveItemBuilder::__createInternals(core::control::item::Drive* drive, descriptor::item::Drive* descr)
{
    ItemBuilder::_createInternals(drive, descr);
    EquipmentBuilder::_createInternals(drive, descr);
    drive->model()->setSpeed(descr->speed());
    drive->model()->setHyper(descr->hyper());
}

} // namespace builder

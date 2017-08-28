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

#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Drive*
Drive::gen()
{
    descriptor::item::Drive* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::DRIVE_EQUIPMENT)) {
        descr = descriptor::item::genDrive();
    } else {
        descr = descriptor::Manager::get().randDrive();
    }
    assert(descr);
    return gen(descr);
}

control::item::Drive*
Drive::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Drive* descr = descriptor::Manager::get().drive(descriptor_id);
    control::item::Drive* drive = __genTemplate(descr, ob_id);
    __createInternals(drive, descr);
    return drive;
}

control::item::Drive*
Drive::gen(descriptor::item::Drive* descr)
{
    control::item::Drive* drive = __genTemplate(descr);
    __createInternals(drive, descr);
    return drive;
}        

control::item::Drive*
Drive::__genTemplate(descriptor::item::Drive* descr, int_t ob_id)
{
    model::item::Drive* model = new model::item::Drive(descr->id(), ob_id);
    control::item::Drive* drive = new control::item::Drive(descr, model);
    core::Sessions::get().session()->entity()->add(drive);
    return drive;
}

void Drive::__createInternals(control::item::Drive* drive, descriptor::item::Drive* descr)
{
    Item::_createInternals(drive, descr);
    Equipment::_createInternals(drive, descr);
    drive->model()->setSpeed(descr->speed());
    drive->model()->setHyper(descr->hyper());
}

} // namespace item
} // namespace builder

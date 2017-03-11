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


#include "ProtectorBuilder.hpp"
#include <core/model/item/equipment/Protector.hpp>
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/managers/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/descriptor/DescriptorManager.hpp>

#include <ceti/Logger.hpp>

namespace builder {
namespace item {

model::item::Protector*
Protector::getNew()
{
    descriptor::item::Protector* descr = descriptor::Manager::get().randProtector();
    model::item::Protector* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
} 

std::vector<model::item::Protector*>
Protector::getNew(int num)
{
    std::vector<model::item::Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(getNew());
    }
    return result;
}

//model::item::Protector*
//Protector::getNew(const std::string& data)
//{
//    descriptor::item::Protector descr(data);
//    assert(descr->descriptor() != descriptor::type::PROTECTOR_EQUIPMENT);
//    return getNew(descr);
//}

model::item::Protector*
Protector::getNew(descriptor::item::Protector* descr)
{
    model::item::Protector* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}

model::item::Protector*
Protector::__genTemplate(int_t descriptor_id)
{
    model::item::Protector* model = new model::item::Protector(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void
Protector::__createInternals(model::item::Protector* model, descriptor::item::Protector* descr)
{     
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setProtection(descr->protection());
}

} // namespace item
} // namespace builder

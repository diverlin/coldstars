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


#include <builder/dock/AngarBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/slot/VehicleSlot.hpp>
#include <core/slot/ItemSlot.hpp>

#include <core/descriptor/dock/Angar.hpp>
#include <core/model/dock/Angar.hpp>
#include <core/dock/Angar.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Angar*
Angar::gen()
{
    descriptor::Angar* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::ANGAR)) {
        descr = descriptor::genAngar();
    } else {
        descr = descriptor::Manager::get().randAngar();
    }
    return gen(descr);
} 

control::Angar*
Angar::gen(descriptor::Angar* descr)
{
    control::Angar* angar = __createTemplate(descr);
    __createInternals(angar);
    return angar;
}

control::Angar*
Angar::__createTemplate(descriptor::Angar* descr)
{
    model::Angar* model = new model::Angar(descr->id());
    assert(model);

    control::Angar* angar = new control::Angar(descr, model);
    assert(angar);

    manager::Entity::get().add(angar);

    return angar;
}

void
Angar::__createInternals(control::Angar* angar)
{ 
    for (int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM; i++) {
        slot::Vehicle* slot = new slot::Vehicle(i);
        angar->add(slot);
    }

    for (int i=0; i<ANGAR_ITEM_SLOTS_NUM; i++) {
        slot::Item* slot = new slot::Item(entity::Type::CARGO_SLOT);
        angar->add(slot);
    }
    
    //angar->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ANGAR_BACKGROUND));
}

} // namespace builder

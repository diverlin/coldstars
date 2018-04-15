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

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Angar*
AngarBuilder::gen()
{
    core::AngarDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::ANGAR)) {
        descr = core::genAngar();
    } else {
        descr = core::shortcuts::descriptors()->randAngar();
    }
    return gen(descr);
} 

core::control::Angar*
AngarBuilder::gen(core::AngarDescr* descr)
{
    core::control::Angar* angar = __createTemplate(descr);
    __createInternals(angar);
    return angar;
}

core::control::Angar*
AngarBuilder::__createTemplate(core::AngarDescr* descr)
{
    AngarModel* model = new AngarModel(descr->id());
    assert(model);

    core::control::Angar* angar = new core::control::Angar(descr, model);
    assert(angar);

    core::shortcuts::entities()->add(angar);

    return angar;
}

void
AngarBuilder::__createInternals(core::control::Angar* angar)
{ 
    for (int i=0; i<ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM; i++) {
        core::VehicleSlot* slot = new core::VehicleSlot(i);
        angar->add(slot);
    }

    for (int i=0; i<ANGAR_ITEM_SLOTS_NUM; i++) {
        core::ItemSlot* slot = new core::ItemSlot(core::SlotType::CARGO);
        slot->setOffset(i);
        angar->add(slot);
    }
    
    //angar->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ANGAR_BACKGROUND));
}

} // namespace core

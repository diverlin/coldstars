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


#include <core/builder/dock/KosmoportBuilder.hpp>
#include <core/builder/dock/AngarBuilder.hpp>
#include <core/builder/dock/StoreBuilder.hpp>
#include <core/builder/dock/ShopBuilder.hpp>
#include <core/builder/dock/GovermentBuilder.hpp>
#include <core/builder/CommonBuilderHeaders.hpp>

#include <core/descriptor/dock/Kosmoport.hpp>
#include <core/model/dock/Kosmoport.hpp>
#include <core/dock/Kosmoport.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Kosmoport*
KosmoportBuilder::gen()
{
    core::KosmoportDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::KOSMOPORT)) {
        descr = core::genKosmoport();
    } else {
        descr = core::shortcuts::descriptors()->randKosmoport();
    }
    assert(descr);
    return gen(descr);
} 

core::control::Kosmoport*
KosmoportBuilder::gen(core::KosmoportDescr* descr)
{
    core::control::Kosmoport* kosmoport = __createTemplate(descr);
    __createInternals(kosmoport, descr);
    return kosmoport;
}

core::control::Kosmoport*
KosmoportBuilder::__createTemplate(core::KosmoportDescr* descr)
{
    model::Kosmoport* model = new model::Kosmoport(descr->id());
    assert(model);

    core::control::Kosmoport* kosmoport = new core::control::Kosmoport(descr, model);
    assert(kosmoport);

    core::shortcuts::entities()->add(kosmoport);
    return kosmoport;
}

void
KosmoportBuilder::__createInternals(core::control::Kosmoport* kosmoport, core::KosmoportDescr* descr)
{
    kosmoport->bindAngar(core::AngarBuilder::gen());
    kosmoport->bindStore(core::StoreBuilder::gen());
    kosmoport->bindShop(core::ShopBuilder::gen());
    kosmoport->bindGoverment(core::GovermentBuilder::gen());
}

} // namespace core

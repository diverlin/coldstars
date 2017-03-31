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

#include <core/dock/Kosmoport.hpp>

namespace builder {

control::Kosmoport*
Kosmoport::gen()
{
    control::Kosmoport* kosmoport = __createTemplate();
    __createInternals(kosmoport);

    return kosmoport;
} 

control::Kosmoport*
Kosmoport::__createTemplate(int_t id)
{
    control::Kosmoport* kosmoport = new control::Kosmoport(id);
    assert(kosmoport);

    EntityManager::get().reg(kosmoport);
    return kosmoport;
}

void
Kosmoport::__createInternals(control::Kosmoport* kosmoport)
{
    kosmoport->bindAngar(builder::Angar::gen());
    kosmoport->bindStore(builder::Store::gen());
    kosmoport->bindShop(builder::Shop::gen());
    kosmoport->bindGoverment(builder::Goverment::gen());
}

} // namespace builder

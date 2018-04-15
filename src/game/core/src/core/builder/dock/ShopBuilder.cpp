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


#include <builder/dock/ShopBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/descriptor/dock/Shop.hpp>
#include <core/model/dock/Shop.hpp>
#include <core/dock/Shop.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

core::control::Shop*
ShopBuilder::gen()
{
    descriptor::Shop* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::SHOP)) {
        descr = descriptor::genShop();
    } else {
        descr = core::shortcuts::descriptors()->randShop();
    }
    return gen(descr);
}

core::control::Shop*
ShopBuilder::gen(descriptor::Shop* descr)
{
    core::control::Shop* shop = __createTemplate(descr);
    __createInternals(shop);

    return shop;
}

core::control::Shop*
ShopBuilder::__createTemplate(descriptor::Shop* descr)
{
    model::Shop* model = new model::Shop(descr->id());
    assert(model);

    core::control::Shop* shop = new core::control::Shop(descr, model);
    assert(shop);

    core::shortcuts::entities()->add(shop);
    return shop;
} 

void
ShopBuilder::__createInternals(core::control::Shop* shop)
{    
    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SHOP_BACKGROUND);
    //shop->SetTextureObBackground(textureOb_background);
}

} // namespace builder

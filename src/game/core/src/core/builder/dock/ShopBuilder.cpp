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

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Shop*
Shop::gen()
{
    descriptor::Shop* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::SHOP)) {
        descr = descriptor::genShop();
    } else {
        descr = descriptor::Manager::get().randShop();
    }
    return gen(descr);
}

control::Shop*
Shop::gen(descriptor::Shop* descr)
{
    control::Shop* shop = __createTemplate(descr);
    __createInternals(shop);

    return shop;
}

control::Shop*
Shop::__createTemplate(descriptor::Shop* descr)
{
    model::Shop* model = new model::Shop(descr->id());
    assert(model);

    control::Shop* shop = new control::Shop(descr, model);
    assert(shop);

    manager::EntityManager::get().add(shop);
    return shop;
} 

void
Shop::__createInternals(control::Shop* shop)
{    
    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SHOP_BACKGROUND);
    //shop->SetTextureObBackground(textureOb_background);
}

} // namespace builder

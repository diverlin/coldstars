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

#include <dock/Shop.hpp>

namespace builder {

control::Shop*
Shop::gen()
{
    control::Shop* shop = __createTemplate();
    __createInternals(shop);

    return shop;
}

control::Shop*
Shop::__createTemplate(int_t id)
{
    control::Shop* shop = new control::Shop(id);
    assert(shop);

    EntityManager::get().reg(shop);
    return shop;
} 

void
Shop::__createInternals(control::Shop* shop)
{    
    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SHOP_BACKGROUND);
    //shop->SetTextureObBackground(textureOb_background);
}

} // namespace builder

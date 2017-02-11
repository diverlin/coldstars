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


ShopBuilder::ShopBuilder()
{
}

ShopBuilder::~ShopBuilder()
{}

Shop* ShopBuilder::createTemplate(int_t id) const
{
    Shop* shop = new Shop(id);
    assert(shop);

    assert(false);
    //core::global::get().entityManager().reg(shop);

    return shop;
} 

Shop* ShopBuilder::create() const
{
    Shop* shop = createTemplate();
    createInternals(shop);

    return shop;
} 

void ShopBuilder::createInternals(Shop* shop) const
{    
    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::SHOP_BACKGROUND_ID);
    //shop->SetTextureObBackground(textureOb_background);
}


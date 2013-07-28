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

#include "ShopBuilder.hpp"

#include "../docking/Shop.hpp"

#include "../common/IdGenerator.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../resources/TextureManager.hpp"

ShopBuilder& ShopBuilder::Instance()
{
	static ShopBuilder instance;
	return instance;
}

ShopBuilder::~ShopBuilder()
{}

Shop* ShopBuilder::GetNewShopTemplate(INTLONGEST id) const
{
	Shop* shop = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        shop = new Shop(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(shop);
    
    return shop;
} 
 
Shop* ShopBuilder::GetNewShop() const
{
	Shop* shop = GetNewShopTemplate();
	CreateNewInternals(shop);
        
        return shop;
} 
       	
void ShopBuilder::CreateNewInternals(Shop* shop) const
{    
	TextureOb* textureOb_background  = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::SHOP_BACKGROUND_ID); 
	shop->SetTextureObBackground(textureOb_background);
}



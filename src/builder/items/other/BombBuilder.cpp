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

#include "BombBuilder.hpp"
#include "../../../items/others/Bomb.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/id.hpp"
#include "../../../world/EntityManager.hpp"

#include "../../../resources/TextureManager.hpp"

BombBuilder& BombBuilder::Instance()
{
	static BombBuilder instance;
	return instance;
}

BombBuilder::~BombBuilder()
{}

Bomb* BombBuilder::GetNewBombTemplate(int id) const
{
	Bomb* bomb = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

   	try 
        { 
        	bomb = new Bomb(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(bomb);
        
        return bomb;
} 

Bomb* BombBuilder::GetNewBomb(int damage, int radius) const
{
	Bomb* bomb = GetNewBombTemplate();
	CreateNewInternals(bomb, damage, radius);
        
        return bomb;
} 
        	
void BombBuilder::CreateNewInternals(Bomb* bomb, int damage, int radius) const
{     
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BOMB_ID); 
	damage = 300;
        radius = 300;
        
	bomb->SetTextureOb(texOb);
	bomb->SetDamage(damage);
	bomb->SetRadius(radius);
	bomb->SetParentSubTypeId(ENTITY::CARGO_SLOT_ID);
}



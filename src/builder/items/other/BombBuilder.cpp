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

#include "../../../common/Logger.hpp"

BombBuilder& BombBuilder::Instance()
{
	static BombBuilder instance;
	return instance;
}

BombBuilder::~BombBuilder()
{}

void BombBuilder::CreateNewBomb(int id)
{
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
} 
        	
void BombBuilder::CreateNewInternals()
{     
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BOMB_ID); 
	int damage = 300;
        int radius = 300;
        
	bomb->SetTextureOb(texOb);
	bomb->SetDamage(damage);
	bomb->SetRadius(radius);
	bomb->SetFunctionalSlotSubTypeId(ENTITY::CARGO_SLOT_ID);
}



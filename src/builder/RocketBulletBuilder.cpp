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

#include "RocketBulletBuilder.hpp"
#include "../common/id.hpp"
#include "../common/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"

RocketBulletBuilder& RocketBulletBuilder::Instance()
{	
	static RocketBulletBuilder instance;
	return instance;
}	


RocketBulletBuilder::~RocketBulletBuilder() {}


void RocketBulletBuilder::CreateNewRocket(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	rocket = new RocketBullet(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }        
      
        EntityManager::Instance().RegisterEntity(rocket);
}

void RocketBulletBuilder::CreateNewInternals(BulletData data_bullet) 
{
	LifeData data_life;	
        data_life.armor = data_bullet.armor;        

        rocket->SetBulletData(data_bullet);
        
        rocket->SetLifeData(data_life);
        rocket->SetTextureOb(TextureManager::Instance().GetRandomTextureOb(TEXTURE::ROCKET_BULLET_ID));
         
        CreateKorpusGeometry(rocket);
        //CreateShieldGeometry(rocket);

	rocket->CreateDriveComplexTextureDependedStuff();       
}

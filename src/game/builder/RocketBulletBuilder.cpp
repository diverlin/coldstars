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
#include "../spaceobjects/RocketBullet.hpp"

#include "../common/IdGenerator.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/textureOb.hpp"

RocketBulletBuilder& RocketBulletBuilder::Instance()
{	
	static RocketBulletBuilder instance;
	return instance;
}	


RocketBulletBuilder::~RocketBulletBuilder() {}


RocketBullet* RocketBulletBuilder::GetNewRocketBulletTemplate(unsigned long int id) const
{
	RocketBullet* rocket_bullet = NULL;

	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	rocket_bullet = new RocketBullet(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }        
      
        EntityManager::Instance().RegisterEntity(rocket_bullet);
        
        return rocket_bullet;
}

RocketBullet* RocketBulletBuilder::GetNewRocketBullet(const BulletData& data_bullet) const
{
	RocketBullet* rocket_bullet = GetNewRocketBulletTemplate();
	CreateNewInternals(rocket_bullet, data_bullet);	
        
        return rocket_bullet;
}

void RocketBulletBuilder::CreateNewInternals(RocketBullet* rocket_bullet, const BulletData& data_bullet) const
{
	LifeData data_life;	
        data_life.armor = data_bullet.armor;        

        rocket_bullet->SetBulletData(data_bullet);
        
        rocket_bullet->SetLifeData(data_life);
        rocket_bullet->SetTextureOb(TextureManager::Instance().GetRandomTextureOb(TEXTURE::ROCKET_BULLET_ID));
         
        CreateKorpusGeometry(rocket_bullet);

	rocket_bullet->CreateDriveComplexTextureDependedStuff();       
}

void RocketBulletBuilder::CreateKorpusGeometry(RocketBullet* rocket_bullet) const
{
	rocket_bullet->CalculateCollisionRadius();

    	rocket_bullet->GetPoints().initMainQuadPoints(rocket_bullet->GetTextureOb()->GetFrameWidth(), rocket_bullet->GetTextureOb()->GetFrameHeight());
    	rocket_bullet->GetPoints().addMainQuadPoints();
}

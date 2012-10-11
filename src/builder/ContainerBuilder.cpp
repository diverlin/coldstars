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

#include "ContainerBuilder.hpp"
#include "../common/Logger.hpp"
#include "../builder/ItemSlotBuilder.hpp"
#include "../common/id.hpp"
#include "../common/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"

ContainerBuilder& ContainerBuilder::Instance()
{
	static ContainerBuilder instance;
	return instance;
}

ContainerBuilder::~ContainerBuilder()
{}

void ContainerBuilder::CreateNewContainer(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}
        
        try 
        { 
		container = new Container(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(container);
} 
        	
void ContainerBuilder::CreateNewInternals(TextureOb* textureOb, BaseItem* item)
{           
        LifeData data_life;
        data_life.armor = 1;
        data_life.dying_time = 30;
        
        vec3f d_angle;
        d_angle.z      = -getRandInt(10, 100)*0.01;      
        
        container->SetLifeData(data_life);
	container->SetTextureOb(textureOb);
	container->SetDeltaAngle(d_angle);

   	container->CalcCollisionrRadius();
   	container->BindItemSlot(GetNewItemSlot(ENTITY::CARGO_SLOT_ID));
        container->GetItemSlot()->InsertItem(item);
}






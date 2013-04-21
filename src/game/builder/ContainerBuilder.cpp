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
#include "../spaceobjects/Container.hpp"
#include "../common/Logger.hpp"
#include "../builder/ItemSlotBuilder.hpp"
#include "../common/IdGenerator.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"

#include "../animations/AnimationConstantRotationAxisZ.hpp"

ContainerBuilder& ContainerBuilder::Instance()
{
	static ContainerBuilder instance;
	return instance;
}

ContainerBuilder::~ContainerBuilder()
{}

Container* ContainerBuilder::GetNewContainerTemplate(unsigned long int id) const
{
	Container* container = NULL;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
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
        
        return container;
} 

Container* ContainerBuilder::GetNewContainer(TextureOb* textureOb, BaseItem* item) const
{
	Container* container = GetNewContainerTemplate();
	CreateNewInternals(container, textureOb, item);
        
        return container;
} 
       	
void ContainerBuilder::CreateNewInternals(Container* container, TextureOb* textureOb, BaseItem* item) const
{           
        LifeData data_life;
        data_life.armor = 1;
        data_life.dying_time = 30;
        
        vec3f d_angle;
        d_angle.z = -getRandInt(10, 100)*0.01;      
        
        container->SetLifeData(data_life);
	container->SetTextureOb(textureOb);
	
	float step = getRandInt(10, 100)*0.01;
	AnimationConstantRotationAxisZ* animation_program = new AnimationConstantRotationAxisZ(step);
	container->SetRenderAnimation(animation_program);

       	container->SetGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);
        
   	container->CalculateCollisionRadius();
   	container->BindItemSlot(GetNewItemSlot(ENTITY::CARGO_SLOT_ID));
        container->GetItemSlot()->InsertItem(item);
}






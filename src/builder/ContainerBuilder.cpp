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


Container* GetNewContainer(TextureOb* textureOb, BaseItem* item, int id)
{
       	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	} 
        
        LifeData data_life;
        data_life.armor = getRandInt(1,6);
        data_life.dying_time = 30;
        
        vec3f d_angle;
        d_angle.z      = -getRandInt(10, 100)*0.01;      
       
        Container* container = new Container(id);
        
        container->SetLifeData(data_life);
	container->SetTextureOb(textureOb);
	container->SetDeltaAngle(d_angle);

   	container->CalcCollisionrRadius();
	container->GetPoints().CreateCenter();
        container->GetItemSlot()->InsertItem(item);
}

//ContainerBuilder& ContainerBuilder::Instance()
//{
	//static ContainerBuilder instance;
	//return instance;
//}

//ContainerBuilder::~ContainerBuilder()
//{}

//void ContainerBuilder::CreateNewContainer(int id)
//{
	//if (id == NONE_ID)
	//{
		//id = g_ID_GENERATOR.getNextId();
	//}

	//Container* container = new Container(id);

//} 
        	
//void ContainerBuilder::CreateNewInternals()
//{
        //LifeData data_life;
        //data_life.armor = getRandInt(1,6);
        //data_life.dying_time = 30;
        
        //vec3f d_angle;
        //d_angle.z      = -getRandInt(10, 100)*0.01; 
        
	//TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::CONTAINER_ID); 
        
        //container->SetLifeData(data_life);
	//container->SetTextureOb(texOb);
	//container->SetDeltaAngle(d_angle);

	//container->postCreateInit();
//}

  	

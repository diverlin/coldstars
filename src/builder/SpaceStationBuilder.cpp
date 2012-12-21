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

#include "SpaceStationBuilder.hpp"
#include "KosmoportBuilder.hpp"
#include "../docking/Kosmoport.hpp"

#include "../common/id.hpp"
#include "../managers/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/textureOb.hpp"

SpaceStationBuilder& SpaceStationBuilder::Instance()
{	
	static SpaceStationBuilder instance;
	return instance;
}	

SpaceStationBuilder::~SpaceStationBuilder() {}

SpaceStation* SpaceStationBuilder::GetNewSpaceStationTemplate(int id) const
{
	SpaceStation* spacestation = NULL;
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}
	        
	try 
        { 
        	spacestation = new SpaceStation(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(spacestation);
        
        return spacestation;
}

SpaceStation* SpaceStationBuilder::GetNewSpaceStation() const
{
	SpaceStation* spacestation = GetNewSpaceStationTemplate();
        CreateNewInternals(spacestation);
        
        return spacestation;
}

void SpaceStationBuilder::CreateNewInternals(SpaceStation* spacestation) const
{
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::SPACESTATION_ID); 
       
       	int protection_rate = 50;
       	//if (subtype_id == ENTITY::WARRIOR_ID)
        //{
        	//protection_rate = 5;
        //}
        
        VehicleKorpusData data_korpus;
    	data_korpus.space       = 2500 + getRandInt(0, 1000);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 10000000;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = 5;
       
        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.draw_turrels = true; 
                           
    	spacestation->SetSubSubTypeId(SPACESTATION::MILITARY_ID);
    	spacestation->SetKorpusData(data_korpus);
	spacestation->SetTextureOb(texOb);
	spacestation->SetLifeData(data_life);
    	
	CreateKorpusGeometry(spacestation);

        spacestation->CreateDriveComplexTextureDependedStuff();
        spacestation->CreateProtectionComplexTextureDependedStuff();
                
        CreateItemSlots(spacestation);
                
	spacestation->BindLand(KosmoportBuilder::Instance().GetNewKosmoport());
}

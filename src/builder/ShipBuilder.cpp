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

#include "ShipBuilder.hpp"
#include "../common/id.hpp"
#include "../common/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"

#include "../resources/TextureManager.hpp"
#include "../resources/textureOb.hpp"

ShipBuilder& ShipBuilder::Instance()
{	
	static ShipBuilder instance;
	return instance;
}	

ShipBuilder::~ShipBuilder() {}

Ship* ShipBuilder::GetNewShipTemplate(int id) const
{
	Ship* ship = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	ship = new Ship(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(ship);
        
        return ship;
}

Ship* ShipBuilder::GetNewShip(int race_id, int subsubtype_id, int size_id, int weapons_num) const
{
        Ship* ship = GetNewShipTemplate();
        CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);     
        
        return ship;
}

Ship* ShipBuilder::GetNewShip() const
{
	int race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
	int subsubtype_id = ENTITY::WARRIOR_ID;
	int size_id = getRandInt(1, 9);
	int weapons_num = size_id;
        	
        Ship* ship = GetNewShipTemplate();
        CreateNewInternals(ship, race_id, subsubtype_id, size_id, weapons_num);     
        
        return ship;
}

void ShipBuilder::CreateNewInternals(Ship* ship, int race_id, int subsubtype_id, int size_id, int weapons_num) const
{
	TextureOb* texOb = TextureManager::Instance().GetRandomShipTexObWithFollowingAtrributes(race_id, subsubtype_id, size_id); 

       	int protection_rate = 1;
       	if (subsubtype_id == ENTITY::WARRIOR_ID)
        {
        	protection_rate = 2;
        }
        
        VehicleKorpusData data_korpus;
    	data_korpus.space       = size_id*100 + getRandInt(0, 100);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = protection_rate*size_id/(SIZE_1_ID);
    	data_korpus.temperature = 100;
        data_korpus.price       = getRandInt(200, 400)*size_id;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = weapons_num;       

    	LifeData data_life;
        data_life.armor      = data_korpus.armor*0.1;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
    	if (texOb->size_id > size_threshold)
       		data_korpus.draw_turrels = true; 
    	else
       		data_korpus.draw_turrels = false; 
	
	ship->SetSubSubTypeId(subsubtype_id);
	ship->SetKorpusData(data_korpus);
	ship->SetTextureOb(texOb);
	ship->SetLifeData(data_life);
	
	CreateKorpusGeometry(ship);

	ship->CreateDriveComplexTextureDependedStuff();
	ship->CreateProtectionComplexTextureDependedStuff();
	                            
        CreateItemSlots(ship);
}

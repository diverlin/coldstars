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

#include "SatelliteBuilder.hpp"

SatelliteBuilder& SatelliteBuilder::Instance()
{	
	static SatelliteBuilder instance;
	return instance;
}	


SatelliteBuilder::~SatelliteBuilder() {}


void SatelliteBuilder::CreateNewSatellite(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}
	 	
	try 
        { 
        	satellite = new Satellite(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }

        CreateProtectionComplex(satellite);
        CreateDriveComplex(satellite);
        CreateWeaponsComplex(satellite); 
        
        EntityManager::Instance().RegisterEntity(satellite);
}

void SatelliteBuilder::CreateNewInternals() 
{
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::SATELLITE_ID);  
	
       	int protection_rate = 1;
       	//if (subtype_id == CLASS::WARRIOR_ID)
        //{
        	//protection_rate = 1;
        //}
        
        VehicleKorpusData data_korpus;
    	data_korpus.space       = 60 + getRandInt(0, 20);
    	data_korpus.armor       = 10*data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 1000;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = 2;
 
        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.draw_turrels = true;       
	
	satellite->SetKorpusData(data_korpus);
	satellite->SetLifeData(data_life);
	satellite->SetTextureOb(texOb);
	
	CreateKorpusGeometry(satellite);

        CreateDriveComplexTextureDependedStuff(satellite);
        CreateProtectionComplexTextureDependedStuff(satellite);
                        
        CreateItemSlots(satellite);
}

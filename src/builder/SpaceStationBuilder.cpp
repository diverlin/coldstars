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


SpaceStationBuilder& SpaceStationBuilder::Instance()
{	
	static SpaceStationBuilder instance;
	return instance;
}	


SpaceStationBuilder::~SpaceStationBuilder() {}


void SpaceStationBuilder::CreateNewSpaceStation(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        spacestation = new SpaceStation(id);
        EntityManager::Instance().RegisterEntity(spacestation);
}

void SpaceStationBuilder::CreateNewInternals() 
{
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SPACESTATION_ID); 
       
       	int protection_rate = 1;
       	//if (subtype_id == CLASS::WARRIOR_ID)
        //{
        	protection_rate = 5;
        //}
        
        KorpusData data_korpus;
    	data_korpus.space       = 2500 + getRandInt(0, 1000);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 10000000;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = 5;
       
        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.draw_turrels = true; 
                           
    	spacestation->SetSubTypeId(SPACESTATION::MILITARY_ID);
    	spacestation->SetKorpusData(data_korpus);
	spacestation->SetTextureOb(texOb);
	spacestation->SetLifeData(data_life);
    	
	CreateKorpusGeometry(spacestation);
        CreateKorpusGui(spacestation);
        CreateDriveComplex(spacestation);
        CreateWeaponsComplex(spacestation);
        CreateProtectionComplex(spacestation);	
        CreateEquipmentSlots(spacestation);
                
    	spacestation->CreateLand(RACE::R0_ID);
}

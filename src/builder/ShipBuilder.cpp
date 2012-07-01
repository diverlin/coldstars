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


ShipBuilder& ShipBuilder::Instance()
{	
	static ShipBuilder instance;
	return instance;
}	


ShipBuilder::~ShipBuilder() {}


void ShipBuilder::CreateNewShip(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
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
}

void ShipBuilder::CreateNewInternals(int race_id, int subsubtype_id, int size_id, int weapons_num) 
{
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomShipTexObWithFollowingAtrributes(race_id, subsubtype_id, size_id); 
       
       	int protection_rate = 1;
       	if (subsubtype_id == CLASS::WARRIOR_ID)
        {
        	protection_rate = 3;
        }
        
        KorpusData data_korpus;
    	data_korpus.space       = size_id*150 + getRandInt(0, 100);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = size_id/2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = getRandInt(200, 400)*size_id;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = weapons_num;
       

    	LifeData data_life;
        data_life.armor      = data_korpus.armor;
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
        CreateKorpusGui(ship);
        
        CreateProtectionComplex(ship);
        CreateDriveComplex(ship);
        CreateWeaponsComplex(ship);
                                
        CreateEquipmentSlots(ship);
}

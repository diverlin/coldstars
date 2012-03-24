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


Ship :: Ship()
{}

Ship :: ~Ship()
{} 


//overriding
void Ship :: updateInfo()
{
	info.clear();

    	info.addTitleStr("SHIP");
    	info.addNameStr("id/ss_id:");          	info.addValueStr( int2str(data_id.id) + " / " + int2str(starsystem->getId()) );
    	info.addNameStr("race:");   		info.addValueStr( returnRaceStringByRaceId(texOb->race_id) ); 
    	info.addNameStr("armor/max:");     	info.addValueStr( int2str(data_life.armor) + "/" + int2str(data_korpus.armor) );
    	info.addNameStr("size id:");     	info.addValueStr( int2str(texOb->size_id) );
    	info.addNameStr("space/free:");   	info.addValueStr( int2str(data_korpus.space) + "/" + int2str(data_korpus.space - propetries.mass) );
    	info.addNameStr("mass:");   		info.addValueStr( int2str(propetries.mass) );
    	info.addNameStr("energy:");            	info.addValueStr( int2str(propetries.energy) );
	info.addNameStr("temp.:");       	info.addValueStr( int2str(data_korpus.temperature) );
        info.addNameStr("radius:");    		info.addValueStr( int2str(propetries.radius) );
    	info.addNameStr("protect:");        	info.addValueStr( returnProtectionStr() );
	info.addNameStr("speedx:");       	info.addValueStr(int2str(int(propetries.speed*100)) );
}


void Ship :: update_inSpace(int time, bool show_effect)
{   
	checkDeath(show_effect);
	if (time > 0)
	{
		points.update();   
		weapon_complex->fire(time, show_effect);

    		if (ableTo.DRIVE == true) 
    		{ 
       			drive_complex->update_inSpace_inDynamic();
    		}
    
    		if (ableTo.GRAB == true)
    		{
    			GrappleMicroProgramm();
    		}
    	}
}


void Ship :: updateRenderStuff()
{
    	//points.update(); 
    	shield->update();
    	
    	if (ableTo.DRIVE == true)
    	{
       		drive_trail->update();
    	}
}

void Ship :: render_inSpace() const
{   
        if (ableTo.GRAB == true)
        {
                RenderGrappleTrail();
        }
        
    	RenderKorpus();
    	
    	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }

    	if (ableTo.DRIVE == true)
    	{
		RenderDriveTrail();
    	}
    	
    	if (ableTo.PROTECT == true)
    	{
        	RenderShield(); 
        }
}


void Ship :: render_atPlanet() const
{
	RenderKorpus();
	
	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }
}		



Ship* shipGenerator(int race_id, int subtype_id, int size_id, int weapons_num)
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 
       
       	int protection_rate = 1;
       	if (subtype_id == WARRIOR_ID)
        {
        	protection_rate = 3;
        }
        
        KorpusData data_korpus;
    	data_korpus.space       = size_id*150 + getRandInt(0, 100);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = size_id/2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = getRandInt(200, 400)*size_id;

        data_korpus.inhibit_GRAPPLE = false;
        data_korpus.weapon_slot_num = weapons_num;
            
            
        LifeData data_life;
        data_life.armor = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
       
        IdData data_id;
        data_id.id      = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id = SHIP_ID;
    	//subtype_id = ;       

        int size_threshold = 2; 
    	if (texOb->size_id > size_threshold)
       		data_korpus.render_TURRELS = true; 
    	else
       		data_korpus.render_TURRELS = false; 
                           
    	Ship* ship = new Ship();
    	ship->SetKorpusData(data_korpus);
	ship->setTextureOb(texOb);
	ship->setIdData(data_id);
	ship->setLifeData(data_life);
    	
    	ship->PostCreateInit();
    	    
    	GetEntityManager().RegisterEntity(ship);
    	
    	return ship;
}



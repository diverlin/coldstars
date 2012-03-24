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



Satellite :: Satellite()
{        
    	mass = getRandInt(SATELLITE_MASS_MIN, SATELLITE_MASS_MAX);
    	orbit = new Orbit();
    	
    	d_angle.z = 1.0f;
}

Satellite :: ~Satellite() 
{
	delete orbit;
}
    
Orbit* Satellite :: getOrbit() const { return orbit; }
    				
void Satellite :: update_inSpace(int time, bool show_effect)
{
	checkDeath(show_effect);
	if (time > 0)
	{
		orbit->updatePosition();

		//printf("sat orbit =%f,%f\n", orbit->getPosition().x, orbit->getPosition().y);
		//if (parent != NULL)
		//{		
			vec2f new_pos;
			new_pos.x = parent->getPoints()->getCenter().x + orbit->getPosition().x;
			new_pos.y = parent->getPoints()->getCenter().y + orbit->getPosition().y;
			points.setCenter(new_pos);
			points.update();
		//}
		//else
		//{
			//points.setCenter(orbit->getPosition());
		//}
	}
}


void Satellite :: updateInfo()
{
	info.clear();

    	info.addTitleStr("SATELLITE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            


void Satellite :: updateRenderStuff()
{
    	//points.update(); 
    	shield->update();
    	
    	this->updateRotation();
	points.setAngle(angle.z);
    	//printf("3. angle = %f\n", angle.z);
    	points.update();
    		
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void Satellite :: render_inSpace() const
{   
        //if (ableTo.GRAB == true)
        //{
                //renderGrappleTrail();
        //}
        
    	RenderKorpus();
    	
    	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }

    	//if (ableTo.DRIVE == true)
    	//{
		//renderDriveTrail();
    	//}
    	
    	if (ableTo.PROTECT == true)
    	{
        	RenderShield(); 
        }
}


void Satellite :: render_atPlanet() const
{
	RenderKorpus();
	
	if (data_korpus.render_TURRELS == true)
    	{
        	weapon_complex->renderTurrels();
        }
}		


Satellite* getNewSatellite()
{
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(SATELLITE_TEXTURE_ID);  
	
       	int protection_rate = 1;
       	//if (subtype_id == WARRIOR_ID)
        //{
        	protection_rate = 1;
        //}
        
        KorpusData data_korpus;
    	data_korpus.space       = 60 + getRandInt(0, 20);
    	data_korpus.armor       = 10*data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 1000;

        data_korpus.inhibit_GRAPPLE = true;
        data_korpus.weapon_slot_num = 2;
            
            
        LifeData data_life;
        data_life.armor = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
       
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = SATELLITE_ID;
    	//data_id.subtype_id = MILITARY_ID;       

        int size_threshold = 2; 
	data_korpus.render_TURRELS = true;       

	Satellite* satellite = new Satellite();
	satellite->SetKorpusData(data_korpus);
	satellite->setIdData(data_id);
	satellite->setLifeData(data_life);
	satellite->setTextureOb(texOb);
	
	satellite->PostCreateInit();
	
	return satellite;
}





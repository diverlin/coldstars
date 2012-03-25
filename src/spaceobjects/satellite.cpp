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
			new_pos.x = parent->GetPoints().getCenter().x + orbit->getPosition().x;
			new_pos.y = parent->GetPoints().getCenter().y + orbit->getPosition().y;
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
    	protection_complex->GetShieldEffect()->update();
    	
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







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



SpaceStation :: SpaceStation(int race_id)
{        
    	mass = getRandInt(STARBASE_MASS_MIN, STARBASE_MASS_MAX);
	land = NULL;
}

SpaceStation :: ~SpaceStation() 
{
	delete land;
}    
    
LandBase* SpaceStation :: getLand() const { return land; }
	
	      
void SpaceStation :: createLand(int race_id)
{
	land = new Kosmoport(race_id);
}
	        	
		
void SpaceStation :: update_inSpace(int time, bool show_effect)
{
	checkDeath(show_effect);
	if (time > 0)
	{}
}


//overriding
void SpaceStation :: updateInfo()
{
	info.clear();

    	info.addTitleStr("StarBase" + int2str(data_id.subtype_id));

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
} 



void SpaceStation :: updateRenderStuff()
{
    	//points.update(); 
    	shield->update();
    	
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void SpaceStation :: render_inSpace() const
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


void SpaceStation :: render_atPlanet() const
{
	//renderKorpus();
	
	//if (data_korpus.render_TURRELS == true)
    	//{
        	//weapon_complex->renderTurrels();
        //}
}		






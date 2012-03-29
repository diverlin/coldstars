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
    	info.addNameStr("id/ss_id:");          	info.addValueStr( int2str(data_id.id) + " / " + int2str(starsystem->GetId()) );
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
		weapon_complex->Fire(time, show_effect);

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
    	protection_complex->GetShieldEffect()->update();
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
        	weapon_complex->RenderTurrels();
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
        	weapon_complex->RenderTurrels();
        }
}		







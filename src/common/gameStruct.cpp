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

#include "gameStruct.hpp"

PlanetData :: PlanetData()
{
        scale = 0; 
    	orbit_center = vec2f(0, 0); 
    	radius_A = 0;
    	radius_B = 0; 
    	orbit_phi_inD = 0.0;
    	speed = 0.0;
}


Color4f :: Color4f()
{
	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;
}


Color4i :: Color4i()
{
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}


VisionStatus :: VisionStatus()
{
   	ASTEROID  = false;
	CONTAINER = false;
   	MINERAL   = false;

   	RANGER   = false;
   	WARRIOR  = false;
   	TRADER   = false;  
   	PIRAT    = false;
   	DIPLOMAT = false;
}



NeedsToDo :: NeedsToDo()
{
  	REPAIR_KORPUS    = false;
  	REPAIR_EQUIPMENT = false;
        
  	GET_FUEL    = false;
   	GET_BULLETS = false;
        GET_CREDITS = false;
        
   	BUY         = false;
   	SELL        = false;
}


AbilitiesStatus :: AbilitiesStatus()
{
        RADAR    = false;
   	DRIVE    = false;
   	HJUMP    = false;
   	ENERGIZE = false;
   	PROTECT  = false;
   	REPAIR   = false;
   	FREEZE   = false;
   	GRAB     = false;
   	SCAN     = false;
   	//FIRE     = false;
}


KorpusData :: KorpusData()
{        
        space       = 0;
        armor       = 0;
        protection  = 0; 
        temperature = 0;   
        
        price = 0;
       
        inhibit_GRAPPLE = false;
        render_TURRELS = false;
        
        weapon_slot_num = 0;
}



ShipPropetries :: ShipPropetries()
{       
        protection   = 0;
        radius       = 0;
        speed        = 0;  // depends on mass and drive

        hyper        = 0;  // depends on drive and bak
        repair       = 0; // depends on droid
        freeze       = 0; // depends on freezer
        scan         = 0;   // depends on scaner
        
        energy       = 0;
        temperature  = 0;
        
        average_damage = 0;
        average_fire_radius = 0;
}


LifeData :: LifeData()
{
        is_alive = true;
        armor = 1;
        	
        dying_time = 0;
        
        garbage_ready = false;
}	


IdData :: IdData()
{
	id         = -1;
	type_id    = -1;
	subtype_id = -1;
}


ParticleData :: ParticleData()
{	
      	size_start = 0.0;
      	size_end   = 0.0;
        d_size     = 0.0;

      	velocity_start = 0.0;
      	velocity_end   = 0.0;
	d_velocity     = 0.0;
        
        frame = 0;
}
	

WeaponSelector :: WeaponSelector()
{
	slot_1 = false;
     	slot_2 = false;
     	slot_3 = false;
     	slot_4 = false;
     	slot_5 = false;
}

     	
void WeaponSelector :: setAll(bool _status)
{
	slot_1 = _status;
     	slot_2 = _status;
     	slot_3 = _status;
     	slot_4 = _status;
     	slot_5 = _status;
}

bool WeaponSelector :: isAnySelected() const
{
	return (slot_1 or slot_2 or slot_3 or slot_4 or slot_5);
}
		


ControlWord :: ControlWord()
{
	scan = false;
	grapple = false;

	worldmap = false;
	ship_info = false;
	planet_info = false;	
	planet_orbits = false;
	radar_radius = false;
}

ControlWord :: ~ControlWord()
{}



AngleData :: AngleData()
{}

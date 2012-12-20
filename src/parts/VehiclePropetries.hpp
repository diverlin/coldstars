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

#ifndef VEHICLEPROPETRIES_H
#define VEHICLEPROPETRIES_H

/* this data is changed during game play, the propetries depends on many factors */
struct VehiclePropetries
{    
	int free_space;
	
	int protection;
	int radar;
	int speed;  // depends on mass and drive

	int energy;
	int hyper;  // depends on drive
	int fuel;    // depends on bak
	int repair; // depends on droid
	int freeze; // depends on freezer
	int scan;   // depends on scaner

        int grab_strength;
        int grab_radius;
        
	int temperature;
	
	int artefact_gravity;
	int artefact_protection;
		
	// simplification
	int average_damage;
	int average_fire_radius;
	
	bool equipment_radar;
	bool shield_effect_enabled;
	bool hibernate_mode_enabled;

	VehiclePropetries():
	free_space(0),
	protection(0),
        radar(0),
        speed(0),
        hyper(0),
        fuel(0),
        repair(0),
        freeze(0),
        scan(0),    
        grab_radius(0),
        grab_strength(0),
            
        energy(0),
        temperature(0),
        artefact_gravity(0),
        artefact_protection(0),
        
        average_damage(0),
        average_fire_radius(0),
        equipment_radar(false),
        shield_effect_enabled(false),
        hibernate_mode_enabled(false)
        {}
};

#endif 

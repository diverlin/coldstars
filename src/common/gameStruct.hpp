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

#ifndef GAMESTRUCT_H
#define GAMESTRUCT_H

struct PlanetData
{
        PlanetData();
        
	float scale; 
    	vec2f orbit_center; 
    	int radius_A;
    	int radius_B; 
    	float orbit_phi_inD;
    	float speed;
};


struct Color4f
{
	Color4f();

   	float r;
   	float g;
   	float b;
   	float a;
};


struct Color4i
{
	Color4i();

   	int r;
   	int g;
   	int b;
   	int a;
};

struct VisionStatus
{
	VisionStatus();
	
   	bool ASTEROID;
   	bool CONTAINER;
   	bool MINERAL;

   	bool RANGER;
   	bool WARRIOR;
   	bool TRADER;  
   	bool PIRAT;
   	bool DIPLOMAT;
};



struct NeedsToDo
{
	NeedsToDo();

  	bool REPAIR_KORPUS;
  	bool REPAIR_EQUIPMENT;
        
  	bool GET_FUEL;
   	bool GET_BULLETS;
        bool GET_CREDITS;
        
   	bool BUY;
   	bool SELL;
};

struct AbilitiesStatus
{
        /* this structure shows what feature are avaliable for ship */
        AbilitiesStatus();
         
        bool RADAR;
   	bool DRIVE;
   	bool HJUMP;
   	bool ENERGIZE;
   	bool PROTECT;
   	bool REPAIR;
   	bool FREEZE;
   	bool GRAB;
   	bool SCAN;
   	bool FIRE;
};


struct KorpusData
{
        /* this data depends only on korpus and cannot be changed by artefacts/items */        
        KorpusData();
        
        unsigned int space;
        unsigned int armor;
        unsigned int protection; 
        unsigned int temperature;   
        
        unsigned int price;
        
        float collision_radius;
        
        bool inhibit_GRAPPLE;
        bool render_TURRELS;
        
        unsigned int weapon_slot_num;
};

struct ShipPropetries
{       
        /* this data is changed during game play, the propetries depends on many factors */
        ShipPropetries();
        
        int protection;
        int radius;
        int mass;   // depends on all items mass
        int speed;  // depends on mass and drive

        int hyper;  // depends on drive and bak
        int repair; // depends on droid
        int freeze; // depends on freezer
        int scan;   // depends on scaner
        
        int energy;
        int temperature;
        
        // simplification
        int average_damage;
        int average_fire_radius;
};

struct LifeData
{
	LifeData();
	
        bool is_alive;
        int armor;
        	
        bool is_dying;
        int dying_time;
        
        bool is_explosed;
};


struct IdData  
{
	IdData();
	
	int id;
	int type_id;
	int subtype_id;
};


 
struct ParticleData
{
	ParticleData();
	
      	float alpha_start;
      	float alpha_end;
      	float d_alpha;
      		
      	float size_start;
      	float size_end;
        float d_size;

      	float velocity_start;
      	float velocity_end;
	float d_velocity;
};




struct EquipmentCommonData 
{
	EquipmentCommonData();
	
	unsigned int modules_num_max; 
	unsigned int condition_max; 
	unsigned int deterioration_rate;
	unsigned int mass; 
};




class WeaponSelector
{
	public:
		WeaponSelector();
		
    		bool slot_1;
     		bool slot_2;
     		bool slot_3;
     		bool slot_4;
     		bool slot_5;
     	
		void setAll(bool);
};


class ControlWord
{
	public:
		bool scan;
		bool grapple;

		bool worldmap;
		bool ship_info;
		bool planet_info;	
		bool planet_orbits;
		bool radar_radius;
		
		ControlWord();
		~ControlWord();
};


struct AngleData
{
	AngleData();
	
	float x;
	float y;
	float z;
	float d_x;
	float d_y;
	float d_z;
};

#endif

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

struct See
{
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
  	bool REPAIR;
  	bool CHARGE;
   	bool GETBULLETS;
   	bool BUY;
   	bool SELL;
};

struct Abilities
{
        /* this structure explain hat feature are avaliable for ship */ 
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
        unsigned int protection; 
        unsigned int space;
        unsigned int armor;
        unsigned int temperature;   //???
        
        unsigned int price;
        
        unsigned int size_id;
        float collision_radius;
        
        bool inhibit_GRAPPLE;
        bool render_TURRELS;
        unsigned int weapon_slot_num;
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
	int id;
	int type_id;
	int subtype_id;
};


 
struct ParticleData
{
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
	unsigned int modules_num_max; 
	unsigned int condition_max; 
	unsigned int deterioration_rate;
	unsigned int mass; 
};




class WeaponSelector
{
	public:
    		bool slot_1;
     		bool slot_2;
     		bool slot_3;
     		bool slot_4;
     		bool slot_5;
     	
		void setAll(bool status)
		{
			slot_1 = status;
     			slot_2 = status;
     			slot_3 = status;
     			slot_4 = status;
     			slot_5 = status;
		}
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

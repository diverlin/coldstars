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

#include "../common/myVector.hpp"

struct PlanetData
{
	PlanetData();

	vec2f orbit_center; 
	int radius_A;
	int radius_B; 
	float orbit_phi_inD;
	float speed;
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
	//bool FIRE;
};



struct LifeData
{
	LifeData();

	bool is_alive;
	int armor;

	int dying_time;

	bool garbage_ready;
};


struct IdData  
{
	IdData();

	int id;
	int type_id;
	int subtype_id;
	int subsubtype_id;
};



struct ParticleData
{
	ParticleData();

	float size_start;
	float size_end;
	float d_size;

	float velocity_start;
	float velocity_end;
	float d_velocity;

	Color4f color_start;
	Color4f color_end;
	Color4f color_delta;

	int frame;
};



struct AngleData
{
	AngleData();

	vec3f angle;
	vec3f d_angle;
};

#endif

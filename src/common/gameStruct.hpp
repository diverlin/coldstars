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

#include "../resources/objLoader.hpp"
#include "../common/myVector.hpp"


static struct
{
	ObjMeshInstance* SPHERE_MESH; 
	ObjMeshInstance* DEFORMED_SPHERE_MESH;
} MeshCollector;

static struct
{
	std::vector<int> RACES_ALL_vec;
	std::vector<int> RACES_GOOD_vec;
	std::vector<int> RACES_EVIL_vec;

	std::vector<int> RACE0_ALLOWED_SUBTYPE_vec;
	std::vector<int> RACE1_ALLOWED_SUBTYPE_vec;
	std::vector<int> RACE2_ALLOWED_SUBTYPE_vec;
	std::vector<int> RACE3_ALLOWED_SUBTYPE_vec; 
	std::vector<int> RACE4_ALLOWED_SUBTYPE_vec;
	std::vector<int> RACE6_ALLOWED_SUBTYPE_vec;
	std::vector<int> RACE7_ALLOWED_SUBTYPE_vec;
	
} RaceInformationCollector; 



struct PlanetData
{
	PlanetData();

	vec2f orbit_center; 
	int radius_A;
	int radius_B; 
	float orbit_phi_inD;
	float speed;
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
	bool is_alive;
	int armor;

	int dying_time;

	bool garbage_ready;

	LifeData():
	is_alive(true),
        armor(1),
        dying_time(0),
        garbage_ready(false) {};
        
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

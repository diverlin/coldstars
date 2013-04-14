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

#include "../render/Mesh.hpp"
#include "../common/myVector.hpp"
#include "../common/constants.hpp"

class RaceInformationCollector
{
	public:
		static RaceInformationCollector& Instance();
		~RaceInformationCollector() {};
		
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
                
                std::vector<int> SUBSUBTYPE_vec;
		
		bool IsGood(int) const;
	
	private:
		RaceInformationCollector() {};
		RaceInformationCollector(const RaceInformationCollector&) = delete;
		RaceInformationCollector& operator=(const RaceInformationCollector&) = delete;
	
}; 



struct PlanetData
{
	vec2f orbit_center; 
	int radius_A;
	int radius_B; 
	float orbit_phi_inD;
	float speed;
	bool clockwise;

	PlanetData():
	orbit_center(vec2f(0, 0)),
	radius_A(0),
    	radius_B(0), 
    	orbit_phi_inD(0.0),
    	speed(0.0),
    	clockwise(false)
    	{};
};

struct LifeData
{
	bool is_alive;
	int armor;

	int life_time;
	int dying_time;

	bool garbage_ready;

	LifeData():
	is_alive(true),
        armor(1),
        life_time(0),
        dying_time(0),
        garbage_ready(false) 
        {};
        
};


struct IdData  
{
	unsigned long int id;
	int type_id;
	int subtype_id;
	int subsubtype_id;

	IdData():
        id(NONE_ID),
	type_id(NONE_ID),
	subtype_id(NONE_ID),
	subsubtype_id(NONE_ID)
        {}
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

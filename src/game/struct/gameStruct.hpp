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
#include "../math/myVector.hpp"
#include "../common/constants.hpp"
#include "../common/RaceTypes.hpp"

class RaceInformationCollector
{
	public:
		static RaceInformationCollector& Instance();
		~RaceInformationCollector() {};
		
		std::vector<TYPE::RACE> RACES_ALL_vec;
		std::vector<TYPE::RACE> RACES_GOOD_vec;
		std::vector<TYPE::RACE> RACES_EVIL_vec;

		std::vector<TYPE::ENTITY> RACE0_ALLOWED_SUBTYPE_vec;
		std::vector<TYPE::ENTITY> RACE1_ALLOWED_SUBTYPE_vec;
		std::vector<TYPE::ENTITY> RACE2_ALLOWED_SUBTYPE_vec;
		std::vector<TYPE::ENTITY> RACE3_ALLOWED_SUBTYPE_vec; 
		std::vector<TYPE::ENTITY> RACE4_ALLOWED_SUBTYPE_vec;
		std::vector<TYPE::ENTITY> RACE6_ALLOWED_SUBTYPE_vec;
		std::vector<TYPE::ENTITY> RACE7_ALLOWED_SUBTYPE_vec;
                
        std::vector<TYPE::ENTITY> SUBSUBTYPE_vec;
		
		bool IsGood(TYPE::RACE) const;
	
	private:
		RaceInformationCollector() {};
		RaceInformationCollector(const RaceInformationCollector&) = delete;
		RaceInformationCollector& operator=(const RaceInformationCollector&) = delete;
	
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



struct ParticleData
{
	ParticleData();

	float size_start;
	float size_end;
	float d_size;

	float velocity_start;
	float velocity_end;
	float d_velocity;

	Color4<float> color_start;
	Color4<float> color_end;
	Color4<float> color_delta;

	int frame;
};



struct AngleData
{
	AngleData();

	Vec3<float> angle;
	Vec3<float> d_angle;
};

#endif

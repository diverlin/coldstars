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
#include "../common/constants.hpp"
#include "../common/rand.hpp"

RaceInformationCollector& RaceInformationCollector::Instance()
{
	static RaceInformationCollector instance;
	return instance;
}

bool RaceInformationCollector::IsGood(RACE::TYPE race_id) const
{
	for (unsigned int i=0; i<RACES_GOOD_vec.size(); i++)
	{
		if (race_id == RACES_GOOD_vec[i])
		{
			return true;
		}
	}
	
	return false;
}		
		

ParticleData::ParticleData()
{	
      	size_start = 0.0;
      	size_end   = 0.0;
        d_size     = 0.0;

      	velocity_start = 0.0;
      	velocity_end   = 0.0;
	d_velocity     = 0.0;
        
        frame = 0;
}
	



AngleData::AngleData()
{}

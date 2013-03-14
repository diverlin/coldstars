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


#ifndef DISTANTNEBULAEFFECT_H
#define DISTANTNEBULAEFFECT_H

#include "../effects/BaseBackGroundEffect.hpp"    
#include "../common/constants.hpp"

class DistantNebulaEffect : public BaseBackGroundEffect
{
    	public:
	        DistantNebulaEffect();
	        ~DistantNebulaEffect();

	      	void SetAngle(float angle_inD) 	{ this->angle_inD = angle_inD; };	        	        
	      	void SetDAngle(float d_angle_inD) 	{ this->d_angle_inD = d_angle_inD; };

        	void Update();
        	void Render(float vx, float vy);
        	
        	void SaveData(boost::property_tree::ptree&, const std::string&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        private:
        	float angle_inD, d_angle_inD;
        	
        	void SaveDataUniqueDistantNebulaEffect(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueDistantNebulaEffect(const boost::property_tree::ptree&);
		void ResolveDataUniqueDistantNebulaEffect();  
};

DistantNebulaEffect* GetNewDistantNebulaEffect(int color_id = NONE_ID);

#endif 

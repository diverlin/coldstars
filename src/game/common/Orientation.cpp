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

#include "Orientation.hpp"
#include "../common/Logger.hpp"

Orientation::Orientation():is_updated(false)
{
        uOrient.Set(1.0, 0.0, 0.0); // -> (0 degree)
}

/* virtual */
Orientation::~Orientation()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Orientation("+int2str(GetId())+")");
	#endif
}

void Orientation::UpdateOrientation()
{
	if (is_updated == false)
    	{   
    	       	float angle_radian = angle.z/RADIAN_TO_DEGREE_RATE;
         
        	uOrient.x = cos(angle_radian);
        	uOrient.y = sin(angle_radian);
 		uOrient.z = 0.0; 
 		
 		points.Update(center, angle, scale, uOrient);
 		
    		is_updated = true;
    	}
    		
}		

void Orientation::SaveDataUniqueOrientation(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Orientation("+int2str(GetId())+")::SaveDataUniqueOrientation", SAVELOAD_LOG_DIP);
	#endif
		
	save_ptree.put(root+"data_unresolved_Orientation.center.x", GetCenter().x);
	save_ptree.put(root+"data_unresolved_Orientation.center.y", GetCenter().y);
	save_ptree.put(root+"data_unresolved_Orientation.center.z", GetCenter().z);
	
	save_ptree.put(root+"data_unresolved_Orientation.angle.x", GetAngle().x);
	save_ptree.put(root+"data_unresolved_Orientation.angle.y", GetAngle().y);
	save_ptree.put(root+"data_unresolved_Orientation.angle.z", GetAngle().z);
		
}

void Orientation::LoadDataUniqueOrientation(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Orientation("+int2str(GetId())+")::LoadDataUniqueOrientation", SAVELOAD_LOG_DIP);
	#endif
		
	data_unresolved_Orientation.center.x = load_ptree.get<float>("data_unresolved_Orientation.center.x");
	data_unresolved_Orientation.center.y = load_ptree.get<float>("data_unresolved_Orientation.center.y");
	data_unresolved_Orientation.center.z = load_ptree.get<float>("data_unresolved_Orientation.center.y");
	
	data_unresolved_Orientation.angle.x = load_ptree.get<float>("data_unresolved_Orientation.angle.x");
	data_unresolved_Orientation.angle.y = load_ptree.get<float>("data_unresolved_Orientation.angle.y");
	data_unresolved_Orientation.angle.z = load_ptree.get<float>("data_unresolved_Orientation.angle.z");
}

void Orientation::ResolveDataUniqueOrientation()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Orientation("+int2str(GetId())+")::ResolveDataUniqueOrientation", SAVELOAD_LOG_DIP);
	#endif
}

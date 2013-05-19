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


#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "Base.hpp"
#include "points.hpp"
#include "Box.hpp"

struct UnresolvedDataUniqueOrientation
{	
	Vec3<float> center;
	Vec3<float> angle; 
};

class Orientation : public Base
{
	public:      
		Orientation();
		virtual ~Orientation();
                
		void SetAngle(const Vec3<float>& angle)		{ points.SetAngle(angle); }
						
   		Points& GetPoints()          { return points; }
   				
		float GetCollisionRadius() const  { return collision_radius; }
				
	protected:
		Vec3<float> scale;
			
		float collision_radius;
			
		Points points;

		UnresolvedDataUniqueOrientation data_unresolved_Orientation;
		void SaveDataUniqueOrientation(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueOrientation(const boost::property_tree::ptree&);
		void ResolveDataUniqueOrientation();
				
	friend class BaseVehicleBuilder;
};

#endif 

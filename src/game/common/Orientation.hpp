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

		void SetParentCenter(float px, float py, float pz) { parent_center.Set(px, py, pz); }		
		void SetParentCenter(Vec3<float> parent_center) { this->parent_center.Set(parent_center); }
		
		void SetCenter(float cx, float cy, float cz)	{ center.Set(cx, cy, cz); is_updated = false; }
		void SetCenter(const Vec3<float>& center)       { this->center.Set(center); is_updated = false; }
		
		void SetAngle(float ax, float ay, float az) { angle.Set(ax, ay, az); is_updated = false; }
		void SetAngle(const Vec3<float>& angle) { this->angle.Set(angle); is_updated = false; }
		void SetAngleZ(float angle_z) 	{ this->angle.z = angle_z; is_updated = false; }
		
		void SetSize(float sx, float sy, float sz) { size.Set(sx, sy, sz); is_updated = false; }
		void SetSize(const Vec3<float>& size) { this->size.Set(size); is_updated = false; }
		
		float GetWidth() const  { return size.x; }
		float GetHeight() const { return size.y; }
		
		const Vec3<float>& GetAngle() const { return angle; }       
		Vec3<float>& GetAngle() { return angle; }
		float* GetpAngleZ() { return &angle.z; }
		
		const Vec3<float>& GetCenter() const { return center; }
		const Vec3<float>& GetSize()  const { return size; } 
		
		Vec3<float>* GetpCenter() { return &center; }
		Vec3<float>* GetpParentCenter() { return &parent_center; }
						
   		Points& GetPoints()          { return points; }
   				
		float GetCollisionRadius() const  { return collision_radius; }

		void UpdateOrientation();
						
	protected:			
		float collision_radius;
			
		Points points;
		
		UnresolvedDataUniqueOrientation data_unresolved_Orientation;
		void SaveDataUniqueOrientation(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueOrientation(const boost::property_tree::ptree&);
		void ResolveDataUniqueOrientation();
		
	private:
		bool is_updated;
		
		Vec3<float> center;                  
		Vec3<float> size;
		Vec3<float> angle;
		
		Vec3<float> uOrient;
		
		Vec3<float> parent_center; 
                		
	friend class BaseVehicleBuilder;
};

#endif 

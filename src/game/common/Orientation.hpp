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


#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include <common/Base.hpp>
#include <common/points.hpp>

struct UnresolvedDataUniqueOrientation
{	
	Vec3<float> center;
	Vec3<float> angle; 
};

class Orientation : public Base
{
	public:      
		Orientation();
		virtual ~Orientation() override;

		void SetParentCenter(float x, float y, float z) { m_ParentCenter.Set(x, y, z); }		
		void SetParentCenter(Vec3<float> parent_center) { m_ParentCenter.Set(parent_center); }
		
		void SetCenter(float x, float y, float z)	{ m_Center.Set(x, y, z); m_IsUpdated = false; }
		void SetCenter(const Vec3<float>& center)   { m_Center.Set(center); m_IsUpdated = false; }
		
		void SetAngle(float x, float y, float z) { m_Angle.Set(x, y, z); m_IsUpdated = false; }
		void SetAngle(const Vec3<float>& angle) { m_Angle.Set(angle); m_IsUpdated = false; }
		void SetAngleZ(float angle_z) 	{ m_Angle.z = angle_z; m_IsUpdated = false; }
		
		void SetSize(float sx, float sy, float sz) { m_Size.Set(sx, sy, sz); m_IsUpdated = false; }
		void SetSize(const Vec3<float>& size) { m_Size.Set(size); m_IsUpdated = false; }
		
		const Vec3<float>& GetAngle() const { return m_Angle; }       
		Vec3<float>& GetAngle() { return m_Angle; }      // !!!
		const float* const GetpAngleZ() { return &m_Angle.z; } 
		
		const Vec3<float>& GetCenter() const { return m_Center; }
		const Vec3<float>& GetSize()  const { return m_Size; } 
		
		Vec3<float>* const GetpCenter() { return &m_Center; }
		const Vec3<float>* const GetpParentCenter() { return &m_ParentCenter; }
						
   		Points& GetPoints()          { return m_Points; }  // !!!
   		
		float GetCollisionRadius() const  { return m_CollisionRadius; }

		void UpdateOrientation();
        						
	protected:			
		UnresolvedDataUniqueOrientation data_unresolved_Orientation;
		void SaveDataUniqueOrientation(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueOrientation(const boost::property_tree::ptree&);
		void ResolveDataUniqueOrientation();

		void SetCollisionRadius(float collision_radius) { m_CollisionRadius = collision_radius; }	
                		
	private:
		bool m_IsUpdated;

		float m_CollisionRadius;
        		
		Vec3<float> m_Center;                  
		Vec3<float> m_Size;
		Vec3<float> m_Angle;
		
		Vec3<float> m_Orient;
		
		Vec3<float> m_ParentCenter; 

		Points m_Points;
                        		
	friend class BaseVehicleBuilder;
};

#endif 

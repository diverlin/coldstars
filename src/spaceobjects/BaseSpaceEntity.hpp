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


#ifndef BASEGAMEENTITY_H
#define BASEGAMEENTITY_H

#include "../common/Base.hpp"

class StarSystem;
class ObjMesh;
#include "../common/points.hpp"
#include "../text/InfoTable.hpp" 
class TextureOb;
class Vehicle;

struct UnresolvedDataUniqueBaseSpaceEntity
{
	int mesh_type_id;
	std::string textureOb_path;
	int parent_id;
	int starsystem_id;
	vec2f center;
	float angle;
};


class BaseSpaceEntity : public Base
{
	public:      
		BaseSpaceEntity();
		virtual ~BaseSpaceEntity();

		void SetLifeData(const LifeData& data_life) { this->data_life = data_life; }
		void SetMesh(ObjMesh* mesh)		    { this->mesh = mesh; }
		void SetTextureOb(TextureOb* textureOb)     { this->textureOb = textureOb; }
		void SetStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }
		void SetPlaceTypeId(int place_type_id)      { this->place_type_id = place_type_id;  }

		int SetGivenExpirience(int given_expirience) { this->given_expirience = given_expirience; }
                
		void SetAngle(const vec3f& angle)           { this->angle = angle; }
		void SetDeltaAngle(const vec3f& d_angle)    { this->d_angle = d_angle; }

		void SetParent(BaseSpaceEntity* parent)     { this->parent = parent; }
		void SetScale(float scale) { this->scale = scale; }

		StarSystem* GetStarSystem() const { return starsystem; }           
		int GetPlaceTypeId()        const { return place_type_id; }
		Points& GetPoints()          { return points; }

		virtual int GetGivenExpirience() const { return given_expirience; }
		int GetCollisionRadius() const { return collision_radius; }   
		bool GetAlive()          const { return data_life.is_alive; }
		bool GetGarbageReady()   const { return data_life.garbage_ready; }             

		int GetMass()         const { return mass; }
		TextureOb* GetTextureOb() const { return textureOb; }
		int GetArmor()        const { return data_life.armor; }

		BaseSpaceEntity* GetParent() const { return parent; }

		void RecalculateCollisionRadius();

		void MovingByExternalForce(const vec2f&, float);

		virtual void TakeIntoAccountAgressor(Vehicle*) {};
		virtual void Hit(int, bool);
		void SilentKill();
		
		void RenderInfoInSpace(const vec2f&);		
		void RenderInfo(const vec2f&);
		void virtual UpdateInfo() {};		
				
	protected:
		LifeData data_life;
		
		vec3f angle, d_angle;
		vec2f d_pos;

		float collision_radius;

		TextureOb* textureOb;
		ObjMesh* mesh; 

		StarSystem* starsystem;
		int place_type_id;
		Points points;

		InfoTable info;

		int mass;
		float scale;
		int given_expirience;

		BaseSpaceEntity* parent;

		void UpdateRotation();

		void CheckDeath(bool);
		virtual void PostDeathUniqueEvent(bool) {};

		UnresolvedDataUniqueBaseSpaceEntity data_unresolved_BaseSpaceEntity;
		void SaveDataUniqueBaseSpaceEntity(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseSpaceEntity(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseSpaceEntity();
				
		friend class BaseVehicleBuilder;
};

#endif 

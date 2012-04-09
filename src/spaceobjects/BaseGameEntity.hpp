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
//#include "../world/starsystem.hpp"
//#include "../common/gameStruct.hpp"

struct UnresolvedDataUniqueBaseGameEntity
{
	std::string mesh_path;
	std::string textureOb_path;
	int parent_id;
	int starsystem_id;
	vec2f center;
	float angle;
};


class BaseGameEntity : public Base
{
	public:      
		BaseGameEntity();
		virtual ~BaseGameEntity();

		void SetLifeData(LifeData data_life)        { this->data_life = data_life; }
		void SetMesh(ObjMeshInstance* mesh)         { this->mesh = mesh; }
		void SetTextureOb(TextureOb* textureOb)     { this->textureOb = textureOb; }
		void SetStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }
		void SetPlaceTypeId(int place_type_id)      { this->place_type_id = place_type_id;  }

		void SetAngle(vec3f angle)                  { this->angle = angle; }
		void SetDeltaAngle(vec3f d_angle)           { this->d_angle = d_angle; }

		void SetParent(BaseGameEntity* parent)     { this->parent = parent; }

		StarSystem* GetStarSystem() const { return starsystem; }           
		int GetPlaceTypeId()        const { return place_type_id; }
		Points& GetPoints()          { return points; }

		int GetCollisionRadius() const { return collision_radius; }   
		bool GetAlive()          const { return data_life.is_alive; }
		bool GetGarbageReady()   const { return data_life.garbage_ready; }             

		int GetMass()         const { return mass; }
		TextureOb* GetTextureOb() const { return textureOb; }
		int GetArmor()        const { return data_life.armor; }

		BaseGameEntity* GetParent() const { return parent; }

		void MovingByExternalForce(vec2f, float);

		void Hit(int, bool);
				
	protected:
		LifeData data_life;
		
		UnresolvedDataUniqueBaseGameEntity data_unresolved_bge;
		
		vec3f angle, d_angle;

		float collision_radius;

		TextureOb* textureOb;
		ObjMeshInstance* mesh; 

		StarSystem* starsystem;
		int place_type_id;
		Points points;

		InfoTable info;

		int mass;

		BaseGameEntity* parent;

		void UpdateRotation();

		void CheckDeath(bool);
		virtual void PostDeathUniqueEvent(bool) {};

		void SaveDataUniqueBaseGameEntity(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseGameEntity(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseGameEntity();
				
		friend class BaseVehicleBuilder;
};

#endif 

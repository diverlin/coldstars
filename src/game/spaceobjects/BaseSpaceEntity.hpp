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

#include "../common/BaseDrawable.hpp"

class StarSystem;
class Mesh;
#include "../common/points.hpp"
#include "../text/InfoTable.hpp" 
class TextureOb;
class Vehicle;
class AnimationBase;

struct UnresolvedDataUniqueBaseSpaceEntity
{
	int parent_id;
	int starsystem_id;
	
};


class BaseSpaceEntity : public BaseDrawable
{
	public:      
		BaseSpaceEntity();
		virtual ~BaseSpaceEntity();

		void SetLifeData(const LifeData& data_life) { this->data_life = data_life; }

		void SetStarSystem(StarSystem* starsystem)  { this->starsystem = starsystem; }
		void SetPlaceTypeId(int place_type_id)      { this->place_type_id = place_type_id;  }
		void SetMass(int mass) 			    { this->mass = mass; }
				
		int SetGivenExpirience(int given_expirience) { this->given_expirience = given_expirience; }                
	
		void SetParent(BaseSpaceEntity* parent)     { this->parent = parent; }

		StarSystem* GetStarSystem() const { return starsystem; }           
		int GetPlaceTypeId()        const { return place_type_id; }

		virtual int GetGivenExpirience() const { return given_expirience; }
 
		bool GetAlive()          const { return data_life.is_alive; }
		bool GetGarbageReady()   const { return data_life.garbage_ready; }             

		int GetMass()         const { return mass; }
		int GetArmor()        const { return data_life.armor; }

		BaseSpaceEntity* GetParent() const { return parent; }

		void MovingByExternalForce(const Vec3<float>&, float);

		virtual void TakeIntoAccountAgressor(Vehicle*) {};
		virtual void Hit(int, bool);
		void SilentKill();
		
		void RenderInfoInSpace(const Vec2<float>&);		
		void RenderInfo(const Vec2<float>&);
		void virtual UpdateInfo() {};	
				
	protected:
		LifeData data_life;		

		Vec3<float> d_pos;

		StarSystem* starsystem;
		int place_type_id;

		InfoTable info;

		int mass;
		int given_expirience;

		BaseSpaceEntity* parent;

		void CheckDeath(bool);
		virtual void PostDeathUniqueEvent(bool) {};

		UnresolvedDataUniqueBaseSpaceEntity data_unresolved_BaseSpaceEntity;
		void SaveDataUniqueBaseSpaceEntity(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseSpaceEntity(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseSpaceEntity();
				
	friend class BaseVehicleBuilder;
};

#endif 

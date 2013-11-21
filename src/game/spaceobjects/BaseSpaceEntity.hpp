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


#ifndef BASESPACEENTITY_HPP
#define BASESPACEENTITY_HPP

#include <common/BaseDrawable.hpp>
#include <struct/LifeData.hpp>
#include <text/InfoTable.hpp>
#include <types/PlaceTypes.hpp>

class StarSystem;
class Mesh;
class TextureOb;
class Vehicle;
class AnimationBase;
class Renderer;


struct UnresolvedDataBaseSpaceEntity
{
    int parent_id;
    int starsystem_id;     
}; 

class BaseSpaceEntity : public BaseDrawable
{
    public:      
        BaseSpaceEntity();
        virtual ~BaseSpaceEntity() override;

        void SetLifeData(const LifeData& data_life) { m_DataLife = data_life; }

        void SetStarSystem(StarSystem* starsystem) { m_Starsystem = starsystem; }
        void SetPlaceTypeId(TYPE::PLACE place_type_id) { m_PlaceTypeId = place_type_id;  }
        void SetMass(int mass) { m_Mass = mass; }
                
        void SetGivenExpirience(int given_expirience) { m_GiveExpirience = given_expirience; }                
    
        void SetParent(const BaseSpaceEntity* const parent) { m_Parent = parent; }

        StarSystem* GetStarSystem() const { return m_Starsystem; }           
        TYPE::PLACE GetPlaceTypeId() const { return m_PlaceTypeId; }

        virtual int GetGivenExpirience() const { return m_GiveExpirience; }  // !!!
 
        bool GetAlive()          const { return m_DataLife.is_alive; }
        bool GetGarbageReady()   const { return m_DataLife.garbage_ready; }             

        int GetMass()         const { return m_Mass; }
        int GetArmor()        const { return m_DataLife.armor; }

        const BaseSpaceEntity* const GetParent() const { return m_Parent; }

        void ApplyImpulse(const glm::vec3&, float);

        virtual void TakeIntoAccountAgressor(Vehicle*) {}
        virtual void Hit(int, bool);
        void SilentKill();
        
        virtual void RenderStuffWhenFocusedInSpace() {};
        virtual void RenderInfoInSpace(const Renderer&, const glm::vec2&, float);        
        void RenderInfo(const glm::vec2&);
        void virtual UpdateInfo() {}    
                
    protected:
        void SetMass(float mass) { m_Mass = mass; }
        void ChangeMass(int d_mass) { m_Mass += d_mass; }
        
        InfoTable& GetInfo() { return m_Info; }
        LifeData& GetDataLife() { return m_DataLife; }
        const LifeData& GetDataLife() const { return m_DataLife; }
        
        const glm::vec3& GetAppliedForce() const { return m_AppliedForce; } 
        glm::vec3& GetAppliedForce() { return m_AppliedForce; }     // !!!
                                    
        void CheckDeath(bool);
        virtual void PostDeathUniqueEvent(bool) {}

        UnresolvedDataBaseSpaceEntity data_unresolved_BaseSpaceEntity;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
    
    private:
        LifeData m_DataLife;        

        glm::vec3 m_AppliedForce;

        StarSystem* m_Starsystem;
        TYPE::PLACE m_PlaceTypeId;

        InfoTable m_Info;

        int m_Mass;
        int m_GiveExpirience;

        const BaseSpaceEntity* m_Parent;
                        
    friend class BaseVehicleBuilder;
};

#endif 

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


#pragma once

#include <common/Base.hpp>
#include <jeti/Orientation.hpp>
#include <struct/LifeData.hpp>
#include <types/PlaceTypes.hpp>

class StarSystem;

struct UnresolvedDataBaseSpaceEntity
{
    int parent_id;
    int starsystem_id;     
}; 

class BaseSpaceEntity : public jeti::Orientation, public Base
{
    public:      
        BaseSpaceEntity();
        virtual ~BaseSpaceEntity() override;

        void setLifeData(const LifeData& data_life) { m_dataLife = data_life; }

        void setStarSystem(StarSystem* starsystem) { m_starsystem = starsystem; }
        void setPlaceTypeId(TYPE::PLACE place_type_id) { m_placeTypeId = place_type_id;  }
        void setMass(int mass) { m_mass = mass; }
                
        void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }
    
        void setParent(const BaseSpaceEntity* const parent) { m_parent = parent; }

        StarSystem* starsystem()    const { return m_starsystem; }
        TYPE::PLACE placeTypeId()   const { return m_placeTypeId; }

        virtual int givenExpirience() const { return m_expirienceToGive; }  // !!!
 
        bool isAlive()              const { return m_dataLife.is_alive; }
        bool isReadyForGarbage()    const { return m_dataLife.garbage_ready; }

        int mass()         const { return m_mass; }
        int armor()        const { return m_dataLife.armor; }

        const BaseSpaceEntity* const parent() const { return m_parent; }

        void addImpulse(const glm::vec3&, float);

        virtual void remeberAgressor(BaseSpaceEntity*) {}
        virtual void hit(int, bool);
        void killSilently();
        
//        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) {};
//        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float);
//        void RenderInfo(const glm::vec2&);
//        void virtual UpdateInfo() {}
                
    protected:
        void setMass(float mass) { m_mass = mass; }
        void addMass(int d_mass) { m_mass += d_mass; }
        
//        InfoTable& GetInfo() { return m_Info; }
        LifeData& dataLife() { return m_dataLife; }
        const LifeData& dataLife() const { return m_dataLife; } // !!! remove
        
        const glm::vec3& externalForce() const { return m_externalForce; }
        glm::vec3& externalForce() { return m_externalForce; }     // !!! remove
                                    
        void checkDeath(bool);
        virtual void postDeathUniqueEvent(bool) {}

        UnresolvedDataBaseSpaceEntity data_unresolved_BaseSpaceEntity;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
    
    private:
        LifeData m_dataLife;

        glm::vec3 m_externalForce;

        StarSystem* m_starsystem;
        TYPE::PLACE m_placeTypeId;

        int m_mass;
        int m_expirienceToGive;

        const BaseSpaceEntity* m_parent;
                        
    friend class BaseVehicleBuilder;
};


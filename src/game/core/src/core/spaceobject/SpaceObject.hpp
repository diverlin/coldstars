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

#include <core/Base.hpp>
#include <core/type/PlaceType.hpp>

#include <core/descriptor/spaceobject/SpaceObject.hpp>
#include <core/model/spaceobject/SpaceObject.hpp>

#include <ceti/Orientation.hpp>

namespace core {
namespace control {

class StarSystem;

class SpaceObject : public ceti::control::Orientation, public Base
{
public:
    SpaceObject(SpaceObjectDescr*, model::SpaceObject*);
    ~SpaceObject() override = default;

    place::Type place() const { return model()->place(); }

    StarSystem* starsystem() const  { return m_starsystem; }
    SpaceObject* parent() const { return m_parent; }

    void setStarSystem(StarSystem* starsystem);
    void setPlace(place::Type) const;
    void setParent(SpaceObject* parent);

    void resetStarSystem();
    void resetParent();

    const meti::vec3& nextTurnPosition() const { return m_nextTurnPosition; }
    void setNextTurnPosition(const meti::vec3& position) { m_nextTurnPosition = position; }

    void addImpulse(const glm::vec3&, float);
    void addImpulse(const glm::vec3&);

    [[warning("do we need this?")]]
    virtual int givenExpirience() const { return model()->givenExpirience(); }

    virtual void __remeberAgressor(SpaceObject*) {}
    virtual void hit(int, SpaceObject* agressor = nullptr);
    void die();

    int mass() const { return m_mass; }

    SpaceObjectDescr* descriptor() const { return m_descriptor_spaceobject; }
    model::SpaceObject* model() const { return m_model_spaceobject; }

private:
    StarSystem* m_starsystem = nullptr;
    SpaceObject* m_parent = nullptr;
    int m_mass = 0;

protected:
    glm::vec3 m_impulse;
    meti::vec3 m_nextTurnPosition;

    SpaceObjectDescr* m_descriptor_spaceobject = nullptr;
    model::SpaceObject* m_model_spaceobject = nullptr;

    void _addMass(int d_mass) { m_mass += d_mass; }

    const glm::vec3& _externalForce() const { return m_impulse; }
    [[deprecated("!!! not sure, probably needed for the containrs and bullets")]]
    glm::vec3& _externalForce() { return m_impulse; }

    void _checkDeath(bool show_effect = false);
    virtual void _postDeathUniqueEvent(bool) {}

    void _init();
};

} // namespace control
} // namespace core

//class SpaceObject : public ceti::control::Orientation, public core::Base
//{
//public:
//    SpaceObject();
//    ~SpaceObject() override;

//    void setLifeData(const LifeData& data_life) { m_dataLife = data_life; }

//    void setStarSystem(Starsystem* starsystem) { m_starsystem = starsystem; }
//    void setPlaceTypeId(place::type place_type_id) { m_placeTypeId = place_type_id;  }
//    void setMass(int mass) { m_mass = mass; }

//    void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }
    
//    void setParent(const SpaceObject* const parent) { m_parent = parent; }

//    Starsystem* starsystem()  const { return m_starsystem; }
//    place::type place() const { return m_placeTypeId; }

//    virtual int givenExpirience() const { return m_expirienceToGive; }  // !!!

//    bool isAlive()           const { return m_dataLife.is_alive; }
//    bool isDying()           const { return m_dataLife.is_dying; }
//    bool isReadyForGarbage() const { return m_dataLife.garbage_ready; }

//    int mass()  const { return m_mass; }
//    int armor() const { return m_dataLife.armor; }

//    const SpaceObject* const parent() const { return m_parent; }

//    void addImpulse(const glm::vec3&, float);

//    virtual void remeberAgressor(SpaceObject*) {}
//    virtual void hit(int);

//    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) {};
//    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float);
//    //        void RenderInfo(const glm::vec2&);
//    //        void virtual UpdateInfo() {}

//protected:
//    void _addMass(int d_mass) { m_mass += d_mass; }

//    //        InfoTable& GetInfo() { return m_Info; }
//    LifeData& _dataLife() { return m_dataLife; }
//    const LifeData& _dataLife() const { return m_dataLife; } // !!! remove

//    const glm::vec3& _externalForce() const { return m_externalForce; }
//    glm::vec3& _externalForce() { return m_externalForce; }     // !!! remove

//    void _checkDeath(bool);
//    virtual void _postDeathUniqueEvent(bool) {}

//    UnresolvedDataSpaceObject data_unresolved_SpaceObject;
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
    
//private:
//    LifeData m_dataLife;

//    glm::vec3 m_externalForce;

//    Starsystem* m_starsystem = nullptr;
//    place::type m_placeTypeId = type::place::NONE;

//    int m_mass = 0;
//    int m_expirienceToGive = 0;

//    const SpaceObject* m_parent = nullptr;

//    friend class BaseVehicleBuilder;
//};


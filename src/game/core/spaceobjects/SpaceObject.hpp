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
#include <ceti/Orientation.hpp>
#include <struct/LifeData.hpp>
#include <types/PlaceTypes.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


class Starsystem;

struct UnresolvedDataSpaceObject
{
    int parent_id;
    int starsystem_id;
}; 


namespace model {

class SpaceObject : public ceti::model::Orientation, public core::model::Base
{
public:
    SpaceObject() = default;
    ~SpaceObject() = default;
    SpaceObject(const std::string& data);
    std::string data() const;

    void setArmor(int armor) { m_dataLife.armor = armor; }
    void setLifeData(const LifeData& data_life) { m_dataLife = data_life; }

    void setStarSystem(const int_t& starsystem) { m_starsystem = starsystem; }
    void setPlace(type::place place) { m_place = place;  }
    void setMass(int mass) { m_mass = mass; }

    void setIsAlive(bool is_alive) { m_dataLife.is_alive = is_alive; }
    void setIsDying(bool is_dying) { m_dataLife.is_dying = is_dying; }
    void setDyingTime(bool dying_time) { m_dataLife.dying_time = dying_time; }

    void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }
    void setGarbageReady(bool garbage_ready) { m_dataLife.garbage_ready = garbage_ready; }

    void setParent(const int_t& parent) { m_parent = parent; }

    bool isAlive() const { return m_dataLife.is_alive; }
    bool isDying() const { return m_dataLife.is_dying; }
    int dyingTime() const { return m_dataLife.dying_time; }
    bool garbageReady() const { return m_dataLife.garbage_ready; }

    const int_t& starsystem() const { return m_starsystem; }
    const int_t& parent() const { return m_parent; }

    int mass()  const { return m_mass; }
    int armor() const { return m_dataLife.armor; }
    type::place place() const { return m_place; }
    int givenExpirience() const { return m_expirienceToGive; }

private:
    LifeData m_dataLife;
    int_t m_parent = NONE;
    int_t m_starsystem = NONE;
    type::place m_place = type::place::NONE;
    int m_mass = 0;
    int m_expirienceToGive = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ceti::model::Orientation>(*this);
        ar & boost::serialization::base_object<core::model::Base>(*this);
        ar & m_dataLife;
        ar & m_parent;
        ar & m_starsystem;
        ar & m_place;
        ar & m_mass;
        ar & m_expirienceToGive;
    }
};

} // namespace model

namespace control {

class SpaceObject : public ceti::control::Orientation, public core::control::Base
{
public:
    SpaceObject(model::SpaceObject*);
    ~SpaceObject() override;

    [[warning("check const basense")]]
    Starsystem* starsystem();

    model::SpaceObject* parent();

    void addImpulse(const glm::vec3&, float);

    virtual void remeberAgressor(SpaceObject*) {}
    virtual void hit(int);
    void killSilently();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) {};
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float);
    //        void RenderInfo(const glm::vec2&);
    //        void virtual UpdateInfo() {}

    model::SpaceObject* model() const { return m_model_spaceobject; }

protected:
    Starsystem* m_starsystem = nullptr;
    model::SpaceObject* m_parent = nullptr;

    glm::vec3 externalForce;

    model::SpaceObject* m_model_spaceobject = nullptr;

    void _addMass(int d_mass) { model()->setMass(model()->mass() + d_mass); }

    //        InfoTable& GetInfo() { return m_Info; }
//    [[deprecated("!!! why we need this?")]]
//    LifeData& _dataLife() { return model()->dataLife; }
//    [[deprecated("!!! remove")]]
//    const LifeData& _dataLife() const { return model()->dataLife; }

    const glm::vec3& _externalForce() const { return externalForce; }
    [[deprecated("!!! remove")]]
    glm::vec3& _externalForce() { return externalForce; }

    void _checkDeath(bool);
    virtual void _postDeathUniqueEvent(bool) {}
};

} // namespace control

class SpaceObject : public ceti::control::Orientation, public core::Base
{
public:
    SpaceObject();
    ~SpaceObject() override;

    void setLifeData(const LifeData& data_life) { m_dataLife = data_life; }

    void setStarSystem(Starsystem* starsystem) { m_starsystem = starsystem; }
    void setPlaceTypeId(type::place place_type_id) { m_placeTypeId = place_type_id;  }
    void setMass(int mass) { m_mass = mass; }

    void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }
    
    void setParent(const SpaceObject* const parent) { m_parent = parent; }

    Starsystem* starsystem()  const { return m_starsystem; }
    type::place place() const { return m_placeTypeId; }

    virtual int givenExpirience() const { return m_expirienceToGive; }  // !!!

    bool isAlive()           const { return m_dataLife.is_alive; }
    bool isDying()           const { return m_dataLife.is_dying; }
    bool isReadyForGarbage() const { return m_dataLife.garbage_ready; }

    int mass()  const { return m_mass; }
    int armor() const { return m_dataLife.armor; }

    const SpaceObject* const parent() const { return m_parent; }

    void addImpulse(const glm::vec3&, float);

    virtual void remeberAgressor(SpaceObject*) {}
    virtual void hit(int);
    void killSilently();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) {};
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float);
    //        void RenderInfo(const glm::vec2&);
    //        void virtual UpdateInfo() {}

protected:
    void _addMass(int d_mass) { m_mass += d_mass; }

    //        InfoTable& GetInfo() { return m_Info; }
    LifeData& _dataLife() { return m_dataLife; }
    const LifeData& _dataLife() const { return m_dataLife; } // !!! remove

    const glm::vec3& _externalForce() const { return m_externalForce; }
    glm::vec3& _externalForce() { return m_externalForce; }     // !!! remove

    void _checkDeath(bool);
    virtual void _postDeathUniqueEvent(bool) {}

    UnresolvedDataSpaceObject data_unresolved_SpaceObject;
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
    
private:
    LifeData m_dataLife;

    glm::vec3 m_externalForce;

    Starsystem* m_starsystem = nullptr;
    type::place m_placeTypeId = type::place::NONE;

    int m_mass = 0;
    int m_expirienceToGive = 0;

    const SpaceObject* m_parent = nullptr;

    friend class BaseVehicleBuilder;
};


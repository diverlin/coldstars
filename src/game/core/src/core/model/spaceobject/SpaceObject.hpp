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

#include <core/common/Base.hpp>
#include <core/struct/LifeData.hpp>
#include <core/type/PlaceType.hpp>

#include <ceti/Orientation.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


namespace model {

class SpaceObject : public ceti::model::Orientation, public Base
{
public:
    SpaceObject() = default;
    ~SpaceObject() = default;

    void addArmor(int armor) { m_dataLife.armor += armor; }

    void setArmor(int armor) { m_dataLife.armor = armor; }
    void setLifeData(const LifeData& data_life) { m_dataLife = data_life; }

    void setStarSystem(int_t starsystem) { m_starsystem = starsystem; }
    void setPlace(place::Type place) { m_place = place;  }
//    void setMass(int mass) { m_mass = mass; }

    void setIsDying(bool is_dying) { m_dataLife.is_dying = is_dying; }
    void setDyingTime(bool dying_time) { m_dataLife.dying_time = dying_time; }

    void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }
    void setGarbageReady(bool garbage_ready) { m_dataLife.garbage_ready = garbage_ready; }

    void setParent(int_t parent) { m_parent = parent; }

    bool isDying() const { return m_dataLife.is_dying; }
    int dyingTime() const { return m_dataLife.dying_time; }
    bool garbageReady() const { return m_dataLife.garbage_ready; }

    int_t starsystem() const { return m_starsystem; }
    int_t parent() const { return m_parent; }

//    int mass()  const { return m_mass; }
    int armor() const { return m_dataLife.armor; }
    place::Type place() const { return m_place; }
    int givenExpirience() const { return m_expirienceToGive; }

    void immidiateKill() {
        m_dataLife.dying_time = -1;
    }

private:
    LifeData m_dataLife;
    int_t m_parent = NONE;
    int_t m_starsystem = NONE;
    place::Type m_place = place::Type::NONE;
//    int m_mass = 0;
    int m_expirienceToGive = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ceti::model::Orientation>(*this);
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_dataLife;
        ar & m_parent;
        ar & m_starsystem;
        ar & m_place;
//        ar & m_mass;
        ar & m_expirienceToGive;
    }
};

} // namespace model


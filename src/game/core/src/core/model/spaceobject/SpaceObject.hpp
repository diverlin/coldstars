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
#include <core/model/Base.hpp>
#include <core/type/PlaceType.hpp>

#include <ceti/Orientation.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


namespace core {

class SpaceObjectModel : public ceti::OrientationModel, public BaseModel
{
public:
    SpaceObjectModel() = default;
    ~SpaceObjectModel() override = default;

    void addArmor(int armor) { m_armor += armor; }
    void setArmor(int armor) { m_armor = armor; }
    void setLifeTime(int lifeTime) { m_lifeTime = lifeTime; }

    void setStarSystem(int_t starsystem) { m_starsystem = starsystem; }
    void setPlace(place::Type place) { m_place = place;  }

    void setGivenExpirience(int expirience_to_give) { m_expirienceToGive = expirience_to_give; }

    void setParent(int_t parent) { m_parent = parent; }

    int_t starsystem() const { return m_starsystem; }
    int_t parent() const { return m_parent; }

    int armor() const { return m_armor; }
    place::Type place() const { return m_place; }
    int givenExpirience() const { return m_expirienceToGive; }

    ceti::InfoTable info() const override {
        ceti::InfoTable result = ceti::OrientationModel::info();
        ceti::InfoTable result2 = core::BaseModel::info();
        result.insert(result.begin(), result2.begin(), result2.end());
        result.add("SpaceObject");
        result.add("armor", m_armor);
        result.add("lifeTime", m_lifeTime);
        result.add("parent", m_parent);
        result.add("starsystem", m_starsystem);
        result.add("place", place::strip(place::to_string(m_place)));
        result.add("expirienceToGive", m_expirienceToGive);
        return result;
    }

private:
    int m_armor = 0;
    int m_lifeTime = 0;
    int_t m_parent = NONE;
    int_t m_starsystem = NONE;
    place::Type m_place = place::Type::NONE;
    int m_expirienceToGive = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<ceti::OrientationModel>(*this);
        ar & boost::serialization::base_object<BaseModel>(*this);
        ar & m_armor;
        ar & m_lifeTime;
        ar & m_parent;
        ar & m_starsystem;
        ar & m_place;
        ar & m_expirienceToGive;
    }
};

} // namespace core


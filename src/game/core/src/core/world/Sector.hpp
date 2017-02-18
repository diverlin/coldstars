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

#include <core/spaceobjects/SpaceObject.hpp>
#include "../common/constants.hpp"

#include <boost/serialization/vector.hpp>

class Galaxy;

namespace model {
class Starsystem;
} // namespace model

namespace control {
class Starsystem;
} // namespace control

class StarSystemsConditionData;


namespace descriptor {

class Sector : public SpaceObject
{
public:
    Sector();
    ~Sector() = default;
    Sector(const std::string& data);
    std::string data() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<model::SpaceObject>(*this);
    }
};

} // namespace descriptor


namespace model {

class Sector : public SpaceObject
{
public:
    Sector();
    ~Sector() = default;
    Sector(const std::string& data);
    std::string data() const;

    bool operator==(const Sector& rhs) const;
    bool operator!=(const Sector& rhs) const;

    void setGalaxy(int_t galaxy)  { m_galaxy = galaxy; }
    void setPosition(const glm::vec3& center) { m_position = center; }

    int_t galaxy() const  { return m_galaxy; }
    const glm::vec3& position() const  { return m_position; }

    void add(int_t starsystem) { m_starsystems.push_back(starsystem); }

private:
    int_t m_galaxy = NONE;
    glm::vec3 m_position; // do we need this?

    std::vector<int_t> m_starsystems;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<model::SpaceObject>(*this);
        ar & m_galaxy;
        assert(false);
        //ar & m_position;
        ar & m_starsystems;
    }
};


} // namespace model

namespace control {

class Sector : public control::SpaceObject
{
public:
    Sector(model::Sector*, descriptor::Sector*);
    ~Sector();

    model::Starsystem* activeStarsystem() const;

    void setGalaxy(Galaxy* galaxy)  { m_galaxy = galaxy; }
    Galaxy* galaxy() const  { return m_galaxy; }

    virtual void putChildrenToGarbage() const;

    void add(model::Starsystem*, const glm::vec3&);

    model::Starsystem* randomStarsystem(int condition_id = NONE);
    model::Starsystem* closestStarsystemTo(model::Starsystem*, int condition_id = NONE);

    void update(int);

    //void FillStarSystemsCondition(StarSystemsConditionData&) const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

    model::Sector* model() const { return m_model_sector; }
    descriptor::Sector* descriptor() const { return m_descriptor_sector; }

private:
    model::Sector* m_model_sector = nullptr;
    descriptor::Sector* m_descriptor_sector = nullptr;

    Galaxy* m_galaxy = nullptr;

    std::vector<control::Starsystem*> m_starsystems;

//    friend class GuiGalaxyMap;
//    friend class Observation;
//    friend class God;
};

} // namespace control



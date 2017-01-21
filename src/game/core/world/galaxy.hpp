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

#include <boost/serialization/vector.hpp>

#include <glm/glm.hpp>

namespace  model {
class Sector;
class Starsystem;
} // namespace model

namespace  control {
class Sector;
} // namespace control

class StarSystemsConditionData;

namespace model {

class Galaxy : public model::Base {

public:
    Galaxy();
    ~Galaxy() = default;
    Galaxy(const std::string& data);
    std::string data() const;

    bool operator==(const Galaxy& rhs) const;
    bool operator!=(const Galaxy& rhs) const;

    void add(int_t sector) { m_sectors.push_back(sector); }

private:
    std::vector<int_t> m_sectors;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<model::Base>(*this);
        ar & m_sectors;
    }
};

} // namespace model

namespace control {

class Galaxy : public core::Base
{
public:
    Galaxy(model::Galaxy*);
    ~Galaxy();

    model::Starsystem* activeStarsystem() const;

    virtual void putChildrenToGarbage() const;

    void add(model::Sector*, const glm::vec3&);

    model::Sector* randomSector();
    model::Sector* closestSectorTo(model::Sector*);

    void update(int);

    void analizeStarSystemsCondition(StarSystemsConditionData&) const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

private:
    model::Galaxy* m_model_galaxy = nullptr;
    model::Galaxy* model() const { return m_model_galaxy; }
    std::vector<control::Sector*> m_sectors;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

    // ugly
    //        friend class GuiGalaxyMap;
    //        friend class Observation;
    friend class God;
};

} // namespace control

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

#include <meti/VectorUtils.hpp>

#include <ceti/Pack.hpp>

#include <boost/serialization/vector.hpp>

namespace descriptor {
class Galaxy;
} // namespace descriptor

namespace  control {
class Sector;
class StarSystem;
} // namespace control

class StarSystemsConditionData;

namespace model {

class Galaxy : public Base {

public:
    Galaxy(int_t);
    ~Galaxy() = default;
    Galaxy(const std::string& data);
    std::string data() const;

//    bool operator==(const Galaxy& rhs) const;
//    bool operator!=(const Galaxy& rhs) const;

    void add(int_t sector) { m_sectors.add(sector); }

private:
    ceti::pack<int_t> m_sectors;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<model::Base>(*this);
        ar & m_sectors;
    }
};

} // namespace model

namespace control {

class Galaxy : public Base
{
public:
    Galaxy(descriptor::Galaxy*, model::Galaxy*);
    ~Galaxy();

    virtual void putChildrenToGarbage() const;

    void add(Sector*, const meti::vec3&);

    Sector* randomSector();
    Sector* closestSectorTo(Sector*);
    const std::vector<Sector*>& sectors() const { return m_sectors; }

    void update(int);

    void analizeStarSystemsCondition(StarSystemsConditionData&) const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

    descriptor::Galaxy* descriptor() const { return m_descriptor_galaxy; }
    model::Galaxy* model() const { return m_model_galaxy; }

private:
    descriptor::Galaxy* m_descriptor_galaxy = nullptr;
    model::Galaxy* m_model_galaxy = nullptr;

    std::vector<Sector*> m_sectors;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

    // ugly
    //        friend class GuiGalaxyMap;
    //        friend class Observation;
    friend class God;
};

} // namespace control

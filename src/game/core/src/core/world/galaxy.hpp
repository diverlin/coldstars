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

namespace core {
class GalaxyDescr;
} // namespace core

namespace model {
class GalaxyModel;
} // namespace model

class StarSystemsConditionData;

namespace core {
namespace control {

class Sector;
class StarSystem;

class Galaxy : public Base
{
public:
    Galaxy(GalaxyDescr*, model::GalaxyModel*);
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

    GalaxyDescr* descriptor() const { return m_descriptor_galaxy; }
    model::GalaxyModel* model() const { return m_model_galaxy; }

private:
    GalaxyDescr* m_descriptor_galaxy = nullptr;
    model::GalaxyModel* m_model_galaxy = nullptr;

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
} // namespace core

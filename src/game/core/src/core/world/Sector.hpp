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

#include <core/descriptor/world/SectorDescriptor.hpp>

#include "../common/constants.hpp"

namespace model {
class SectorModel;
} // namespace model

namespace core {
namespace control {

class Galaxy;
class StarSystem;

class Sector : public Base
{
public:
    Sector(SectorDescr*, model::SectorModel*);
    ~Sector();

    void setGalaxy(Galaxy* galaxy)  { m_galaxy = galaxy; }
    Galaxy* galaxy() const  { return m_galaxy; }

    virtual void putChildrenToGarbage() const;

    void add(StarSystem*, const glm::vec3&);

    StarSystem* randomStarSystem(int condition_id = NONE);
    StarSystem* closestStarsystemTo(StarSystem*, int condition_id = NONE);
    const std::vector<StarSystem*>& starSystems() const { return m_starsystems; }

    void update(int);

    SectorDescr* descriptor() const { return m_descriptor_sector; }
    model::SectorModel* model() const { return m_model_sector; }

private:
    SectorDescr* m_descriptor_sector = nullptr;
    model::SectorModel* m_model_sector = nullptr;

    Galaxy* m_galaxy = nullptr;

    std::vector<StarSystem*> m_starsystems;

//    friend class GuiGalaxyMap;
//    friend class Observation;
//    friend class God;
};

} // namespace control
} // naemspace core


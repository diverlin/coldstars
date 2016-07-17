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
#include <glm/glm.hpp>

class Sector;
class StarSystemsConditionData;

class Galaxy : public Base
{
    public:
        Galaxy(int);
        ~Galaxy();

        virtual void putChildrenToGarbage() const;

        void add(Sector*, const glm::vec3&);

        Sector* randomSector();
        Sector* closestSectorTo(Sector*);

        void update(int);

        void analizeStarSystemsCondition(StarSystemsConditionData&) const;

        void Save(boost::property_tree::ptree&) const;
        void Load(const boost::property_tree::ptree&);
        void Resolve();

    private:
        std::vector<Sector*> m_sectors;
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();

        // ugly
//        friend class GuiGalaxyMap;
//        friend class Observation;
        friend class God;
};



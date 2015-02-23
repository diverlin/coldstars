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


#ifndef GOD_HPP
#define GOD_HPP

#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

#include <common/Date.hpp>
#include <struct/StarSystemsConditionData.hpp>

class Galaxy;
class GalaxyDescription;
class StarSystem;
class StarSystemDescription;
class Planet;

class NormalRunScenario;


class God
{
    public:
        static God& Instance();
        ~God();

        void SetGalaxy(Galaxy* galaxy) { m_Galaxy = galaxy; }

        void CreateLife(const GalaxyDescription&) const;
        void CreateInvasion(const GalaxyDescription&) const;
        
        void Update(const Date&);
                
    private:
        God();
        God(const God&) = delete;
        God& operator=(const God&) = delete;
       
        Date m_DateLastUpdate;
        Galaxy* m_Galaxy;
        
        StarSystemsConditionData data_starsystems_condition;
        
        void CreateLifeAtPlanet(Planet*, const StarSystemDescription&) const;
        
        void CreateSpaceStations(StarSystem*, int) const;
        void CreateShips(StarSystem*, int, TYPE::RACE race_id = TYPE::RACE::NONE_ID, TYPE::ENTITY subtype_id = TYPE::ENTITY::NONE_ID, TYPE::ENTITY subsubtype_id = TYPE::ENTITY::NONE_ID) const;   
        
        void ProceedInvasion() const;
        
    friend class NormalRunScenario;
}; 

#endif 
    

        



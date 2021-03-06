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


#ifndef GALAXY_H
#define GALAXY_H

#include "../common/Base.hpp"
#include "../common/constants.hpp"
class Sector;
class StarSystemsConditionData;

class Galaxy : public Base
{
      public:
             Galaxy(int);
             ~Galaxy();
                
                virtual void PutChildsToGarbage() const;
                
             void Add(Sector*, const glm::vec3&);
             
             Sector* GetRandomSector();
                Sector* GetClosestSectorTo(Sector*);
                     
            void Update(int);

        void FillStarSystemsCondition(StarSystemsConditionData&) const;

            void Save(boost::property_tree::ptree&) const;
            void Load(const boost::property_tree::ptree&);
            void Resolve();

         private:
               std::vector<Sector*> SECTOR_vec;
        
            void SaveData(boost::property_tree::ptree&, const std::string&) const;
            void LoadData(const boost::property_tree::ptree&);
            void ResolveData();
                           
               friend class GuiGalaxyMap;
               friend class Observation;
                friend class God;
};

#endif 

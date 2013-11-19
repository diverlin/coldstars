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


#ifndef SECTOR_HPP
#define SECTOR_HPP

#include "../spaceobjects/BaseSpaceEntity.hpp"
#include "../common/constants.hpp"
class Galaxy;
class StarSystem;
class StarSystemsConditionData;

struct UnresolvedDataUniqueSector
{
    int galaxy_id;
};

class Sector : public BaseSpaceEntity
{
      public:
             Sector(int);
             ~Sector();
                
                void SetGalaxy(Galaxy* galaxy)  { this->galaxy = galaxy; };
                void SetCenter(const glm::vec3& center) { this->center = center; };
                
                Galaxy* GetGalaxy() const  { return galaxy; };
                const glm::vec3& GetCenter() const  { return center; };
                                                        
                virtual void PutChildsToGarbage() const;
                
             void Add(StarSystem*, const glm::vec3&);
             
             StarSystem* GetRandomStarSystem(int condition_id = NONE_ID);
                StarSystem* GetClosestStarSystemTo(StarSystem*, int condition_id = NONE_ID);
                     
            void Update(int);

        //void FillStarSystemsCondition(StarSystemsConditionData&) const;

            void Save(boost::property_tree::ptree&) const;
            void Load(const boost::property_tree::ptree&);
            void Load();

         private:
             Galaxy* galaxy;
             glm::vec3 center;
             
             UnresolvedDataUniqueSector data_unresolved_Sector;
             
               std::vector<StarSystem*> STARSYSTEM_vec;
        
            void SaveDataUniqueSector(boost::property_tree::ptree&, const std::string&) const;
            void LoadDataUniqueSector(const boost::property_tree::ptree&);
            void ResolveDataUniqueSector();
                           
               friend class GuiGalaxyMap;
               friend class Observation;
                friend class God;
};


#endif 

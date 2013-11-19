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


#ifndef PLANET_HPP
#define PLANET_HPP

#include "BasePlanet.hpp"
class BaseLand;
class BaseDecor;


class Planet : public BasePlanet
{
    public:
        Planet(int);
        virtual ~Planet();
        
        void AddDecoration(BaseDecor* decor) { m_Decorations.push_back(decor); }
        
        void BindLand(BaseLand*);
        void SetPopulation(unsigned long int population)  { m_Population = population; }
        
        unsigned long int GetPopulation() const { return m_Population; }
        BaseLand* const GetLand() const { return m_Land; }
        
        void AddVehicle(Vehicle*) const;
        
        void UpdateInSpace(int, bool);
        void UpdateInSpaceInStatic();
        
        void Render_NEW(const Renderer&);
        void Render_OLD(const Renderer&);
        
        virtual void SaveData(boost::property_tree::ptree&) const override final;
        virtual void LoadData(const boost::property_tree::ptree&) override final;
        virtual void ResolveData() override final;
        
    private:
        BaseLand* m_Land; 
        std::vector<BaseDecor*> m_Decorations;
        
        unsigned long int m_Population;
        
        virtual void PutChildsToGarbage() const override final;
        
        virtual void UpdateInfo() override final;
        
        void PostDeathUniqueEvent(bool);
        
        void Save(boost::property_tree::ptree&, const std::string&) const;
        void Load(const boost::property_tree::ptree&);
        void Resolve();
}; 
 
#endif 






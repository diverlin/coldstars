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


#ifndef SHIP_HPP
#define SHIP_HPP

#include <spaceobjects/Vehicle.hpp>

class Render;

class Ship : public Vehicle
{   
    public:
        Ship(int);
        virtual ~Ship();
        
        virtual void UpdateInSpace(int, bool) override final;
        
        virtual void UpdateInfo() override final;  
        
        void RenderInSpace_2D(const Renderer&, float);            
        void RenderInSpace_3D(const Renderer&, float);
        void RenderAtPlanet(const Renderer&, const glm::vec3&);       
        
        virtual void SaveData(boost::property_tree::ptree&) const override final;
        virtual void LoadData(const boost::property_tree::ptree&) override final;
        virtual void ResolveData() override final;
         
    private:        
        void SaveDataUniqueShip(boost::property_tree::ptree&, const std::string&) const;        
        void LoadDataUniqueShip(const boost::property_tree::ptree&);
        void ResolveDataUniqueShip();
};

#endif 

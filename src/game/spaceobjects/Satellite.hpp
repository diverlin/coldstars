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


#ifndef SATELLITE_HPP
#define SATELLITE_HPP

#include <spaceobjects/Vehicle.hpp>
#include <parts/orbit.hpp>

class Satellite : public Vehicle
{
    public:  
        Satellite(int);
        virtual ~Satellite();

        void BindParent(const BaseSpaceEntity* const);
            
        virtual void UpdateInSpace(int, bool) override final;
        
        void RenderInSpace(const Renderer&, float);
        void RenderAtPlanet(const Renderer&); 
                
        virtual void SaveData(boost::property_tree::ptree&) const override final;
        virtual void LoadData(const boost::property_tree::ptree&) override final;
        virtual void ResolveData() override final;
            
    private:
        Orbit m_Orbit;

        virtual void UpdateInfo() override final;
        void UpdateRenderStuff();
                        
        void SaveDataUniqueSatellite(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueSatellite(const boost::property_tree::ptree&);
        void ResolveDataUniqueSatellite();
};


#endif 


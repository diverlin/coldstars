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

#include <spaceobjects/SpaceObject.hpp>
#include <parts/orbit.hpp>
#include <descriptors/PlanetDescriptor.hpp>
//#include <jeti/Render.hpp>


struct UnresolvedDataPlanetoid
{
    int orbit_it;
};


class Planetoid : public SpaceObject 
{
    public:      
        Planetoid();
        virtual ~Planetoid();
        
        void SetPlanetDescriptor(const PlanetDescriptor& planet_descriptor) { m_PlanetDescriptor = planet_descriptor; }
        
        Orbit& GetOrbit() { return m_Orbit; }   // !!!
        const Orbit& GetOrbit() const { return m_Orbit; }   
        const PlanetDescriptor& GetPlanetDescriptor() const { return m_PlanetDescriptor; }
        
        void BindParent(const SpaceObject* const, int);
        
//        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
        
    protected:
        virtual void putChildrenToGarbage() const {}
        
        virtual void postDeathUniqueEvent(bool);
        void UpdatePosition();
        
        UnresolvedDataPlanetoid data_unresolved_Planetoid;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
    private:
        PlanetDescriptor m_PlanetDescriptor;
        Orbit m_Orbit;     
        
        void CreateOrbit();    
};


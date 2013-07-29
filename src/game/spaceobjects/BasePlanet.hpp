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


#ifndef BASEPLANET_HPP
#define BASEPLANET_HPP

#include <spaceobjects/BaseSpaceEntity.hpp>
#include <parts/orbit.hpp>
#include <struct/PlanetData.hpp>

struct UnresolvedDataBasePlanet
{
	int orbit_it;
};


class BasePlanet : public BaseSpaceEntity 
{
	public:      
		BasePlanet();
		virtual ~BasePlanet();
      		
		void SetPlanetData(const PlanetData& data_planet) { m_DataPlanet = data_planet; }
        
		Orbit& GetOrbit() { return m_Orbit; }   // !!!
		const Orbit& GetOrbit() const { return m_Orbit; }   
		const PlanetData& GetDataPlanet() const { return m_DataPlanet; }
        
        void BindParent(const BaseSpaceEntity* const, int);
	
		virtual void RenderStuffWhenFocusedInSpace() override final;
				
		void RenderMesh_OLD() const;
				
	protected:
        virtual void PutChildsToGarbage() const {}
        
		virtual void PostDeathUniqueEvent(bool);
		void UpdatePosition();
				
		UnresolvedDataBasePlanet data_unresolved_BasePlanet;
		void SaveDataUniqueBasePlanet(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBasePlanet(const boost::property_tree::ptree&);
		void ResolveDataUniqueBasePlanet();
		
    private:
		PlanetData m_DataPlanet;   
		Orbit m_Orbit;     

		void CreateOrbit();    
};

#endif 

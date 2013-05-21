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


#ifndef BASEPLANET_H
#define BASEPLANET_H

#include "BaseSpaceEntity.hpp"
#include "../math/myVector.hpp"
#include "../parts/orbit.hpp"
#include "../struct/PlanetData.hpp"

struct UnresolvedDataBasePlanet
{
	int orbit_it;
};

class BasePlanet : public BaseSpaceEntity 
{
	public:      
		BasePlanet();
		virtual ~BasePlanet();

      		virtual void PutChildsToGarbage() const {};
      		
		void SetPlanetData(PlanetData data_planet) { this->data_planet = data_planet; };
		Orbit& GetOrbit() { return orbit; };

		void CreateOrbit();
		
		void RenderMesh_OLD() const;
				
	protected:
		PlanetData data_planet;   
		Orbit orbit;  	
				
		virtual void PostDeathUniqueEvent(bool);
		void UpdatePosition();
				
		UnresolvedDataBasePlanet data_unresolved_BasePlanet;
		void SaveDataUniqueBasePlanet(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBasePlanet(const boost::property_tree::ptree&);
		void ResolveDataUniqueBasePlanet();
		
	friend class StarSystem;
};

#endif 

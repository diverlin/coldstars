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


#ifndef PLANET_H
#define PLANET_H

#include "BasePlanet.hpp"
#include "../docking/BaseLand.hpp"

//struct UnresolvedDataUniquePlanet
//{
//};


class Planet : public BasePlanet
{
	public:
		Planet(int);
		~Planet();
		
		void PutChildsToGarbage() const;

		void BindLand(BaseLand* land);
		void SetPopulation(unsigned long int population) 	{ this->population = population; };
		
		unsigned long int GetPopulation() const { return population; }; 
		int GetDockingRadius() const { return scale; };
		BaseLand* GetLand() const { return land; };

		void AddVehicle(Vehicle*) const;
		
		void UpdateInSpace(int, bool);
		void UpdateInSpaceInStatic();
			
		void Render_NEW(const vec2f&) const;
		void Render_OLD() const;

		void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
	private:
		TextureOb* textureOb_atmosphere;
		
		vec3f angle_atmosphere;
		vec3f d_angle_atmosphere;
		
		BaseLand* land;

		unsigned long int population;
		void UpdateInfo();

		void PostDeathUniqueEvent(bool);

		void RenderAtmosphere_NEW(const vec2f&) const;
		
		void SaveDataUniquePlanet(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniquePlanet(const boost::property_tree::ptree&);
		void ResolveDataUniquePlanet();
}; 


#endif 






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
//#include "planetBase.hpp"
//#include "../common/myVector.hpp"

class Planet : public BasePlanet
{
	public:
		Planet(int, int, unsigned long int);
		~Planet();

		int GetDockingRadius() const;
		BaseLand* GetLand() const { return land; };

		void Update_inSpace(int, bool);
		void Update_inSpace_inStatic();

		void renderInfo_inSpace(vec2f);

		void CreateLand();

		void SaveUniquePlanet(const std::string&) const;		
		void LoadUniquePlanet(const std::string&);
		void ResolveUniquePlanet();

	private:
		TextureOb* textureOb_atmosphere;

		BaseLand* land;

		unsigned long int population;
		void UpdateInfo();

		void PostDeathUniqueEvent(bool);
}; 


#endif 






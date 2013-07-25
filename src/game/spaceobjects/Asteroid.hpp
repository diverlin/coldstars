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


#ifndef ASTEROID_H
#define ASTEROID_H

#include "BasePlanet.hpp"

class Asteroid : public BasePlanet
{
	public:
		Asteroid(int);
		virtual ~Asteroid();

		int GetDamage() const { return GetMass()*10; };

		void UpdateInSpace(int, bool);        	
		void CollisionEvent(bool);

		void Render_NEW(const Vec2<float>& scroll_coords);	
		void Render_OLD() const;

        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
	private:      	
		void PostDeathUniqueEvent(bool);

		void UpdateInfo();
		
		void SaveDataUniqueAsteroid(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueAsteroid(const boost::property_tree::ptree&);
		void ResolveDataUniqueAsteroid();
}; 

#endif 

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


#ifndef ORBIT_H
#define ORBIT_H
#include "../render/pathVisual.hpp"


class Orbit
{
	public:      
		Orbit();
		~Orbit();

		int GetIt() const { return it; };
		vec2f GetPosition() const { return coords_vec[it]; };
		vec2f GetNextTurnPosition() const; 

		void CalcPath(float, float, float, float);
		void CalcPath(float, float);
		
		void UpdatePosition();

		void Draw();

	protected:
		PathVisual orbit_visual;

		std::vector<vec2f> coords_vec;
		int len, it; 

		void UpdateVisual();
};

#endif 

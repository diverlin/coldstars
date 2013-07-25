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

#include "../render/PathVisual.hpp"

class Orbit
{
	public:      
		Orbit();
		~Orbit();

		void SetIt(int it) { m_It = it; };

		int GetIt() const { return m_It; };
		const Vec3<float>& GetPosition() const { return m_Coords_vec[m_It]; };
		const Vec3<float>& GetNextTurnPosition() const; 

		void CalcPath(float, float, float, float, bool);
		void CalcPath(float, float, bool);
		
		void UpdatePosition();

		void UpdatePathVisualisation();
		void DrawPath();

	private:
		PathVisual m_VisualOrbitPath;
		PathVisual m_VisualOrbitTurn;
                
		std::vector<Vec3<float>> m_Coords_vec;
		int m_Len, m_It; 
};

#endif 

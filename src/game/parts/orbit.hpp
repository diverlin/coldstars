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


#ifndef ORBIT_HPP
#define ORBIT_HPP

#include <render/PathVisual.hpp>

namespace jeti {
class Renderer;
}

class Orbit
{
    public:      
        Orbit();
        ~Orbit();

        void SetIt(int it) { m_It = it; };

        int GetIt() const { return m_It; };
        const glm::vec3& GetPosition() const { return m_Coords_vec[m_It]; };
        const glm::vec3& GetNextTurnPosition() const; 

        void CalcPath(float, float, float, float, bool);
        void CalcPath(float, float, bool);
        
        void UpdatePosition();

        void UpdatePathVisualisation();
        void DrawPath(const jeti::Renderer&);

    private:
        jeti::PathVisual m_VisualOrbitPath;
        jeti::PathVisual m_VisualOrbitTurn;
                
        std::vector<glm::vec3> m_Coords_vec;
        int m_Len;
        int m_It; 
};

#endif 

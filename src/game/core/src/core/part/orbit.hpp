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

//#include <jeti/PathVisual.hpp>
#include <glm/glm.hpp>
#include <vector>

class Orbit
{
public:
    Orbit();
    ~Orbit();

    bool initialized() const { return m_initialized; }
    void setIt(int it) { m_it = it; }

    const glm::vec3& position() const;
    const glm::vec3& nextTurnPosition() const;

    void calcPath(float, float, float, float, bool);
    void calcPath(float, float, bool);

    void updatePosition();

    //        void UpdatePathVisualisation();
    //        void DrawPath(const jeti::Renderer&);

private:
    //        jeti::PathVisual m_VisualOrbitPath;
    //        jeti::PathVisual m_VisualOrbitTurn;

    bool m_initialized = false;
    std::vector<glm::vec3> m_coordinates;
    int m_length = -1;
    int m_it = -1;

    void __validate() const;
};

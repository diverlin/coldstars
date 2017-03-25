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

#include <cmath>
#include "orbit.hpp"
#include "../common/constants.hpp"
//#include <jeti/Render.hpp>


Orbit::Orbit()
{}

Orbit::~Orbit()
{}

void
Orbit::__validate() const
{
    assert(m_it >= 0);
    assert(m_coordinates.size());
}

const glm::vec3&
Orbit::position() const
{
    __validate();
    return m_coordinates[m_it];
}

const glm::vec3& Orbit::nextTurnPosition() const
{ 
    __validate();
    if (m_it + TURN_TIME < m_length) {
        return m_coordinates[m_it+TURN_TIME];
    } else {
        int d_orbit = m_length - m_it;
        return m_coordinates[TURN_TIME - d_orbit];
    }
}

void Orbit::calcPath(float radiusA,
                     float radiusB,
                     float speed,
                     float orbit_phi_inD,
                     bool clockwise)
{   
    m_coordinates.clear();
    if (speed > 0) {
        float d_angleInRad = glm::radians(speed);
        if (clockwise) {
            d_angleInRad *= -1;
        }

        float orbitPhiInRad = glm::radians(orbit_phi_inD);

        glm::vec3 new_coord(0, 0, DEFAULT_ENTITY_ZPOS);
        for(float angleInRad=0; fabs(angleInRad)<2*PI; angleInRad+=d_angleInRad) {
            new_coord.x = radiusA * cos(angleInRad) * cos(orbitPhiInRad) - radiusB * sin(angleInRad) * sin(orbitPhiInRad);
            new_coord.y = radiusA * cos(angleInRad) * sin(orbitPhiInRad) + radiusB * sin(angleInRad) * cos(orbitPhiInRad);
            m_coordinates.push_back(new_coord);
        }
    } else {
        glm::vec3 new_coord(0, 0, DEFAULT_ENTITY_ZPOS);
        m_coordinates.push_back(new_coord);
    }

    m_length = m_coordinates.size();
    m_it = 0;
}    

void Orbit::calcPath(float radius,
                     float speed,
                     bool clockwise)
{       
    assert(speed > 0);
    m_coordinates.clear();
    
    float d_angleInRad  = glm::radians(speed);
    if (clockwise) {
        d_angleInRad *= -1;
    }
    
    glm::vec3 new_coord;
    for(float angleInRad=0; fabs(angleInRad)<2*PI; angleInRad+=d_angleInRad) {
        new_coord.x = radius*(cos(angleInRad) - sin(angleInRad));
        new_coord.y = radius*(cos(angleInRad) + sin(angleInRad));
        new_coord.z = DEFAULT_ENTITY_ZPOS;
        m_coordinates.push_back(new_coord);
    }
    m_length = m_coordinates.size();
    m_it = 0;
}    

void Orbit::updatePosition()
{   
    if (m_it < m_length-1) {
        m_it++;
    } else {
        m_it=0;
    }
}    

//void Orbit::UpdatePathVisualisation()
//{
//    m_VisualOrbitPath.FillData(m_Coords_vec, 30, 10);
//    m_VisualOrbitTurn.FillData(m_Coords_vec, TURN_TIME, 13);
//}

//void Orbit::DrawPath(const jeti::Renderer& render)
//{
//    UpdatePathVisualisation();   // TOO SLOW
////    m_VisualOrbitPath.Draw(render);
////    m_VisualOrbitTurn.Draw(render);
//}



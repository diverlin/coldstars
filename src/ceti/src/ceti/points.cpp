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

#include "points.hpp"
//#include <ceti/constants.hpp>

namespace ceti {

static float DEFAULT_ENTITY_ZPOS = 0.0f;

Points::Points()
{}

Points::~Points()
{}              

void Points::add(glm::vec3* const point, const glm::vec3* const point_orig)
{ 
    m_points_orig.push_back(point_orig);
    m_points.push_back(point);
}

void Points::addMidLeftPoint()
{
    m_midLeft_origin = glm::vec3(-0.5, 0.0, DEFAULT_ENTITY_ZPOS);
    m_midLeft = glm::vec3(-0.5, 0.0, DEFAULT_ENTITY_ZPOS);

    m_points_orig.push_back(&m_midLeft_origin);
    m_points.push_back(&m_midLeft);
}

void Points::addMidFarLeftPoint()
{
    m_midFarLeft_origin = glm::vec3(-1.0, 0.0, DEFAULT_ENTITY_ZPOS);
    m_midFarLeft = glm::vec3(-1.0, 0.0, DEFAULT_ENTITY_ZPOS);

    m_points_orig.push_back(&m_midFarLeft_origin);
    m_points.push_back(&m_midFarLeft);
}


void Points::update(const glm::vec3& center, const glm::vec3& angle, const glm::vec3& scale, const glm::vec3& uOrient)
{
    glm::vec3 pos = center;

    for (unsigned int i=0; i<m_points.size(); i++)
    {
        ////// rotation around center
        m_points[i]->x = uOrient.x*scale.x*m_points_orig[i]->x - uOrient.y*scale.y*m_points_orig[i]->y;
        m_points[i]->y = uOrient.y*scale.x*m_points_orig[i]->x + uOrient.x*scale.y*m_points_orig[i]->y;
        ////// moving to position
        m_points[i]->x += pos.x;
        m_points[i]->y += pos.y;
        
        m_points[i]->z = m_points_orig[i]->z;
    }
}        

} // namespace ceti









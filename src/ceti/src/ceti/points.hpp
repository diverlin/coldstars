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

#include <vector>
#include <cmath>
#include <meti/VectorUtils.hpp>

namespace ceti {

class Points
{
    /*****************************************
        The class holds points(verticles) collection relevant for game entity,
        and provides the transformation methodsin 2D (rotation, moving).
        If entity is rotated/moved then all relevant points are passing the same transformation (rotation and moving).
        The numbers relevant points can be varry and it depends on game entity type.
        All relevant points for particular entity placed to the STL vector were
        they are updated rely on game entity angle value and center position
        (the points outside the STL are not relevant and are not dated).
        The points with prefix <<_origin>> are used internally in the class for rotation calculation.
        ******************************************/

public:
    Points();
    ~Points();

    const glm::vec3& bottomLeft()  const { return m_bottomLeft; }
    const glm::vec3& bottomRight() const { return m_bottomRight; }
    const glm::vec3& topRight()    const { return m_topRight; }
    const glm::vec3& topLeft()     const { return m_topLeft; }

    const glm::vec3& midLeftOrig()    { return m_midLeft_origin; }    // used in path calc
    const glm::vec3& midLeft()    { return m_midLeft; }                    // used in path calc
    glm::vec3* pMidLeft()    { return &m_midLeft; }                    // used in drive jet
    glm::vec3* pMidFarLeft() { return &m_midFarLeft; }

    void add(glm::vec3* const, const glm::vec3* const);

    void addMidLeftPoint();
    void addMidFarLeftPoint();

    void update(const glm::vec3& center, const glm::vec3& angle, const glm::vec3& scale, const glm::vec3& uOrient);

private:
    std::vector<const glm::vec3*> m_points_orig;
    std::vector<glm::vec3*> m_points;

    // Origin entity rect (for rotation only transformation)
    glm::vec3 m_bottomLeft_origin;
    glm::vec3 m_bottomRight_origin;
    glm::vec3 m_topRight_origin;
    glm::vec3 m_topLeft_origin;

    // jet normilized
    glm::vec3 m_midLeft_origin;
    glm::vec3 m_midFarLeft_origin;

    // Actual entity rect
    glm::vec3 m_bottomLeft;
    glm::vec3 m_bottomRight;
    glm::vec3 m_topRight;
    glm::vec3 m_topLeft;

    // jet actual
    glm::vec3 m_midLeft;
    glm::vec3 m_midFarLeft;
};

} // namespace ceti


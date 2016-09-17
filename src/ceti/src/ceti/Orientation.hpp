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

#include <ceti/points.hpp>

namespace ceti {

namespace model {

class Orientation
{
public:
    float collisionRadius;

    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 direction;
    glm::vec3 parentPosition;

    ceti::Points points;
};


} // namespace model

namespace control {

class Orientation
{
public:
    Orientation(model::Orientation* model);
    virtual ~Orientation();

    void setParentPosition(float x, float y, float z) { m_model->parentPosition = glm::vec3(x, y, z); }
    void setParentPosition(const glm::vec3& parentPosition) { m_model->parentPosition = parentPosition; }

    void setPosition(float x, float y, float z)    { m_model->position = glm::vec3(x, y, z); m_isUpdated = false; }
    void setPosition(const glm::vec3& position)   { m_model->position = position; m_isUpdated = false; }

    void setSize(float x, float y, float z) { m_model->size = glm::vec3(x, y, z); m_isUpdated = false; }
    void setSize(const glm::vec3& size) { m_model->size = size; m_isUpdated = false; }

    const glm::vec3& direction() const { return m_model->direction; }

    const glm::vec3& position() const { return m_model->position; }
    const glm::vec3& size()  const { return m_model->size; }

    glm::vec3* pPosition() { return &m_model->position; } // depr
    const glm::vec3* pParentPosition() { return &m_model->parentPosition; } // depr

    ceti::Points& points()          { return m_model->points; }  // depr !!!

    float collisionRadius() const  { return m_model->collisionRadius; }

    void updateOrientation();     //depr

    void setDirection(const glm::vec3& direction)   { assert(int(direction.length()) != 1); m_model->direction = glm::normalize(direction); m_isUpdated = false; }
    void setCollisionRadius(float collision_radius) { m_model->collisionRadius = collision_radius; }

private:
    model::Orientation* m_model = nullptr;

    bool m_isUpdated = false;
};

} // namespace control

} // namespace ceti



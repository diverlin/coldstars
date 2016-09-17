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

#include <boost/property_tree/ptree.hpp>
#include <ceti/points.hpp>

namespace ceti {

struct UnresolvedDataOrientation
{    
    glm::vec3 center;
    glm::vec3 direction;
};

class Orientation
{
public:
    Orientation();
    virtual ~Orientation();

    void setParentPosition(float x, float y, float z) { m_parentPosition = glm::vec3(x, y, z); }
    void setParentPosition(const glm::vec3& parentPosition) { m_parentPosition = parentPosition; }

    void setPosition(float x, float y, float z)    { m_position = glm::vec3(x, y, z); m_isUpdated = false; }
    void setPosition(const glm::vec3& position)   { m_position = position; m_isUpdated = false; }

    void setSize(float x, float y, float z) { m_size = glm::vec3(x, y, z); m_isUpdated = false; }
    void setSize(const glm::vec3& size) { m_size = size; m_isUpdated = false; }
    
    const glm::vec3& direction() const { return m_direction; }

    const glm::vec3& position() const { return m_position; }
    const glm::vec3& size()  const { return m_size; }

    glm::vec3* const pPosition() { return &m_position; }
    const glm::vec3* const pParentPosition() { return &m_parentPosition; }

    ceti::Points& points()          { return m_points; }  // depr !!!

    float collisionRadius() const  { return m_collisionRadius; }

    void updateOrientation();     //depr

    void setDirection(const glm::vec3& direction)   { assert((int)direction.length() != 1); m_direction = glm::normalize(direction); m_isUpdated = false; }
    void setCollisionRadius(float collision_radius) { m_collisionRadius = collision_radius; }

protected:
    UnresolvedDataOrientation data_unresolved_Orientation;
    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    bool m_isUpdated;

    float m_collisionRadius;

    glm::vec3 m_position;
    glm::vec3 m_size;

    glm::vec3 m_direction;

    glm::vec3 m_parentPosition;

    ceti::Points m_points;
};

} // namespace ceti

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



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

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace ceti {

namespace model {

class Orientation
{
public:
    Orientation() = default;
    ~Orientation() = default;
    Orientation(const std::string& data);
    std::string data() const;

    void setPosition(const meti::vec3& position) { m_position = position; }
    void setSize(const meti::vec3& size) { m_size = size; }
    void setDirection(const meti::vec3& direction) { m_direction = direction; }

    const meti::vec3& position() const { return m_position; }
    const meti::vec3& size() const { return m_size; }
    const meti::vec3& direction() const { return m_direction; }

private:
    meti::vec3 m_position;
    meti::vec3 m_size;
    meti::vec3 m_direction /*= meti::OZ*/;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_position;
        ar & m_size;
        ar & m_direction;
    }
};

} // namespace model

namespace control {

class Orientation
{
public:
    Orientation(model::Orientation* model);
    virtual ~Orientation();

    void setParentPosition(float x, float y, float z) { m_parentPosition = glm::vec3(x, y, z); }
    void setParentPosition(const glm::vec3& parentPosition) { m_parentPosition = parentPosition; }

    void setPosition(float x, float y, float z)    { model()->setPosition(meti::vec3(x, y, z)); m_isUpdated = false; }
    void setPosition(const meti::vec3& position)   { model()->setPosition(position); m_isUpdated = false; }

    void setSize(float x, float y, float z) { model()->setSize(meti::vec3(x, y, z)); m_isUpdated = false; }
    void setSize(const meti::vec3& size) { model()->setSize(size); m_isUpdated = false; }

    const meti::vec3& direction() const { return model()->direction(); }
    const meti::vec3& position() const { return model()->position(); }
    const meti::vec3& size() const { return model()->size(); }

    [[deprecated("depr")]]
    //glm::vec3* pPosition() { return &model()->position(); }
    [[deprecated("depr")]]
    const glm::vec3* pParentPosition() { return &m_parentPosition; }

    [[deprecated("depr")]]
    ceti::Points& points()          { return m_points; }

    float collisionRadius() const  { return m_collisionRadius; }

    [[deprecated("depr")]]
    void updateOrientation();

    void setDirection(const meti::vec3& direction)   { model()->setDirection(meti::normalize(direction)); m_isUpdated = false; }
    void setCollisionRadius(float collision_radius) { m_collisionRadius = collision_radius; }

    model::Orientation* model() const { return m_model_orientation; }

private:
    model::Orientation* m_model_orientation = nullptr;

    bool m_isUpdated = false;
    float m_collisionRadius;
    glm::vec3 m_parentPosition;

    ceti::Points m_points;
};

} // namespace control

} // namespace ceti



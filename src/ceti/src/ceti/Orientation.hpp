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

#include <ceti/InfoTable.hpp>
#include <ceti/StringUtils.hpp>

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


namespace ceti {

class OrientationModel
{
public:
    OrientationModel() = default;
    virtual ~OrientationModel() = default;
    OrientationModel(const std::string& data);
    std::string data() const;

    void setPosition(const meti::vec3& position) { m_position = position; }
    void setSize(const meti::vec3& size) { m_size = size; }
    void setScale(float scale) { m_scale = scale; }
    void setDirection(const meti::vec3& direction) { m_direction = direction; }

    const meti::vec3& position() const { return m_position; }
    const meti::vec3& size() const { return m_size; }
    float scale() const { return m_scale; }
    const meti::vec3& direction() const { return m_direction; }

public:
    virtual ceti::InfoTable info() const {
        ceti::InfoTable result;
        result.add("ceti::Orientation");
        result.add("position", m_position);
        result.add("size", m_size);
        result.add("scale", m_scale);
        result.add("direction", m_direction);
        return result;
    }

private:
    meti::vec3 m_position;
    meti::vec3 m_size;
    float m_scale = 1.0f;
    meti::vec3 m_direction = glm::vec3(0.0f, 1.0f, 0.0f);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_position;
        ar & m_size;
        ar & m_scale;
        ar & m_direction;
    }
};

namespace control {

class Orientation
{
public:
    Orientation();
    Orientation(OrientationModel* model);
    virtual ~Orientation();

    void setPosition(float x, float y, float z);
    void setPosition(const meti::vec3& position);

    void setSize(float x, float y, float z);
    void setSize(const meti::vec3& size);

    void setDirection(float x, float y, float z);
    void setDirection(const meti::vec3& size);
    void setScale(float);

    const meti::vec3& direction() const { return model()->direction(); }
    const meti::vec3& position() const { return model()->position(); }
    const meti::vec3& size() const { return model()->size(); }

    float distanceTo(const glm::vec2&) const;
    float distanceTo(const glm::vec3&) const;

    bool isPointInsideCircle(const glm::vec2&) const;
    bool isPointInsideShape(const glm::vec3&) const;

    float collisionRadius() const  { return m_collisionRadius; }

    void setCollisionRadius(float collision_radius) { m_collisionRadius = collision_radius; }

    OrientationModel* model() const { return m_model_orientation; }

private:
    bool m_own_model = false;
    OrientationModel* m_model_orientation = nullptr;

    bool m_isUpdated = false;
    float m_collisionRadius = 0;

    void __updateCollisionRadius();
};

} // namespace control

} // namespace ceti



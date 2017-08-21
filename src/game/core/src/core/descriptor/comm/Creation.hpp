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

#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {


class Object
{
public:
    Object(int_t);
    Object(const std::string& data);
    ~Object() = default;
    std::string data() const;

    int_t object() const { return m_object; }

    std::string info() const {
        std::string result = "descriptor::comm::Creation:\n";
        result += std::string(" object = ") + std::to_string(m_object) + "\n";
        return result;
    }

private:
    int_t m_object = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_object;
    }
};

class Creation
{
public:
    Creation(int_t, int_t);
    Creation(const std::string& data);
    Creation() = default;
    ~Creation() = default;
    std::string data() const;

    int_t object() const { return m_object; }
    int_t descriptor() const { return m_descriptor; }

    std::string info() const {
        std::string result = "descriptor::comm::Creation:\n";
        result += std::string(" object = ") + std::to_string(m_object) + "\n";
        result += std::string(" descriptor = ") + std::to_string(m_descriptor) + "\n";
        return result;
    }

private:
    int_t m_object = NONE;
    int_t m_descriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_object;
        ar & m_descriptor;
    }
};


class CreateContainer : public Creation
{
public:
    CreateContainer(int_t, int_t, int_t);
    CreateContainer(const std::string& data);
    ~CreateContainer() = default;
    std::string data() const;

    int item() const { return m_item; }

    std::string info() const {
        std::string result = Creation::info();
        result += "descriptor::comm::Container:\n";
        result += std::string(" item = ") + std::to_string(m_item) + "\n";
        return result;
    }

private:
    int m_item = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Creation>(*this);
        ar & m_item;
    }
};

class CreateMineral : public Creation
{
public:
    CreateMineral(int_t, int_t, int);
    CreateMineral(const std::string& data);
    ~CreateMineral() = default;
    std::string data() const;

    int mass() const { return m_mass; }

    std::string info() const {
        std::string result = Creation::info();
        result += "descriptor::comm::Container:\n";
        result += std::string(" mass = ") + std::to_string(m_mass) + "\n";
        return result;
    }

private:
    int m_mass = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Creation>(*this);
        ar & m_mass;
    }
};


class CreateBullet
{
public:
    CreateBullet(int_t, int_t, int_t);
    CreateBullet(const std::string& data);
    ~CreateBullet() = default;
    std::string data() const;

    int_t owner() const { return m_owner; }
    int_t weapon() const { return m_item; }
    int_t target() const { return m_target; }

    std::string info() const {
        std::string result = "descriptor::comm::BulletShoot:\n";
        result += std::string(" owner = ") + std::to_string(m_owner) + "\n";
        result += std::string(" item = ") + std::to_string(m_item) + "\n";
        result += std::string(" target = ") + std::to_string(m_target) + "\n";
        return result;
    }

private:
    int_t m_owner = 0;
    int_t m_item = 0;
    int_t m_target = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_owner;
        ar & m_item;
        ar & m_target;
    }
};


namespace effect {

class Explosion
{
public:
    Explosion(float, const glm::vec3&);
    Explosion(const std::string& data);
    ~Explosion() = default;
    std::string data() const;

    float size() const { return m_size; }
    const meti::vec3& position() const { return m_position; }

    std::string info() const {
        std::string result = "descriptor::comm::effect::Explosion:\n";
        result += std::string(" size = ") + std::to_string(m_size) + "\n";
        result += std::string(" position = ") + meti::to_string(m_position) + "\n";
        return result;
    }

private:
    float m_size = 0.0f;
    meti::vec3 m_position;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_size;
        ar & m_position;
    }
};

} // namespace effect

} // namespace comm
} // namespace descriptor



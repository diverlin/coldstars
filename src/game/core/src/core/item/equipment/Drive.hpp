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

#include <core/item/equipment/Base.hpp>

namespace descriptor {
namespace item {
namespace equipment {

class Drive : public Base
{
public:
    static const int SPEED_MIN;
    static const int SPEED_MAX;
    static const int HYPER_MIN;
    static const int HYPER_MAX;

public:
    Drive() = default;
    Drive(const std::string& data);
    virtual ~Drive() = default;
    std::string data() const;

    std::string info() const override final {
        std::string result = "Drive descriptor: " + Base::info();
        return result;
    }

private:
    int m_speed = 0;
    int m_hyper = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_speed;
        ar & m_hyper;
    }
};

} // namespace equipment
} // namespace item
} // namespace descriptor



namespace model {
namespace item {
namespace equipment {

class Drive : public Base
{
public:
    Drive();
    ~Drive() = default;
    Drive(const std::string& data);
    std::string data() const;

    int speed() const { return m_speed; }
    int hyper() const { return m_hyper; }

private:
    int m_speed = 0;
    int m_hyper = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_speed;
        ar & m_hyper;
    }
};

} // namespace equipment
} // namespace item
} // namespace model


namespace control {
namespace item {
namespace equipment {

class Drive : public control::item::equipment::Base
{
public:
    Drive(int_t id);
    virtual ~Drive();

private:
    virtual void updateProperties();
    void CountPrice();

    model::item::equipment::Drive* model() const { return m_model_drive; }

private:
    int m_speed_add = 0;
    int m_hyper_add = 0;

    model::item::equipment::Drive* m_model_drive = nullptr;
    descriptor::item::equipment::Drive* m_descriptor = nullptr;

    void virtual addUniqueInfo();
    std::string GetSpeedStr();
    std::string GetHyperStr();
};

} // namespace equipment
} // namespace item
} // namespace control

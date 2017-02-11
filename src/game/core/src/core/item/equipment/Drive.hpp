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

class Drive : public BaseEquipment
{
public:
    static const float OVERLOAD_RATE;
    static const float OVERLOAD_DETERIORATION_RATE;

    static const float SPEED_MIN;
    static const float SPEED_MAX;
    static const float SPEED_TECH_RATE;

    static const int HYPER_MIN;
    static const int HYPER_MAX;
    static const float HYPER_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float SPEED_WEIGHT;
    static const float HYPER_WEIGHT;
    static const float MODULES_NUM_WEIGHT;


public:
    Drive();
    Drive(const std::string& data);
    ~Drive() = default;
    std::string data() const;

    void setSpeed(int speed) { m_speed = speed; }
    void setHyper(int hyper) { m_hyper = hyper; }

    int speed() const { return m_speed; }
    int hyper() const { return m_hyper; }

    std::string info() const {
        std::string result = "descriptor::item::Drive:\n";
        result += std::string(" speed = ") + std::to_string(m_speed) + "\n";
        result += std::string(" hyper = ") + std::to_string(m_hyper) + "\n";
        result += descriptor::item::BaseEquipment::info();
        return result;
    }

private:
    int m_speed = 0;
    int m_hyper = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_speed;
        ar & m_hyper;
    }
};

} // namespace item
} // namespace descriptor



namespace model {
namespace item {

class Drive : public BaseEquipment
{
public:
    Drive();
    ~Drive() = default;
    Drive(const std::string& data);
    std::string data() const;

    void setSpeed(int speed) { m_speed = speed; }
    void setHyper(int hyper) { m_hyper = hyper; }

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

} // namespace item
} // namespace model


namespace control {
namespace item {

class Drive : public control::item::Base
{
public:
    Drive(model::item::Drive*);
    virtual ~Drive() = default;

private:
    virtual void updateProperties();
    void CountPrice();

    model::item::Drive* model() const { return m_model_drive; }
    descriptor::item::Drive* descriptor() const { return m_descriptor_drive; }

private:
    int m_speed_add = 0;
    int m_hyper_add = 0;

    model::item::Drive* m_model_drive = nullptr;
    descriptor::item::Drive* m_descriptor_drive = nullptr;

    void virtual addUniqueInfo();
    std::string speedStr();
    std::string hyperStr();
};

} // namespace item
} // namespace control

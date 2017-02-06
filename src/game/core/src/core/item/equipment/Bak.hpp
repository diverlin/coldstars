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

class Bak : public BaseEquipment
{
public:
    static const int FUEL_MIN;
    static const int FUEL_MAX;
    static const float FUEL_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float FUEL_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Bak();
    ~Bak() = default;
    Bak(const std::string& data);
    std::string data() const;

    void setFuel(int fuel) { m_fuel = fuel; }

    int fuel() const { return m_fuel; }

    std::string info() const {
        std::string result = "descriptor::item::Bak:\n";
        result += std::string(" fuel = ") + std::to_string(m_fuel) + "\n";
        result += descriptor::item::BaseEquipment::info();
        return result;
    }

private:
    int m_fuel = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_fuel;
    }
};

} // namespace item
} // namespace descriptor


namespace model {
namespace item {

class Bak : public BaseEquipment
{
public:
    Bak();
    ~Bak() = default;
    Bak(const std::string& data);
    std::string data() const;

    void setFuel(int fuel) { m_fuel = fuel; }

    int fuel() const    { return m_fuel; }

private:
    int m_fuel = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_fuel;
    }
};

} // namespace item
} // namespace model


namespace control {
namespace item {

class Bak : public BaseEquipment
{
public:
    Bak() = default;
    virtual ~Bak() = default;

    void increaseFuel(int fuel);
    int fuelMiss() const;

private:
    void updateProperties() override final;
    void countPrice();

    model::item::Bak* model() const { return m_model_bak; }
    descriptor::item::Bak* descriptor() const { return m_descriptor_bak; }

private:
    int m_fuelMaxAdd = 0;
    int m_fuelMax = 0;

    model::item::Bak* m_model_bak = nullptr;
    descriptor::item::Bak* m_descriptor_bak = nullptr;

    void virtual addUniqueInfo();
    std::string getFuelStr();
};

} // namespace item
} // namespace control


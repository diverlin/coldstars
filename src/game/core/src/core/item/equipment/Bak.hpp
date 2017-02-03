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

namespace model {
namespace item {

class Bak : public Base
{
public:
    Bak();
    ~Bak() = default;
    Bak(const std::string& data);
    std::string data() const;

    void setFuelMaxOrig(int fuelMaxOrig) { m_fuelMaxOrig = fuelMaxOrig; }
    void setFuelMax(int fuelMax) { m_fuelMax = fuelMax; }
    void setFuel(int fuel) { m_fuel = fuel; }

    int fuelMaxOrig() const { return m_fuelMaxOrig; }
    int fuelMaxAdd() const { return m_fuelMaxAdd; }
    int fuelMax() const { return m_fuelMax; }
    int fuel() const    { return m_fuel; }

private:
    int m_fuelMaxOrig = 0;
    int m_fuelMaxAdd = 0;
    int m_fuelMax = 0;
    int m_fuel = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_fuelMaxOrig;
        ar & m_fuelMaxAdd;
        ar & m_fuelMax;
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
    Bak(int_t id);
    virtual ~Bak();

    void increaseFuel(int fuel);
    int fuelMiss() const { return (model()->fuelMax() - model()->fuel()); }

//    virtual void Save(boost::property_tree::ptree&) const;
//    virtual void Load(const boost::property_tree::ptree&);
//    virtual void Resolve();

private:
    void updateProperties() override final;
    void countPrice();

    model::item::Bak* model() const { return m_model_bak; }

private:
    model::item::Bak* m_model_bak = nullptr;

    void virtual addUniqueInfo();
    std::string getFuelStr();

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace item
} // namespace control


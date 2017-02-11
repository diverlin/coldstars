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

#include "Base.hpp"
//#include <core/common/BulletData.hpp>

namespace descriptor {
namespace item {

class Rocket : public BaseEquipment
{
public:
    static const int AMMO_MIN;
    static const int AMMO_MAX;
    static const float AMMO_TECH_RATE;

    static const int RADIUS_MIN;
    static const int RADIUS_MAX;
    static const float RADIUS_TECH_RATE;

    static const int DAMAGE_MIN;
    static const int DAMAGE_MAX;
    static const float DAMAGE_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float AMMO_WEIGHT;
    static const float DAMAGE_WEIGHT;
    static const float RADIUS_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Rocket();
    ~Rocket() = default;
    Rocket(const std::string& data);
    std::string data() const;

    void setRadius(int radius) { m_radius = radius; }
    void setDamage(int damage) { m_damage = damage; }
    void setAmmo(int ammo) { m_ammo = ammo; }

    int radius() const { return m_radius; }
    int damage() const { return m_damage; }
    int ammo() const { return m_ammo; }

    std::string info() const {
        std::string result = "descriptor::item::Radar:\n";
        result += std::string(" radius = ") + std::to_string(m_radius) + "\n";
        result += std::string(" damage = ") + std::to_string(m_damage) + "\n";
        result += std::string(" ammo = ") + std::to_string(m_ammo) + "\n";
        result += descriptor::item::BaseEquipment::info();
        return result;
    }

private:
    int m_radius = 0;
    int m_damage = 0;
    int m_ammo = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_radius;
        ar & m_damage;
        ar & m_ammo;
    }
};

} // namespace item
} // namespace descriptor


namespace model {
namespace item {

class Rocket : public BaseEquipment
{
public:
    Rocket();
    ~Rocket() = default;
    Rocket(const std::string& data);
    std::string data() const;

    void setRadius(int radius) { m_radius = radius; }
    void setDamage(int damage) { m_damage = damage; }
    void setAmmo(int ammo) { m_ammo = ammo; }

    int radius() const { return m_radius; }
    int damage() const { return m_damage; }
    int ammo() const { return m_ammo; }

private:
    int m_radius = 0;
    int m_damage = 0;
    int m_ammo = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_radius;
        ar & m_damage;
        ar & m_ammo;
    }
};

} // namespace item
} // namespace model


namespace control {
namespace item {

class Rocket : public BaseEquipment
{ 
public:
    Rocket(model::item::Rocket*);
    virtual ~Rocket() = default;

//    void SetBulletData(BulletData data_bullet) { data_bullet = data_bullet; }

//    void FireEvent(float);

    virtual void updateProperties();

    void countPrice();

protected:
    model::item::Rocket* model() const { return m_model_rocket; }
    descriptor::item::Rocket* descriptor() const { return m_descriptor_rocket; }

private:
    model::item::Rocket* m_model_rocket = nullptr;
    descriptor::item::Rocket* m_descriptor_rocket = nullptr;

    int m_ammo_add = 0;
    int m_damage_add = 0;
    int m_radius_add = 0;

//    int fire_atOnce;

//    BulletData data_bullet;

    void virtual addUniqueInfo();

    std::string ammoStr();
    std::string damageStr();
    std::string radiusStr();
};

} // namespace item
} // namespace control

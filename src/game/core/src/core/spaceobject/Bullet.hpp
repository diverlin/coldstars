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

#include <core/spaceobject/SpaceObject.hpp>
#include <core/common/BulletData.hpp>

namespace descriptor {

class Bullet : public SpaceObject {

public:
    Bullet();
    ~Bullet() = default;
    Bullet(const std::string& data);
    std::string data() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
    }
};

} // namespace descriptor



namespace model {

class Bullet : public SpaceObject {

public:
    Bullet();
    ~Bullet() = default;
    Bullet(const std::string& data);
    std::string data() const;

    void setOwner(int_t owner) { m_owner = owner; }
    void setTarget(int_t target) { m_target = target; }
    void setDamageRate(float damage_rate) { m_damageRate = damage_rate; }
    void setSpeed(float speed) { m_speed = speed; }

    void increaseSpeed(float d_speed) { m_speed += d_speed; }
    void decreaseLiveTime(int val) { m_liveTime -= val; }

    float speed() const { return m_speed; }
    int_t owner() const { return m_owner; }

    void setBulletData(const BulletData& bulletData) { m_data_bullet = bulletData; }
    const BulletData& bulletData() const { return m_data_bullet; }

private:
    int m_liveTime = 0;
    float m_speed = 0.0f;
    float m_damageRate = 0.0f;

    int_t m_owner = NONE;
    int_t m_target = NONE;

    BulletData m_data_bullet;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_liveTime;
        ar & m_speed;
        ar & m_damageRate;
        ar & m_owner; // is it needed?
        ar & m_target; // is it needed?
    }
};

} // namespace model

namespace control {

class Bullet : public SpaceObject
{
public:
    Bullet(descriptor::Bullet*, model::Bullet*);
    virtual ~Bullet();

    void update(int);

    bool collideable() const { return true; }
    void collisionEvent();

    void hit(int, SpaceObject* agresor = nullptr) override final;
    void _postDeathUniqueEvent(bool) override final;

    int damage() const { return model()->bulletData().damage(); }

    descriptor::Bullet* descriptor() const { return m_descriptor_rocket; }
    model::Bullet* model() const { return m_model_rocket; }

private:
    descriptor::Bullet* m_descriptor_rocket = nullptr;
    model::Bullet* m_model_rocket = nullptr;

    model::SpaceObject* m_target = nullptr;

    bool __checkTarget() const;
};

} // namespace control

//class Bullet : public SpaceObject
//{
//public:
//    Bullet(int);
//    virtual ~Bullet();

//    void SetBulletData(BulletData data_bullet) { m_DataBullet = data_bullet; m_Speed = data_bullet.speed_init; };
//    void SetOwnerId(int owner_id) { m_OwnerId = owner_id; };
//    void SetTarget(SpaceObject* target) { m_Target = target; };
//    void SetDamageRate(float damage_rate) { m_DamageRate = damage_rate; };

//    int damage() const { return m_DataBullet.damage; };
//    int GetOwnerId() const { return m_OwnerId; };

//    void CreateDriveComplexTextureDependedStuff();
//    void UpdateInSpace(int, bool);

//    void collisionEvent(bool);

//    virtual void hit(int) override final;
//    virtual void _postDeathUniqueEvent(bool) override final;

//    //void RenderInSpace(const Renderer&, float);

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    float m_Speed;
//    float m_DamageRate;

//    int m_OwnerId;
//    SpaceObject* m_Target;

//    BulletData m_DataBullet;
//    jeti::DriveEffect* m_EffectDrive;

//    //        virtual void UpdateInfo() override final;

//    virtual void putChildrenToGarbage() const override final {}

//    bool CheckTarget() const;

//    int unresolved_Bullet_target_id;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};


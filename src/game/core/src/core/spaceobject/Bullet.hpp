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

class RocketBullet : public SpaceObject {

public:
    RocketBullet();
    ~RocketBullet() = default;
    RocketBullet(const std::string& data);
    std::string data() const;

    void setBulletData(BulletData data_bullet) { m_dataBullet = data_bullet; m_speed = data_bullet.speed_init; }
    void setOwner(int_t owner) { m_owner = owner; }
    void setTarget(int_t target) { m_target = target; }
    void setDamageRate(float damage_rate) { m_damageRate = damage_rate; }

    void increaseSpeed(float d_speed) { m_speed += d_speed; }
    void decreaseLiveTime(int val) { m_dataBullet.live_time -= val; }

    float speed() const { return m_speed; }
    int damage() const { return m_dataBullet.damage; }
    int_t owner() const { return m_owner; }
    const BulletData& bulletData() const { return m_dataBullet; }

private:
    float m_speed = 0.0f;
    float m_damageRate = 0.0f;

    int_t m_owner = NONE;
    int_t m_target = NONE;

    BulletData m_dataBullet;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_speed;
        ar & m_damageRate;
        ar & m_owner;
        ar & m_target;
    }
};

} // namespace model

namespace control {

class RocketBullet : public SpaceObject
{
public:
    RocketBullet(descriptor::Bullet*, model::RocketBullet*);
    virtual ~RocketBullet();

    void CreateDriveComplexTextureDependedStuff();
    void UpdateInSpace(int, bool);

    void collisionEvent(bool);

    void hit(int, SpaceObject* agresor = nullptr) override final;
    void _postDeathUniqueEvent(bool) override final;

    int damage() const { return model()->damage(); }
    //void RenderInSpace(const Renderer&, float);

    descriptor::Bullet* descriptor() const { return m_descriptor_rocket; }
    model::RocketBullet* model() const { return m_model_rocket; }

private:
    descriptor::Bullet* m_descriptor_rocket = nullptr;
    model::RocketBullet* m_model_rocket = nullptr;

    model::SpaceObject* m_target = nullptr;

//    jeti::DriveEffect* m_EffectDrive;

    //        virtual void UpdateInfo() override final;

    bool CheckTarget() const;
};

} // namespace control

//class RocketBullet : public SpaceObject
//{
//public:
//    RocketBullet(int);
//    virtual ~RocketBullet();

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

//    int unresolved_RocketBullet_target_id;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};


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


#ifndef ROCKETBULLET_HPP
#define ROCKETBULLET_HPP

#include <spaceobjects/BaseSpaceEntity.hpp>
#include <common/BulletData.hpp>

namespace jeti {
class DriveEffect;
}

class RocketBullet : public BaseSpaceEntity
{
    public:
        RocketBullet(int);
        
        virtual ~RocketBullet();
      
        void SetBulletData(BulletData data_bullet) { m_DataBullet = data_bullet; m_Speed = data_bullet.speed_init; };
        void SetOwnerId(int owner_id) { m_OwnerId = owner_id; };
        void SetTarget(BaseSpaceEntity* target) { m_Target = target; };
        void SetDamageRate(float damage_rate) { m_DamageRate = damage_rate; };
        
        int GetDamage() const { return m_DataBullet.damage; };
        int GetOwnerId() const { return m_OwnerId; };
        
        void CreateDriveComplexTextureDependedStuff();
        void UpdateInSpace(int, bool);
        
        void CollisionEvent(bool);
        
        virtual void Hit(int, bool) override final;
        virtual void PostDeathUniqueEvent(bool) override final;  
        
        //void RenderInSpace(const Renderer&, float);
        
        virtual void Save(boost::property_tree::ptree&) const override final;
        virtual void Load(const boost::property_tree::ptree&) override final;
        virtual void Resolve() override final;
            
    private:
        float m_Speed;        
        float m_DamageRate;
        
        int m_OwnerId;
        BaseSpaceEntity* m_Target;
        
        BulletData m_DataBullet;
        jeti::DriveEffect* m_EffectDrive;
        
//        virtual void UpdateInfo() override final;
        
        virtual void putChildrenToGarbage() const override final {}
                
        bool CheckTarget() const;
        
        int unresolved_RocketBullet_target_id; 
                     
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

#endif 

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

//#include <client/effects/ShockWaveEffect.hpp> //depr
#include <core/spaceobject/Planetoid.hpp>

#include <core/descriptor/spaceobject/WormHole.hpp>
#include <core/model/spaceobject/WormHole.hpp>

namespace control {

class WormHole : public Planetoid
{
public:
    WormHole(model::WormHole*);
    virtual ~WormHole();

    //void BindShockWaveEffect(ShockWaveEffect* shockwave) { this->shockwave = shockwave; };

    void setPosition(const glm::vec3&);

    //        ShockWaveEffect* GetShockWaveEffect() const { return shockwave; };

    void updateInSpace(int, bool);

    model::WormHole* model() const { return m_model_wormhole; }
    descriptor::WormHole* descriptor() const { return m_descriptor_wormhole; }

private:
    model::WormHole* m_model_wormhole = nullptr;
    descriptor::WormHole* m_descriptor_wormhole = nullptr;

    //        virtual void UpdateInfo() override final;
};

} // namespace control

//class BlackHole : public Planetoid
//{
//    public:
//        BlackHole(int);
//        virtual ~BlackHole();

//        //void BindShockWaveEffect(ShockWaveEffect* shockwave) { this->shockwave = shockwave; };

//        void setPosition(const glm::vec3&);

////        ShockWaveEffect* GetShockWaveEffect() const { return shockwave; };

//        void updateInSpace(int, bool);

//        virtual void Save(boost::property_tree::ptree&) const;
//        virtual void Load(const boost::property_tree::ptree&);
//        virtual void Resolve();

//    private:
////        ShockWaveEffect* shockwave;

////        void UpdateInfo();

//        void SaveData(boost::property_tree::ptree&, const std::string&) const;
//        void LoadData(const boost::property_tree::ptree&);
//        void ResolveData();
//};




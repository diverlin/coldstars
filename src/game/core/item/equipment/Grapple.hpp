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

//namespace jeti {
//class Renderer;
//}

#include "Base.hpp"
#include "../../spaceobjects/SpaceObject.hpp"

namespace item {
namespace equipment {

class Grapple : public Base
{
public:
    Grapple(int_t id);
    virtual ~Grapple();

    void SetStrengthOrig(int strength_orig)     { m_strength_orig   = strength_orig; }
    void SetRadiusOrig(int radius_orig)         { m_radius_orig     = radius_orig; }
    void SetSpeedOrig(int speed_orig)           { m_speed_orig      = speed_orig; }

    int strength()   const { return m_strength; }
    int radius()     const override final { return m_radius; }
    int speed()      const { return m_speed; }

    bool CheckIfTargetAlreadyExistInQueue(SpaceObject* target) const;
    void AddTarget(SpaceObject*);
    void RemoveTarget(SpaceObject*);

    void RemoveAllTargets();

    std::string GetTarstr() const;

    void UpdateGrabScenarioProgram_inDynamic();
    //        void RenderGrabTrail(const jeti::Renderer&);

    virtual void updateProperties();

    void CountPrice();

    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

private:
    int m_strength_orig;
    int m_strength_add;
    int m_strength;

    int m_radius_orig;
    int m_radius_add;
    int m_radius;

    int m_speed_orig;
    int m_speed_add;
    int m_speed;

    int m_free_strength;

    std::vector<SpaceObject*> m_targets;

    void virtual addUniqueInfo();
    std::string GetStrengthStr();
    std::string GetRadiusStr();
    std::string GetSpeedStr();

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};

} // namespace equipment
} // namespace item

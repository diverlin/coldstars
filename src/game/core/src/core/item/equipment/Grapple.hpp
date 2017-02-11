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

#include "Equipment.hpp"

namespace descriptor {
namespace item {
class Grapple;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Grapple;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Grapple : public Equipment
{
public:
    Grapple(model::item::Grapple*);
    virtual ~Grapple() = default;

//    bool CheckIfTargetAlreadyExistInQueue(model::SpaceObject* target) const;
//    void AddTarget(model::SpaceObject*);
//    void RemoveTarget(model::SpaceObject*);

//    void RemoveAllTargets();

//    std::string GetTarstr() const;

    void UpdateGrabScenarioProgram_inDynamic();
    //        void RenderGrabTrail(const jeti::Renderer&);

    virtual void updateProperties();

    void CountPrice();

    model::item::Grapple* model() const { return m_model_grapple; }
    descriptor::item::Grapple* descriptor() const { return m_descriptor_grapple; }

private:
    int m_strength_add = 0;
    int m_radius_add = 0;
    int m_speed_add = 0;

    int m_free_strength = 0;

    model::item::Grapple* m_model_grapple = nullptr;
    descriptor::item::Grapple* m_descriptor_grapple = nullptr;

//    std::vector<model::SpaceObject*> m_targets;

    void virtual addUniqueInfo();
    std::string strengthStr();
    std::string radiusStr();
    std::string speedStr();
};

} // namespace item
} // namespace control

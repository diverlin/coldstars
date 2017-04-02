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

//#include <jeti/PathVisual.hpp>
#include <meti/VectorUtils.hpp>

#include <vector>

namespace control {
class Vehicle;
} // namespace control

namespace slot {
class Item;
} // namespace slot

namespace jeti {
class DriveEffect;
}

namespace jeti {
class Renderer;
}


namespace control {
class SpaceObject;
} // namespace control


class DriveComplex
{
public:
    enum class Action : int {
        NONE=0, DOCKING, COLLECTING, KEEP_FIRE_DISTANCE, KEEP_CLOSE, KEEP_MIDDLE, KEEP_FAR
    };
public:
    DriveComplex();
    ~DriveComplex();

    void setOwnerVehicle(control::Vehicle* owner_vehicle)    { m_ownerVehicle = owner_vehicle; }
    void SetDriveEffect(jeti::DriveEffect* drive_effect)  { m_effectDrive = drive_effect; }

    void addDriveSlot(slot::Item* drive_slot) { m_driveSlots.push_back(drive_slot); }
    void addBakSlot(slot::Item* bak_slot)     { m_bakSlots.push_back(bak_slot); }

    void setTarget(control::SpaceObject*, Action);
    void SetStaticTargetCoords(const glm::vec3&);

    Action GetActionId() const { return m_action; }
    jeti::DriveEffect* GetDriveEffect() const { return m_effectDrive; }

    std::vector<slot::Item*> driveSlots() const { return m_driveSlots; }
    std::vector<slot::Item*> bakSlots() const { return m_bakSlots; }

    control::SpaceObject* target() const { return m_target; }
    Action action() const { return m_action; }

    bool PathExists() const;

    bool CheckTargetEchievement();
    bool GetDockingPermission();

    void resetTarget();

    void UpdatePath();
    void UpdatePosition();

    void UpdatePathVisualisation();
    void DrawPath(const jeti::Renderer&);

private:
    std::vector<slot::Item*> m_driveSlots;
    std::vector<slot::Item*> m_bakSlots;

    control::Vehicle* m_ownerVehicle = nullptr;
    control::SpaceObject* m_target = nullptr;

    jeti::DriveEffect* m_effectDrive = nullptr;

    glm::vec3 m_TargetPos;

    Action m_action = Action::NONE;
    float m_TargetDistance;
    glm::vec3 m_TargetOffset;

    std::vector<glm::vec3> m_PathCenterVec;
    std::vector<glm::vec3> m_PathDirectionVec;

    bool m_PathEnd;
    unsigned int m_PathIndex;

    bool m_HasTarget;

    //        jeti::PathVisual m_PathVisualCenter;
    //        jeti::PathVisual m_PathVisualTurn;

    void ClearPath();
    void CalcPath();
    void CalcPath_DEBUG();

    bool ValidateTarget() const;

    void UpdateDynamicTargetCoord();

    void DefineDistance();
};



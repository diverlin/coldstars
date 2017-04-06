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

//namespace jeti {
//class DriveEffect;
//}

//namespace jeti {
//class Renderer;
//}

namespace control {
class SpaceObject;
} // namespace control

namespace complex {

class Drive
{
public:
    enum class Action : int {
        NONE=0, DOCKING, COLLECTING, KEEP_FIRE_DISTANCE, KEEP_CLOSE, KEEP_MIDDLE, KEEP_FAR
    };
public:
    Drive(control::Vehicle* owner):m_ownerVehicle(owner) {}
    ~Drive() = default;

//    void setDriveEffect(jeti::DriveEffect* drive_effect)  { m_effectDrive = drive_effect; }

    void addDriveSlot(slot::Item* drive_slot) { m_driveSlots.push_back(drive_slot); }
    void addBakSlot(slot::Item* bak_slot)     { m_bakSlots.push_back(bak_slot); }

    void setTarget(control::SpaceObject*, Action action = Action::KEEP_CLOSE);
    void setCoordinates(const glm::vec3&);

    Action action() const { return m_action; }
//    jeti::DriveEffect* driveEffect() const { return m_effectDrive; }

    std::vector<slot::Item*> driveSlots() const { return m_driveSlots; }
    std::vector<slot::Item*> bakSlots() const { return m_bakSlots; }

    control::SpaceObject* target() const { return m_target; }

    bool pathExists() const;

    bool checkTargetEchievement(const meti::vec3&);
    bool getDockingPermission();

    void resetTarget();

    void updatePath();
    void updatePosition();

//    void updatePathVisualisation();
//    void drawPath(const jeti::Renderer&);

private:
    std::vector<slot::Item*> m_driveSlots;
    std::vector<slot::Item*> m_bakSlots;

    control::Vehicle* m_ownerVehicle = nullptr;
    control::SpaceObject* m_target = nullptr;

//    jeti::DriveEffect* m_effectDrive = nullptr;

    glm::vec3 m_targetPos;

    Action m_action = Action::NONE;
    float m_targetDistance = 0.0f;
    glm::vec3 m_targetOffset;

    std::vector<glm::vec3> m_pathCenterVec;
    std::vector<glm::vec3> m_pathDirectionVec;

    bool m_pathEnd = true;
    unsigned int m_pathIndex = 0;
    bool m_hasTarget = false;

    //        jeti::PathVisual m_PathVisualCenter;
    //        jeti::PathVisual m_PathVisualTurn;

    void __clearPath();
    void __calcPath();
    void __calcPath_DEBUG();

    bool __validateTarget() const;

    void __updateDynamicTargetCoord();

//    void __defineDistance();
};

} // namespace complex

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

#include <core/part/Path.hpp>

#include <meti/VectorUtils.hpp>

#include <vector>

namespace core {

namespace control {
class SpaceObject;
class Vehicle;

} // namespace control

class ItemSlot;

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

    const path::Path& path() const { return m_path; }

    void addDriveSlot(ItemSlot* drive_slot) { m_driveSlots.push_back(drive_slot); }
    void addBakSlot(ItemSlot* bak_slot)     { m_bakSlots.push_back(bak_slot); }

    void setTarget(control::SpaceObject*, Action action = Action::KEEP_CLOSE);
    void setTarget(const glm::vec3&);

    Action action() const { return m_action; }

    std::vector<ItemSlot*> driveSlots() const { return m_driveSlots; }
    std::vector<ItemSlot*> bakSlots() const { return m_bakSlots; }

    control::SpaceObject* target() const { return m_target; }

    bool pathExists() const;

    bool checkTargetEchievement(const meti::vec3&);
    bool getDockingPermission();

    void resetTarget();

    void refreshPath();
    void update();

private:
    std::vector<ItemSlot*> m_driveSlots;
    std::vector<ItemSlot*> m_bakSlots;

    control::Vehicle* m_ownerVehicle = nullptr;
    control::SpaceObject* m_target = nullptr;

    glm::vec3 m_targetPos;

    Action m_action = Action::NONE;
    float m_targetDistance = 0.0f;
    glm::vec3 m_targetOffset;

    path::Path m_path;

    bool m_hasTarget = false;

    void __calcPath();

    bool __validateTarget() const;

    void __updateDynamicTargetCoord();

//    void __defineDistance();
};

} // namespace complex
} // namespace core

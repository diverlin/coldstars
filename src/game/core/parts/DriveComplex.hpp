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

class Vehicle;
namespace jeti {
class DriveEffect;
}
class ItemSlot; 
class SpaceObject;

namespace jeti {
class Renderer;
}

class DriveComplex
{
    public:
        DriveComplex();
        ~DriveComplex();
        
        void SetOwnerVehicle(Vehicle* owner_vehicle)    { m_ownerVehicle = owner_vehicle; }
        void SetDriveEffect(jeti::DriveEffect* drive_effect)  { m_effectDrive = drive_effect; }
        
        void SetDriveSlot(ItemSlot* drive_slot) { m_driveSlot = drive_slot; }
        void SetBakSlot(ItemSlot* bak_slot)     { m_bakSlot = bak_slot; }
        
        void SetTarget(SpaceObject*, int);       
        void SetStaticTargetCoords(const glm::vec3&);

        int GetActionId() const { return m_ActionId; }
        jeti::DriveEffect* GetDriveEffect() const { return m_effectDrive; }
                                    
        ItemSlot* driveSlot() const { return m_driveSlot; }
        ItemSlot* bakSlot()   const { return m_bakSlot; }
              
        SpaceObject* GetTarget() const { return m_target; }
                    
        bool PathExists() const;
        
        bool CheckTargetEchievement();
        bool GetDockingPermission();               
    
        void ResetTarget();

        void UpdatePath();
        void UpdatePosition();

        void UpdatePathVisualisation();                
        void DrawPath(const jeti::Renderer&);
            
    private:
        ItemSlot* m_driveSlot = nullptr;
        ItemSlot* m_bakSlot = nullptr;
        
        Vehicle* m_ownerVehicle = nullptr;
        SpaceObject* m_target = nullptr;

        jeti::DriveEffect* m_effectDrive = nullptr;

        glm::vec3 m_TargetPos;
        
        int m_ActionId;
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


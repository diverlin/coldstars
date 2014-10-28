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

#ifndef DRIVECOMPLEX_HPP
#define DRIVECOMPLEX_HPP

#include <render/PathVisual.hpp> 
#include <math/myVector.hpp> 

class Vehicle;
namespace jeti {
class DriveEffect;
}
class ItemSlot; 
class BaseSpaceEntity;

namespace {
class Renderer;
}

class DriveComplex
{
    public:
        DriveComplex();
        ~DriveComplex();
        
        void SetOwnerVehicle(Vehicle* owner_vehicle)    { m_OwnerVehicle = owner_vehicle; };
        void SetDriveEffect(jeti::DriveEffect* drive_effect)  { m_EffectDrive = drive_effect; };
        
        void SetDriveSlot(ItemSlot* drive_slot) { m_DriveSlot = drive_slot; };
        void SetBakSlot(ItemSlot* bak_slot)     { m_BakSlot = bak_slot; };
        
        void SetTarget(BaseSpaceEntity*, int);       
        void SetStaticTargetCoords(const glm::vec3&);

        int GetActionId() const { return m_ActionId; };
        jeti::DriveEffect* GetDriveEffect() const { return m_EffectDrive; };
                                    
        ItemSlot* GetDriveSlot() const { return m_DriveSlot; };
        ItemSlot* GetBakSlot()   const { return m_BakSlot; };
              
        BaseSpaceEntity* GetTarget() const { return m_Target; };                
                    
        bool PathExists() const;
        
        bool CheckTargetEchievement();
        bool GetDockingPermission();               
    
        void ResetTarget();

        void UpdatePath();
        void UpdatePosition();

        void UpdatePathVisualisation();                
        void DrawPath(const jeti::Renderer&);
            
    private:
        ItemSlot* m_DriveSlot;
        ItemSlot* m_BakSlot;
        
        Vehicle* m_OwnerVehicle;
        BaseSpaceEntity* m_Target;

        jeti::DriveEffect* m_EffectDrive;

        glm::vec3 m_TargetPos;
        
        int m_ActionId;
        float m_TargetDistance;   
        glm::vec3 m_TargetOffset;

        std::vector<glm::vec3> m_PathCenterVec;
        std::vector<glm::vec3> m_PathDirectionVec;

        bool m_PathEnd;
        unsigned int m_PathIndex;
                
        bool m_HasTarget;
        
        jeti::PathVisual m_PathVisualCenter;
        jeti::PathVisual m_PathVisualTurn;
        
        void ClearPath();
        void CalcPath();      
        void CalcPath_DEBUG();      

        bool ValidateTarget() const;
        
        void UpdateDynamicTargetCoord();

        void DefineDistance();
};

#endif

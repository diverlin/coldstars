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


#ifndef ITEMSLOT_HPP
#define ITEMSLOT_HPP

#include <types/MyInt.hpp>
#include <types/StatusTypes.hpp>

#include <slots/BaseSlot.hpp>
#include <render/PathVisual.hpp>  // !!!

class Turrel; 
class BaseItem;
class BaseSpaceEntity;

class RocketEquipment; 
class LazerEquipment; 
class RadarEquipment; 
class BakEquipment; 
class EnergizerEquipment; 
class ProtectorEquipment; 
class DroidEquipment; 
class FreezerEquipment; 
class ScanerEquipment;
class DriveEquipment; 
class GrappleEquipment; 

class RocketModule;
class LazerModule;
class RadarModule; 
class BakModule; 
class EnergizerModule; 
class ProtectorModule; 
class DroidModule; 
class FreezerModule; 
class ScanerModule;
class DriveModule; 
class GrappleModule; 

class Bomb; 
class GoodsPack; 

class Box2D;

namespace jeti {
class Renderer;
}

struct UnresolvedDataItemSlot
{
    UnresolvedDataItemSlot():target_id(NONE_ID), subtarget_id(NONE_ID) 
    {};
    
    INTLONGEST target_id;    
    INTLONGEST subtarget_id; 
};

class ItemSlot : public BaseSlot
{   
    public:        
        ItemSlot(INTLONGEST, TYPE::ENTITY);
        virtual ~ItemSlot();                
        
        virtual void PutChildsToGarbage() const;
        
        void SetTarget(BaseSpaceEntity* target, ItemSlot* subtarget = nullptr);
        void SetTurrel(Turrel* turrel) { m_Turrel = turrel; }
        
        BaseSpaceEntity* GetTarget() const { return m_Target; }
        ItemSlot* GetSubTarget() const { return m_Subtarget; }        
        
        int GetHitProbability() const { return m_HitProbability; }
        
        Turrel* GetTurrel() const { return m_Turrel; }
        
        BaseItem* GetItem()                         const { return m_Item; }                
        RocketEquipment*    GetRocketEquipment()    const { return (RocketEquipment*)m_Item; }
         LazerEquipment*     GetLazerEquipment()     const { return (LazerEquipment*)m_Item; }
        RadarEquipment*     GetRadarEquipment()     const { return (RadarEquipment*)m_Item; }
        DriveEquipment*     GetDriveEquipment()     const { return (DriveEquipment*)m_Item; }
        BakEquipment*       GetBakEquipment()       const { return (BakEquipment*)m_Item; }
        EnergizerEquipment* GetEnergizerEquipment() const { return (EnergizerEquipment*)m_Item; }
        ProtectorEquipment* GetProtectorEquipment() const { return (ProtectorEquipment*)m_Item; }
        DroidEquipment*     GetDroidEquipment()     const { return (DroidEquipment*)m_Item; }
        FreezerEquipment*   GetFreezerEquipment()   const { return (FreezerEquipment*)m_Item; }
        ScanerEquipment*    GetScanerEquipment()    const { return (ScanerEquipment*)m_Item; }
        GrappleEquipment*   GetGrappleEquipment()   const { return (GrappleEquipment*)m_Item; }

        RocketModule*       GetRocketModule()       const { return (RocketModule*)m_Item; }
        LazerModule*        GetLazerModule()        const { return (LazerModule*)m_Item; }
        RadarModule*        GetRadarModule()        const { return (RadarModule*)m_Item; }
        DriveModule*        GetDriveModule()        const { return (DriveModule*)m_Item; }
        BakModule*          GetBakModule()          const { return (BakModule*)m_Item; }
        EnergizerModule*    GetEnergizerModule()    const { return (EnergizerModule*)m_Item; }
        ProtectorModule*    GetProtectorModule()    const { return (ProtectorModule*)m_Item; }
        DroidModule*        GetDroidModule()        const { return (DroidModule*)m_Item; }
        FreezerModule*      GetFreezerModule()      const { return (FreezerModule*)m_Item; }
        ScanerModule*       GetScanerModule()       const { return (ScanerModule*)m_Item; }
        GrappleModule*      GetGrappleModule()      const { return (GrappleModule*)m_Item; }

        Bomb* GetBomb()           const { return (Bomb*)m_Item; }
        //Artefact* GetArtefact() const { return artefact; }
        GoodsPack* GetGoodsPack() const { return (GoodsPack*)m_Item; }
                              
        bool InsertItem(BaseItem*);            
        void RemoveItem();
        
        STATUS ValidateTarget();                    
        void ResetTarget();
        bool CheckAmmo() const;
        void FireEvent(float, bool);
        
        void UpdateVehiclePropetries() const;
        
        virtual void Render(const jeti::Renderer&, const Box2D&, const glm::vec2&, bool draw_text = true) const;
        virtual void RenderItem(const jeti::Renderer&, const Box2D&, const glm::vec2&, bool draw_text = true) const;
        void RenderMark(const jeti::Renderer&, const Box2D&, jeti::TextureOb*) const;
        void RenderTargetMark(const jeti::Renderer&, const Box2D&, jeti::TextureOb*, jeti::TextureOb*) const;
        
        void DropItemToSpace();
        
        bool SwapItem(ItemSlot*);
        
        void UpdateRange(jeti::TextureOb*);
        void DrawRange(const glm::vec2&);
        
        bool CheckSubTarget(ItemSlot*) const;
        STATUS CheckTarget(BaseSpaceEntity*) const;
        STATUS CheckTargetPure(BaseSpaceEntity*) const;
                
        void SelectEvent();
        void DeselectEvent();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
        int GetItemRadius() const;
        int GetItemDamage() const;
                                      
    private:                               
        Turrel* m_Turrel;          // only for weapons slot
        
        BaseItem* m_Item;
        
        BaseSpaceEntity* m_Target;
        ItemSlot* m_Subtarget;      
        
        int m_HitProbability;
        jeti::PathVisual m_VisualPath;    // !!!
        
        bool CheckItemInsertion(BaseItem*) const;  
        
        bool IsTargetAlive(BaseSpaceEntity*) const;
        bool IsTargetInSpace(BaseSpaceEntity*) const;  
        bool IsTargetInSameStarSystem(BaseSpaceEntity*) const;
        bool CheckDistanceToTarget(BaseSpaceEntity*) const;
        
        UnresolvedDataItemSlot unresolved_ItemSlot;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
        void Log(const std::string&) const;
}; 

#endif

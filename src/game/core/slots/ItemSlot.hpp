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

#include <types/MyInt.hpp>
#include <types/StatusTypes.hpp>

#include <slots/BaseSlot.hpp>
//#include <jeti/PathVisual.hpp>  // !!!

class Turrel; 
class BaseItem;
class SpaceObject;

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

namespace ceti {
class Box2D;
}

namespace jeti {
class Renderer;
}

struct UnresolvedDataItemSlot
{
    UnresolvedDataItemSlot()
    {}
    
    IDTYPE target_id = NONE_ID;
    IDTYPE subtarget_id = NONE_ID;
};

class ItemSlot : public BaseSlot
{   
    public:        
        ItemSlot(unsigned long intPE::ENTITY);
        virtual ~ItemSlot();                
        
        virtual void putChildrenToGarbage() const;
        
        void setTarget(SpaceObject* target, ItemSlot* subtarget = nullptr);
        void setTurrel(Turrel* turrel) { m_turrel = turrel; }
        
        SpaceObject* target() const { return m_target; }
        ItemSlot* subtarget() const { return m_subtarget; }
        
        int hitProbability() const { return m_hitProbability; }
        
        Turrel* turrel() const { return m_turrel; }
        
        BaseItem* item()                         const { return m_item; }
        RocketEquipment*    rocketEquipment()    const { return (RocketEquipment*)m_item; }
        LazerEquipment*     lazerEquipment()     const { return (LazerEquipment*)m_item; }
        RadarEquipment*     radarEquipment()     const { return (RadarEquipment*)m_item; }
        DriveEquipment*     driveEquipment()     const { return (DriveEquipment*)m_item; }
        BakEquipment*       bakEquipment()       const { return (BakEquipment*)m_item; }
        EnergizerEquipment* energizerEquipment() const { return (EnergizerEquipment*)m_item; }
        ProtectorEquipment* protectorEquipment() const { return (ProtectorEquipment*)m_item; }
        DroidEquipment*     droidEquipment()     const { return (DroidEquipment*)m_item; }
        FreezerEquipment*   freezerEquipment()   const { return (FreezerEquipment*)m_item; }
        ScanerEquipment*    scanerEquipment()    const { return (ScanerEquipment*)m_item; }
        GrappleEquipment*   grappleEquipment()   const { return (GrappleEquipment*)m_item; }

        RocketModule*       rocketModule()       const { return (RocketModule*)m_item; }
        LazerModule*        lazerModule()        const { return (LazerModule*)m_item; }
        RadarModule*        radarModule()        const { return (RadarModule*)m_item; }
        DriveModule*        driveModule()        const { return (DriveModule*)m_item; }
        BakModule*          bakModule()          const { return (BakModule*)m_item; }
        EnergizerModule*    energizerModule()    const { return (EnergizerModule*)m_item; }
        ProtectorModule*    protectorModule()    const { return (ProtectorModule*)m_item; }
        DroidModule*        droidModule()        const { return (DroidModule*)m_item; }
        FreezerModule*      freezerModule()      const { return (FreezerModule*)m_item; }
        ScanerModule*       scanerModule()       const { return (ScanerModule*)m_item; }
        GrappleModule*      grappleModule()      const { return (GrappleModule*)m_item; }

        Bomb* bomb()           const { return (Bomb*)m_item; }
        //Artefact* GetArtefact() const { return artefact; }
        GoodsPack* goodsPack() const { return (GoodsPack*)m_item; }
                              
        bool insertItem(BaseItem*);
        void removeItem();
        
        STATUS validateTarget();
        void resetTarget();
        bool checkAmmo() const;
        void fireEvent(float, bool);
        
        void updateVehiclePropetries() const;
        
//        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
//        virtual void RenderItem(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true) const;
//        void RenderMark(const jeti::Renderer&, const ceti::Box2D&, jeti::TextureOb*) const;
//        void RenderTargetMark(const jeti::Renderer&, const ceti::Box2D&, jeti::TextureOb*, jeti::TextureOb*) const;
        
        void dropItemToSpace();
        
        bool swapItem(ItemSlot*);
        
        void updateRange(jeti::TextureOb*);
        void drawRange(const glm::vec2&);
        
        bool checkSubTarget(ItemSlot*) const;
        STATUS checkTarget(SpaceObject*) const;
        STATUS checkTargetPure(SpaceObject*) const;
                
        void selectEvent();
        void deselectEvent();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
        int itemRadius() const;
        int itemDamage() const;
                                      
    private:                               
        Turrel* m_turrel;          // only for weapons slot
        
        BaseItem* m_item;
        
        SpaceObject* m_target;
        ItemSlot* m_subtarget;
        
        int m_hitProbability;
//        jeti::PathVisual m_VisualPath;    // !!!
        
        bool checkItemInsertion(BaseItem*) const;
        
        bool isTargetAlive(SpaceObject*) const;
        bool isTargetInSpace(SpaceObject*) const;
        bool isTargetInSameStarSystem(SpaceObject*) const;
        bool checkDistanceToTarget(SpaceObject*) const;
        
        UnresolvedDataItemSlot m_unresolved_ItemSlot;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
        void log(const std::string&) const;
}; 

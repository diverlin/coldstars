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

#include "../slots/BaseSlot.hpp"
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
#include "../render/PathVisual.hpp"
#include "../common/constants.hpp"
class Box;

struct UnresolvedDataUniqueItemSlot
{
	UnresolvedDataUniqueItemSlot():target_id(NONE_ID), subtarget_id(NONE_ID) 
	{};
	
	int target_id;    
	int subtarget_id; 
};

class ItemSlot : public BaseSlot
{   
	public:        
		ItemSlot(int, ENTITY::TYPE);
		virtual ~ItemSlot();                
        
        virtual void PutChildsToGarbage() const;
        
        void SetTarget(BaseSpaceEntity* target, ItemSlot* subtarget = nullptr);
        void SetTurrel(Turrel* turrel) { this->turrel = turrel; };
        
        BaseSpaceEntity* GetTarget() const { return target; };
        ItemSlot* GetSubTarget() const { return subtarget; };          
        
        Turrel* GetTurrel() const { return turrel; };
        
        BaseItem* GetItem()                         const { return item; };                
        RocketEquipment*    GetRocketEquipment()    const { return (RocketEquipment*)item; }
 		LazerEquipment*     GetLazerEquipment()     const { return (LazerEquipment*)item; }
		RadarEquipment*     GetRadarEquipment()     const { return (RadarEquipment*)item; }
		DriveEquipment*     GetDriveEquipment()     const { return (DriveEquipment*)item; }
		BakEquipment*       GetBakEquipment()       const { return (BakEquipment*)item; }
		EnergizerEquipment* GetEnergizerEquipment() const { return (EnergizerEquipment*)item; }
		ProtectorEquipment* GetProtectorEquipment() const { return (ProtectorEquipment*)item; }
		DroidEquipment*     GetDroidEquipment()     const { return (DroidEquipment*)item; }
		FreezerEquipment*   GetFreezerEquipment()   const { return (FreezerEquipment*)item; }
		ScanerEquipment*    GetScanerEquipment()    const { return (ScanerEquipment*)item; }
		GrappleEquipment*   GetGrappleEquipment()   const { return (GrappleEquipment*)item; }

		RocketModule*       GetRocketModule()       const { return (RocketModule*)item; }
		LazerModule*        GetLazerModule()        const { return (LazerModule*)item; }
		RadarModule*        GetRadarModule()        const { return (RadarModule*)item; }
		DriveModule*        GetDriveModule()        const { return (DriveModule*)item; }
		BakModule*          GetBakModule()          const { return (BakModule*)item; }
		EnergizerModule*    GetEnergizerModule()    const { return (EnergizerModule*)item; }
		ProtectorModule*    GetProtectorModule()    const { return (ProtectorModule*)item; }
		DroidModule*        GetDroidModule()        const { return (DroidModule*)item; }
		FreezerModule*      GetFreezerModule()      const { return (FreezerModule*)item; }
		ScanerModule*       GetScanerModule()       const { return (ScanerModule*)item; }
		GrappleModule*      GetGrappleModule()      const { return (GrappleModule*)item; }

		Bomb* GetBomb()           const { return (Bomb*)item; }
		//Artefact* GetArtefact() const { return artefact; }
		GoodsPack* GetGoodsPack() const { return (GoodsPack*)item; }
                              
		bool InsertItem(BaseItem*);            
		void RemoveItem();
		
        bool ValidateTarget();                    
        void ResetTarget();
        bool CheckAmmo() const;
        void FireEvent(float, bool);
        
        void UpdateVehiclePropetries() const;
        
        virtual void Render(const Box&, const Vec2<float>&, bool draw_text = true) const;
        void RenderMark(const Box&, TextureOb*) const;
        
        void DropItemToSpace();
        
        bool SwapItem(ItemSlot*);
        
        void UpdateRange(TextureOb*);
        void DrawRange(const Vec3<float>&);
        
        bool CheckSubTarget(ItemSlot*) const;
        bool CheckTarget(BaseSpaceEntity*) const;
        bool CheckTargetPure(BaseSpaceEntity*) const;
        
        void SelectEvent();
        void DeselectEvent();
        
        virtual void SaveData(boost::property_tree::ptree&) const;
        virtual void LoadData(const boost::property_tree::ptree&);
        virtual void ResolveData();
        
        int GetItemRadius() const;
        int GetItemDamage() const;
           	           			
    private:                               
        Turrel* turrel;          // only for weapons slot
        
        BaseItem* item;
        
        BaseSpaceEntity* target;
        ItemSlot* subtarget;      
        
        PathVisual range_visual;
        
        bool CheckItemInsertion(BaseItem*) const;  
        
        bool IsTargetAlive(BaseSpaceEntity*) const;
        bool IsTargetInSpace(BaseSpaceEntity*) const;  
        bool IsTargetInSameStarSystem(BaseSpaceEntity*) const;
        bool CheckDistanceToTarget(BaseSpaceEntity*) const;
        
        UnresolvedDataUniqueItemSlot unresolved_ItemSlot;
        void SaveDataUniqueItemSlot(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueItemSlot(const boost::property_tree::ptree&);
        void ResolveDataUniqueItemSlot();
        
        void Log(const std::string&) const;
}; 

#endif

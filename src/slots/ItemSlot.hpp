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


#ifndef ITEMSLOT_H
#define ITEMSLOT_H

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

class ItemSlot : public BaseSlot
{   
	public:        
		ItemSlot(int id);
		virtual ~ItemSlot();                
	
		void SetTurrel(Turrel* turrel) { this->turrel = turrel; };
                                
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
		
		void UpdateVehiclePropetries() const;
                
		virtual void Render(const Rect&, const vec2f&, bool draw_text = true) const;
		void RenderMark(const Rect&, TextureOb*) const;

		void RenderItemInfo(const vec2f&, const vec2f&) const;		       
		void RenderItemInfo(const vec2f&, float offset_x = 0, float offset_y = 0) const;
                
                void DropItemToSpace(Vehicle*);
                                                
                bool SwapItem(ItemSlot*);
                
                void UpdateRange(TextureOb*);
           	void DrawRange(const vec2f&);
           	
           	bool CheckTarget(BaseSpaceEntity*) const;
        
        	void SelectEvent();
        	void DeselectEvent();
        
        	void RemoveChildFromEntityManager();
        
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();

           	int GetItemRadius() const;
           			
        private:                               
                Turrel* turrel;          // only for weapons slot
                
                BaseItem* item;

           	PathVisual range_visual;
           	              
           	bool CheckAlive(BaseSpaceEntity*) const;
           	bool CheckPlaceTypeId(BaseSpaceEntity*) const;  
                bool CheckStarSystem(BaseSpaceEntity*) const;
           	bool CheckDistance(BaseSpaceEntity*) const;
                
                void SaveDataUniqueItemSlot(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueItemSlot(const boost::property_tree::ptree&);
		void ResolveDataUniqueItemSlot();
}; 

#endif

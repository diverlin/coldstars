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


class ItemSlot
{   
	public:        
                int type_id, subtype_id;
                int item_type_id, item_subtype_id;

                bool is_EQUIPED;  
                bool is_FLASHING;
                bool is_CURSORED;      

                Ship* pTo_ship;

                Rect rect;
                TextureOb* pTo_texOb;
                GLuint texture;

                int w, h;
        
        	ItemSlot();
		ItemSlot(int _subtype_id, Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y);
                
                RocketEquipment*    get_pToRocketEquipment()    const;
                LazerEquipment*     get_pToLazerEquipment()     const;
                RadarEquipment*     get_pToRadarEquipment()     const;
                DriveEquipment*     get_pToDriveEquipment()     const;
                BakEquipment*       get_pToBakEquipment()       const;
                EnergizerEquipment* get_pToEnergizerEquipment() const;
                ProtectorEquipment* get_pToProtectorEquipment() const;
                DroidEquipment*     get_pToDroidEquipment()     const;
                FreezerEquipment*   get_pToFreezerEquipment()   const;
                ScanerEquipment*    get_pToScanerEquipment()    const;
                GrappleEquipment*   get_pToGrappleEquipment()   const;
                
                RocketModule*    get_pToRocketModule()    const;
                LazerModule*     get_pToLazerModule()     const;
                RadarModule*     get_pToRadarModule()     const;                
                DriveModule*     get_pToDriveModule()     const;  
                BakModule*       get_pToBakModule()       const; 
                EnergizerModule* get_pToEnergizerModule() const; 
                ProtectorModule* get_pToProtectorModule() const;
                DroidModule*     get_pToDroidModule()     const;
                FreezerModule*   get_pToFreezerModule()   const;
                ScanerModule*    get_pToScanerModule()    const;
                GrappleModule*   get_pToGrappleModule()   const;

		bool insertItem(RocketEquipment* pTo_item);
		bool insertItem(LazerEquipment* pTo_item);
        
		bool insertItem(RadarEquipment* pTo_item);
		bool insertItem(DriveEquipment* pTo_item);
		bool insertItem(BakEquipment* pTo_item);
		bool insertItem(EnergizerEquipment* pTo_item);
		bool insertItem(ProtectorEquipment* pTo_item);
		bool insertItem(DroidEquipment* pTo_item);
		bool insertItem(FreezerEquipment* pTo_item);
		bool insertItem(ScanerEquipment* pTo_item);
		bool insertItem(GrappleEquipment* pTo_item);
        
		bool insertItem(RocketModule* pTo_item);
		bool insertItem(LazerModule* pTo_item);
		bool insertItem(RadarModule* pTo_item);
		bool insertItem(DriveModule* pTo_item);
		bool insertItem(BakModule* pTo_item);
		bool insertItem(EnergizerModule* pTo_item);
		bool insertItem(ProtectorModule* pTo_item);
		bool insertItem(DroidModule* pTo_item);
		bool insertItem(FreezerModule* pTo_item);
		bool insertItem(ScanerModule* pTo_item);
		bool insertItem(GrappleModule* pTo_item);
                
		void removeItem();

		int getItemMass(); 
		int getItemPrice(); 
                int getItemDamage();
                int getItemRadius();
                int getItemCondition();
                
		void renderFrame(GLuint flash_tex);
		void renderFrames(GLuint flash_tex);
       
		void renderEquipedItem();
		void renderItemInfo();
                
                bool interaction(int _x, int _y);
        
        private:
                RocketEquipment*    pTo_rocketEquipment;
                LazerEquipment*     pTo_lazerEquipment;
		RadarEquipment*     pTo_radarEquipment;
		DriveEquipment*     pTo_driveEquipment;
		BakEquipment*       pTo_bakEquipment;
		EnergizerEquipment* pTo_energizerEquipment;
		ProtectorEquipment* pTo_protectorEquipment;
		DroidEquipment*     pTo_droidEquipment;
		FreezerEquipment*   pTo_freezerEquipment;
		ScanerEquipment*    pTo_scanerEquipment;
		GrappleEquipment*   pTo_grappleEquipment;
                
		RocketModule*    pTo_rocketModule;
		LazerModule*     pTo_lazerModule;
		RadarModule*     pTo_radarModule;
		DriveModule*     pTo_driveModule;
		BakModule*       pTo_bakModule;
		EnergizerModule* pTo_energizerModule;
                ProtectorModule* pTo_protectorModule;
		DroidModule*     pTo_droidModule;
		FreezerModule*   pTo_freezerModule;
		ScanerModule*    pTo_scanerModule;
		GrappleModule*   pTo_grappleModule;
}; 

#endif

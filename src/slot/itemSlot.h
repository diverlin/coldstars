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
        	ItemSlot();
		ItemSlot(int _subtype_id, Ship* _ship, TextureOb* _texOb, int _pos_x, int _pos_y);
                
                int getType()        const;
                int getSubType()     const;
                int getItemType()    const;
                int getItemSubType() const;

                Turrel* getTurrel()  const;
                Turrel* bindTurrel(Turrel* _turrel);
                                    
                bool getEquipedStatus()  const;
                bool getCursoredStatus() const;
                void setCursoredStatus(bool new_status);
                bool getFlashingStatus() const;
                void setFlashingStatus(bool new_status);
                      
                Rect& getRect();
                Ship* getShip() const;
                
                RocketEquipment*    getRocketEquipment()    const;
                LazerEquipment*     getLazerEquipment()     const;
                RadarEquipment*     getRadarEquipment()     const;
                DriveEquipment*     getDriveEquipment()     const;
                BakEquipment*       getBakEquipment()       const;
                EnergizerEquipment* getEnergizerEquipment() const;
                ProtectorEquipment* getProtectorEquipment() const;
                DroidEquipment*     getDroidEquipment()     const;
                FreezerEquipment*   getFreezerEquipment()   const;
                ScanerEquipment*    getScanerEquipment()    const;
                GrappleEquipment*   getGrappleEquipment()   const;
                
                RocketModule*    getRocketModule()    const;
                LazerModule*     getLazerModule()     const;
                RadarModule*     getRadarModule()     const;                
                DriveModule*     getDriveModule()     const;  
                BakModule*       getBakModule()       const; 
                EnergizerModule* getEnergizerModule() const; 
                ProtectorModule* getProtectorModule() const;
                DroidModule*     getDroidModule()     const;
                FreezerModule*   getFreezerModule()   const;
                ScanerModule*    getScanerModule()    const;
                GrappleModule*   getGrappleModule()   const;

		bool insertItem(RocketEquipment* item);
		bool insertItem(LazerEquipment* item);
        
		bool insertItem(RadarEquipment* item);
		bool insertItem(DriveEquipment* item);
		bool insertItem(BakEquipment* item);
		bool insertItem(EnergizerEquipment* item);
		bool insertItem(ProtectorEquipment* item);
		bool insertItem(DroidEquipment* item);
		bool insertItem(FreezerEquipment* item);
		bool insertItem(ScanerEquipment* item);
		bool insertItem(GrappleEquipment* item);
        
		bool insertItem(RocketModule* item);
		bool insertItem(LazerModule* item);
		bool insertItem(RadarModule* item);
		bool insertItem(DriveModule* item);
		bool insertItem(BakModule* item);
		bool insertItem(EnergizerModule* item);
		bool insertItem(ProtectorModule* item);
		bool insertItem(DroidModule* item);
		bool insertItem(FreezerModule* item);
		bool insertItem(ScanerModule* item);
		bool insertItem(GrappleModule* item);
                
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
                int type_id, subtype_id;               
                int item_type_id, item_subtype_id;     
                                                
                bool is_EQUIPED;                       // slot is empty or equiped 
                bool is_CURSORED;                      // cursor position collide with slot rect or not (used for rendering inserted item info) 
                bool is_FLASHING;                      // flashing the slot to show that item can be inserted in that one 
                
                TextureOb* texOb;
                GLuint texture;
                int w, h;
                
                Rect rect;
                                
                Ship* ship;
                        
                Turrel* turrel;
                
                RocketEquipment*    rocket_equipment;
                LazerEquipment*     lazer_equipment;
		RadarEquipment*     radar_equipment;
		DriveEquipment*     drive_equipment;
		BakEquipment*       bak_equipment;
		EnergizerEquipment* energizer_equipment;
		ProtectorEquipment* protector_equipment;
		DroidEquipment*     droid_equipment;
		FreezerEquipment*   freezer_equipment;
		ScanerEquipment*    scaner_equipment;
		GrappleEquipment*   grapple_equipment;
                
		RocketModule*    rocket_module;
		LazerModule*     lazer_module;
		RadarModule*     radar_module;
		DriveModule*     drive_module;
		BakModule*       bak_module;
		EnergizerModule* energizer_module;
                ProtectorModule* protector_module;
		DroidModule*     droid_module;
		FreezerModule*   freezer_module;
		ScanerModule*    scaner_module;
		GrappleModule*   grapple_module;
}; 

#endif

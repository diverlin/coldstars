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
		ItemSlot(int _subtype_id, Ship* _ship, TextureOb* _texOb, int _pos_x, int _pos_y, int w, int h);
		~ItemSlot();
                
                void setShipOwner(Ship*);
                void bindTurrel(Turrel*);
                                
                int getTypeId()        const;
                int getSubTypeId()     const;
                int getItemTypeId()    const;
                int getItemSubTypeId() const;
                
                Turrel* getTurrel()  const;  
                                                  
                bool getEquipedStatus()  const;
                bool getCursoredStatus() const;
                void setCursoredStatus(bool new_status);
                bool getFlashingStatus() const;
                void setFlashingStatus(bool new_status);
                      
                Rect& getRect();
                Ship* getOwnerShip();
                
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
                
                Bomb* getBomb() const;
                //Artefact* getArtefact() const;
                GoodsPack* getGoodsPack() const;
                Ship* getShip() const;

                TextureOb* getItemTexOb() const;
		int getItemMass() const; 
		int getItemPrice() const; 
                int getItemDamage() const;
                int getItemRadius() const;
                int getItemCondition() const;
                
		template <typename ITEM_TYPE>
		bool insertItem(ITEM_TYPE*);

		bool insertGoods(GoodsPack*);
		bool insertContainer(Container*);
						                
		void removeItem();
                
		void render(GLuint);
       
		void renderEquipedItem();
		void renderItemInfo(float offset_x = 0, float offset_y = 0);
                
                bool interaction(int _x, int _y);
                
                void dropItemToSpace();
                
                bool SwapItemWith(ItemSlot*);
                
                void updateRange(TextureOb*);
           	void drawRange();
           	
           	void targetObValidation(TargetObject*);
        
        private:
                int type_id, subtype_id;               
                int item_type_id, item_subtype_id;     
                                                
                bool is_EQUIPED;                       // slot is empty or equiped 
                bool is_FLASHING;                      // flashing the slot to show that item can be inserted in that one 
                
                TextureOb* texOb;
                
                Rect rect;
                                
                Ship* owner_ship;  // reference to the ship_owenr                
                Turrel* turrel;    // only for weapons slot
                
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
		
		GoodsPack* goods_pack;
		Bomb*      bomb;
		Ship* 	   ship;
		//Artefact   artefact;
		
		void insert(RocketEquipment*);
		void insert(LazerEquipment*);        
		void insert(RadarEquipment*);
		void insert(DriveEquipment*);
		void insert(BakEquipment*);
		void insert(EnergizerEquipment*);
		void insert(ProtectorEquipment*);
		void insert(DroidEquipment*);
		void insert(FreezerEquipment*);
		void insert(ScanerEquipment*);
		void insert(GrappleEquipment*);
				
		void insert(RocketModule*);
		void insert(LazerModule*);
		void insert(RadarModule*);
		void insert(DriveModule*);
		void insert(BakModule*);
		void insert(EnergizerModule*);
		void insert(ProtectorModule*);
		void insert(DroidModule*);
		void insert(FreezerModule*);
		void insert(ScanerModule*);
		void insert(GrappleModule*);

		void insert(Bomb*);
		void insert(Ship*);
		//void insert(Artefact*);
				
		void resetFlags();
		
		std::vector<vec2f> range_vec;
           	PathVisual range_visual;
           	
           	bool checkDistance(TargetObject*);
}; 

#endif

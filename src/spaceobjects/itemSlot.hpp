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
		ItemSlot(int _subtype_id, Vehicle*, TextureOb*);
		~ItemSlot();
                
                void setOwner(Vehicle*);
                void bindTurrel(Turrel*);
                void setRect(int _pos_x, int _pos_y, int w, int h);
                      
                int getTypeId()        const;
                int getSubTypeId()     const;
                ItemBase* getItem()    const;
                
                Turrel* getTurrel()  const;  
                
                Rect& getRect();
                Vehicle* getOwnerVehicle() const;

                void setCursoredStatus(bool new_status);
                void setFlashingStatus(bool new_status);                
                                                                  
                bool getEquipedStatus()  const;
                bool getCursoredStatus() const;
                bool getFlashingStatus() const;
                
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
                Vehicle* getVehicle() const;
                
		bool insertItem(ItemBase*);
                
		bool extractContainer(Container*);
						                
		void removeItem();
                
		void render(GLuint);
       
		void renderEquipedItem();
		void renderItemInfo(float offset_x = 0, float offset_y = 0);
                
                bool interaction(int _x, int _y);
                
                void dropItemToSpace();
                
                bool SwapItemWith(ItemSlot*);
                
                void updateRange(TextureOb*);
           	void drawRange();
           	
           	bool isTargetOk(BaseGameEntity*) const;
        
        private:
                int type_id, subtype_id;               
                                                
                bool is_EQUIPED;                       // slot is empty or equiped 
                bool is_FLASHING;                      // flashing the slot to show that item can be inserted in that one 
                
                TextureOb* texOb;
                
                Rect rect;
                                
                Vehicle* owner_vehicle;  // reference to the ship_owenr                
                Turrel* turrel;              // only for weapons slot
                
                ItemBase*    item;

		std::vector<vec2f> range_vec;
           	PathVisual range_visual;
           	
           	int getItemRadius() const;
           	                
                bool isStarSystemOk(BaseGameEntity*) const;
           	bool isDistanceOk(BaseGameEntity*) const;
}; 

#endif

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


#ifndef STORE_H
#define STORE_H


class Store
{
        public:
                Store(TextureOb* _texOb_background, TextureOb* _texOb_slot);                      
                ~Store();

                ItemSlot* getEmptySlot();
                                                        void createSlots();
                                                        void initItemsGenerator();
                void addKorpusItem(Ship*);
                void addLazerEquipment(LazerEquipment*);
                void addRocketEquipment(RocketEquipment*);
                //void addTorpedItem(     int _race_id, int _revision_id);
                void addRadarEquipment(RadarEquipment*);
                void addGrappleEquipment(GrappleEquipment*);
                void addDriveEquipment(DriveEquipment*);
                void addProtectorEquipment(ProtectorEquipment*);
                void addBakEquipment(BakEquipment*);
                void addDroidEquipment(DroidEquipment*);
                void addScanerEquipment(ScanerEquipment*);
                void addFreezerEquipment(FreezerEquipment*);
                void addEnergizerEquipment(EnergizerEquipment*);

                int buyWeaponSlotItem(ItemSlot*); 
                int buyDriveSlotItem(ItemSlot*); 
                int buyBakSlotItem(ItemSlot*); 
                int buyRadarSlotItem(ItemSlot*); 
                int buyScanerSlotItem(ItemSlot*); 
                int buyEnergizerSlotItem(ItemSlot*); 
                int buyGrappleSlotItem(ItemSlot*); 
                int buyProtectorSlotItem(ItemSlot*); 
                int buyDroidSlotItem(ItemSlot*); 
                int buyFreezerSlotItem(ItemSlot*); 

                int buyOtsecSlotItem(ItemSlot*); 

                void update();
                void render() const;
                
        public:
                TextureOb* texOb_background; 
                TextureOb* texOb_slot; 
                
                unsigned int korpus_num;      
                unsigned int lazer_num;       
                unsigned int rocket_num;      
                unsigned int torped_num;      
                unsigned int radar_num;       
                unsigned int grapple_num;     
                unsigned int drive_num;       
                unsigned int protector_num;   
                unsigned int bak_num;         
                unsigned int droid_num;       
                unsigned int scaner_num;      
                unsigned int freezer_num;     
                unsigned int energyBlock_num; 
                
                std::vector<ItemSlot*> slot_pList;
                
                void mouseControl();
                void resetSlotsRenderInfoFlag();
        
                void renderBackground() const;
                void renderInternals() const;
                void renderItemInfo() const;
};
           
#endif





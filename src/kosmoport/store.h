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
        TextureOb* pTo_bg_texOb; 
        TextureOb* pTo_slot_texOb; 

        int korpus_num;      
        int lazer_num;       
        int rocket_num;      
        int torped_num;      
        int radar_num;       
        int grapple_num;     
        int drive_num;       
        int protector_num;   
        int bak_num;         
        int droid_num;       
        int scaner_num;      
        int freezer_num;     
        int energyBlock_num; 

        std::vector<ItemSlot*> slot_pList;


        Store(TextureOb* _pTo_bg_texOb, TextureOb* _pTo_slot_texOb);
        ~Store();

        void linkTexture();
        void unlinkTexture();

        void createSlots();

        ItemSlot* return_pToEmptySlot();

        void initItemsGenerator();

        void addKorpusItem(Ship*     _pTo_ship);
        void addLazerEquipment(LazerEquipment*         _pTo_lazerEquipment);
        void addRocketEquipment(RocketEquipment*       _pTo_rocketEquipment);
        //void addTorpedItem(     int _race_id, int _revision_id);
        void addRadarEquipment(RadarEquipment*         _pTo_radarEquipment);
        void addGrappleEquipment(GrappleEquipment*     _pTo_grappleEquipment);
        void addDriveEquipment(DriveEquipment*         _pTo_driveEquipment);
        void addProtectorEquipment(ProtectorEquipment* _pTo_protectorEquipment);
        void addBakEquipment(BakEquipment*             _pTo_bakEquipment);
        void addDroidEquipment(DroidEquipment*         _pTo_droid);
        void addScanerEquipment(ScanerEquipment*       _pTo_scaner);
        void addFreezerEquipment(FreezerEquipment*     _pTo_freezer);
        void addEnergizerEquipment(EnergizerEquipment* _pTo_energyBlockItem);


        void manageInitItems();
       
        //void soldItem(ob, slot);
        //void buyItem(ob, slot);
        //void buyKorpus(ob, slot);
    
        int buyWeaponSlotItem(ItemSlot*    pTo_weapon_slot); 
        int buyDriveSlotItem(ItemSlot*     pTo_drive_slot); 
        int buyBakSlotItem(ItemSlot*       pTo_bak_slot); 
        int buyRadarSlotItem(ItemSlot*     pTo_radar_slot); 
        int buyScanerSlotItem(ItemSlot*    pTo_scaner_slot); 
        int buyEnergizerSlotItem(ItemSlot* pTo_energizer_slot); 
        int buyGrappleSlotItem(ItemSlot*   pTo_grapple_slot); 
        int buyProtectorSlotItem(ItemSlot* pTo_protector_slot); 
        int buyDroidSlotItem(ItemSlot*     pTo_droid_slot); 
        int buyFreezerSlotItem(ItemSlot*   pTo_freezer_slot); 

        int buyOtsecSlotItem(ItemSlot* pTo_otsec_slot); 

        void mouseControl();
             void resetSlotsRenderInfoFlag();
        
        void renderBackground();
        void renderInternals();
        void renderItemInfo();
};
           
#endif





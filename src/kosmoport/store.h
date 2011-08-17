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

        VEC_pOtsecSlot_type slot_pList;


        Store(TextureOb* _pTo_bg_texOb, TextureOb* _pTo_slot_texOb);
        ~Store();

        void linkTexture();
        void unlinkTexture();

        void createSlots();

        OtsecSlot* return_pToEmptySlot();

        void initItemsGenerator();

        void addKorpusItem(Ship*     _pTo_ship);
        void addLazerItem(LazerItem*         _pTo_lazerItem);
        void addRocketItem(RocketItem*       _pTo_rocketItem);
        //void addTorpedItem(     int _race_id, int _revision_id);
        void addRadarItem(RadarItem*         _pTo_radarItem);
        void addGrappleItem(GrappleItem*     _pTo_grappleItem);
        void addDriveItem(DriveItem*         _pTo_driveItem);
        void addProtectorItem(ProtectorItem* _pTo_protectorItem);
        void addBakItem(BakItem*             _pTo_bakItem);
        void addDroidItem(DroidItem*         _pTo_droid);
        void addScanerItem(ScanerItem*       _pTo_scaner);
        void addFreezerItem(FreezerItem*     _pTo_freezer);
        void addEnergizerItem(EnergizerItem* _pTo_energyBlockItem);


        void manageInitItems();
       
        //void soldItem(ob, slot);
        //void buyItem(ob, slot);
        //void buyKorpus(ob, slot);
    
        int buyWeaponSlotItem(WeaponSlot*   pTo_weapon_slot); 
        int buyDriveSlotItem(OtsecSlot*     pTo_drive_slot); 
        int buyBakSlotItem(OtsecSlot*       pTo_bak_slot); 
        int buyRadarSlotItem(OtsecSlot*     pTo_radar_slot); 
        int buyScanerSlotItem(OtsecSlot*    pTo_scaner_slot); 
        int buyEnergizerSlotItem(OtsecSlot* pTo_energizer_slot); 
        int buyGrappleSlotItem(OtsecSlot*   pTo_grapple_slot); 
        int buyProtectorSlotItem(OtsecSlot* pTo_protector_slot); 
        int buyDroidSlotItem(OtsecSlot*     pTo_droid_slot); 
        int buyFreezerSlotItem(OtsecSlot*   pTo_freezer_slot); 

        int buyOtsecSlotItem(OtsecSlot* pTo_otsec_slot); 

        void mouseControl();
             void resetSlotsRenderInfoFlag();
        
        void renderBackground();
        void renderInternals();
        void renderItemInfo();
};
           
#endif





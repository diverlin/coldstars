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


#ifndef OTSECSLOT_H
#define OTSECSLOT_H


class OtsecSlot : public CommonForSlot
{   
     public:
        RocketItem*      pTo_rocketItem;
        LazerItem*       pTo_lazerItem;
        RadarItem*       pTo_radarItem;
        DriveItem*       pTo_driveItem;
        BakItem*         pTo_bakItem;
        EnergizerItem*   pTo_energizerItem;
        ProtectorItem*   pTo_protectorItem;
        DroidItem*       pTo_droidItem;
        FreezerItem*     pTo_freezerItem;
        ScanerItem*      pTo_scanerItem;
        GrappleItem*     pTo_grappleItem;

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
        
        OtsecSlot();
        OtsecSlot(int _type_id, Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y);

        void insertItem(RocketItem* pTo_item);
        void insertItem(LazerItem* pTo_item);
        void insertItem(RadarItem* pTo_item);
        void insertItem(DriveItem* pTo_item);
        void insertItem(BakItem* pTo_item);
        void insertItem(EnergizerItem* pTo_item);
        void insertItem(ProtectorItem* pTo_item);
        void insertItem(DroidItem* pTo_item);
        void insertItem(FreezerItem* pTo_item);
        void insertItem(ScanerItem* pTo_item);
        void insertItem(GrappleItem* pTo_item);
        void insertItem(RocketModule* pTo_module);
        void insertItem(LazerModule* pTo_module);
        void insertItem(RadarModule* pTo_module);
        void insertItem(DriveModule* pTo_module);
        void insertItem(BakModule* pTo_module);
        void insertItem(EnergizerModule* pTo_module);
        void insertItem(ProtectorModule* pTo_module);
        void insertItem(DroidModule* pTo_module);
        void insertItem(FreezerModule* pTo_module);
        void insertItem(ScanerModule* pTo_module);
        void insertItem(GrappleModule* pTo_module);
                
        void removeItem();

        int getItemMass(); 
        int getItemPrice(); 

        void renderFrame(GLuint flash_tex);
        void renderFrames(GLuint flash_tex);
       
        void renderEquipedItem();
        void renderItemInfo();
}; 

#endif

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
        RocketItem*      pTo_rocketEquipment;
        LazerItem*       pTo_lazerEquipment;
        RadarItem*       pTo_radarEquipment;
        DriveItem*       pTo_driveEquipment;
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

        bool insertItem(RocketItem* pTo_item);
        bool insertItem(LazerItem* pTo_item);
        
        bool insertItem(RadarItem* pTo_item);
        bool insertItem(DriveItem* pTo_item);
        bool insertItem(BakItem* pTo_item);
        bool insertItem(EnergizerItem* pTo_item);
        bool insertItem(ProtectorItem* pTo_item);
        bool insertItem(DroidItem* pTo_item);
        bool insertItem(FreezerItem* pTo_item);
        bool insertItem(ScanerItem* pTo_item);
        bool insertItem(GrappleItem* pTo_item);
        
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

        void renderFrame(GLuint flash_tex);
        void renderFrames(GLuint flash_tex);
       
        void renderEquipedItem();
        void renderItemInfo();
}; 

#endif

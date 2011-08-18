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



#ifndef CONTAINER_H
#define CONTAINER_H


class Container : public CommonForSpaceItems
{
    public: 
        //StarSystem* pTo_starsystem;

        int id;
        int type_id;
        int item_subtype_id; 
        int item_id;
                  
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
                            
        VEC_pString_type info_title_pList;  
        VEC_pString_type info_value_pList; 
 
        int mass;

        int size;

        Container();
        Container(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _pos_x, float _pos_y, float _target_x, float _target_y);
        ~Container();
        
        void packRocketItem(RocketItem* pTo_item);
        void packLazerItem(LazerItem* pTo_item);
        void packRadarItem(RadarItem* pTo_item);
        void packDriveItem(DriveItem* pTo_item);
        void packBakItem(BakItem* pTo_item);
        void packEnergizerItem(EnergizerItem* pTo_item);
        void packProtectorItem(ProtectorItem* pTo_item);
        void packDroidItem(DroidItem* pTo_item);
        void packFreezerItem(FreezerItem* pTo_item);
        void packScanerItem(ScanerItem* pTo_item);
        void packGrappleItem(GrappleItem* pTo_item);
        
        void renderInfo();
};

#endif 

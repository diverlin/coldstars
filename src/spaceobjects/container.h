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
        int id;
        int type_id;
        int item_subtype_id; 
        int item_id;
                  
        RocketEquipment*      pTo_rocketEquipment;
        LazerEquipment*       pTo_lazerEquipment;
        RadarEquipment*       pTo_radarEquipment;
        DriveEquipment*       pTo_driveEquipment;
        BakEquipment*         pTo_bakEquipment;
        EnergizerEquipment*   pTo_energizerEquipment;
        ProtectorEquipment*   pTo_protectorEquipment;
        DroidEquipment*       pTo_droidEquipment;
        FreezerEquipment*     pTo_freezerEquipment;
        ScanerEquipment*      pTo_scanerEquipment;
        GrappleEquipment*     pTo_grappleEquipment;
                            
        VEC_pString_type info_title_pList;  
        VEC_pString_type info_value_pList; 
 
        int mass;

        int size;

        Container();
        Container(TextureOb* _pTo_texOb, float _pos_x, float _pos_y, float _target_x, float _target_y);
        ~Container();
        
        void packRocketEquipment(RocketEquipment* pTo_item);
        void packLazerEquipment(LazerEquipment* pTo_item);
        void packRadarEquipment(RadarEquipment* pTo_item);
        void packDriveEquipment(DriveEquipment* pTo_item);
        void packBakEquipment(BakEquipment* pTo_item);
        void packEnergizerEquipment(EnergizerEquipment* pTo_item);
        void packProtectorEquipment(ProtectorEquipment* pTo_item);
        void packDroidEquipment(DroidEquipment* pTo_item);
        void packFreezerEquipment(FreezerEquipment* pTo_item);
        void packScanerEquipment(ScanerEquipment* pTo_item);
        void packGrappleEquipment(GrappleEquipment* pTo_item);
        
        void renderInfo();
};

#endif 

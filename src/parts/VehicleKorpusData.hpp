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

#ifndef VEHICLEKORPUSDATA_H
#define VEHICLEKORPUSDATA_H

struct VehicleKorpusData
{
	/* this data depends only on korpus and cannot be changed by artefacts/items */        
	unsigned int space;
	unsigned int armor;
	unsigned int protection; 
	unsigned int temperature;   

	unsigned int price;

	bool draw_turrels;

        int slot_grapple_num;
        int slot_drive_num;
        int slot_protector_num;
        int slot_radar_num;
        int slot_scaner_num;
        int slot_freezer_num;
	int slot_weapon_num;

	VehicleKorpusData():
	space(0),
        armor(0),
        protection(0), 
        temperature(0),   
        
        price(0),
       
        draw_turrels(false),
        
        slot_grapple_num(0),
        slot_drive_num(0),
        slot_protector_num(0),
        slot_radar_num(0),
        slot_scaner_num(0),
        slot_freezer_num(0),
	slot_weapon_num(0)	
	{}
};

#endif 

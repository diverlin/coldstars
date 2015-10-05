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

#pragma once

struct StarSystemDescriptor
{
    public:
        int race_id = 0;
        
        int planet_num = 0;
        int spacestation_num = 0;
        int asteroid_num = 0;
        int asteroid_delay = 0;
        
        bool allow_satellites = true;
        bool allow_spacestations = true;
        bool allow_ships = true;
        bool allow_ship_ranger = true;
        bool allow_ship_warrior = true;
        bool allow_ship_trader = true;
        bool allow_ship_pirat = true;
        bool allow_ship_diplomat = true;
                                                        
        StarSystemDescriptor() {}
        ~StarSystemDescriptor() {}
}; 


    

        



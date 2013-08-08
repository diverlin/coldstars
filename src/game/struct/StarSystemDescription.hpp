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

#ifndef STARSYSTEMDESCRIPTION_H
#define STARSYSTEMDESCRIPTION_H

struct StarSystemDescription
{
    public:
        int race_id;
        
        int planet_num;
        int spacestation_num;
        int asteroid_num;
        int asteroid_delay;
        
        bool allow_satellites;        
        bool allow_spacestations;
        bool allow_ships;    
        bool allow_ship_ranger;
        bool allow_ship_warrior;
        bool allow_ship_trader;
        bool allow_ship_pirat;
        bool allow_ship_diplomat;
                                                        
        StarSystemDescription():
        race_id(0),
        planet_num(0),
        spacestation_num(0),
        asteroid_num(0),
        asteroid_delay(0),
        allow_satellites(true),
        allow_spacestations(true),
        allow_ships(true),
        allow_ship_ranger(true),
        allow_ship_warrior(true),
        allow_ship_trader(true),
        allow_ship_pirat(true),
        allow_ship_diplomat(true)
        {};
        
        ~StarSystemDescription() {};
}; 

#endif 
    

        



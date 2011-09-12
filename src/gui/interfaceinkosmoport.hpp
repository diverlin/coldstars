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



#ifndef INTERFACEINKOSMOPORT_H
#define INTERFACEINKOSMOPORT_H


class InterfaceInKosmoport
{
    public:
           
        Button* pTo_angar_screen_button;
        Button* pTo_store_screen_button;
        Button* pTo_shop_screen_button;
        Button* pTo_galaxymap_screen_button;
        Button* pTo_goverment_screen_button;

        Button* pTo_repair_button;
        Button* pTo_fuel_button;  
        Button* pTo_launch_button;

        bool angar_screen_SELECTED;
        bool store_screen_SELECTED;
        bool shop_screen_SELECTED;
        bool galaxymap_screen_SELECTED;
        bool goverment_screen_SELECTED;
          
          
       InterfaceInKosmoport();
       ~InterfaceInKosmoport();

       void mouseInteraction();
       void render();
       void renderInfo();
};


#endif 

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


#ifndef KOSMOPORT_H
#define KOSMOPORT_H


class Kosmoport
{
    public:
        Angar*     pTo_angar;
        Store*     pTo_store;
        Shop*      pTo_shop;
        Goverment* pTo_goverment;  

        VEC_pNpc_type NPC_pList;
        VEC_pShip_type SHIP_pList;

        Kosmoport(int _race_id);
        ~Kosmoport();

        void clearScreen();

    bool addShip(Ship* _pTo_ship);
    bool addNpc(Npc* _pTo_npc);
    bool removeShipById(int _id);
    bool removeNpcById(int _id);

};

#endif

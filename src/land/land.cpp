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


#include "land.h"

Land :: Land()
{}

Land :: ~Land()
{}



//// ******* TRANSITION ******* 
bool Land :: addShip(Ship* _pTo_ship)
{
     SHIP_pList.push_back(_pTo_ship);
     _pTo_ship->in_SPACE = false;
     return true;
}

bool Land :: addNpc(Npc* _npc)
{
     NPC_pList.push_back(_npc);
     _npc->setLand(this);
     _npc->setInSpace(false);
 
     return true;
}

bool Land :: removeShipById(int _id)
{
    bool is_removed = false;
    for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++) 
        if (SHIP_pList[ki]->id == _id)
        {
           SHIP_pList.erase(SHIP_pList.begin() + ki);
           is_removed = true;
        }
    return is_removed;
}

bool Land :: removeNpcById(int _id)
{
    bool is_removed = false;
    for (unsigned int ni = 0; ni < NPC_pList.size(); ni++) 
        if (NPC_pList[ni]->getId() == _id)
        {
           NPC_pList.erase(NPC_pList.begin() + ni);
           is_removed = true;
        }
    return is_removed;
}
//// ******* TRANSITION ******* 

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


#include "kosmoport.h"

Kosmoport :: Kosmoport(int _race_id)
{
    TextureOb* pTo_slot_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);

    TextureOb* pTo_angar_bg_texOb     = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.angarBg_texOb_pList);   
    TextureOb* pTo_store_bg_texOb     = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.storeBg_texOb_pList);    
    TextureOb* pTo_shop_bg_texOb      = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shopBg_texOb_pList);    
    TextureOb* pTo_goverment_bg_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.govermentBg_texOb_pList);    

    pTo_angar     = new Angar(pTo_angar_bg_texOb, pTo_slot_texOb);
    pTo_store     = new Store(pTo_store_bg_texOb, pTo_slot_texOb);
    pTo_shop      = new Shop(pTo_shop_bg_texOb);
    pTo_goverment = new Goverment(pTo_store_bg_texOb, pTo_slot_texOb);
}


Kosmoport :: ~Kosmoport()
{}

void Kosmoport :: clearScreen()
{
     // Clear color and depth buffer
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
}


//// ******* TRANSITION ******* 
bool Kosmoport :: addShip(Ship* _pTo_ship)
{
     SHIP_pList.push_back(_pTo_ship);
     pTo_angar->placeShipTolandingArea(_pTo_ship);
     _pTo_ship->in_SPACE = false;
     return true;
}

bool Kosmoport :: addNpc(Npc* _pTo_npc)
{
     NPC_pList.push_back(_pTo_npc);
     _pTo_npc->setKosmoport(this);
     _pTo_npc->setInSpace(false);
 
     return true;
}

bool Kosmoport :: removeShipById(int _id)
{
    bool is_removed_from_list = false;
    for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++) 
        if (SHIP_pList[ki]->id == _id)
        {
           SHIP_pList.erase(SHIP_pList.begin() + ki);
           is_removed_from_list = true;
        }

    bool is_removed_from_landing_area = pTo_angar->removeShipFromlandingAreaById(_id); 
    
    if (is_removed_from_list && is_removed_from_landing_area)
       return true;
    else
       return false;
}

bool Kosmoport :: removeNpcById(int _id)
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



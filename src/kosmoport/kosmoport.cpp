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


#include "kosmoport.hpp"

Kosmoport :: Kosmoport(int _race_id)
{
	id = 0;
	type_id = KOSMOPORT_ID;

        TextureOb* _texOb_slot = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.slot_texOb_pList);

        TextureOb* _texOb_angarBackground  = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.angarBg_texOb_pList);   
        TextureOb* _texOb_storeBackground  = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.storeBg_texOb_pList);    
        TextureOb* _texOb_shopBackground   = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.shopBg_texOb_pList);    
        TextureOb* _texOb_govermentBackground = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.govermentBg_texOb_pList);    

        angar     = new Angar(_texOb_angarBackground, _texOb_slot);
        store     = new Store(_texOb_storeBackground, _texOb_slot);
        shop      = new Shop(_texOb_shopBackground);
        goverment = new Goverment(_texOb_govermentBackground, _texOb_slot);
}


Kosmoport :: ~Kosmoport()
{}

Angar* Kosmoport :: getAngar()         { return angar; }
Store* Kosmoport :: getStore()         { return store; }
Shop*  Kosmoport :: getShop()          { return shop; }
Goverment* Kosmoport :: getGoverment() { return goverment; }
                
                

bool Kosmoport :: addShip(Ship* _ship)
{
        _ship->setPlaceTypeId(type_id);
                
        SHIP_pList.push_back(_ship);
        angar->addShip(_ship);
        
        return true;
}

bool Kosmoport :: addNpc(Npc* _npc)
{
        NPC_pList.push_back(_npc);
        _npc->setKosmoport(this);
        _npc->setPlaceTypeId(type_id);
 
        return true;
}

bool Kosmoport :: removeShip(int _id)
{
        bool is_removed_from_list = false;
        for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
        { 
                if (SHIP_pList[ki]->getId() == _id)
                {
                        SHIP_pList.erase(SHIP_pList.begin() + ki);
                        is_removed_from_list = true;
                }
        }
        
        bool is_removed_from_landing_area = angar->removeShipFromlandingAreaById(_id); 
    
        if (is_removed_from_list && is_removed_from_landing_area)
                return true;
        else
                return false;
}

bool Kosmoport :: removeNpc(int _id)
{
        bool is_removed = false;
        for (unsigned int ni = 0; ni < NPC_pList.size(); ni++)
        { 
                if (NPC_pList[ni]->getId() == _id)
                {
                        NPC_pList.erase(NPC_pList.begin() + ni);
                        is_removed = true;
                }
        }
    
        return is_removed;
}


void Kosmoport :: ai()
{
        for (unsigned int ni = 0; ni < NPC_pList.size(); ni++)
                NPC_pList[ni]->thinkCommon_inKosmoport_inStatic();

}


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


Kosmoport :: Kosmoport(int _race_id) 
{
	type_id = ENTITY::KOSMOPORT_ID;

        TextureOb* _texOb_slot = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::SLOT_ID);
        TextureOb* _texOb_landingArea = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::LANDINGAREA_ID);
        
        TextureOb* _texOb_angarBackground  = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::ANGAR_BACKGROUND_ID);   
        TextureOb* _texOb_storeBackground  = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::STORE_BACKGROUND_ID);    
        TextureOb* _texOb_shopBackground   = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::SHOP_BACKGROUND_ID);    
        TextureOb* _texOb_govermentBackground = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::GOVERMENT_BACKGROUND_ID);    

        angar     = new Angar(_texOb_angarBackground, _texOb_landingArea);
        store     = new Store(_texOb_storeBackground, _texOb_slot);
        shop      = new Shop(_texOb_shopBackground);
        goverment = new Goverment(_texOb_govermentBackground, _texOb_slot);
        
        equipStore(store);
}

/* virtual */
Kosmoport :: ~Kosmoport()
{}

Angar* Kosmoport :: getAngar()         { return angar; }
Store* Kosmoport :: getStore()         { return store; }
Shop*  Kosmoport :: getShop()          { return shop; }
Goverment* Kosmoport :: getGoverment() { return goverment; }
      
           
/* virtual */
bool Kosmoport :: getPermissionToLand() const
{
      	if (angar->getFreePlatformTotalNum() > 0) 
        { 
        	return true; 
        }
        
        return false;
}

     
                
/* virtual */
bool Kosmoport :: add(Vehicle* vehicle)
{
        vehicle->SetPlaceTypeId(type_id);
                
        VEHICLE_vec.push_back(vehicle);
        angar->add(vehicle);
        
        return true;
}

/* virtual */
bool Kosmoport :: add(Npc* npc)
{
        npc->SetPlaceTypeId(type_id);
        NPC_vec.push_back(npc);
        
        npc->setLand(this);
 
        return true;
}

/* virtual */
bool Kosmoport :: remove(Vehicle* vehicle)
{
        bool is_removed_from_list = false;
        for (unsigned int i = 0; i < VEHICLE_vec.size(); i++)
        { 
                if (VEHICLE_vec[i] == vehicle)
                {
                        VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
                        is_removed_from_list = true;
                }
        }
        
        bool is_removed_from_landing_area = angar->remove(vehicle); 
    
        if (is_removed_from_list && is_removed_from_landing_area)
                return true;
        else
                return false;
}

/* virtual */
bool Kosmoport :: remove(Npc* npc)
{
        bool is_removed = false;
        for (unsigned int i = 0; i < NPC_vec.size(); i++)
        { 
                if (NPC_vec[i] == npc)
                {
                        NPC_vec.erase(NPC_vec.begin() + i);
                        is_removed = true;
                }
        }
    
        return is_removed;
}

/* virtual */
void Kosmoport :: ai()
{
        for (unsigned int i = 0; i < NPC_vec.size(); i++)
        {
                NPC_vec[i]->thinkCommon_inKosmoport_inStatic();
	}
}


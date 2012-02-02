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



Player :: Player()
{ 
    	id = g_PLAYER_ID_GENERATOR.getNextId(); 
    	type_id = PLAYER_ID;

	is_alive = true;
    	
    	ship = NULL;
    	npc  = NULL;
    	cursor = new Cursor();
    	
    	show_all_orbit     = false;
     	show_all_path      = false;
     	show_radar_range   = false;
     	show_grapple_range = false;
}
    
Player :: ~Player()
{
	delete cursor;
}  
    
    
void Player :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }	
void Player :: setScanFlag(bool _scan) { control.scan =_scan; }
void Player :: setWorldMapShowFlag(bool _show_worldmap) { control.worldmap = _show_worldmap; }
          	
void Player :: setShowAllOrbit(bool show_all_orbit)     { this->show_all_orbit = show_all_orbit; }
void Player :: setShowAllPath(bool show_all_path)       { this->show_all_path = show_all_path; }
void Player :: setShowRadarRange(bool show_radar_range) { this->show_radar_range = show_radar_range; }
void Player :: setShowGrappleRange(bool show_grapple_range)  { this->show_grapple_range = show_grapple_range; }
          	
bool Player :: getAlive() const { return is_alive; }
bool Player :: getWorldMapShowFlag() const { return control.worldmap; }         	
bool Player :: getScanFlag() const              { return control.scan; }
Ship* Player :: getShip() 	      { return ship; }
Npc* Player :: getPilot() 	      { return npc; }
StarSystem* Player :: getStarSystem() { return starsystem; }	
Cursor* Player :: getCursor()         { return cursor; }
int Player ::  getPlaceTypeId() const { return place_type_id; }
         
 bool Player :: getShowAllOrbit() const     { return show_all_orbit; }
 bool Player :: getShowAllPath() const      { return show_all_path; }
 bool Player :: getShowRadarRange() const   { return show_radar_range; }
 bool Player :: getShowGrappleRange() const { return show_grapple_range; }          	 
          
void Player :: update_global()
{
	if (is_alive == true)
	{
		if (npc->getAlive() == false)
		{
			is_alive = false;
			place_type_id = SPACE_ID;
		}
	}
	
	if (is_alive == true)
	{
		if (control.scan == false)
		{
            		npc->removeScanTarget();
        	}
  		
		place_type_id = getPilot()->getPlaceTypeId();
		
		if (ship->getPlaceTypeId() == PLANET_ID)       // FUUUUUUUUUUUUUUUUUUUUUU must be imprroved
		{
        		npc->setPlaceTypeId(PLANET_ID);
        	}
        	
        	npc->getShip()->getWeaponComplex()->weapon_selector = weapon_selector;
	}
}  
               			
void Player :: bindNpc(Npc* _npc)
{
    	npc = _npc;

    	ship = npc->getShip();
    	ship->getNpc()->setUpperControl(true);
    	cursor->getSlot()->setShipOwner(ship);
}

    




        

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


TargetObject :: TargetObject()
{
        reset();
}


TargetObject :: ~TargetObject()
{}
                
                
bool TargetObject :: getValid() const     { return is_valid; }
int TargetObject :: getObId() const       { return ob_id; }
int TargetObject :: getObTypeId() const   { return ob_type_id; }
int TargetObject :: getObPlaceTypeId() const { return *pTo_place_type_id; }
int* TargetObject :: getpObPlaceTypeId() const { return pTo_place_type_id; }
                
Star* TargetObject :: getStar()   	      { return star; }
Planet* TargetObject :: getPlanet()   	      { return planet; }
Asteroid* TargetObject :: getAsteroid()       { return asteroid; }
Mineral* TargetObject :: getMineral()         { return mineral; }
Container* TargetObject :: getContainer()     { return container; }
Vehicle* TargetObject :: getVehicle()         { return vehicle; }
Npc* TargetObject :: getNpc() const           { return npc; }
StarSystem* TargetObject :: getStarSystem()   { return starsystem; }
Bomb* TargetObject :: getBomb() const         { return bomb; }
                
vec2f* TargetObject :: getpCenter() { return pCenter; }
bool* TargetObject :: getpAlive()   { return pTo_is_alive; } 
bool TargetObject :: getAlive() const  { return *pTo_is_alive; } 


float TargetObject :: getCollisionRadius() const { return collision_radius; }


template <typename TARGET>
void TargetObject :: setObject(TARGET _target)
{
	set(_target);
        
        ob_id      = _target->getId();
	ob_type_id = _target->getTypeId();
        
       	pCenter      = _target->getPoints()->getpCenter();
       	pTo_is_alive = _target->getpAlive();
       	pTo_place_type_id = _target->getpPlaceTypeId();
        starsystem = _target->getStarSystem();
        
        collision_radius = _target->getCollisionRadius();
        
	is_valid = true;
}

void TargetObject :: set(Star* _star) 		   { star = _star; }
void TargetObject :: set(Planet* _planet)     	   { planet = _planet; }
void TargetObject :: set(Asteroid* _asteroid)      { asteroid = _asteroid; }
void TargetObject :: set(Mineral* _mineral)        { mineral = _mineral; }
void TargetObject :: set(Container* _container)    { container = _container; }
void TargetObject :: set(Vehicle* vehicle)         { this->vehicle = vehicle; }
void TargetObject :: set(Npc* _npc)                { npc = _npc; }
void TargetObject :: set(StarSystem* _starsystem)  { starsystem = _starsystem; }
void TargetObject :: set(Bomb* bomb)               { this->bomb = bomb; }

void TargetObject :: reset()
{
	star	   = NULL;
	planet 	   = NULL;
        asteroid   = NULL;
        mineral    = NULL;
        container  = NULL;
	vehicle    = NULL;
	npc        = NULL;
	bomb       = NULL;
        
        pCenter      = NULL;
        pTo_is_alive = NULL;
        pTo_place_type_id = NULL;
        starsystem   = NULL;
        
        collision_radius = 0;
        
        ob_id      = NONE_ID; 
	ob_type_id = NONE_ID;
        
        is_valid = false; 
}

void TargetObject :: copy(TargetObject* tgOb)
{
	star	   = tgOb->getStar();
	planet 	   = tgOb->getPlanet();
        asteroid   = tgOb->getAsteroid();
        mineral    = tgOb->getMineral();
        container  = tgOb->getContainer();
	vehicle    = tgOb->getVehicle();
	npc        = tgOb->getNpc();
	bomb       = tgOb->getBomb();
        
        pCenter      = tgOb->getpCenter();
        pTo_is_alive = tgOb->getpAlive();
        pTo_place_type_id = tgOb->getpObPlaceTypeId();
        starsystem   = tgOb->getStarSystem();
        
        collision_radius = tgOb->getCollisionRadius();
        
        ob_id      = tgOb->getObId(); 
	ob_type_id = tgOb->getObTypeId();
        
        is_valid = tgOb->getValid(); 

}
      
void TargetObject :: moveExternalyToPosition(vec2f _target_pos)
{
	switch(ob_type_id)
	{
		case MINERAL_ID:
		{
			mineral->moveExternalyToPosition(_target_pos);
			break;
		}
	
		case CONTAINER_ID:
		{
			container->moveExternalyToPosition(_target_pos);
			break;
		}	
	
		case BOMB_ID:
		{
			bomb->moveExternalyToPosition(_target_pos);
			break;
		}

		case SHIP_ID:
		{
			vehicle->moveExternalyToPosition(_target_pos);
			break;
		}
	}
}


bool TargetObject :: checkAvaliability(StarSystem* _starsystem)
{
        if (*pTo_is_alive == true) 
        {
                if (*pTo_place_type_id == SPACE_ID)
                { 
                        if (starsystem == _starsystem) 
                        {       
                                return true;
                        }
                        else return false;
                }
                else return false;
        }
        else return false;
}


bool TargetObject :: validation(StarSystem* _starsystem)
{        
        if (is_valid == true)
        { 
                if ( checkAvaliability(_starsystem) == true)
                {
                	return true;
                }
                else
                {              
                	reset();
                }
        }
        
        return false;
}

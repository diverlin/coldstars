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


TargetObject :: TargetObject(ItemSlot* _slot)
{
        slot = _slot;
        
        reset();
}


TargetObject :: ~TargetObject()
{}


StarSystem* TargetObject :: getStarSystem() { return starsystem; }
bool TargetObject :: getValid() const     { return is_valid; }
int TargetObject :: getObId() const       { return ob_id; }
int TargetObject :: getObTypeId() const   { return ob_type_id; }

Asteroid* TargetObject :: getAsteroid()   { return asteroid; }
Mineral* TargetObject :: getMineral()     { return mineral; }
Container* TargetObject :: getContainer() { return container; }
Ship* TargetObject :: getShip()           { return ship; }

vec2f* TargetObject :: getpCenter() { return pCenter; }
bool* TargetObject :: getpAlive()   { return pTo_is_alive; } 

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

	is_valid = true;
}
void TargetObject :: set(Asteroid* _asteroid)     { asteroid = _asteroid; }
void TargetObject :: set(Mineral* _mineral)       { mineral = _mineral; }
void TargetObject :: set(Container* _container)   { container = _container; }
void TargetObject :: set(Ship* _ship)             { ship = _ship; }


void TargetObject :: reset()
{
        asteroid  = NULL;
        mineral   = NULL;
        container = NULL;
	ship      = NULL;
        
        pCenter      = NULL;
        pTo_is_alive = NULL;
        pTo_place_type_id = NULL;
        starsystem   = NULL;
        
        ob_id      = NONE_ID; 
	ob_type_id = NONE_ID;
        
        is_valid = false; 

}

      

void TargetObject :: validation(vec2f _point0)
{
        if (is_valid == true)
        {
                if ( (*pTo_is_alive == false) or (*pTo_place_type_id != SPACE_ID) or (starsystem != slot->getShip()->getStarSystem()) )
                {
                        reset();                        
                        return;
                }
                else
                {
                        if (checkDistance(_point0) == false)
                        {
                                reset();
                                return;
                        }
                        else
                        {
                                return;
                        }
                } 
        }
}


bool TargetObject :: checkDistance(vec2f _point0)
{
        float dist = distBetweenCenters(_point0, *pCenter);                                               
    	if (dist < slot->getItemRadius())
        {
                return true;
        }
        else
        {
                return false;
        }
}

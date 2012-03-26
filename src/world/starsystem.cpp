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



StarSystem :: StarSystem(int race_id)
{ 
    	data_id.id = g_ID_GENERATOR.getNextId();
    	data_id.type_id = ENTITY::STARSYSTEM;
    	
    	is_CAPTURED = false;
    	
    	this->race_id = race_id;
    	conqueror_race_id = NONE_ID;

    	calculation_per_turn_allowed = true;
    	calculation_per_turn_allowed_inDynamic = true;

    	detalied_simulation = false; // will be changing depending on player presence

    	galaxy = NULL;    	
    	this->setStarSystem(this);
}

StarSystem :: ~StarSystem()
{}
      

void StarSystem :: setPosition(vec2f center) { this->center = center; }
void StarSystem :: setGalaxy(Galaxy* galaxy)  { this->galaxy = galaxy;}
						
bool StarSystem :: getDetailedSimulationFlag() const { return detalied_simulation; }
bool StarSystem :: getCaptured() const { return is_CAPTURED; }    
vec2f StarSystem :: getPosition() const { return center; }  
Galaxy* StarSystem :: getGalaxy() const { return galaxy; }
      
int StarSystem :: getRaceId() const 	     { return race_id; }
int StarSystem :: getConquerorRaceId() const { return conqueror_race_id; }  
     

   		
Star* StarSystem :: getStar() const { return STAR_vec[0]; }
int StarSystem :: getShockWaveNum() const { return effect_SHOCKWAVE_vec.size(); }  
   		           
// poor                
Planet* StarSystem :: getClosestPlanet(vec2f _pos)
{
     	return PLANET_vec[getRandInt(0, PLANET_vec.size()-1)];
}
Npc* StarSystem :: getRandomNpc()
{
     	return NPC_inSPACE_vec[getRandInt(0, NPC_inSPACE_vec.size()-1)];
}
Npc* StarSystem :: getRandomNpcExcludingRaceId(int _race_id)
{
        std::vector<Npc*> _npc_vec;
        Npc* requested_npc;
        
        for (unsigned int i = 0; i < NPC_inSPACE_vec.size(); i++)
        {
                if (NPC_inSPACE_vec[i]->getRaceId() != _race_id)
                {
                        _npc_vec.push_back(NPC_inSPACE_vec[i]);
                }
        }
        
        if (_npc_vec.size() > 0)
        {
                requested_npc = _npc_vec[getRandInt(0, _npc_vec.size()-1)];
        }
        
        return requested_npc;
}

Npc* StarSystem :: getRandNpcByRaceId(int _race_id) const
{
	std::vector<Npc*> _npc_vec;
	Npc* requested_npc = NULL;
	
	for (unsigned int i = 0; i < NPC_inSPACE_vec.size(); i++)
        {
                if (NPC_inSPACE_vec[i]->getRaceId() == _race_id)
                {
                        _npc_vec.push_back(NPC_inSPACE_vec[i]);
                }
        }
        
        if (_npc_vec.size() > 0)
        {
                requested_npc = _npc_vec[getRandInt(0, _npc_vec.size()-1)];
        }	
	
	return requested_npc;
}
                

Npc* StarSystem:: getRandNpc(std::vector<int>* _pVec_race_id) const
{
	std::vector<Npc*> _npc_vec;
	Npc* requested_npc = NULL;
	
	for (unsigned int i = 0; i < NPC_inSPACE_vec.size(); i++)
        {
        	for (unsigned int j = 0; j < _pVec_race_id->size(); j++)
        	{
        		if ( NPC_inSPACE_vec[i]->getRaceId() == (*_pVec_race_id)[j])
        		{
        			_npc_vec.push_back(NPC_inSPACE_vec[i]);
        			break;
        		}
        	}
        }
        
        if (_npc_vec.size() > 0)
        {
                requested_npc = _npc_vec[getRandInt(0, _npc_vec.size()-1)];
        }	
	
	return requested_npc;
}

//Npc* StarSystem:: getRandNpcFromVec(_pVec_id)
//{
	//std::vector<Npc*> _npc_vec;
	//Npc* requested_npc = NULL;
	
	//for (unsigned int i = 0; i < NPC_inSPACE_vec.size(); i++)
        //{
                //if ( (NPC_inSPACE_vec[i]->getRaceId() == RACE_6_ID) or (NPC_inSPACE_vec[i]->getRaceId() == RACE_7_ID) )
                //{
                        //_npc_vec.push_back(NPC_inSPACE_vec[i]);
                //}
        //}
        
        //if (_npc_vec.size() > 0)
        //{
                //requested_npc = _npc_vec[getRandInt(0, _npc_vec.size()-1)];
        //}	
	
	//return requested_npc;
//}
//
void StarSystem :: update_s()
{
	asteroidManager_s(5);
	     	
	if (PLAYER_vec.size() > 0)
	{
		detalied_simulation = true;
	}
	else
	{
		detalied_simulation = false;
	}

	bool enemy_is_here;
	bool friendly_is_here; 
	
	Npc* _npc_evil = getRandNpc(&RACES_EVIL_LIST);
	if (_npc_evil != NULL)
	{
		enemy_is_here = true;
	}
	else
	{
		enemy_is_here = false;
	}
	
	Npc* _npc_good = getRandNpc(&RACES_GOOD_LIST);
	if (_npc_good != NULL)
	{
		friendly_is_here = true;
	}
	else
	{
		friendly_is_here = false;
	}

	
	
	if (is_CAPTURED == false)
	{
		if (enemy_is_here == true)
		{
			if (friendly_is_here == true)
			{
				// war is going
			}
			else
			{
				is_CAPTURED = true;
				if (getRandNpcByRaceId(RACE::R6) != NULL)
				{
					conqueror_race_id = RACE::R6;
				}
				
				if (getRandNpcByRaceId(RACE::R7) != NULL)
				{
					conqueror_race_id = RACE::R7;
				}
			}
		}
	}

	if (is_CAPTURED == true)
	{
		if (friendly_is_here == true)
		{
			if (enemy_is_here == true)
			{
				// war is going
			}
			else
			{
				is_CAPTURED = false;
				conqueror_race_id = NONE_ID;
			}
		}
	}
}


void StarSystem :: update_s(int time, bool detalied_simulation)
{
        manageUnavaliableObjects_s();
        manageDeadObjects_s();         // no need to update so frequently, pri /6
                        
	updateEntities_s(time, detalied_simulation);
	    		
	if (time > 0)
	{
		if (calculation_per_turn_allowed_inDynamic == true)
		{
                        postHyperJumpEvent_s();
                        launchingEvent_s();

			calculation_per_turn_allowed_inDynamic = false;
		}

    		rocketCollision_s(detalied_simulation);   // pri/2
    		asteroidCollision_s(detalied_simulation); // pri/2

		calculation_per_turn_allowed = true;
	}
	else
	{
		update_s();
	    		
		if (calculation_per_turn_allowed == true)
		{    		
    			updateEntities_inStatic_s();     			

    			calculation_per_turn_allowed = false;
    			calculation_per_turn_allowed_inDynamic = true;

			garbage_entities.clear();
			garbage_effects.clear(); 
    		}    		
	}
}




void StarSystem :: rocketCollision_s(bool show_effect)
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                if (ROCKET_vec[ri]->getAlive() == true) 
                {
                	// vehicle
                	if (collide == false)
                	{
                		for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
                		{
                        		if (ROCKET_vec[ri]->getOwnerShipId() != SHIP_inSPACE_vec[ki]->getId())
                        		{                        
                        			collide = checkCollision(ROCKET_vec[ri], SHIP_inSPACE_vec[ki], show_effect);
                        			if (collide == true) { break; }                        
                        		}
                		}
                	}
                	else  { continue; }
                
                
                        if (collide == false)
                	{
                		for (unsigned int si = 0; si < SATELLITE_vec.size(); si++)
                		{
                        		if (ROCKET_vec[ri]->getOwnerShipId() != SATELLITE_vec[si]->getId())
                        		{                        
                        			collide = checkCollision(ROCKET_vec[ri], SATELLITE_vec[si], show_effect);
                        			if (collide == true) { break; }                        
                        		}
                		}
                	}
                	else  { continue; }
                
                        if (collide == false)
                	{
                		for (unsigned int si = 0; si < SPACESTATION_vec.size(); si++)
                		{
                        		if (ROCKET_vec[ri]->getOwnerShipId() != SPACESTATION_vec[si]->getId())
                        		{                        
                        			collide = checkCollision(ROCKET_vec[ri], SPACESTATION_vec[si], show_effect);
                        			if (collide == true) { break; }                        
                        		}
                		}
                	}
                	else  { continue; }
                	//
                	
                	
                	if (collide == false)
                	{
                        	for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
                        	{
                        		collide = checkCollision(ROCKET_vec[ri], ASTEROID_vec[ai], show_effect);
                        		if (collide == true) { break; }
                        	}
                	}
                	else  { continue; }



                	if (collide == false)
                	{
                        	for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
                        	{
                        		collide = checkCollision(ROCKET_vec[ri], MINERAL_vec[mi], show_effect);
                        		if (collide == true) { 	break; }
                        	}
                	}
                	else  { continue; }
               	
                	
                	if (collide == false)
                	{
                        	for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
                        	{
                        		collide = checkCollision(ROCKET_vec[ri], CONTAINER_vec[ci], show_effect);
                        		if (collide == true) { 	break; }
                        	}
                	}
                	else  { continue; }
                }
        }
}






void StarSystem :: asteroidCollision_s(bool show_effect)
{
	bool collide = false;
	
        for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
        {
                if (ASTEROID_vec[ai]->getAlive() == true) 
                {
                	// vehicle
                	if (collide == false)
                	{
                        	for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], SHIP_inSPACE_vec[ki], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	
                	if (collide == false)
                	{
                        	for (unsigned int si = 0; si < SPACESTATION_vec.size(); si++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], SPACESTATION_vec[si], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	
                	if (collide == false)
                	{
                        	for (unsigned int si = 0; si < SATELLITE_vec.size(); si++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], SATELLITE_vec[si], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	//
                	
                	
                	if (collide == false)
                	{
                        	for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], PLANET_vec[pi], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	
                	
                	
                	if (collide == false)
                	{
                        	for (unsigned int si = 0; si < STAR_vec.size(); si++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], STAR_vec[si], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                }
	}
}




void StarSystem :: updateEntities_s(int time, bool show_effect)
{
        for (unsigned int si = 0; si < STAR_vec.size(); si++)
        {
                STAR_vec[si]->update_inSpace(time, show_effect); 
	}
	
        for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
        {
                PLANET_vec[pi]->update_inSpace(time, show_effect); 
    	}
    	
        for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
        {
                MINERAL_vec[mi]->update_inSpace(time, show_effect); 
     	}
     	
     	
     	for (unsigned int i = 0; i < BLACKHOLE_vec.size(); i++)
        {
                BLACKHOLE_vec[i]->update_inSpace(time, show_effect); 
     	}
     	     	     	
     	
     	
        for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
        {
                CONTAINER_vec[ci]->update_inSpace(time, show_effect); 
	}
	
        for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++) 
        {
                ASTEROID_vec[ai]->update_inSpace(time, show_effect); 
    	}
    	
        for (unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
        {
                NPC_inSPACE_vec[ni]->update_inSpace(time, show_effect); 
    	}
    	
    	// vehicle
        for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
        {
                SHIP_inSPACE_vec[ki]->update_inSpace(time, show_effect);         
    	}

        for (unsigned int si = 0; si < SPACESTATION_vec.size(); si++)
        {
                SPACESTATION_vec[si]->update_inSpace(time, show_effect); 
        }
                
        for (unsigned int si = 0; si < SATELLITE_vec.size(); si++)
        {
                SATELLITE_vec[si]->update_inSpace(time, show_effect);         
    	}        
    	//
    	
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                ROCKET_vec[ri]->update_inSpace(time, show_effect); 
        }
        
        
        // effects
        for(unsigned int i = 0; i<effect_LAZERTRACE_vec.size(); i++)
	{ 
		effect_LAZERTRACE_vec[i]->update(); 
	}

	for(unsigned int i = 0; i < effect_PARTICLESYSTEM_vec.size(); i++)
	{ 
		effect_PARTICLESYSTEM_vec[i]->update();
	}

	
	for (unsigned int i = 0; i < effect_SHOCKWAVE_vec.size(); i++)
	{         
		effect_SHOCKWAVE_vec[i]->update();

	}
	
	for(unsigned int i = 0; i<text_DAMAGE_vec.size(); i++)
    	{ 
    	        text_DAMAGE_vec[i]->update(); 
    	}   
        
}  
      
 


void StarSystem :: updateEntities_inStatic_s()
{
     	for (unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
     	{
		NPC_inSPACE_vec[ni]->update_inSpace_inStatic();
    	}

	// vehicle (robot mind)
     	for (unsigned int si = 0; si < SPACESTATION_vec.size(); si++)
     	{
		//SPACESTATION_vec[si]->update_inSpace_inStatic();
    	}
    	    	
    	for (unsigned int si = 0; si < SATELLITE_vec.size(); si++)
     	{
		//SATELLITE_vec[si]->update_inSpace_inStatic();
    	}
    	//
    	
     	for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
     	{
         	PLANET_vec[pi]->update_inSpace_inStatic();
     	}
}      

    		


void StarSystem :: findVisibleEntities_c(Player* player)
{
	player->clearVisibleEntities();
	
        for (unsigned int i = 0; i < STAR_vec.size(); i++)         { player->addIfVisible(STAR_vec[i]); }    
        for (unsigned int i = 0; i < PLANET_vec.size(); i++)       { player->addIfVisible(PLANET_vec[i]); }
        for (unsigned int i = 0; i < ASTEROID_vec.size(); i++)     { player->addIfVisible(ASTEROID_vec[i]); } 
        for (unsigned int i = 0; i < MINERAL_vec.size(); i++)      { player->addIfVisible(MINERAL_vec[i]); }
        for (unsigned int i = 0; i < CONTAINER_vec.size(); i++)    { player->addIfVisible(CONTAINER_vec[i]); }
    	for (unsigned int i = 0; i < SHIP_inSPACE_vec.size(); i++) { player->addIfVisible(SHIP_inSPACE_vec[i]); } 
    	for (unsigned int i = 0; i < SPACESTATION_vec.size(); i++) { player->addIfVisible(SPACESTATION_vec[i]); } 
    	for (unsigned int i = 0; i < SATELLITE_vec.size(); i++)    { player->addIfVisible(SATELLITE_vec[i]); } 
    	for (unsigned int i = 0; i < ROCKET_vec.size(); i++)       { player->addIfVisible(ROCKET_vec[i]); }
    	for (unsigned int i = 0; i < BLACKHOLE_vec.size(); i++)    { player->addIfVisible(BLACKHOLE_vec[i]); } 
           		
    	
    	//effects
	for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)      { player->addIfVisible(effect_SHOCKWAVE_vec[i]); }
	for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)     { player->addIfVisible(effect_LAZERTRACE_vec[i]); }
	for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { player->addIfVisible(effect_PARTICLESYSTEM_vec[i]); }
	for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)		{ player->addIfVisible(text_DAMAGE_vec[i]); }
}

      
void StarSystem :: restoreSceneColor()
{
        setColor(STAR_vec[0]->getColor());
}     

void StarSystem :: restoreDefaultColor()
{
	Color4f _color;
	setColor(_color);
}


void StarSystem :: renderBackground(vec2f scroll_coords)
{   
	// HACK for point sprites
    	enable_POINTSPRITE();
    		distantStarBgEffect_vec[0]->render(scroll_coords.x, scroll_coords.y); 
    	disable_POINTSPRITE();
    	// HACK for point sprites

	clearScreen();
	resetRenderTransformation();
        restoreSceneColor();

    	enable_BLEND();
		glDepthMask(false);

    		for(unsigned int i = 0; i<distantNebulaBgEffect_vec.size(); i++)
    		{ 
       			distantNebulaBgEffect_vec[i]->updateRenderStuff(); 
        		distantNebulaBgEffect_vec[i]->render(scroll_coords.x, scroll_coords.y); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<distantStarBgEffect_vec.size(); i++)
    			{ 
       				distantStarBgEffect_vec[i]->render(scroll_coords.x, scroll_coords.y); 
    			}
    		disable_POINTSPRITE();
    	
		glDepthMask(true);
	disable_BLEND();
}
    
void StarSystem :: drawOrbits()
{
        for(unsigned int i = 0; i < PLANET_vec.size(); i++) 
	{ 
		PLANET_vec[i]->getOrbit()->draw(); 
	}

	for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
	{ 
		ASTEROID_vec[i]->getOrbit()->draw(); 
	}
}
 
void StarSystem :: drawPath()
{
        for(unsigned int i = 0; i < SHIP_inSPACE_vec.size(); i++) 
	{ 
		SHIP_inSPACE_vec[i]->GetDriveComplex()->drawPath(); 
	}
}
   

 










  
    


void StarSystem :: asteroidManager_s(unsigned int num)
{
        while (ASTEROID_vec.size() < num)
        {
                Asteroid* _asteroid = getNewAsteroid();
                addToSpace(_asteroid);
                break;
        }
}



void StarSystem :: addToSpace(Vehicle* vehicle, vec2f center, float angle, BaseGameEntity* parent)
{
     	vehicle->setPlaceTypeId(SPACE_ID);
     	vehicle->setStarSystem(this);  

	switch(vehicle->getTypeId())
	{
		case ENTITY::SHIP:         	
		{ 	
			SHIP_inSPACE_vec.push_back((Ship*)vehicle);  
			 
		     	vehicle->GetPoints().setCenter(center); 
    			vehicle->GetPoints().setAngle(angle);   
    			vehicle->GetPoints().update();  
    	
			break; 
		}
					
		case ENTITY::SPACESTATION:
		{
		 	SPACESTATION_vec.push_back((SpaceStation*)vehicle);   
			 	
			vehicle->GetPoints().setCenter(center); 
    			vehicle->GetPoints().setAngle(angle);   
    			vehicle->GetPoints().update();  
    			
		 	break; 
		}
		
		case ENTITY::SATELLITE:    	
		{ 
			vehicle->setParent(parent);
			((Satellite*)vehicle)->getOrbit()->calcPath(parent->getCollisionRadius(), 1.0);
			SATELLITE_vec.push_back((Satellite*)vehicle); 
		
			break; 
		}
	}
     	
     	
}

void StarSystem :: addToSpace(Npc* npc)
{
     	npc->setPlaceTypeId(SPACE_ID);
     	npc->setStarSystem(this);  

     	NPC_inSPACE_vec.push_back(npc);

	switch(npc->getSubTypeId())
	{
     	 	case RANGER_ID:     { NPC_RANGER_inSPACE_vec.push_back(npc);    break; }
     		case WARRIOR_ID:    { NPC_WARRIOR_inSPACE_vec.push_back(npc);   break; }
     		case TRADER_ID:     { NPC_TRADER_inSPACE_vec.push_back(npc);    break; }
     		case PIRAT_ID:      { NPC_PIRAT_inSPACE_vec.push_back(npc);    break; }
     		case DIPLOMAT_ID:   { NPC_DIPLOMAT_inSPACE_vec.push_back(npc); break; }
     	}
}


void StarSystem :: addToSpace(Star* star)
{
        star->setStarSystem(this);
        star->setPlaceTypeId(SPACE_ID);
        STAR_vec.push_back(star);
}

void StarSystem :: addToSpace(Planet* planet, BaseGameEntity* parent)
{
	planet->createOrbit();
        planet->setParent(parent);
        
        planet->setStarSystem(this);
        planet->setPlaceTypeId(SPACE_ID);
        PLANET_vec.push_back(planet);
}
                
void StarSystem :: addToSpace(Asteroid* asteroid)
{   
	asteroid->createOrbit();
	asteroid->update_inSpace(1, true);
	
        asteroid->setStarSystem(this);
        asteroid->setPlaceTypeId(SPACE_ID);
        ASTEROID_vec.push_back(asteroid);
}

void StarSystem :: addToSpace(Mineral* _mineral, vec2f pos)
{
	_mineral->moveToSpace(this, pos);
        MINERAL_vec.push_back(_mineral);
}

//void StarSystem :: addToSpace(Bomb* bomb, vec2f pos)
//{
	//bomb->moveToSpace(this, pos);
        //BOMB_vec.push_back(bomb);
//}

void StarSystem :: addToSpace(Container* _container, vec2f pos)
{
	_container->moveToSpace(this, pos);
        CONTAINER_vec.push_back(_container);
}


void StarSystem :: addToSpace(RocketBullet* _rocket)
{
	_rocket->setStarSystem(this);
	ROCKET_vec.push_back(_rocket);
}    

void StarSystem :: addToSpace(BlackHole* blackhole, vec2f pos)
{
	blackhole->moveToSpace(this, pos);
	//blackhole->setEffect(getNewBlackHoleEffect(this, pos, 8));
	getNewBlackHoleEffect(this, pos, 8);
	BLACKHOLE_vec.push_back(blackhole);
}    
    		
	


void StarSystem :: addToSpace(ShockWaveEffect* _shockWave)
{
	effect_SHOCKWAVE_vec.push_back(_shockWave);
}

void StarSystem :: addToSpace(LazerTraceEffect* _lazerTraceEffect)
{
	effect_LAZERTRACE_vec.push_back(_lazerTraceEffect);
}

void StarSystem :: addToSpace(BaseParticleSystem* _ps)
{
	effect_PARTICLESYSTEM_vec.push_back(_ps);
}

void StarSystem :: addToSpace(VerticalFlowText* _text)
{
	text_DAMAGE_vec.push_back(_text);
}
    	
    		
void StarSystem :: addToSpace(DistantNebulaBgEffect* dn)
{
	distantNebulaBgEffect_vec.push_back(dn);
}

void StarSystem :: addToSpace(DistantStarBgEffect* ds)
{
	distantStarBgEffect_vec.push_back(ds);
}
    		
    		
    		
void StarSystem :: addToRemoveFromOuterSpaceQueue(Mineral* mineral) 
{
	remove_MINERAL_queue.push_back(mineral);
}

void StarSystem :: addToRemoveFromOuterSpaceQueue(Container* container) 
{
	remove_CONTAINER_queue.push_back(container);
}


void StarSystem :: addToRemoveFromOuterSpaceQueue(Vehicle* vehicle)
{
	switch(vehicle->getTypeId())
	{
		case ENTITY::SHIP: { remove_SHIP_queue.push_back((Ship*)vehicle); break; }
	}
	
}   		

void StarSystem :: manageUnavaliableObjects_s()
{
	for(unsigned int i = 0; i < remove_MINERAL_queue.size(); i++)
    	{
    		for (unsigned int j = 0; j < MINERAL_vec.size(); j++)
    		{
    			if (MINERAL_vec[j]->getId() == remove_MINERAL_queue[i]->getId())
    			{
    				MINERAL_vec.erase(MINERAL_vec.begin() + j );
    				continue;
    			}
    		}
    	}
    	remove_MINERAL_queue.clear();  
    	
    	for(unsigned int i = 0; i < remove_CONTAINER_queue.size(); i++)
    	{
    		for (unsigned int j = 0; j < CONTAINER_vec.size(); j++)
    		{
    			if (CONTAINER_vec[j]->getId() == remove_CONTAINER_queue[i]->getId())
    			{
    				CONTAINER_vec.erase(CONTAINER_vec.begin() + j );
    				continue;
    			}
    		}
    	}
    	remove_CONTAINER_queue.clear();    	
}
    		
void StarSystem :: manageDeadObjects_s()
{  
	{
	
   	for(unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
    	{
               	if (SHIP_inSPACE_vec[ki]->getGarbageReady() == true)
        	{           
            		SHIP_inSPACE_vec[ki]->GetOwnerNpc()->setAlive(false);
               		SHIP_inSPACE_vec[ki]->GetOwnerNpc()->setGarbageReady(true);
               
            		garbage_entities.add(SHIP_inSPACE_vec[ki]);
            		SHIP_inSPACE_vec.erase(SHIP_inSPACE_vec.begin() + ki);
        	} 
    	}
    	for(unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		garbage_entities.add(NPC_inSPACE_vec[ni]);
            		NPC_inSPACE_vec.erase(NPC_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	//
    	for(unsigned int i = 0; i < SPACESTATION_vec.size(); i++)
    	{
	        if (SPACESTATION_vec[i]->getGarbageReady() == true)
        	{   
            		SPACESTATION_vec.erase(SPACESTATION_vec.begin() + i);            		
        	} 
    	}

    	for(unsigned int i = 0; i < SATELLITE_vec.size(); i++)
    	{
	        if (SATELLITE_vec[i]->getGarbageReady() == true)
        	{   
            		SATELLITE_vec.erase(SATELLITE_vec.begin() + i);            		
        	} 
    	}
    	    	
    	for(unsigned int ni = 0; ni < NPC_RANGER_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_RANGER_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		NPC_RANGER_inSPACE_vec.erase(NPC_RANGER_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_WARRIOR_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_WARRIOR_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		NPC_WARRIOR_inSPACE_vec.erase(NPC_WARRIOR_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	    	
    	for(unsigned int ni = 0; ni < NPC_TRADER_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_TRADER_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		NPC_TRADER_inSPACE_vec.erase(NPC_TRADER_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_PIRAT_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_PIRAT_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		NPC_PIRAT_inSPACE_vec.erase(NPC_PIRAT_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_DIPLOMAT_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_DIPLOMAT_inSPACE_vec[ni]->getGarbageReady() == true)
        	{   
            		NPC_DIPLOMAT_inSPACE_vec.erase(NPC_DIPLOMAT_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	//
    	
    	}

    	


    	for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
    	{
        	if (ASTEROID_vec[i]->getGarbageReady() == true)
        	{
            		garbage_entities.add(ASTEROID_vec[i]);
            		ASTEROID_vec.erase(ASTEROID_vec.begin() + i );
            	}
        } 
    

    	for(unsigned int i = 0; i < MINERAL_vec.size(); i++)
    	{
        	if ( (MINERAL_vec[i]->getGarbageReady() == true) or (MINERAL_vec[i]->getPlaceTypeId() == NONE_ID) )
        	{  
            		garbage_entities.add(MINERAL_vec[i]);
            		MINERAL_vec.erase(MINERAL_vec.begin() + i );
        	} 
    	}
    	    
    	for(unsigned int i = 0; i < CONTAINER_vec.size(); i++)
    	{
        	if ( (CONTAINER_vec[i]->getGarbageReady() == true) or (CONTAINER_vec[i]->getPlaceTypeId() == NONE_ID) )
        	{   
            		garbage_entities.add(CONTAINER_vec[i]);
            		CONTAINER_vec.erase(CONTAINER_vec.begin() + i );
        	}	 
    	}

    	for(unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
    	{
        	if (ROCKET_vec[ri]->getGarbageReady() == true)
        	{   
            		garbage_entities.add(ROCKET_vec[ri]);
            		ROCKET_vec.erase(ROCKET_vec.begin() + ri );
        	} 
    	}
    	
    	
    	//effects
    	for (unsigned int wi = 0; wi < effect_SHOCKWAVE_vec.size(); wi++)
    	{
    		if (effect_SHOCKWAVE_vec[wi]->is_alive == false)
    		{
    			garbage_effects.add(effect_SHOCKWAVE_vec[wi]);
    	   		effect_SHOCKWAVE_vec.erase(effect_SHOCKWAVE_vec.begin() + wi);
    		}
    	}


    	for (unsigned int lei = 0; lei < effect_LAZERTRACE_vec.size(); lei++)
    	{
         	if (effect_LAZERTRACE_vec[lei]->getAlive() == false)
         	{   
           		garbage_effects.add(effect_LAZERTRACE_vec[lei]);
            		effect_LAZERTRACE_vec.erase(effect_LAZERTRACE_vec.begin() + lei);
         	} 
    	}


    	for(unsigned int i = 0; i<effect_PARTICLESYSTEM_vec.size(); i++)  
    	{
        	if (effect_PARTICLESYSTEM_vec[i]->getAlive() == false)
        	{   
            		garbage_effects.add(effect_PARTICLESYSTEM_vec[i]);
            		effect_PARTICLESYSTEM_vec.erase(effect_PARTICLESYSTEM_vec.begin() + i );
        	} 
    	}

    	for(unsigned int ti = 0; ti < text_DAMAGE_vec.size(); ti++)    
    	{
        	if (text_DAMAGE_vec[ti]->getAlive() == false)
        	{   
            		garbage_effects.add(text_DAMAGE_vec[ti]);
            		text_DAMAGE_vec.erase(text_DAMAGE_vec.begin() + ti);
        	} 
    	}
    
    
    
    
}
    
            






//// ******* TRANSITION ******* 
void StarSystem :: addToHyperJumpQueue(Npc* npc)
{
        NPC_appear_vec.push_back(npc);
}

void StarSystem :: postHyperJumpEvent_s()
{
        for (unsigned int i = 0; i<NPC_appear_vec.size(); i++)
        {               
        	vec2f center(getRandInt(700, 1200), getRandInt(700, 1200));
		float angle = getRandInt(0, 360);  
		
                addToSpace(NPC_appear_vec[i]->getVehicle(), center, angle, NPC_appear_vec[i]->getVehicle()->getParent());  
                addToSpace(NPC_appear_vec[i]);
        }
              
        NPC_appear_vec.clear();  
}

void StarSystem :: launchingEvent_s() const
{
	for (unsigned int i=0; i<PLANET_vec.size(); i++)
	{
		PLANET_vec[i]->getLand()->manageLaunchingQueue();
	}
}		


bool StarSystem :: removeShip(int _id)
{       
        for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
        {
                if (SHIP_inSPACE_vec[ki]->getId() == _id)
                {
                        SHIP_inSPACE_vec.erase(SHIP_inSPACE_vec.begin() + ki);
                        return true; 
                }
        }        
        return false;
}



bool StarSystem :: removeNpc(int _id, int _subtype_id)
{
        removeFromTheListById(&NPC_inSPACE_vec, _id);

	switch(_subtype_id)
	{
        	case RANGER_ID:   { return removeFromTheListById(&NPC_RANGER_inSPACE_vec, _id);   break; }
        	case WARRIOR_ID:  { return removeFromTheListById(&NPC_WARRIOR_inSPACE_vec, _id);  break; }
        	case TRADER_ID:   { return removeFromTheListById(&NPC_TRADER_inSPACE_vec, _id);   break; }
        	case PIRAT_ID:    { return removeFromTheListById(&NPC_PIRAT_inSPACE_vec, _id);    break; } 
        	case DIPLOMAT_ID: { return removeFromTheListById(&NPC_DIPLOMAT_inSPACE_vec, _id); break; }
	}
	
        return false;
}


bool StarSystem :: removeFromTheListById(std::vector<Npc*>* _pTo_npc_vec, int _id)
{
      	for (unsigned int ni = 0; ni < _pTo_npc_vec->size(); ni++)
      	if ((*_pTo_npc_vec)[ni]->getId() == _id)
        {
        	_pTo_npc_vec->erase(_pTo_npc_vec->begin() + ni);
                return true;
        }        
        return false; 
}
//// ******* TRANSITION ******* 


void StarSystem :: bombExplosionEvent(Container* container, bool show_effect)
{
	float radius = ((Bomb*)container->getItemSlot()->getItem())->getRadius();
	float damage = ((Bomb*)container->getItemSlot()->getItem())->getDamage(); 
	vec2f epicentr = container->GetPoints().getCenter();
	
	damageEventInsideCircle(epicentr, radius, damage, show_effect);
		
	if (show_effect == true)
	{
		createExplosion(this, container->GetPoints().getCenter(), 9);
	}
}


void StarSystem :: damageEventInsideCircle(vec2f epicentr, float radius, int damage, bool show_effect)
{
	for (unsigned int i = 0; i < SHIP_inSPACE_vec.size(); i++)
    	{
       	        if ( distBetweenPoints(SHIP_inSPACE_vec[i]->GetPoints().getCenter(), epicentr) < radius )
               	{
       			SHIP_inSPACE_vec[i]->hit(damage, show_effect); 
       		}
    	}
    	
    	for (unsigned int i = 0; i < SPACESTATION_vec.size(); i++)
    	{
       	        if ( distBetweenPoints(SPACESTATION_vec[i]->GetPoints().getCenter(), epicentr) < radius )
               	{
       			SPACESTATION_vec[i]->hit(damage, show_effect); 
       		}
    	}
    	
    	for (unsigned int i = 0; i < SATELLITE_vec.size(); i++)
    	{
       	        if ( distBetweenPoints(SATELLITE_vec[i]->GetPoints().getCenter(), epicentr) < radius )
               	{
       			SATELLITE_vec[i]->hit(damage, show_effect); 
       		}
    	}
}



void StarSystem :: postDeathUniqueEvent(bool) /*virtual */
{}




template <typename AGRESSOR, typename VICTIM>
bool checkCollision(AGRESSOR* agressor,  VICTIM* victim, bool show_effect)
{
	if (collisionBetweenCenters(agressor->GetPoints(), victim->GetPoints(), victim->getCollisionRadius()) == true)
        {
        	victim->hit(agressor->getDamage(), show_effect);
                agressor->collisionEvent(show_effect);
                
                return true;
        }
        else
        {
        	return false;
        }
}





bool collisionBetweenCenters(Points& points1, Points& points2, float collision_radius)
{
    if(abs(points1.getCenter().x - points2.getCenter().x) > collision_radius)
       return false;
    if(abs(points1.getCenter().y - points2.getCenter().y) > collision_radius)
       return false;

    return true;
}

bool collisionBetweenCenters(Points& points1, vec2f point2, float collision_radius)
{
    if(abs(points1.getCenter().x - point2.x) > collision_radius)
       return false;
    if(abs(points1.getCenter().y - point2.y) > collision_radius)
       return false;

    return true;
}

bool collisionBetweenCenters(Points& points1, float center2_x, float center2_y, float collision_radius)
{
    if(abs(points1.getCenter().x - center2_x) > collision_radius)
       return false;
    if(abs(points1.getCenter().y - center2_y) > collision_radius)
       return false;

    return true;
}













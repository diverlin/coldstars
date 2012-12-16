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

#include "starsystem.hpp"
#include "galaxy.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include "../common/myVector.hpp"

#include "../effects/particlesystem/ExplosionEffect.hpp"
#include "../builder/AsteroidBuilder.hpp"
#include "../builder/BlackHoleBuilder.hpp"
#include "../builder/ShipBuilder.hpp"
#include "../builder/NpcBuilder.hpp"
#include "../common/Collision.hpp"
#include "../common/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../config/config.hpp"
#include "../render/Render.hpp"

#include "../items/others/Bomb.hpp"

#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/Satellite.hpp"
#include "../spaceobjects/Ship.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/BlackHole.hpp"

#include "../pilots/Player.hpp"

#include "../effects/DistantNebulaEffect.hpp"
#include "../effects/DistantStarEffect.hpp"
#include "../text/VerticalFlowText.hpp" 
#include "../effects/lazerTrace.hpp"

#include "../spaceobjects/RocketBullet.hpp"
#include "../spaceobjects/Container.hpp"
#include "../spaceobjects/Star.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/BlackHole.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/Satellite.hpp"
#include "../spaceobjects/Ship.hpp"

#include "../common/Logger.hpp"

#include "../garbage/EntityGarbage.hpp"

StarSystem::StarSystem(int id):
unique_update_inDymanic_done(false),
unique_update_inStatic_done(false)
{ 
    	data_id.id = id;
    	data_id.type_id = ENTITY::STARSYSTEM_ID;
    	
    	place_type_id = ENTITY::SPACE_ID;
    	
    	condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
    	
    	race_id = RACE::R0_ID;
    	conqueror_race_id = NONE_ID;

    	galaxy = NULL;    	
    	this->SetStarSystem(this);
}

StarSystem::~StarSystem()
{	
    	// effects	
        for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)   { delete distantNebulaEffect_vec[i]; } 
        for(unsigned int i=0; i<distantStarEffect_vec.size(); i++)     { delete distantStarEffect_vec[i];   } 
        for(unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)     { delete effect_LAZERTRACE_vec[i]; } 
        for(unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { delete effect_PARTICLESYSTEM_vec[i]; } 
        for(unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)      { delete effect_SHOCKWAVE_vec[i]; } 
        for(unsigned int i=0; i<text_DAMAGE_vec.size(); i++)           { delete text_DAMAGE_vec[i]; } 
}      

void StarSystem::PutChildsToGarbage() const
{	
	for(unsigned int i=0; i<STAR_vec.size(); i++) 
	{ 
		//STAR_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(STAR_vec[i]); 
	} 
	for(unsigned int i=0; i<PLANET_vec.size(); i++) 
	{ 
		PLANET_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(PLANET_vec[i]); 
	} 

	for(unsigned int i=0; i<ASTEROID_vec.size(); i++) 
	{ 
		//ASTEROID_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(ASTEROID_vec[i]); 
	} 
	for(unsigned int i=0; i<CONTAINER_vec.size(); i++) 
	{ 
		CONTAINER_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(CONTAINER_vec[i]); 
	} 

	for(unsigned int i=0; i<ROCKET_vec.size(); i++) 
	{ 
		//ROCKET_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(ROCKET_vec[i]); 
	} 
	for(unsigned int i=0; i<BLACKHOLE_vec.size(); i++) 
	{ 
		//BLACKHOLE_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(BLACKHOLE_vec[i]); 
	} 

	for(unsigned int i=0; i<VEHICLE_vec.size(); i++) 
	{ 
		VEHICLE_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(VEHICLE_vec[i]); 
	} 
}      

void StarSystem::AddVehicle(Vehicle* vehicle, const vec2f& center, float angle, BaseSpaceEntity* parent)
{
	#if ENTITY_TRANSACTION_LOG_ENABLED == 1
	Logger::Instance().Log(" StarSystem(id=" + int2str(GetId()) + ")::AddVehicle(id=" + int2str(vehicle->GetId())+")", ENTITY_TRANSACTION_LOG_DIP);
	
	for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
	{
		if (VEHICLE_vec[i]->GetId() == vehicle->GetId())
		{
			Logger::Instance().Log("StarSystem::AddVehicle dublicated vehicle found(fix that)" + getBaseInfoStr(vehicle));
			exit(0);
		}
	}
	#endif
	
     	vehicle->SetPlaceTypeId(ENTITY::SPACE_ID);
     	vehicle->SetStarSystem(this);  
			
	vehicle->GetPoints().SetCenter(center); 
    	vehicle->GetPoints().SetAngle(angle);   
    	vehicle->GetPoints().Update();  
    	
	vehicle->SetParent(parent);
        vehicle->SetColor(GetColor());
                	
	VEHICLE_vec.push_back(vehicle);  

	if (vehicle->GetSubTypeId() == ENTITY::SATELLITE_ID)
	{
		((Satellite*)vehicle)->GetOrbit()->CalcPath(parent->GetCollisionRadius(), 1.0, getRandBool());
	}
}


void StarSystem::AddBullet(RocketBullet* rocket, const vec2f& center, float angle)
{
     	rocket->SetPlaceTypeId(ENTITY::SPACE_ID);
     	rocket->SetStarSystem(this);  
			
	rocket->GetPoints().SetCenter(center); 
    	rocket->GetPoints().SetAngle(angle);   
    	rocket->GetPoints().Update();      	

	ROCKET_vec.push_back(rocket);  
}

void StarSystem::Add(BasePlanet* object, BaseSpaceEntity* parent, int it)
{
	object->CreateOrbit();
        object->SetParent(parent);
        
        object->SetStarSystem(this);
        object->SetPlaceTypeId(ENTITY::SPACE_ID);
        
        object->GetOrbit()->SetIt(it);
        object->UpdatePosition();
        
	switch(object->GetTypeId())
	{
		case ENTITY::STAR_ID:
		{
			STAR_vec.push_back((Star*)object);
			break;
		}
		
		case ENTITY::PLANET_ID:
		{
			PLANET_vec.push_back((Planet*)object);
			break;
		}
		
		case ENTITY::ASTEROID_ID:
		{
			ASTEROID_vec.push_back((Asteroid*)object);
			break;
		}
	}
}
                
void StarSystem::AddContainer(Container* container, const vec2f& center)
{
	#if ENTITY_TRANSACTION_LOG_ENABLED == 1
	Logger::Instance().Log(" StarSystem(id=" + int2str(GetId()) + ")::AddVehicle(id=" + int2str(container->GetId()) + ")", ENTITY_TRANSACTION_LOG_DIP);
	
	
	for (unsigned int i=0; i<CONTAINER_vec.size(); i++)
	{
		if (CONTAINER_vec[i]->GetId() == container->GetId())
		{
			Logger::Instance().Log("StarSystem::AddContainer dublicated container found(fix that)" + getBaseInfoStr(container));
			exit(0);
		}
	}
	#endif
	
	container->SetStarSystem(this);
        container->SetPlaceTypeId(ENTITY::SPACE_ID);
    	container->GetPoints().SetCenter(center);
    	container->SetTargetPos(center+getRandVec2f(60, 100), 4.0);
        
        CONTAINER_vec.push_back(container);
}

void StarSystem::Add(BlackHole* blackhole, const vec2f& center)
{
	blackhole->SetStarSystem(this);
        blackhole->SetPlaceTypeId(ENTITY::SPACE_ID);
	blackhole->SetCenter(center);
	BLACKHOLE_vec.push_back(blackhole);
}    
    		
void StarSystem::Add(ShockWaveEffect* shockwave, const vec2f& center)           { shockwave->SetCenter(center); effect_SHOCKWAVE_vec.push_back(shockwave); }
void StarSystem::Add(LazerTraceEffect* lazerTraceEffect)     { effect_LAZERTRACE_vec.push_back(lazerTraceEffect); }
void StarSystem::Add(BaseParticleSystem* ps)                 { effect_PARTICLESYSTEM_vec.push_back(ps); }
void StarSystem::Add(VerticalFlowText* text)                 { text_DAMAGE_vec.push_back(text); }
void StarSystem::Add(DistantNebulaEffect* dn)                { distantNebulaEffect_vec.push_back(dn); }
void StarSystem::Add(DistantStarEffect* ds)                  { distantStarEffect_vec.push_back(ds); }
//// ******* TRANSITION ******* 
  		           
// poor                
Planet* StarSystem::GetClosestInhabitedPlanet(const vec2f& _pos) const
{    	
     	Planet* requested_planet = NULL;
     	
     	std::vector<Planet*> tmp_planet_vec;     	
	for(unsigned int i=0; i<PLANET_vec.size(); i++)
	{
		if (PLANET_vec[i]->GetPopulation() > 0)
		{
			tmp_planet_vec.push_back(PLANET_vec[i]);
		}
	}
	
	if (tmp_planet_vec.size() >= 1)
	{
		requested_planet = tmp_planet_vec[0];
		float dist_min = distBetweenPoints(_pos, tmp_planet_vec[0]->GetPoints().GetCenter());
		if (tmp_planet_vec.size() > 1)
		{
			for (unsigned int i=1; i<tmp_planet_vec.size(); i++)
			{
				float dist = distBetweenPoints(_pos, tmp_planet_vec[i]->GetPoints().GetCenter());
				if (dist < dist_min)
				{
					requested_planet = tmp_planet_vec[i];
					dist_min = dist;
				}
			}
		
		}
	}
	
	return requested_planet;
}
Planet* StarSystem::GetRandomInhabitedPlanet() const
{
	Planet* requested_planet = NULL;

	std::vector<Planet*> tmp_planet_vec;
	for(unsigned int i=0; i<PLANET_vec.size(); i++)
	{
		if (PLANET_vec[i]->GetPopulation() > 0)
		{
			tmp_planet_vec.push_back(PLANET_vec[i]);
		}
	}
	
     	if (tmp_planet_vec.size() >= 1) 
     	{
     		requested_planet = tmp_planet_vec[getRandInt(0, tmp_planet_vec.size()-1)];
     	}

	return requested_planet;
}
Planet* StarSystem::GetRandomPlanet() const
{
	return PLANET_vec[getRandInt(0, PLANET_vec.size()-1)];
}

Vehicle* StarSystem::GetRandomVehicle() const
{
     	return VEHICLE_vec[getRandInt(0, VEHICLE_vec.size()-1)];
}
Vehicle* StarSystem::GetRandomVehicleExcludingNpcRaceId(int _race_id) const
{
        std::vector<Vehicle*> _vehicle_vec;
        Vehicle* requested_vehicle = NULL;
        
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
        {
        	if (VEHICLE_vec[i]->GetOwnerNpc() != NULL)
                {
                	if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() != _race_id)
                	{
                        	_vehicle_vec.push_back(VEHICLE_vec[i]);
                	}
                }
        }
        
        if (_vehicle_vec.size() > 0)
        {
                requested_vehicle = _vehicle_vec[getRandInt(0, _vehicle_vec.size()-1)];
        }
        
        return requested_vehicle;
}

Vehicle* StarSystem::GetRandomVehicleByNpcRaceId(int _race_id) const
{
        std::vector<Vehicle*> _vehicle_vec;
        Vehicle* requested_vehicle = NULL;
        
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
        {
        	if (VEHICLE_vec[i]->GetOwnerNpc() != NULL)
                {
                	if (VEHICLE_vec[i]->GetOwnerNpc()->GetRaceId() == _race_id)
                	{
                        	_vehicle_vec.push_back(VEHICLE_vec[i]);
                	}
                }
        }
        
        if (_vehicle_vec.size() > 0)
        {
                requested_vehicle = _vehicle_vec[getRandInt(0, _vehicle_vec.size()-1)];
        }
        
        return requested_vehicle;
}

Vehicle* StarSystem::GetRandomVehicle(const std::vector<int>& rVec_race_id) const
{
	std::vector<Vehicle*> tmp_vehicle_vec;
	Vehicle* requested_vehicle = NULL;

        for (unsigned int i=0; i<rVec_race_id.size(); i++)
        {	
		for (unsigned int j=0; j<VEHICLE_vec.size(); j++)
        	{
       			if (rVec_race_id[i] == VEHICLE_vec[j]->GetOwnerNpc()->GetRaceId())
       			{
       				tmp_vehicle_vec.push_back(VEHICLE_vec[j]);
       			}
        	}
        }
        
        if (tmp_vehicle_vec.size() > 0)
        {
                requested_vehicle = tmp_vehicle_vec[getRandInt(0, tmp_vehicle_vec.size()-1)];
        }
	
	return requested_vehicle;
}


void StarSystem::UpdateStates()
{
	if (CONTAINER_vec.size() < 100)
	{
		AsteroidManager_s(3);
	}
	     	
	if (Config::Instance().GetGameMode() == GAME_MODE::CRASH_TEST)
	{
		AsteroidManager_s(50);
		ShipManager_s(50);
		
		if (BLACKHOLE_vec.size() < 5)
		{
			Add(BlackHoleBuilder::Instance().GetNewBlackHole(), getRandVec2f(200, 1200));
		}
	}
	
	//if (PLAYER_vec.size() > 0)
	//{
		//detalied_simulation = true;
	//}
	//else
	//{
		//detalied_simulation = false;
	//}

	bool enemy_is_here    = false;
	bool friendly_is_here = false; 
	
	Vehicle* _vehicle_evil = GetRandomVehicle(RaceInformationCollector::Instance().RACES_EVIL_vec);
	if (_vehicle_evil != NULL)
	{
		enemy_is_here = true;
	}
	
	Vehicle* _vehicle_good = GetRandomVehicle(RaceInformationCollector::Instance().RACES_GOOD_vec);
	if (_vehicle_good != NULL)
	{
		friendly_is_here = true;
	}
	
	switch(condition_id)
	{
		case ENTITY::STARSYSTEM::CONDITION::SAFE_ID:
		{
			if (enemy_is_here == true)
			{
				if (friendly_is_here == true)
				{
					condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
				}
				else
				{
					condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
					if (GetRandomVehicleByNpcRaceId(RACE::R6_ID) != NULL)
					{
						conqueror_race_id = RACE::R6_ID;
					}
				
					if (GetRandomVehicleByNpcRaceId(RACE::R7_ID) != NULL)
					{
						conqueror_race_id = RACE::R7_ID;
					}
				}
			}
		
			break;
		}

		case ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID:
		{
			if (friendly_is_here == true)
			{
				if (enemy_is_here == true)
				{
					condition_id = ENTITY::STARSYSTEM::CONDITION::WAR_ID;
				}
				else	
				{
					condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
					conqueror_race_id = NONE_ID;
				}
			}
			
			break;
		}

		case ENTITY::STARSYSTEM::CONDITION::WAR_ID:
		{
			if (friendly_is_here == true)
			{
				if (enemy_is_here == false)
				{
					condition_id = ENTITY::STARSYSTEM::CONDITION::SAFE_ID;
				}
			}
			else
			{
				condition_id = ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID;
			}
				
			break;
		}
	}
}


void StarSystem::Update(int time, bool detalied_simulation)
{                
	UpdateEntities_s(time, detalied_simulation);
	    		
	if (time > 0)
	{
		if (unique_update_inDymanic_done == false)
		{
                        hyperspace.PostHyperJumpEvent(this);
                        //LaunchingEvent();
                        
                        unique_update_inDymanic_done = true;
			unique_update_inStatic_done  = false;
		}

    		rocketCollision_s(detalied_simulation);   // pri/2
    		asteroidCollision_s(detalied_simulation); // pri/2
    		
    		if (CONTAINER_vec.size() > 200)
        	{
               		CONTAINER_vec[getRandInt(0, 199)]->Hit(100, true);
        	}
	}
	else
	{
		if (unique_update_inStatic_done == false)
		{    		
			UpdateStates();
		
    			MindEntitiesInStatic_s();     			

			garbage_effects.clear(); 
			
			unique_update_inDymanic_done = false;
    			unique_update_inStatic_done  = true;
    		}    		
	}

        ManageUnavaliableObjects_s();
        ManageDeadObjects_s();         // no need to update so frequently, pri /6
}

void StarSystem::rocketCollision_s(bool show_effect)
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                if (ROCKET_vec[ri]->GetAlive() == true) 
                {
                	// vehicle
                	if (collide == false)
                	{
                		for (unsigned int vi = 0; vi < VEHICLE_vec.size(); vi++)
                		{
                        		if (ROCKET_vec[ri]->GetOwnerId() != VEHICLE_vec[vi]->GetId())
                        		{                        
                        			collide = checkCollision(ROCKET_vec[ri], VEHICLE_vec[vi], show_effect);
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






void StarSystem::asteroidCollision_s(bool show_effect)
{
	bool collide = false;
	
        for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
        {
                if (ASTEROID_vec[ai]->GetAlive() == true) 
                {
                	if (collide == false)
                	{
                        	for (unsigned int vi = 0; vi < VEHICLE_vec.size(); vi++)
                        	{
                                	collide = checkCollision(ASTEROID_vec[ai], VEHICLE_vec[vi], show_effect);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }        	
                	                	
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

void StarSystem::UpdateEntities_s(int time, bool show_effect)
{
        for (unsigned int i=0; i<STAR_vec.size(); i++)         	{ STAR_vec[i]->UpdateInSpace(time, show_effect);  }	
        for (unsigned int i=0; i<PLANET_vec.size(); i++)       	{ PLANET_vec[i]->UpdateInSpace(time, show_effect); }
    	for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++) 		{ BLACKHOLE_vec[i]->UpdateInSpace(time, show_effect); }
     	for (unsigned int i=0; i<CONTAINER_vec.size(); i++)       	{ CONTAINER_vec[i]->UpdateInSpace(time, show_effect); }
	for (unsigned int i=0; i<ASTEROID_vec.size(); i++)        	{ ASTEROID_vec[i]->UpdateInSpace(time, show_effect); }
    	
    	for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 	        { VEHICLE_vec[i]->UpdateInSpace(time, show_effect); }
        for (unsigned int i=0; i<ROCKET_vec.size(); i++)          	{ ROCKET_vec[i]->UpdateInSpace(time, show_effect); }
                
        // effects
        for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)  	{ effect_LAZERTRACE_vec[i]->update(); }
	for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { effect_PARTICLESYSTEM_vec[i]->Update(); }
	for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++) 	{ effect_SHOCKWAVE_vec[i]->Update(); }
	for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)         { text_DAMAGE_vec[i]->update(); }   
	for (unsigned int i=0; i<distantNebulaEffect_vec.size(); i++) { distantNebulaEffect_vec[i]->Update(); } 
}  
      
void StarSystem::MindEntitiesInStatic_s()
{
     	for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 		
     	{ 
     		VEHICLE_vec[i]->GetOwnerNpc()->MindInSpace(); 
     		if (VEHICLE_vec[i]->GetSubTypeId() == ENTITY::SPACESTATION_ID)
     		{
     			((SpaceStation*)VEHICLE_vec[i])->GetLand()->UpdateInSpaceInStatic();
     		}
     	}
     	
    	for (unsigned int i=0; i<PLANET_vec.size(); i++)     	{ PLANET_vec[i]->UpdateInSpaceInStatic(); }
}      

void StarSystem::FindRenderVisibleEntities_c(Player* player)
{
	player->ClearVisibleEntities();
		
        for (unsigned int i=0; i<STAR_vec.size(); i++)         	{ player->AddIfVisible(STAR_vec[i]); }    
        for (unsigned int i=0; i<PLANET_vec.size(); i++)       	{ player->AddIfVisible(PLANET_vec[i]); }
        for (unsigned int i=0; i<ASTEROID_vec.size(); i++)     	{ player->AddIfVisible(ASTEROID_vec[i]); } 
        for (unsigned int i=0; i<CONTAINER_vec.size(); i++)    	{ player->AddIfVisible(CONTAINER_vec[i]); }
    	for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 	{ player->AddIfVisible(VEHICLE_vec[i]); } 
    	for (unsigned int i=0; i<ROCKET_vec.size(); i++)       	{ player->AddIfVisible(ROCKET_vec[i]); }
    	for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)    	{ player->AddIfVisible(BLACKHOLE_vec[i]); } 
           		
    	//effects
	for (unsigned int i=0; i<effect_SHOCKWAVE_vec.size(); i++)    { player->AddIfVisible(effect_SHOCKWAVE_vec[i]); }
	for (unsigned int i=0; i<effect_LAZERTRACE_vec.size(); i++)   { player->AddIfVisible(effect_LAZERTRACE_vec[i]); }
	for (unsigned int i=0; i<effect_PARTICLESYSTEM_vec.size(); i++) { player->AddIfVisible(effect_PARTICLESYSTEM_vec[i]); }
	for (unsigned int i=0; i<text_DAMAGE_vec.size(); i++)		{ player->AddIfVisible(text_DAMAGE_vec[i]); }
}

void StarSystem::FindRadarVisibleEntities_c(Player* player)
{	
	GuiRadar& gui_radar = player->GetGuiManager().GetGuiRadar();
	const Vehicle& vehicle = *player->GetNpc()->GetVehicle();
	gui_radar.Reset();
		
        for (unsigned int i=0; i<STAR_vec.size(); i++) 	{ gui_radar.Add(STAR_vec[i]); }    
        for (unsigned int i=0; i<PLANET_vec.size(); i++)      { gui_radar.Add(PLANET_vec[i]); } 
    	for (unsigned int i=0; i<BLACKHOLE_vec.size(); i++)   { gui_radar.Add(BLACKHOLE_vec[i]); } 
    	                
        for (unsigned int i=0; i<ASTEROID_vec.size(); i++)    { gui_radar.AddIfWithinRadarRange(ASTEROID_vec[i], vehicle); }         
    	for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 	{ gui_radar.AddIfWithinRadarRange(VEHICLE_vec[i], vehicle); }    	
}

      
void StarSystem::RestoreSceneColor()
{
        setColor4f(STAR_vec[0]->GetColor());
}     

void StarSystem::RestoreDefaultColor()
{
	setColor4f(COLOR::COLOR4F_WHITE);
}

void StarSystem::DrawBackground(vec2f scroll_coords)
{   
	// HACK for point sprites
    	enable_POINTSPRITE();
    		if (distantStarEffect_vec.size()>0) distantStarEffect_vec[0]->Render(scroll_coords.x, scroll_coords.y); 
    	disable_POINTSPRITE();
    	// HACK for point sprites

	clearScreen();
	resetRenderTransformation();
        RestoreSceneColor();

    	enable_BLEND();
		glDepthMask(false);

    		for(unsigned int i=0; i<distantNebulaEffect_vec.size(); i++)
    		{ 
        		distantNebulaEffect_vec[i]->Render(scroll_coords.x, scroll_coords.y); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<distantStarEffect_vec.size(); i++)
    			{ 
       				distantStarEffect_vec[i]->Render(scroll_coords.x, scroll_coords.y); 
    			}
    		disable_POINTSPRITE();
    	
		glDepthMask(true);
	disable_BLEND();
}
    
void StarSystem::DrawOrbits()
{
        for(unsigned int i = 0; i < PLANET_vec.size(); i++) 
	{ 
		PLANET_vec[i]->GetOrbit()->DrawPath(); 
	}

	for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
	{ 
		ASTEROID_vec[i]->GetOrbit()->DrawPath(); 
	}
}
 
void StarSystem::DrawPath()
{
        for(unsigned int i=0; i<VEHICLE_vec.size(); i++) 
	{ 
		//VEHICLE_vec[i]->GetDriveComplex()->DrawPath(); 
	}
}
     
    


void StarSystem::AsteroidManager_s(unsigned int num)
{
        while (ASTEROID_vec.size() < num)
        {
                Add(AsteroidBuilder::Instance().GetNewAsteroid());
                //break;
        }
}

void StarSystem::ShipManager_s(unsigned int num)
{
        while (VEHICLE_vec.size() < num)
        {
		int prace_id    = RACE::R0_ID;
		if (getRandBool())
		{
			prace_id = RACE::R6_ID;
		}
		
      		int psubtype_id = ENTITY::WARRIOR_ID;
      		int size_id     = SIZE_4_ID;
      		int weapons_num = 7;
        
       		Npc* new_pnpc = NpcBuilder::Instance().GetNewNpc(prace_id, psubtype_id);
        	Ship* new_pship = ShipBuilder::Instance().GetNewShip(prace_id, psubtype_id, size_id, weapons_num);
        	ShipBuilder::Instance().Equip(new_pship);   // improove
        
        	new_pship->BindOwnerNpc(new_pnpc);

		vec2f pos = getRandVec2f(100, 800);
		int angle = getRandInt(0, 360);
                AddVehicle(new_pship, pos, angle);
        	//break;
        }
}


void StarSystem::ManageUnavaliableObjects_s()
{               
        for (std::vector<Vehicle*>::iterator it=VEHICLE_vec.begin(); it<VEHICLE_vec.end(); ++it)
        {
               	if ((*it)->GetPlaceTypeId() != ENTITY::SPACE_ID)
               	{	
               		#if ENTITY_TRANSACTION_LOG_ENABLED == 1
			Logger::Instance().Log("starsysten_id="+int2str(GetId())+ " RemoveVehicle, vehicle_id=" + int2str((*it)->GetId()));
			#endif
               		it = VEHICLE_vec.erase(it);
               	}
        }
}
    		
void StarSystem::ManageDeadObjects_s()
{  	
   	for(std::vector<Vehicle*>::iterator it=VEHICLE_vec.begin(); it<VEHICLE_vec.end(); ++it)
    	{
               	if ((*it)->GetGarbageReady() == true)
        	{  
        		Vehicle* vehicle = *it;
    			Npc* npc = vehicle->GetOwnerNpc(); 
    		
        		if (npc != NULL)
        		{
            			npc->SetAlive(false);
            			EntityGarbage::Instance().Add(npc); 
               		}
               		
               		vehicle->PutChildsToGarbage();
            		EntityGarbage::Instance().Add(vehicle);
            		it = VEHICLE_vec.erase(it);
        	} 
    	}

   	for(std::vector<BlackHole*>::iterator it=BLACKHOLE_vec.begin(); it<BLACKHOLE_vec.end(); ++it)
    	{
        	if ((*it)->GetGarbageReady() == true)
        	{
            		EntityGarbage::Instance().Add(*it);
            		it = BLACKHOLE_vec.erase(it);
            	}
        }  
            	
   	for(std::vector<Asteroid*>::iterator it=ASTEROID_vec.begin(); it<ASTEROID_vec.end(); ++it)
    	{
        	if ((*it)->GetGarbageReady() == true)
        	{
            		EntityGarbage::Instance().Add(*it);
            		it = ASTEROID_vec.erase(it);
            	}
        }  

   	for(std::vector<Container*>::iterator it=CONTAINER_vec.begin(); it<CONTAINER_vec.end(); ++it)
    	{
        	if ((*it)->GetGarbageReady() == true)
        	{   
        		(*it)->PutChildsToGarbage();
            		EntityGarbage::Instance().Add(*it);
            		it = CONTAINER_vec.erase(it);
        	}	 
    	}

   	for(std::vector<RocketBullet*>::iterator it=ROCKET_vec.begin(); it<ROCKET_vec.end(); ++it)
    	{
        	if ((*it)->GetGarbageReady() == true)
        	{   
            		EntityGarbage::Instance().Add(*it);
            		it = ROCKET_vec.erase(it);
        	} 
    	}    	
    	
    	//effects
   	for(std::vector<ShockWaveEffect*>::iterator it=effect_SHOCKWAVE_vec.begin(); it<effect_SHOCKWAVE_vec.end(); ++it)
    	{
    		if ((*it)->is_alive == false)
    		{
    			garbage_effects.add(*it);
    	   		it = effect_SHOCKWAVE_vec.erase(it);
    		}
    	}

   	for(std::vector<LazerTraceEffect*>::iterator it=effect_LAZERTRACE_vec.begin(); it<effect_LAZERTRACE_vec.end(); ++it)
    	{
         	if ((*it)->GetAlive() == false)
         	{   
           		garbage_effects.add(*it);
            		it = effect_LAZERTRACE_vec.erase(it);
         	} 
    	}

   	for(std::vector<BaseParticleSystem*>::iterator it=effect_PARTICLESYSTEM_vec.begin(); it<effect_PARTICLESYSTEM_vec.end(); ++it)
    	{
        	if ((*it)->GetAlive() == false)
        	{   
            		garbage_effects.add(*it);
            		it = effect_PARTICLESYSTEM_vec.erase(it);
        	} 
    	}

   	for(std::vector<VerticalFlowText*>::iterator it=text_DAMAGE_vec.begin(); it<text_DAMAGE_vec.end(); ++it)
    	{
        	if ((*it)->GetAlive() == false)
        	{   
            		garbage_effects.add(*it);
            		it = text_DAMAGE_vec.erase(it);
        	} 
    	}
}    
    

//void StarSystem::LaunchingEvent() const
//{
	//for (unsigned int i=0; i<PLANET_vec.size(); i++)
	//{
		////PLANET_vec[i]->GetLand()->ManageLaunching();
	//}
//}		

void StarSystem::BombExplosionEvent(Container* container, bool show_effect)
{
	float radius = ((Bomb*)container->GetItemSlot()->GetItem())->GetRadius();
	float damage = ((Bomb*)container->GetItemSlot()->GetItem())->GetDamage(); 
	vec2f center = container->GetPoints().GetCenter();
	
	DamageEventInsideCircle(center, radius, damage, show_effect);
		
	if (show_effect == true)
	{
		createExplosion(this, container->GetPoints().GetCenter(), 9);
	}
}

void StarSystem::StarSparkEvent(float radius) const
{
	for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    	{
       	        if ( distBetweenPoints(VEHICLE_vec[i]->GetPoints().GetCenter(), GetStar()->GetPoints().GetCenter()) < radius )
               	{
               		if (VEHICLE_vec[i]->GetRadarSlot()->GetItem() != NULL)
               		{
       				VEHICLE_vec[i]->GetRadarSlot()->GetItem()->LockEvent(2); 
       			}
       		}
    	}
}

void StarSystem::DamageEventInsideCircle(const vec2f& center, float radius, int damage, bool show_effect)
{
	for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    	{
       	        if ( distBetweenPoints(VEHICLE_vec[i]->GetPoints().GetCenter(), center) < radius )
               	{
       			VEHICLE_vec[i]->Hit(damage, show_effect); 
       		}
    	}
}


/*virtual */
void StarSystem::PostDeathUniqueEvent(bool) 
{}

void StarSystem::SaveDataUniqueStarSystem(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"galaxy_id", galaxy->GetId());
	
	save_ptree.put(root+"color.r", color.r);
	save_ptree.put(root+"color.g", color.g);
	save_ptree.put(root+"color.b", color.b);
	save_ptree.put(root+"color.a", color.a);
			
	for (unsigned int i=0; i<distantStarEffect_vec.size(); i++)
	{
		distantStarEffect_vec[i]->SaveData(save_ptree, root);
	}

	for (unsigned int i = 0; i<distantNebulaEffect_vec.size(); i++)
	{
		distantNebulaEffect_vec[i]->SaveData(save_ptree, root);
	}

}

void StarSystem::LoadDataUniqueStarSystem(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_StarSystem.galaxy_id = load_ptree.get<int>("galaxy_id");
	
	color.r = load_ptree.get<float>("color.r");
	color.g = load_ptree.get<float>("color.g");
	color.b = load_ptree.get<float>("color.b");
	color.a = load_ptree.get<float>("color.a");
					
	boost::property_tree::ptree tmp_ptree = load_ptree;
	if (tmp_ptree.get_child_optional("distant_nebula_effect"))
	{	
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tmp_ptree.get_child("distant_nebula_effect"))
		{
			DistantNebulaEffect* dn = GetNewDistantNebulaEffect(NONE_ID);
			dn->LoadData(v.second);
			dn->ResolveData();
                	Add(dn);
		}
	}
	
	if (tmp_ptree.get_child_optional("distant_star_effect"))
	{	
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tmp_ptree.get_child("distant_star_effect"))
		{
			DistantStarEffect* ds = GetNewDistantStarEffect(NONE_ID);
			ds->LoadData(v.second);
			ds->ResolveData();
                	Add(ds);
		}
	}
}

void StarSystem::ResolveDataUniqueStarSystem()
{
	((Galaxy*)EntityManager::Instance().GetEntityById(data_unresolved_StarSystem.galaxy_id))->Add(this, data_unresolved_BaseSpaceEntity.center);
}

void StarSystem::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "starsystem." + int2str(starsystem->GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueStarSystem(save_ptree, root);
}

void StarSystem::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueStarSystem(load_ptree);
}

void StarSystem::ResolveData()
{
	ResolveDataUniqueBase(); 
	ResolveDataUniqueBaseSpaceEntity(); 
	ResolveDataUniqueStarSystem(); 
}		


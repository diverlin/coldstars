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

#include "Player.hpp"
#include "../config/config.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../world/starsystem.hpp"

#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../common/EntityManager.hpp"

#include "../ai/Task.hpp"
#include "../ai/StateMachine.hpp"

#include "../items/equipment/ScanerEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"
#include "../parts/WeaponComplex.hpp"

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

#include "../common/TurnTimer.hpp"
#include "../pilots/Npc.hpp"

Player::Player(int id)
{ 
    	data_id.id         = id;
    	data_id.type_id    = ENTITY::PLAYER_ID;
        data_id.subtype_id = NONE_ID;
   	
    	npc  = NULL;
    	starsystem = NULL;
    	
    	cursor.SetPlayer(this);
    	gui_manager.SetPlayer(this);
}
    
Player::~Player()
{}  
            
               			
void Player::BindNpc(Npc* npc)
{
    	this->npc = npc;
    	npc->SetUpperControl(true);
}

void Player::ClearVisibleEntities()
{
        visible_STAR_vec.clear();
        visible_PLANET_vec.clear();
        
        visible_ASTEROID_vec.clear();
        visible_CONTAINER_vec.clear();

        visible_SHIP_vec.clear();
        visible_SATELLITE_vec.clear();
        visible_SPACESTATION_vec.clear();
        visible_ROCKET_vec.clear();
        visible_BLACKHOLE_vec.clear();

    	visible_effect_SHOCKWAVE_vec.clear();
    	visible_effect_LAZERTRACE_vec.clear();
    	visible_effect_PARTICLESYSTEM_vec.clear();  		
    	visible_text_DAMAGE_vec.clear();
}
    		
void Player::AddIfVisible(Star* star)
{
        if (IsObjectOnScreen(star->GetPoints()))
        {         
		visible_STAR_vec.push_back(star);
	}
}

void Player::AddIfVisible(Planet* planet)
{
        if (IsObjectOnScreen(planet->GetPoints()))
        {  
		visible_PLANET_vec.push_back(planet);
	}
}

void Player::AddIfVisible(Asteroid* asteroid)     		
{
	if (IsObjectOnScreen(asteroid->GetPoints()))
        {   	
                if ( npc->GetVehicle()->IsObjectWithinRadarRange(asteroid) )
                {
                	visible_ASTEROID_vec.push_back(asteroid);
                }
        }
}

void Player::AddIfVisible(Container* container)     	
{
        if (IsObjectOnScreen(container->GetPoints()))
        {    
                if ( npc->GetVehicle()->IsObjectWithinRadarRange(container) )
                {
                	visible_CONTAINER_vec.push_back(container);
                }
	}
}

void Player::AddIfVisible(RocketBullet* rocket)  
{
        if (IsObjectOnScreen(rocket->GetPoints()))  
        {  
                if ( npc->GetVehicle()->IsObjectWithinRadarRange(rocket) )
                {
        		visible_ROCKET_vec.push_back(rocket);
        	}
        }
}

void Player::AddIfVisible(BlackHole* blackhole)  
{
        if (IsObjectOnScreen(blackhole->GetPoints()))  
        {  
                if ( npc->GetVehicle()->IsObjectWithinRadarRange(blackhole) )
                {
                	visible_BLACKHOLE_vec.push_back(blackhole);
		}
	}
}


void Player::AddIfVisible(Vehicle* vehicle) 
{
        if (IsObjectOnScreen(vehicle->GetPoints()))
        {	  
                if ( npc->GetVehicle()->IsObjectWithinRadarRange(vehicle) )
                {
			switch(vehicle->GetSubTypeId())
			{			
				case ENTITY::SHIP_ID:         { visible_SHIP_vec.push_back((Ship*)vehicle); break; }
				case ENTITY::SATELLITE_ID:    { visible_SATELLITE_vec.push_back((Satellite*)vehicle); break; }
				case ENTITY::SPACESTATION_ID: { visible_SPACESTATION_vec.push_back((SpaceStation*)vehicle); break; }
			}
		}
	}
}     		
        
void Player::AddIfVisible(ShockWaveEffect* effect)
{
        if (IsObjectOnScreen(effect->GetCenter(), 600))
        {
		visible_effect_SHOCKWAVE_vec.push_back(effect);
	}
}

void Player::AddIfVisible(LazerTraceEffect* effect)
{
	visible_effect_LAZERTRACE_vec.push_back(effect);
}
 
void Player::AddIfVisible(BaseParticleSystem* effect)
{
	visible_effect_PARTICLESYSTEM_vec.push_back(effect);
}

void Player::AddIfVisible(VerticalFlowText* effect)
{
	visible_text_DAMAGE_vec.push_back(effect);
}     		

void Player::UpdatePostTransactionEvent(TurnTimer& turn_timer)
{
	if (starsystem == NULL) //hack
	{
		starsystem = npc->GetVehicle()->GetStarSystem();
	}
	
	if (starsystem->GetId() != npc->GetVehicle()->GetStarSystem()->GetId())
	{
		//Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetPoints().GetCenter());
		Screen::Instance().GetRect().SetCenter(npc->GetVehicle()->GetPoints().GetCenter());
		starsystem = npc->GetVehicle()->GetStarSystem();
	}
	
	int action_id = npc->GetVehicle()->GetSpecialActionId();
	switch(action_id)
	{
		//case SPECIAL_ACTION::INITIATE_JUMPIN_ID:
		//{
			//if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
			//{
				//if (turn_timer.GetTurnEnded() == true)
				//{
					//Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetPoints().GetCenter());	
				//}
			//}
			
			//break;
		//}
		
		case SPECIAL_ACTION::INITIATE_JUMPOUT_ID:
		{
			if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::HYPER_SPACE_ID)
			{
				if (turn_timer.GetTurnEnded() == true)
				{
					turn_timer.NextTurn();
				}
			}
			
			break;
		}

		case SPECIAL_ACTION::INITIATE_LAUNCHING_ID:
		{
			if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
			{
				if (turn_timer.GetTurnEnded() == true)
				{
					Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetPoints().GetCenter());
					turn_timer.NextTurn();				
				}
			}
			
			break;
		}
	
		case SPECIAL_ACTION::INITIATE_DOCKING_ID:
		{
			if (turn_timer.GetTurnEnded() == true)
			{
				Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetPoints().GetCenter());
				turn_timer.NextTurn();				
			}
			
			break;
		}		
	}
	
	Screen::Instance().UpdateInSpace();
}
     		
void Player::RenderInSpace_NEW(StarSystem* starsystem)
{   
	int w = Screen::Instance().GetWindow().GetWidth();
	int h = Screen::Instance().GetWindow().GetHeight();

	Screen::Instance().GetFbo0().Activate(w, h);
   
        	starsystem->DrawBackground(Screen::Instance().GetRect().GetBottomLeft());           
		camera(Screen::Instance().GetRect().GetBottomLeft().x, Screen::Instance().GetRect().GetBottomLeft().y);    
	        

		starsystem->RestoreDefaultColor();
		enable_BLEND();
			for(unsigned int i=0; i<visible_STAR_vec.size(); i++) 
			{ 
        			visible_STAR_vec[i]->Render_NEW(); 
    			}
    		disable_BLEND();
		starsystem->RestoreSceneColor();
	Screen::Instance().GetFbo0().Deactivate();

	// POST PROCESS BLOOM (many FBO)
	Screen::Instance().GetBloom().Proceed(w, h, Screen::Instance().GetFbo0().GetTexture(), visible_STAR_vec[0]->GetBrightThreshold());

	// RENDER to FBO1, VOLUMETRIC LIGHT
	Screen::Instance().GetFbo1().Activate(w, h);
		glUseProgram(ShaderCollector::Instance().volumetriclight);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetBloom().GetFboFinal().GetTexture());
			glUniform1i(glGetUniformLocation(ShaderCollector::Instance().volumetriclight, "FullSampler"), 0);

			glActiveTexture(GL_TEXTURE1);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetBloom().GetTextureBlured());
			glUniform1i(glGetUniformLocation(ShaderCollector::Instance().volumetriclight, "BlurSampler"), 1);

			glUniform4f(glGetUniformLocation(ShaderCollector::Instance().volumetriclight, "sun_pos"), -Screen::Instance().GetRect().GetBottomLeft().x/w, -Screen::Instance().GetRect().GetBottomLeft().y/h, -100.0, 1.0);
          
			glActiveTexture(GL_TEXTURE0);
			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
	Screen::Instance().GetFbo1().Deactivate();


	Screen::Instance().GetFbo2().Activate(w, h);
		drawFullScreenTexturedQuad(Screen::Instance().GetFbo1().GetTexture(), w, h, -999.0);
           
          	camera(Screen::Instance().GetRect().GetBottomLeft().x, Screen::Instance().GetRect().GetBottomLeft().y);    
        
		enable_DEPTH();  
    			for(unsigned int i=0; i<visible_PLANET_vec.size(); i++) 
    			{ 
       				visible_PLANET_vec[i]->Render_NEW(Screen::Instance().GetRect().GetBottomLeft()); 
    			}
    		
    			for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)
    			{ 
       				visible_ASTEROID_vec[i]->Render_NEW(Screen::Instance().GetRect().GetBottomLeft()); 
    			}

    			for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)
			{ 
        			visible_BLACKHOLE_vec[i]->Render_NEW(Screen::Instance().GetRect().GetBottomLeft()); 
        			
    			}  	
    		disable_DEPTH();

    	          
		enable_BLEND();		
		    	for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)
    			{ 
    				visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       				visible_SPACESTATION_vec[i]->RenderInSpace(); 
        			starsystem->RestoreSceneColor();
    			}
   
    			for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)
    			{ 
        			visible_CONTAINER_vec[i]->Render2D(); 
    			} 	 
           

    			for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)
    			{ 
       				visible_SHIP_vec[i]->RenderInSpace(); 
        			starsystem->RestoreSceneColor();
    			}

			for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)
    			{ 
    				visible_SATELLITE_vec[i]->UpdateRenderStuff(); 
       				visible_SATELLITE_vec[i]->RenderInSpace(); 
        			starsystem->RestoreSceneColor();
    			}
    			
    			for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)
    			{ 
    			    	visible_ROCKET_vec[i]->UpdateRenderStuff();
       				visible_ROCKET_vec[i]->RenderInSpace(); 
       				starsystem->RestoreSceneColor();
    			}    	
		disable_BLEND();
		
    	Screen::Instance().GetFbo2().Deactivate();


	// POST PROCESS WAVE SHOCK into FBO2
	Screen::Instance().GetFbo3().Activate(w, h);

		float center_array[10][2];
		float xyz_array[10][3];
		float time_array[10];

		for (unsigned int i=0; i<visible_effect_SHOCKWAVE_vec.size(); i++)
		{         
			center_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->center.x/w - Screen::Instance().GetRect().GetBottomLeft().x/w;
			center_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->center.y/h - Screen::Instance().GetRect().GetBottomLeft().y/h;
			xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->parameter.x;
			xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->parameter.y;
			xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[i]->parameter.z;
				
			time_array[i] = visible_effect_SHOCKWAVE_vec[i]->time;
		}
       

		glUseProgram(ShaderCollector::Instance().shockwave);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetFbo2().GetTexture());
			glUniform1i (glGetUniformLocation(ShaderCollector::Instance().shockwave, "sceneTex"), 0);

			int len_effect_SHOCKWAVE_list = visible_effect_SHOCKWAVE_vec.size();
			glUniform1i (glGetUniformLocation(ShaderCollector::Instance().shockwave, "imax"),        len_effect_SHOCKWAVE_list);
			glUniform2fv(glGetUniformLocation(ShaderCollector::Instance().shockwave, "center"),      len_effect_SHOCKWAVE_list, *center_array);
			glUniform3fv(glGetUniformLocation(ShaderCollector::Instance().shockwave, "shockParams"), len_effect_SHOCKWAVE_list, *xyz_array);
			glUniform1fv(glGetUniformLocation(ShaderCollector::Instance().shockwave, "time"),        len_effect_SHOCKWAVE_list, time_array);

			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
	
	Screen::Instance().GetFbo3().Deactivate();


	// render from FBO
	glEnable(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);      // unbind fbo

	clearScreen();
	resetRenderTransformation();

	//drawFullScreenTexturedQuad(Screen::Instance().GetFbo3().GetTexture(), w, h, -999.0);
	//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug
	// draw fogwar and final scene
    	glUseProgram(ShaderCollector::Instance().fogwar);
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetFbo3().GetTexture());
		glUniform1i (glGetUniformLocation(ShaderCollector::Instance().fogwar, "sceneTex"), 0);

		glUniform2f(glGetUniformLocation(ShaderCollector::Instance().fogwar, "center"), npc->GetVehicle()->GetPoints().GetCenter().x/w, npc->GetVehicle()->GetPoints().GetCenter().y/h);
		glUniform1f(glGetUniformLocation(ShaderCollector::Instance().fogwar, "radius"), (float)npc->GetVehicle()->GetPropetries().radar/w);
		glUniform2f(glGetUniformLocation(ShaderCollector::Instance().fogwar, "pos"), Screen::Instance().GetRect().GetBottomLeft().x/w, Screen::Instance().GetRect().GetBottomLeft().y/h);

		drawFullScreenQuad(w, h, -999.0);
	glUseProgram(0); 



	camera(Screen::Instance().GetRect().GetBottomLeft().x, Screen::Instance().GetRect().GetBottomLeft().y);
	
	enable_BLEND();
		for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		visible_effect_LAZERTRACE_vec[i]->Render(); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i=0; i<visible_effect_PARTICLESYSTEM_vec.size(); i++)
    			{ 
        			visible_effect_PARTICLESYSTEM_vec[i]->Render(); 
    			}
    		disable_POINTSPRITE();
    	disable_BLEND();

    	for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    	{ 
        	visible_text_DAMAGE_vec[i]->Render(Screen::Instance().GetRect().GetBottomLeft()); 
    	}   
    		    	
    	starsystem->RestoreSceneColor();
}
    

	
  
void Player::RenderInSpace_OLD(StarSystem* starsystem)
{   
	glLoadIdentity();
        starsystem->DrawBackground(Screen::Instance().GetRect().GetBottomLeft());
	
        camera(Screen::Instance().GetRect().GetBottomLeft().x, Screen::Instance().GetRect().GetBottomLeft().y);
        
        disable_BLEND();
        enable_DEPTH();
		for(unsigned int i=0; i<visible_STAR_vec.size(); i++) 
		{ 
        		visible_STAR_vec[i]->Render_OLD(); 
    		}

    		for(unsigned int i=0; i<visible_PLANET_vec.size(); i++) 
    		{ 
       			visible_PLANET_vec[i]->Render_OLD(); 
    		}

    		for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)
    		{ 
       			visible_ASTEROID_vec[i]->Render_OLD(); 
    		}

            	for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)
		{ 
        		visible_BLACKHOLE_vec[i]->Render_OLD(); 
    		}    		
        disable_DEPTH();

        enable_BLEND();
                for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)
    		{ 
    			visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       			visible_SPACESTATION_vec[i]->RenderInSpace(); 
        		starsystem->RestoreSceneColor();
    		}
           
    		for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)
    		{ 
        		visible_CONTAINER_vec[i]->Render2D(); 
    		} 	 
           
    		for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)
    		{ 
       			visible_SHIP_vec[i]->RenderInSpace(); 
        		starsystem->RestoreSceneColor();
    		}

		for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)
    		{ 
    			visible_SATELLITE_vec[i]->UpdateRenderStuff(); 
       			visible_SATELLITE_vec[i]->RenderInSpace(); 
        		starsystem->RestoreSceneColor();
                }
                        
    		for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)
    		{ 
                        visible_ROCKET_vec[i]->UpdateRenderStuff();
       			visible_ROCKET_vec[i]->RenderInSpace(); 
                        starsystem->RestoreSceneColor();
    		}

    		for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		visible_effect_LAZERTRACE_vec[i]->Render(); 
    		}
    	disable_BLEND();


	enable_BLEND();
        	enable_POINTSPRITE();
    			for(unsigned int i=0; i<visible_effect_PARTICLESYSTEM_vec.size(); i++)
    			{ 
        			visible_effect_PARTICLESYSTEM_vec[i]->Render(); 
    			}
        	disable_POINTSPRITE();        	
        disable_BLEND();

	// text
        for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    	{ 
        	visible_text_DAMAGE_vec[i]->Render(Screen::Instance().GetRect().GetBottomLeft()); 
    	}    		
              
    	starsystem->RestoreSceneColor();
}


void Player::RenderInSpace(StarSystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{    	
    	if (Config::Instance().MODERN_EFFECTS == true)
    	{
    		RenderInSpace_NEW(starsystem);
    	}
    	else
    	{
        	RenderInSpace_OLD(starsystem); 
        }        

	enable_BLEND();              
        	if (turn_ended == true)
        	{
        		if (forceDraw_orbits == true)
        		{
                		starsystem->DrawOrbits();
        		}
        
        		if (forceDraw_path == true)
        		{
                		starsystem->DrawPath();
        		}
       	 		npc->GetVehicle()->GetDriveComplex().DrawPath();
       			npc->GetVehicle()->GetWeaponComplex().RenderWeaponsRange();
       			npc->GetVehicle()->GetWeaponComplex().RenderWeaponIcons(); 
       	
        		if (show.GetRangeRadar() == true)
        		{
        			npc->GetVehicle()->RenderRadarRange();
        		}

			if ( (npc->GetVehicle()->GetGrappleSlot()->GetEquiped() == true) and (npc->GetVehicle()->GetGrappleSlot()->GetSelected() == true) )
        		{
        			npc->GetVehicle()->RenderGrappleRange();
        		}
		}
	
		cursor.RenderFocusedSpaceObjectStuff();   // perform this function the last, because it resets previos Gl transform
	disable_BLEND();  
} 

bool Player::MouseInteractionWithSpaceObjectsInSpace(const MouseData& data_mouse) 
{
	/* NOTE: the intersection must be checked in order from small objects to huge */	
    	if (MouseInteractionWithRockets(data_mouse)) { return true; }
    	if (MouseInteractionWithContainers(data_mouse)) { return true; }
    	if (MouseInteractionWithSatellites(data_mouse)) { return true; }
    	if (MouseInteractionWithAsteroids(data_mouse)) { return true; }
    	if (MouseInteractionWithShips(data_mouse)) { return true; }	
    	if (MouseInteractionWithBlackHoles(data_mouse)) { return true; }	
    	if (MouseInteractionWithSpaceStations(data_mouse)) { return true; }	
    	if (MouseInteractionWithPlanets(data_mouse)) { return true; }    
    	if (MouseInteractionWithStars(data_mouse)) { return true; }    
}

bool Player::MouseInteractionWithRockets(const MouseData& data_mouse)
{
	for (unsigned int i=0; i<visible_ROCKET_vec.size(); i++)
       	{ 
            	float object_cursor_dist = distBetweenPoints(visible_ROCKET_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
            	if (object_cursor_dist < visible_ROCKET_vec[i]->GetCollisionRadius())
            	{ 
            		cursor.SetFocusedSpaceObject(visible_ROCKET_vec[i]);
               
               		if (data_mouse.left_click == true)
               		{
               			if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
               			{
               				npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_ROCKET_vec[i]);
               			}
               			else
               			{
               				npc->GetVehicle()->GetDriveComplex().SetTarget(visible_ROCKET_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
               			}
			}
				
                	return true; 
            	}
        }
        
        return false;
}

bool Player::MouseInteractionWithContainers(const MouseData& data_mouse)
{
       	for (unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_CONTAINER_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (object_cursor_dist < visible_CONTAINER_vec[i]->GetCollisionRadius())
            	{   
			cursor.SetFocusedSpaceObject(visible_CONTAINER_vec[i]);
			            		
      			if (data_mouse.left_click == true)
       			{          					    
               			npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_CONTAINER_vec[i]);
      			}
       			if (data_mouse.right_click == true)
   			{
      				if (npc->GetVehicle()->GetPropetries().grab_radius > 0)
      				{
       					if (npc->GetVehicle()->GetGrappleSlot()->CheckTarget(visible_CONTAINER_vec[i]) == true)
       					{
       						if (npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->CheckIfTargetAlreadyExistInQueue(visible_CONTAINER_vec[i]) == false)
       						{
       							npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(visible_CONTAINER_vec[i]);
       						}
       						else
       						{
       							npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->RemoveTarget(visible_CONTAINER_vec[i]);
       						}
       					}       						
       				}
       			}

 					
       			return true; 
          	}
        	
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithSatellites(const MouseData& data_mouse)
{
	for (unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)
	{ 
            	float object_cursor_dist = distBetweenPoints(visible_SATELLITE_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
            	if (object_cursor_dist < visible_SATELLITE_vec[i]->GetCollisionRadius())
            	{ 
            	       	cursor.SetFocusedSpaceObject(visible_SATELLITE_vec[i]);
                
               		if (data_mouse.left_click == true)
               		{
               			if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
               			{
               				npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_SATELLITE_vec[i]);
              			}
              			else
               			{
               				npc->GetVehicle()->GetDriveComplex().SetTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
               			}
			}

               		if (data_mouse.right_click == true)
               		{
               			if ( (npc->GetVehicle()->GetGrappleSlot()->GetEquiped() == true) and (npc->GetVehicle()->GetGrappleSlot()->GetSelected() == true) )
               			{
       					//if (pPLAYER->GetVehicle()->ableTo.GRAB == true)
       					//{
       						//pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_SATELLITE_vec[i]);
       						//pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();	       						
       					//}
               			}
               			else
               			{
               			        if ( npc->CheckPossibilityToScan(visible_SATELLITE_vec[i]) == true )
               				{
                      				npc->SetScanTarget(visible_SATELLITE_vec[i]);
                      				gui_manager.GetGuiVehicleScan().BindVehicle(visible_SATELLITE_vec[i]);
               				}

      				}
       			}
						
               		return true; 
            	}
        }
    	
    	return false;
}

bool Player::MouseInteractionWithAsteroids(const MouseData& data_mouse)
{
       	for (unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_ASTEROID_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (object_cursor_dist < visible_ASTEROID_vec[i]->GetCollisionRadius())
       		{   
                        cursor.SetFocusedSpaceObject(visible_ASTEROID_vec[i]);        
                        //visible_ASTEROID_vec[i]->GetOrbit()->Draw();
			
			
                	if (data_mouse.left_click == true)
			{
                	        if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
                		{
                   			npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_ASTEROID_vec[i]);
                   		}
                   		else
                   		{
                   			npc->GetVehicle()->GetDriveComplex().SetTarget(visible_ASTEROID_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   		}
                   	}
			
                		
                	return true; 
            	}
        	
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithShips(const MouseData& data_mouse)
{
	for (unsigned int i=0; i<visible_SHIP_vec.size(); i++)
	{ 
        	float object_cursor_dist = distBetweenPoints(visible_SHIP_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
        	if (object_cursor_dist < visible_SHIP_vec[i]->GetCollisionRadius())
        	{ 
               		cursor.SetFocusedSpaceObject(visible_SHIP_vec[i]);    
                
                	if (npc->GetVehicle()->GetId() != visible_SHIP_vec[i]->GetId())
               		{
               			if (data_mouse.left_click == true)
               			{
               				if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
               				{
               					npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_SHIP_vec[i]);
               				}
               				else
               				{
               					npc->GetVehicle()->GetDriveComplex().SetTarget(visible_SHIP_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
               				}
				}

               			if (data_mouse.right_click == true)
               			{
               				if ( (npc->GetVehicle()->GetGrappleSlot()->GetEquiped() == true) and (npc->GetVehicle()->GetGrappleSlot()->GetSelected() == true) )
               				{
						//if (npc->GetVehicle()->ableTo.GRAB == true)
		       				//{
		       					//if (npc->GetVehicle()->GetGrappleSlot()->CheckTarget(visible_SHIP_vec[i]) == true)
		       					//{
		       						//npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(visible_SHIP_vec[i]);
		       					//}					
		       				//}
	                		}
	                		else
	                		{
	                      		        if (npc->CheckPossibilityToScan(visible_SHIP_vec[i]) == true)
	                			{
	                				if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == false)
	                				{
	                      					npc->SetScanTarget(visible_SHIP_vec[i]);
	                      					gui_manager.GetGuiVehicleScan().BindVehicle(visible_SHIP_vec[i]);
	                				}                			
	                				else
	                				{
	               						gui_manager.GetGuiVehicleTarget().BindVehicle(visible_SHIP_vec[i], 0.6f);
	                				}
	                			}
	       				}
       				}
       			}
       			else
       			{
       				if (data_mouse.right_click == true)
               			{
               				npc->SetScanTarget(visible_SHIP_vec[i]);
	                      		gui_manager.GetGuiVehicleScan().BindVehicle(visible_SHIP_vec[i]);
               			}
       			}
						
               		return true; 
            	}
        }
    	
	return false;
}

bool Player::MouseInteractionWithBlackHoles(const MouseData& data_mouse)
{
       	for (unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)
       	{ 
       		float cursor_dist = distBetweenPoints(visible_BLACKHOLE_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (cursor_dist < visible_BLACKHOLE_vec[i]->GetCollisionRadius())
       		{   
       			cursor.SetFocusedSpaceObject(visible_BLACKHOLE_vec[i]); 
       			
       			return true;
      		}
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithSpaceStations(const MouseData& data_mouse)
{
	for (unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)
	{ 
       		float object_cursor_dist = distBetweenPoints(visible_SPACESTATION_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (object_cursor_dist < visible_SPACESTATION_vec[i]->GetCollisionRadius())
            	{ 
                	cursor.SetFocusedSpaceObject(visible_SPACESTATION_vec[i]); 
                
               		if (data_mouse.left_click == true)
               		{
               			if (npc->GetVehicle()->GetWeaponComplex().IsAnyWeaponSelected() == true)
               			{
               				npc->GetVehicle()->GetWeaponComplex().SetTarget(visible_SPACESTATION_vec[i]);
               			}
               			else
               			{
               				Task microtask(MICROSCENARIO::DOCKING_ID, visible_SPACESTATION_vec[i]->GetId());
               				npc->GetStateMachine().SetCurrentMicroTask(microtask);
               			}
			}

               		if (data_mouse.right_click == true)
               		{
               			if ( (npc->GetVehicle()->GetGrappleSlot()->GetEquiped() == true) and (npc->GetVehicle()->GetGrappleSlot()->GetSelected() == true) )
               			{
					//if (pPLAYER->GetVehicle()->ableTo.GRAB == true)
					//{
						//pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_STARBASE_vec[i]);
						//pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();	       						
					//}
               			}
               			else
               			{
               			        if ( npc->CheckPossibilityToScan(visible_SPACESTATION_vec[i]) == true )
               				{
                      				npc->SetScanTarget(visible_SPACESTATION_vec[i]);
                      				gui_manager.GetGuiVehicleScan().BindVehicle(visible_SPACESTATION_vec[i]);
               				}
       				}
       			}
			
               		return true; 
            	}
        }
        
        return false;
}

bool Player::MouseInteractionWithPlanets(const MouseData& data_mouse)
{
       	for (unsigned int i=0; i<visible_PLANET_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_PLANET_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (object_cursor_dist < visible_PLANET_vec[i]->GetCollisionRadius())
            	{   
                	cursor.SetFocusedSpaceObject(visible_PLANET_vec[i]); 
          
               		if (data_mouse.left_click == true)
               		{
       				Task microtask(MICROSCENARIO::DOCKING_ID, visible_PLANET_vec[i]->GetId());
              			npc->GetStateMachine().SetCurrentMicroTask(microtask);
              		}   
		
				
                	return true; 
            	}
        }
    
    	return false;
}

bool Player::MouseInteractionWithStars(const MouseData& data_mouse)
{
       	for (unsigned int i=0; i<visible_STAR_vec.size(); i++)
       	{ 
      		float object_cursor_dist = distBetweenPoints(visible_STAR_vec[i]->GetPoints().GetCenter(), data_mouse.mxvp, data_mouse.myvp);
       		if (object_cursor_dist < visible_STAR_vec[i]->GetCollisionRadius())
       		{   
                	cursor.SetFocusedSpaceObject(visible_STAR_vec[i]); 
                	
       			return true; 
        	}
    	}
    	
    	return false;
}

void Player::MouseNavigation(const MouseData& data_mouse) const
{
	if (data_mouse.left_click == true)
	{
		ForceStateMachineReset();
		npc->GetVehicle()->GetDriveComplex().SetStaticTargetCoords(vec2f(data_mouse.mxvp, data_mouse.myvp));  
	}
}

bool Player::IsObjectOnScreen(const Points& points) const
{      
        if (points.GetCenter().x < (Screen::Instance().GetRect().GetBottomLeft().x - points.GetWidth()))
                return false;
        if (points.GetCenter().x > (Screen::Instance().GetRect().GetTopRight().x   + points.GetWidth()))
                return false;
        if (points.GetCenter().y < (Screen::Instance().GetRect().GetBottomLeft().y - points.GetHeight()))
                return false;
        if (points.GetCenter().y > (Screen::Instance().GetRect().GetTopRight().y   + points.GetHeight()))
                return false;

        return true;
}

bool Player::IsObjectOnScreen(const vec2f& ob_center, float sizeInPixels) const
{       
        if (ob_center.x < (Screen::Instance().GetRect().GetBottomLeft().x - sizeInPixels))
                return false;
        if (ob_center.x > (Screen::Instance().GetRect().GetTopRight().x + sizeInPixels))
                return false;
        if (ob_center.y < (Screen::Instance().GetRect().GetBottomLeft().y - sizeInPixels))
                return false;
        if (ob_center.y > (Screen::Instance().GetRect().GetTopRight().y + sizeInPixels))
                return false;

        return true;
}


void Player::SessionInSpace(StarSystem* starsystem, const TurnTimer& turn_timer)
{	
	starsystem->FindRenderVisibleEntities_c(this);
	if (getRandInt(1,5) == 1)
	{
		starsystem->FindRadarVisibleEntities_c(this);
	}
	
	RenderInSpace(starsystem, turn_timer.GetTurnEnded(), show.GetAllOrbits(), show.GetAllPath()); 
    	     	
	bool mouse_interaction = gui_manager.RunSession(cursor.GetMouseData()); 
	if (mouse_interaction == false)
	{    	
		if (turn_timer.GetTurnEnded() == true)  
		{
			if ( (npc->GetScanTarget() == NULL) && (show.GetGuiGalaxyMap() == false) )
			{
				mouse_interaction = MouseInteractionWithSpaceObjectsInSpace(cursor.GetMouseData());  
				//mouse_interaction = cursor.UpdateInSpace();
				if (mouse_interaction == false)
				{	
					MouseNavigation(cursor.GetMouseData());  
				}
			}
		}
	}
}


void Player::SessionInKosmoport()
{   	
	gui_manager.RunSession(cursor.GetMouseData());        
}

void Player::RunSession(const TurnTimer& turn_timer)
{
	cursor.UpdateMouseStuff();
	
       	switch(npc->GetVehicle()->GetPlaceTypeId())
       	{
       		case ENTITY::SPACE_ID: 		{ SessionInSpace(npc->GetVehicle()->GetStarSystem(), turn_timer); break; }
       		case ENTITY::HYPER_SPACE_ID: 	{ SessionInSpace((StarSystem*)npc->GetVehicle()->GetDriveComplex().GetTarget(), turn_timer); break; }
       		case ENTITY::KOSMOPORT_ID:  	{ SessionInKosmoport(); break; }
       	}        	
       	
       	Screen::Instance().Draw();
}

void Player::ForceStateMachineReset() const
{
	npc->GetStateMachine().ForceReset();
}     		

void Player::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "player."+int2str(data_id.id)+".";
	
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniquePlayer(save_ptree, root);	
}		

void Player::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniquePlayer(load_ptree);	   
}        

void Player::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniquePlayer();	
}
		
void Player::SaveDataUniquePlayer(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
        save_ptree.put(root+"unresolved.npc_id", npc->GetId());
        save_ptree.put(root+"unresolved.screen_pos_x", Screen::Instance().GetRect().GetBottomLeft().x);
        save_ptree.put(root+"unresolved.screen_pos_y", Screen::Instance().GetRect().GetBottomLeft().y);
}

void Player::LoadDataUniquePlayer(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_player.npc_id = load_ptree.get<int>("unresolved.npc_id");
	data_unresolved_player.screen_pos.x = load_ptree.get<float>("unresolved.screen_pos_x");
	data_unresolved_player.screen_pos.y = load_ptree.get<float>("unresolved.screen_pos_y");
}

void Player::ResolveDataUniquePlayer()
{
        BindNpc((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_player.npc_id));
        Screen::Instance().GetRect().SetBottomLeft(data_unresolved_player.screen_pos);
}		


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

#include "../config/config.hpp"


WeaponSelector::WeaponSelector()
{
	for (unsigned int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		state[i] = false;
	}
}
     	
void WeaponSelector::SetSingle(unsigned int index, bool status)
{
	if (index > GAME::WEAPONS_NUM_MAX )
	{
		assert("WeaponSelector::SetSingle(), index is out of range");
	}
	state[index-1] = status;
}

bool WeaponSelector::GetSingle(unsigned int index) const
{
	if (index > GAME::WEAPONS_NUM_MAX )
	{
		assert("WeaponSelector::GetSingle(), index is out of range");
	}
	return state[index-1];
}
     			
void WeaponSelector::SetAll(bool status)
{
	for (unsigned int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		state[i] = status;
	}
}
   			
bool WeaponSelector::IsAllTrue() const
{
	for (unsigned int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		if (state[i] == false)
		{
			return false;
		}
	}
	return true;
}



Player::Player(int id)
{ 
    	data_id.id         = id;
    	data_id.type_id    = ENTITY::PLAYER_ID;
        data_id.subtype_id = NONE_ID;
   	
    	npc  = NULL;
    	cursor = new Cursor(this);
    	screen = new Screen();
    	
    	GUI_MANAGER    = new GuiManager(this);
 	GUI_SPACE      = new GuiSpace(this);
 	GUI_KOSMOPORT  = new GuiKosmoport(this);
	GUI_MAP        = new GuiMap(this); 
    	
    	show_all_orbit     = false;
     	show_all_path      = false;
     	show_radar_range   = false;
     	show_grapple_range = false;
}
    
Player::~Player()
{
	delete cursor;
	delete screen;
	
	delete GUI_MANAGER;
 	delete GUI_SPACE;
 	delete GUI_KOSMOPORT;
	delete GUI_MAP;
}  
            
void Player::UpdateGlobal()
{
	if (npc->GetAlive() == true)
	{       	
		//npc->GetVehicle()->GetWeaponComplex()->weapon_selector = weapon_selector;
	}
}  
               			
void Player::BindNpc(Npc* npc)
{
    	this->npc = npc;
    	npc->SetUpperControl(true);
}

void Player::ClearVisibleEntities()
{
        visible_STAR_vec.clear();
        visible_PLANET_vec.clear();
        visible_SPACESTATION_vec.clear();
        visible_SATELLITE_vec.clear();
        
        visible_ASTEROID_vec.clear();
        visible_CONTAINER_vec.clear();

        visible_SHIP_vec.clear();
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
                //if ( distBetweenPoints(asteroid->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_ASTEROID_vec.push_back(asteroid);
                }
        }
}

void Player::AddIfVisible(Container* container)     	
{
        if (IsObjectOnScreen(container->GetPoints()))
        {    
        	//if ( distBetweenPoints(container->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_CONTAINER_vec.push_back(container);
                }
	}
}

void Player::AddIfVisible(RocketBullet* rocket)  
{
        if (IsObjectOnScreen(rocket->GetPoints()))  
        {  
             	//if ( distBetweenPoints(rocket->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
        		visible_ROCKET_vec.push_back(rocket);
        	}
        }
}

void Player::AddIfVisible(BlackHole* blackhole)  
{
        if (IsObjectOnScreen(blackhole->GetPoints()))  
        {  
        	//if ( distBetweenPoints(blackhole->getPoints()->getCenter(), player_center) < player_vision_radius )
        	{
                	visible_BLACKHOLE_vec.push_back(blackhole);
		}
	}
}

void Player::AddIfVisible(SpaceStation* spacestation)  
{
        if (IsObjectOnScreen(spacestation->GetPoints()))  
        {	  
                //if ( distBetweenPoints(spacestation->getPoints()->getCenter(), player_center) < player_vision_radius )
               	{
        		visible_SPACESTATION_vec.push_back(spacestation);
        	}
        }
}

void Player::AddIfVisible(Satellite* satellite) 
{
        if (IsObjectOnScreen(satellite->GetPoints()))  
        {	  
        	//if ( distBetweenPoints(satellite->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
        		visible_SATELLITE_vec.push_back(satellite);
        	}
        }
}

void Player::AddIfVisible(Ship* ship) 
{
        if (IsObjectOnScreen(ship->GetPoints()))
        {	  
                //if ( distBetweenPoints(ship->getPoints()->getCenter(), player_center) < player_vision_radius )
               	{
			visible_SHIP_vec.push_back(ship);
		}
	}
}     		
        
void Player::AddIfVisible(ShockWaveEffect* effect)
{
	visible_effect_SHOCKWAVE_vec.push_back(effect);
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

  
void Player::RenderEntities_NEW()
{   
	int w = screen->getWidth();
	int h = screen->getHeight();

	screen->getFbo0()->activate(screen);
   
        	npc->GetStarSystem()->DrawBackground(screen->getBottomLeftGlobalCoord());           
		camera(screen->getBottomLeftGlobalCoord().x, screen->getBottomLeftGlobalCoord().y);    
	        

		npc->GetStarSystem()->RestoreDefaultColor();
		enable_BLEND();
			for(unsigned int i = 0; i < visible_STAR_vec.size(); i++) 
			{ 
        			visible_STAR_vec[i]->Render_NEW(); 
    			}
    		disable_BLEND();
		npc->GetStarSystem()->RestoreSceneColor();
	screen->getFbo0()->deactivate();

	// POST PROCESS BLOOM (many FBO)
	screen->getBloom()->pass0(screen, screen->getFbo0()->getTexture(), visible_STAR_vec[0]->GetBrightThreshold());
	screen->getBloom()->restPasses(screen);
	screen->getBloom()->combine(screen, screen->getFbo0()->getTexture());

	// RENDER to FBO1, VOLUMETRIC LIGHT
	screen->getFbo1()->activate(screen);
		glUseProgram(g_SHADERS.volumetriclight);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, screen->getBloom()->pTo_fbo_final->getTexture());
			glUniform1i(glGetUniformLocation(g_SHADERS.volumetriclight, "FullSampler"), 0);

			glActiveTexture(GL_TEXTURE1);                                
			glBindTexture(GL_TEXTURE_2D, screen->getBloom()->texture_blured);
			glUniform1i(glGetUniformLocation(g_SHADERS.volumetriclight, "BlurSampler"), 1);

			glUniform4f(glGetUniformLocation(g_SHADERS.volumetriclight, "sun_pos"), -screen->getBottomLeftGlobalCoord().x/w, -screen->getBottomLeftGlobalCoord().y/h, -100.0, 1.0);
          
			glActiveTexture(GL_TEXTURE0);
			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
	screen->getFbo1()->deactivate();


	screen->getFbo2()->activate(screen);
		drawFullScreenTexturedQuad(screen->getFbo1()->getTexture(), w, h, -999.0);
           
          	camera(screen->getBottomLeftGlobalCoord().x, screen->getBottomLeftGlobalCoord().y);    
        
		enable_DEPTH();  
    			for(unsigned int i = 0; i < visible_PLANET_vec.size(); i++) 
    			{ 
       				visible_PLANET_vec[i]->Render_NEW(screen->getBottomLeftGlobalCoord()); 
    			}
    		
    			for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    			{ 
       				visible_ASTEROID_vec[i]->Render_NEW(screen->getBottomLeftGlobalCoord()); 
    			}
    		disable_DEPTH();

    	          
		enable_BLEND();		
		    	for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    			{ 
    				visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       				visible_SPACESTATION_vec[i]->RenderInSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}
    			
    			for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
			{ 
        			visible_BLACKHOLE_vec[i]->Render2D(); 
    			}  		
   
    			for(unsigned int i = 0; i < visible_CONTAINER_vec.size(); i++)
    			{ 
        			visible_CONTAINER_vec[i]->Render2D(); 
    			} 	 
           

    			for(unsigned int i = 0; i < visible_SHIP_vec.size(); i++)
    			{ 
    				visible_SHIP_vec[i]->UpdateRenderStuff(); 
       				visible_SHIP_vec[i]->RenderInSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}

			for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    			{ 
    				visible_SATELLITE_vec[i]->UpdateRenderStuff(); 
       				visible_SATELLITE_vec[i]->RenderInSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}
    			
    			for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    			{ 
    			    	visible_ROCKET_vec[i]->UpdateRenderStuff();
       				visible_ROCKET_vec[i]->RenderInSpace(); 
       				npc->GetStarSystem()->RestoreSceneColor();
    			}    	
		disable_BLEND();
		
    	screen->getFbo2()->deactivate();


	// POST PROCESS WAVE SHOCK into FBO2
	screen->getFbo3()->activate(screen);

		float center_array[10][2];
		float xyz_array[10][3];
		float time_array[10];

		for (unsigned int i = 0; i < visible_effect_SHOCKWAVE_vec.size(); i++)
		{         
			center_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->center.x/w - screen->getBottomLeftGlobalCoord().x/w;
			center_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->center.y/h - screen->getBottomLeftGlobalCoord().y/h;
			xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->parameter.x;
			xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->parameter.y;
			xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[i]->parameter.z;
				
			time_array[i] = visible_effect_SHOCKWAVE_vec[i]->time;
		}
       

		glUseProgram(g_SHADERS.shockwave);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, screen->getFbo2()->getTexture());
			glUniform1i (glGetUniformLocation(g_SHADERS.shockwave, "sceneTex"), 0);

			int len_effect_SHOCKWAVE_list = visible_effect_SHOCKWAVE_vec.size();
			glUniform1i (glGetUniformLocation(g_SHADERS.shockwave, "imax"),        len_effect_SHOCKWAVE_list);
			glUniform2fv(glGetUniformLocation(g_SHADERS.shockwave, "center"),      len_effect_SHOCKWAVE_list, *center_array);
			glUniform3fv(glGetUniformLocation(g_SHADERS.shockwave, "shockParams"), len_effect_SHOCKWAVE_list, *xyz_array);
			glUniform1fv(glGetUniformLocation(g_SHADERS.shockwave, "time"),        len_effect_SHOCKWAVE_list, time_array);

			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
	
	screen->getFbo3()->deactivate();


	// render from FBO
	glEnable(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);      // unbind fbo

	clearScreen();
	resetRenderTransformation();

	drawFullScreenTexturedQuad(screen->getFbo3()->getTexture(), w, h, -999.0);
	//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug

	camera(screen->getBottomLeftGlobalCoord().x, screen->getBottomLeftGlobalCoord().y);
	
	enable_BLEND();
		for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		visible_effect_LAZERTRACE_vec[i]->Render(); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i < visible_effect_PARTICLESYSTEM_vec.size(); i++)
    			{ 
        			visible_effect_PARTICLESYSTEM_vec[i]->Render(); 
    			}
    		disable_POINTSPRITE();
    		
    		for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    		{ 
        		visible_text_DAMAGE_vec[i]->Render(screen->getBottomLeftGlobalCoord()); 
    		}    		
    		
    	disable_BLEND();
    	
    	npc->GetStarSystem()->RestoreSceneColor();    	          
}
    

	
  
void Player::RenderEntities_OLD()
{   
	glLoadIdentity();
        npc->GetStarSystem()->DrawBackground(screen->getBottomLeftGlobalCoord());
	
        camera(screen->getBottomLeftGlobalCoord().x, screen->getBottomLeftGlobalCoord().y);
        
        disable_BLEND();
        enable_DEPTH();
		for(unsigned int i = 0; i < visible_STAR_vec.size(); i++) 
		{ 
        		visible_STAR_vec[i]->Render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_PLANET_vec.size(); i++) 
    		{ 
       			visible_PLANET_vec[i]->Render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    		{ 
       			visible_ASTEROID_vec[i]->Render_OLD(); 
    		}
        disable_DEPTH();

        enable_BLEND();
                for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    		{ 
    			visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       			visible_SPACESTATION_vec[i]->RenderInSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
    		}
                        
            	for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
		{ 
        		visible_BLACKHOLE_vec[i]->Render2D(); 
    		}  	
           
    		for(unsigned int i = 0; i < visible_CONTAINER_vec.size(); i++)
    		{ 
        		visible_CONTAINER_vec[i]->Render2D(); 
    		} 	 
           
    		for(unsigned int i = 0; i < visible_SHIP_vec.size(); i++)
    		{ 
    		    	visible_SHIP_vec[i]->UpdateRenderStuff();
       			visible_SHIP_vec[i]->RenderInSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
    		}

		for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    		{ 
    			visible_SATELLITE_vec[i]->UpdateRenderStuff(); 
       			visible_SATELLITE_vec[i]->RenderInSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
                }
                        
    		for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    		{ 
                        visible_ROCKET_vec[i]->UpdateRenderStuff();
       			visible_ROCKET_vec[i]->RenderInSpace(); 
                        npc->GetStarSystem()->RestoreSceneColor();
    		}

    		for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		visible_effect_LAZERTRACE_vec[i]->Render(); 
    		}
    	disable_BLEND();


	enable_BLEND();
        	enable_POINTSPRITE();
    			for(unsigned int i = 0; i < visible_effect_PARTICLESYSTEM_vec.size(); i++)
    			{ 
        			visible_effect_PARTICLESYSTEM_vec[i]->Render(); 
    			}
        	disable_POINTSPRITE();
        disable_BLEND();

        for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    	{ 
        	visible_text_DAMAGE_vec[i]->Render(screen->getBottomLeftGlobalCoord()); 
    	}    		
    		
                
    	npc->GetStarSystem()->RestoreSceneColor();
}


void Player::Render(bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{
    	
    	if (Config::Instance().MODERN_EFFECTS == true)
    	{
    		RenderEntities_NEW();
    	}
    	else
    	{
        	RenderEntities_OLD(); 
        }
                
        if (turn_ended == true)
        {
        	if (forceDraw_orbits == true)
        	{
                	npc->GetStarSystem()->DrawOrbits();
        	}
        
        	if (forceDraw_path == true)
        	{
                	npc->GetStarSystem()->DrawPath();
        	}
       	 	npc->GetVehicle()->GetDriveComplex()->drawPath();
       		npc->GetVehicle()->GetWeaponComplex()->RenderWeaponsRange();
       	
        	if (GetShowRadarRange() == true)
        	{
        		npc->GetVehicle()->RenderRadarRange();
        	}

        	if (GetShowGrappleRange() == true)
        	{
        		npc->GetVehicle()->RenderGrappleRange();
        	}
	}
} 

void Player::MouseInteractionInSpace() // all large objects must be cheked by last
{   
    	bool cursor_has_target = false;   
 
    	int mxvp = cursor->GetMousePos().x                       + screen->getBottomLeftGlobalCoord().x;
    	int myvp = screen->getHeight() - cursor->GetMousePos().y + screen->getBottomLeftGlobalCoord().y;

    	bool mlb = cursor->GetMouseLeftButton();
    	bool mrb = cursor->GetMouseRightButton();

	if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
	{
    		npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);                   				       
        	npc->GetVehicle()->GetWeaponComplex()->RenderWeaponIcons();
        }


	/* NOTE: the intersection must be checked in order from small objects to huge */	
    	if (MouseInteractionWithRockets(mxvp, myvp, mlb, mrb)) { return; }
    	if (MouseInteractionWithContainers(mxvp, myvp, mlb, mrb)) { return; }
    	if (MouseInteractionWithSatellites(mxvp, myvp, mlb, mrb)) { return; }
    	if (MouseInteractionWithAsteroids(mxvp, myvp, mlb, mrb)) { return; }
    	if (MouseInteractionWithShips(mxvp, myvp, mlb, mrb)) { return; }	
    	if (MouseInteractionWithBlackHoles(mxvp, myvp, mlb, mrb)) { return; }	
    	if (MouseInteractionWithSpaceStations(mxvp, myvp, mlb, mrb)) { return; }	
    	if (MouseInteractionWithPlanets(mxvp, myvp, mlb, mrb)) { return; }    

	MouseNavigation(mxvp, myvp, mlb, mrb);  
}

bool Player::MouseInteractionWithRockets(int mxvp, int myvp, bool mlb, bool mrb) const
{
	for (unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
       	{ 
            	float object_cursor_dist = distBetweenPoints(visible_ROCKET_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
            	if (object_cursor_dist < visible_ROCKET_vec[i]->GetCollisionRadius())
            	{ 
               		visible_ROCKET_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
               
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                			if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                			{
                   				npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_ROCKET_vec[i]);
                   			}
                   			else
                   			{
                   				npc->GetVehicle()->GetDriveComplex()->setTarget(visible_ROCKET_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   				npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   			}
				}
			}
				
                	return true; 
            	}
        }
        
        return false;
}

bool Player::MouseInteractionWithContainers(int mxvp, int myvp, bool mlb, bool mrb) const
{
       	for (unsigned int i = 0; i < visible_CONTAINER_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_CONTAINER_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (object_cursor_dist < visible_CONTAINER_vec[i]->GetCollisionRadius())
            	{   
               		visible_CONTAINER_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 

			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
               			if (mlb == true)
               			{
                			npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);                   					    
                			npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_CONTAINER_vec[i]);
               			}
               			if (mrb == true)
	       			{
	       				if (npc->GetVehicle()->ableTo.GRAB == true)
	       				{
	       					npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(visible_CONTAINER_vec[i]);
	       					npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->ValidateTargets();
	       					printf("CONTAINER with id = %i HAS BEEN MARKED\n", visible_CONTAINER_vec[i]->GetId());	       						
	       				}
	       			}
 			}
 					
               		return true; 
            	}
        	
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithSatellites(int mxvp, int myvp, bool mlb, bool mrb) const
{
	for (unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
	{ 
            	float object_cursor_dist = distBetweenPoints(visible_SATELLITE_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
            	if (object_cursor_dist < visible_SATELLITE_vec[i]->GetCollisionRadius())
            	{ 
            	      	visible_SATELLITE_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
                	visible_SATELLITE_vec[i]->GetWeaponComplex()->RenderWeaponIcons();

                	visible_SATELLITE_vec[i]->RenderRadarRange(); 
                	visible_SATELLITE_vec[i]->GetWeaponComplex()->RenderWeaponsRange(); 
                		                                
                        visible_SATELLITE_vec[i]->GetDriveComplex()->drawPath(); 
                
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                			if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                			{
                   				npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_SATELLITE_vec[i]);
                   			}
                   			else
                   			{
                   				npc->GetVehicle()->GetDriveComplex()->setTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
                   				npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   			}
				}

                		if (mrb == true)
                		{
                			if (GetShowGrappleRange() == true)
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
                   				}

	       				}
	       			}
			}
				
                	return true; 
            	}
        }
    	
    	return false;
}

bool Player::MouseInteractionWithAsteroids(int mxvp, int myvp, bool mlb, bool mrb) const
{
       	for (unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_ASTEROID_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (object_cursor_dist < visible_ASTEROID_vec[i]->GetCollisionRadius())
       		{   
                	visible_ASTEROID_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
                                
                        visible_ASTEROID_vec[i]->GetOrbit()->Draw();

			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
				{
                		        if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                			{
                   				npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_ASTEROID_vec[i]);
                   			}
                   			else
                   			{
                   				npc->GetVehicle()->GetDriveComplex()->setTarget(visible_ASTEROID_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   				npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   			}
                   		}
                	}
                		
                	return true; 
            	}
        	
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithShips(int mxvp, int myvp, bool mlb, bool mrb) const
{
	for (unsigned int i = 0; i < visible_SHIP_vec.size(); i++)
	{ 
        	float object_cursor_dist = distBetweenPoints(visible_SHIP_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
        	if (object_cursor_dist < visible_SHIP_vec[i]->GetCollisionRadius())
        	{ 
               		visible_SHIP_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
               		visible_SHIP_vec[i]->GetWeaponComplex()->RenderWeaponIcons();

               		visible_SHIP_vec[i]->RenderRadarRange(); 
               		visible_SHIP_vec[i]->GetWeaponComplex()->RenderWeaponsRange(); 
                		                                
                        visible_SHIP_vec[i]->GetDriveComplex()->drawPath(); 
                
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                			if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                			{
                   				npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_SHIP_vec[i]);
                   			}
                   			else
                   			{
                   				npc->GetVehicle()->GetDriveComplex()->setTarget(visible_SHIP_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   				npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   			}
				}

                		if (mrb == true)
                		{
                			if (GetShowGrappleRange() == true)
                			{
	       					if (npc->GetVehicle()->ableTo.GRAB == true)
	       					{
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(visible_SHIP_vec[i]);
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->ValidateTargets();	       						
	       					}
                   			}
                   			else
                   			{
                   			        if ( npc->CheckPossibilityToScan(visible_SHIP_vec[i]) == true )
                   				{
                        				npc->SetScanTarget(visible_SHIP_vec[i]);
                   				}
       					}
       				}
			}
				
               		return true; 
            	}
        }
    	
	return false;
}

bool Player::MouseInteractionWithBlackHoles(int mxvp, int myvp, bool mlb, bool mrb) const
{
       	for (unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
       	{ 
       		float cursor_dist = distBetweenPoints(visible_BLACKHOLE_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (cursor_dist < visible_BLACKHOLE_vec[i]->GetCollisionRadius())
       		{   
       			visible_BLACKHOLE_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
       			
       			return true;
      		}
    	}
    	
    	return false;
}

bool Player::MouseInteractionWithSpaceStations(int mxvp, int myvp, bool mlb, bool mrb) const
{
	for (unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
	{ 
       		float object_cursor_dist = distBetweenPoints(visible_SPACESTATION_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (object_cursor_dist < visible_SPACESTATION_vec[i]->GetCollisionRadius())
            	{ 
            		visible_SPACESTATION_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 
                	visible_SPACESTATION_vec[i]->GetWeaponComplex()->RenderWeaponIcons();

                	visible_SPACESTATION_vec[i]->RenderRadarRange(); 
                	visible_SPACESTATION_vec[i]->GetWeaponComplex()->RenderWeaponsRange(); 
                		                                
                        visible_SPACESTATION_vec[i]->GetDriveComplex()->drawPath(); 
                
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                			if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                			{
                   				npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_SPACESTATION_vec[i]);
                   			}
                   			else
                   			{
                   				npc->GetStateMachine()->setCurrentMicroTask(MICROSCENARIO_DOCKING, visible_SPACESTATION_vec[i]);
                   			}
				}

                		if (mrb == true)
                		{
                			if (GetShowGrappleRange() == true)
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
                   				}
       					}
       				}
			}
				
               		return true; 
            	}
        }
        
        return false;
}

bool Player::MouseInteractionWithPlanets(int mxvp, int myvp, bool mlb, bool mrb) const
{
       	for (unsigned int i = 0; i < visible_PLANET_vec.size(); i++)
       	{ 
       		float object_cursor_dist = distBetweenPoints(visible_PLANET_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (object_cursor_dist < visible_PLANET_vec[i]->GetCollisionRadius())
            	{   
                	visible_PLANET_vec[i]->RenderInfoInSpace(screen->getBottomLeftGlobalCoord()); 

                        visible_PLANET_vec[i]->GetOrbit()->Draw();
          
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                    			//pPLAYER->GetVehicle()->getNavigator()->setTarget(visible_PLANET_vec[pi], DOCKING_NAVIGATOR_ACTION_ID);
                    			//pPLAYER->GetVehicle()->getNavigator()->Update_inSpace_inStatic();  
                    			npc->GetStateMachine()->setCurrentMicroTask(MICROSCENARIO_DOCKING, visible_PLANET_vec[i]);
                		}   
			}
				
                	return true; 
            	}
        }
    
    	return false;
}

bool Player::MouseInteractionWithStars(int mxvp, int myvp, bool mlb, bool mrb) const
{
       	for (unsigned int i = 0; i < visible_STAR_vec.size(); i++)
       	{ 
      		float object_cursor_dist = distBetweenPoints(visible_STAR_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
       		if (object_cursor_dist < visible_STAR_vec[i]->GetCollisionRadius())
       		{   
       			visible_STAR_vec[i]->RenderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

       			return true; 
        	}
    	}
    	
    	return false;
}

void Player::MouseNavigation(int mxvp, int myvp, bool mlb, bool mrb) const
{
	if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
	{
       		if (mlb == true)
       		{
       			npc->GetVehicle()->GetDriveComplex()->setStaticTargetCoords(vec2f(mxvp, myvp));  
      			npc->GetStateMachine()->reset();
      		}
      	}
}

bool Player::IsObjectOnScreen(const Points& points) const
{
        float ob_centerx = points.GetCenter().x;
        float ob_centery = points.GetCenter().y;
        
        int ob_w = points.GetWidth();
        int ob_h = points.GetHeight();
        
        if (ob_centerx < (screen->getBottomLeftGlobalCoord().x - ob_w))
                return false;
        if (ob_centerx > (screen->getTopRightGlobalCoord().x + ob_w))
                return false;
        if (ob_centery < (screen->getBottomLeftGlobalCoord().y - ob_h))
                return false;
        if (ob_centery > (screen->getTopRightGlobalCoord().y + ob_h))
                return false;

        return true;
}


void Player::SessionInSpace(GameTimer* TIMER)
{
	cursor->UpdateMousePos();

	npc->GetStarSystem()->FindVisibleEntities_c(this);
	Render(TIMER->getTurnEnded(), GetShowAllOrbit(), GetShowAllPath()); 

	if (TIMER->getTurnEnded() == true)  
	{
		if ( (npc->GetScanTarget() == NULL) && (GetWorldMapShowFlag() == false) )
		{
			MouseInteractionInSpace();  // improove to exclude all render calls
		}
	}

	//////////// SCAN ///////////////
	if (GetNpc()->GetScanTarget() != NULL )
	{         
		GUI_MANAGER->UpdateInSpace();
		GUI_MANAGER->RenderInScan();                       
	}

	//////////// WORLDMAP ///////////
	if (GetWorldMapShowFlag() == true )  
	{
		GUI_MAP->update();   
		GUI_MAP->Render();   
	}

	GUI_SPACE->update();    
	GUI_SPACE->Render();
}


void Player::SessionInKosmoport()
{
	cursor->UpdateMousePos();
	
	switch(GUI_KOSMOPORT->GetActiveScreenId())
        {
        	case GUI::SCREEN::ANGAR_ID:
        	{
        		((Kosmoport*)npc->GetLand())->GetAngar()->MouseControl(this);                                
               		((Kosmoport*)npc->GetLand())->GetAngar()->Render(this);

			if (npc->GetScanTarget() != NULL) 
			{ 
				GUI_MANAGER->UpdateInAngar();
				GUI_MANAGER->RenderInScan(); 
			}
			else
			{
				((Kosmoport*)npc->GetLand())->GetAngar()->RenderItemInfo(this);
			}
			
			break;
		}
		
		case GUI::SCREEN::STORE_ID:
        	{
        		//if (npc->GetScanTarget() != npc->GetVehicle())
        		{
        			GetNpc()->SetScanTarget(npc->GetVehicle());
        		}
                                    
        		GUI_MANAGER->UpdateInStore();
                	GUI_MANAGER->RenderInStore(); 
		
			GetNpc()->ResetScanTarget();
		
			break;
		}

        	case GUI::SCREEN::SHOP_ID:
        	{
        		((Kosmoport*)npc->GetLand())->GetShop()->Update();
                	((Kosmoport*)npc->GetLand())->GetShop()->Render(this);
		
			break;
		}

        	case GUI::SCREEN::GALAXYMAP_ID:
        	{
        		clearScreen();
        		GUI_MAP->update();
                	GUI_MAP->Render();   
         	
         		break;
         	}

         	case GUI::SCREEN::GOVERMENT_ID:
         	{
         		((Kosmoport*)npc->GetLand())->GetGoverment()->Update();
                	((Kosmoport*)npc->GetLand())->GetGoverment()->Render(this);
         	
         		break;
         	}
	}
	
        GUI_KOSMOPORT->Update(); 
        GUI_KOSMOPORT->Render(); 
         
}

void Player::RunSession(GameTimer* TIMER)
{
	this->UpdateGlobal();     

       	switch(npc->GetPlaceTypeId())
       	{
       		case ENTITY::SPACE_ID: 	    	{ this->SessionInSpace(TIMER); break; }
       		case ENTITY::KOSMOPORT_ID:  	{ this->SessionInKosmoport(); break; }
       	} 
       	
       	screen->update();           	
       	screen->display();
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
}

void Player::LoadDataUniquePlayer(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_player.npc_id = load_ptree.get<int>("unresolved.npc_id");
}

void Player::ResolveDataUniquePlayer()
{
        BindNpc((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_player.npc_id));
}		


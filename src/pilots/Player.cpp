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
    	
    	GUI_MANAGER    = new GuiManager(this);
    	
    	show_all_orbit     = false;
     	show_all_path      = false;
     	show_radar_range   = false;
     	show_grapple_range = false;
}
    
Player::~Player()
{
	delete cursor;
	
	delete GUI_MANAGER;
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

  
void Player::RenderInSpace_NEW()
{   
	int w = Screen::Instance().GetWindow().GetWidth();
	int h = Screen::Instance().GetWindow().GetHeight();

	Screen::Instance().GetFbo0().Activate(w, h);
   
        	npc->GetStarSystem()->DrawBackground(Screen::Instance().GetBottomLeftGlobalCoord());           
		camera(Screen::Instance().GetBottomLeftGlobalCoord().x, Screen::Instance().GetBottomLeftGlobalCoord().y);    
	        

		npc->GetStarSystem()->RestoreDefaultColor();
		enable_BLEND();
			for(unsigned int i = 0; i < visible_STAR_vec.size(); i++) 
			{ 
        			visible_STAR_vec[i]->Render_NEW(); 
    			}
    		disable_BLEND();
		npc->GetStarSystem()->RestoreSceneColor();
	Screen::Instance().GetFbo0().Deactivate();

	// POST PROCESS BLOOM (many FBO)
	Screen::Instance().GetBloom().Proceed(w, h, Screen::Instance().GetFbo0().GetTexture(), visible_STAR_vec[0]->GetBrightThreshold());

	// RENDER to FBO1, VOLUMETRIC LIGHT
	Screen::Instance().GetFbo1().Activate(w, h);
		glUseProgram(g_SHADERS_PACK.volumetriclight);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetBloom().GetFboFinal().GetTexture());
			glUniform1i(glGetUniformLocation(g_SHADERS_PACK.volumetriclight, "FullSampler"), 0);

			glActiveTexture(GL_TEXTURE1);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetBloom().GetTextureBlured());
			glUniform1i(glGetUniformLocation(g_SHADERS_PACK.volumetriclight, "BlurSampler"), 1);

			glUniform4f(glGetUniformLocation(g_SHADERS_PACK.volumetriclight, "sun_pos"), -Screen::Instance().GetBottomLeftGlobalCoord().x/w, -Screen::Instance().GetBottomLeftGlobalCoord().y/h, -100.0, 1.0);
          
			glActiveTexture(GL_TEXTURE0);
			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
	Screen::Instance().GetFbo1().Deactivate();


	Screen::Instance().GetFbo2().Activate(w, h);
		drawFullScreenTexturedQuad(Screen::Instance().GetFbo1().GetTexture(), w, h, -999.0);
           
          	camera(Screen::Instance().GetBottomLeftGlobalCoord().x, Screen::Instance().GetBottomLeftGlobalCoord().y);    
        
		enable_DEPTH();  
    			for(unsigned int i = 0; i < visible_PLANET_vec.size(); i++) 
    			{ 
       				visible_PLANET_vec[i]->Render_NEW(Screen::Instance().GetBottomLeftGlobalCoord()); 
    			}
    		
    			for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    			{ 
       				visible_ASTEROID_vec[i]->Render_NEW(Screen::Instance().GetBottomLeftGlobalCoord()); 
    			}

    			for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
			{ 
        			visible_BLACKHOLE_vec[i]->Render_NEW(Screen::Instance().GetBottomLeftGlobalCoord()); 
        			
    			}  	
    		disable_DEPTH();

    	          
		enable_BLEND();		
		    	for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    			{ 
    				visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       				visible_SPACESTATION_vec[i]->RenderInSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
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
		
    	Screen::Instance().GetFbo2().Deactivate();


	// POST PROCESS WAVE SHOCK into FBO2
	Screen::Instance().GetFbo3().Activate(w, h);

		float center_array[10][2];
		float xyz_array[10][3];
		float time_array[10];

		for (unsigned int i = 0; i < visible_effect_SHOCKWAVE_vec.size(); i++)
		{         
			center_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->center.x/w - Screen::Instance().GetBottomLeftGlobalCoord().x/w;
			center_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->center.y/h - Screen::Instance().GetBottomLeftGlobalCoord().y/h;
			xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[i]->parameter.x;
			xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[i]->parameter.y;
			xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[i]->parameter.z;
				
			time_array[i] = visible_effect_SHOCKWAVE_vec[i]->time;
		}
       

		glUseProgram(g_SHADERS_PACK.shockwave);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, Screen::Instance().GetFbo2().GetTexture());
			glUniform1i (glGetUniformLocation(g_SHADERS_PACK.shockwave, "sceneTex"), 0);

			int len_effect_SHOCKWAVE_list = visible_effect_SHOCKWAVE_vec.size();
			glUniform1i (glGetUniformLocation(g_SHADERS_PACK.shockwave, "imax"),        len_effect_SHOCKWAVE_list);
			glUniform2fv(glGetUniformLocation(g_SHADERS_PACK.shockwave, "center"),      len_effect_SHOCKWAVE_list, *center_array);
			glUniform3fv(glGetUniformLocation(g_SHADERS_PACK.shockwave, "shockParams"), len_effect_SHOCKWAVE_list, *xyz_array);
			glUniform1fv(glGetUniformLocation(g_SHADERS_PACK.shockwave, "time"),        len_effect_SHOCKWAVE_list, time_array);

			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
	
	Screen::Instance().GetFbo3().Deactivate();


	// render from FBO
	glEnable(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);      // unbind fbo

	clearScreen();
	resetRenderTransformation();

	drawFullScreenTexturedQuad(Screen::Instance().GetFbo3().GetTexture(), w, h, -999.0);
	//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug

	camera(Screen::Instance().GetBottomLeftGlobalCoord().x, Screen::Instance().GetBottomLeftGlobalCoord().y);
	
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
    	disable_BLEND();

    	for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    	{ 
        	visible_text_DAMAGE_vec[i]->Render(Screen::Instance().GetBottomLeftGlobalCoord()); 
    	}   
    		    	
    	npc->GetStarSystem()->RestoreSceneColor();    	          
}
    

	
  
void Player::RenderInSpace_OLD()
{   
	glLoadIdentity();
        npc->GetStarSystem()->DrawBackground(Screen::Instance().GetBottomLeftGlobalCoord());
	
        camera(Screen::Instance().GetBottomLeftGlobalCoord().x, Screen::Instance().GetBottomLeftGlobalCoord().y);
        
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

            	for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
		{ 
        		visible_BLACKHOLE_vec[i]->Render_OLD(); 
    		}    		
        disable_DEPTH();

        enable_BLEND();
                for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    		{ 
    			visible_SPACESTATION_vec[i]->UpdateRenderStuff(); 
       			visible_SPACESTATION_vec[i]->RenderInSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
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

	// text
        for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
    	{ 
        	visible_text_DAMAGE_vec[i]->Render(Screen::Instance().GetBottomLeftGlobalCoord()); 
    	}    		
              
    	npc->GetStarSystem()->RestoreSceneColor();
}


void Player::RenderInSpace(bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{    	
    	if (Config::Instance().MODERN_EFFECTS == true)
    	{
    		RenderInSpace_NEW();
    	}
    	else
    	{
        	RenderInSpace_OLD(); 
        }        

	enable_BLEND();              
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
       	 		npc->GetVehicle()->GetDriveComplex()->DrawPath();
       			npc->GetVehicle()->GetWeaponComplex()->RenderWeaponsRange();
       			npc->GetVehicle()->GetWeaponComplex()->RenderWeaponIcons(); 
       	
        		if (GetShowRadarRange() == true)
        		{
        			npc->GetVehicle()->RenderRadarRange();
        		}

        		if (GetShowGrappleRange() == true)
        		{
        			npc->GetVehicle()->RenderGrappleRange();
        		}
		}
	
		cursor->RenderFocusedSpaceObjectStuff();   // perform this function the last, because it resets previos Gl transform
	disable_BLEND();  
} 

void Player::MouseInteractionInSpace() // all large objects must be cheked by last
{   
    	bool cursor_has_target = false;   
 
    	int mxvp = cursor->GetMousePos().x + Screen::Instance().GetBottomLeftGlobalCoord().x;
    	int myvp = Screen::Instance().GetWindow().GetHeight() - cursor->GetMousePos().y + Screen::Instance().GetBottomLeftGlobalCoord().y;

    	bool mlb = cursor->GetMouseLeftButton();
    	bool mrb = cursor->GetMouseRightButton();

	if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
	{
    		npc->GetVehicle()->GetWeaponComplex()->WeaponsControlledFromUpperLevel(weapon_selector);                   				       
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
    	if (MouseInteractionWithStars(mxvp, myvp, mlb, mrb)) { return; }    
    	
	MouseNavigation(mxvp, myvp, mlb, mrb);  
}

bool Player::MouseInteractionWithRockets(int mxvp, int myvp, bool mlb, bool mrb) const
{
	for (unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
       	{ 
            	float object_cursor_dist = distBetweenPoints(visible_ROCKET_vec[i]->GetPoints().GetCenter(), mxvp, myvp);
            	if (object_cursor_dist < visible_ROCKET_vec[i]->GetCollisionRadius())
            	{ 
            		cursor->SetFocusedSpaceObject(visible_ROCKET_vec[i]);
               
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
                   				npc->GetVehicle()->GetDriveComplex()->SetTarget(visible_ROCKET_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
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
			cursor->SetFocusedSpaceObject(visible_CONTAINER_vec[i]);
			            		
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
            	       	cursor->SetFocusedSpaceObject(visible_SATELLITE_vec[i]);
                
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
                   				npc->GetVehicle()->GetDriveComplex()->SetTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
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
                        cursor->SetFocusedSpaceObject(visible_ASTEROID_vec[i]);        
                        //visible_ASTEROID_vec[i]->GetOrbit()->Draw();

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
                   				npc->GetVehicle()->GetDriveComplex()->SetTarget(visible_ASTEROID_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
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
               		cursor->SetFocusedSpaceObject(visible_SHIP_vec[i]);    
                
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
                   				npc->GetVehicle()->GetDriveComplex()->SetTarget(visible_SHIP_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
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
       			cursor->SetFocusedSpaceObject(visible_BLACKHOLE_vec[i]); 
       			
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
                	cursor->SetFocusedSpaceObject(visible_SPACESTATION_vec[i]); 
                
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
                   				MicroTask* microtask = new MicroTask(visible_SPACESTATION_vec[i], MICROSCENARIO::DOCKING_ID);
                   				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
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
                	cursor->SetFocusedSpaceObject(visible_PLANET_vec[i]); 
                	//visible_PLANET_vec[i]->GetOrbit()->Draw();
          
			if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
			{
                		if (mlb == true)
                		{
                    			//pPLAYER->GetVehicle()->getNavigator()->SetTarget(visible_PLANET_vec[pi], DOCKING_NAVIGATOR_ACTION_ID);
                    			//pPLAYER->GetVehicle()->getNavigator()->Update_inSpace_inStatic();  
               				MicroTask* microtask = new MicroTask(visible_PLANET_vec[i], MICROSCENARIO::DOCKING_ID);
                    			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
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
                	cursor->SetFocusedSpaceObject(visible_STAR_vec[i]); 
                	
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
      			ForceStateMachineReset();
       			npc->GetVehicle()->GetDriveComplex()->SetStaticTargetCoords(vec2f(mxvp, myvp));  
      		}
      	}
}

bool Player::IsObjectOnScreen(const Points& points) const
{
        float ob_centerx = points.GetCenter().x;
        float ob_centery = points.GetCenter().y;
        
        int ob_w = points.GetWidth();
        int ob_h = points.GetHeight();
        
        if (ob_centerx < (Screen::Instance().GetBottomLeftGlobalCoord().x - ob_w))
                return false;
        if (ob_centerx > (Screen::Instance().GetTopRightGlobalCoord().x + ob_w))
                return false;
        if (ob_centery < (Screen::Instance().GetBottomLeftGlobalCoord().y - ob_h))
                return false;
        if (ob_centery > (Screen::Instance().GetTopRightGlobalCoord().y + ob_h))
                return false;

        return true;
}

bool Player::IsObjectOnScreen(const vec2f& ob_center, float sizeInPixels) const
{       
        if (ob_center.x < (Screen::Instance().GetBottomLeftGlobalCoord().x - sizeInPixels))
                return false;
        if (ob_center.x > (Screen::Instance().GetTopRightGlobalCoord().x + sizeInPixels))
                return false;
        if (ob_center.y < (Screen::Instance().GetBottomLeftGlobalCoord().y - sizeInPixels))
                return false;
        if (ob_center.y > (Screen::Instance().GetTopRightGlobalCoord().y + sizeInPixels))
                return false;

        return true;
}


void Player::SessionInSpace(const TurnTimer& turn_timer)
{
	cursor->UpdateMousePos();

	npc->GetStarSystem()->FindVisibleEntities_c(this);
	RenderInSpace(turn_timer.GetTurnEnded(), GetShowAllOrbit(), GetShowAllPath()); 

	if (turn_timer.GetTurnEnded() == true)  
	{
		if ( (npc->GetScanTarget() == NULL) && (GetWorldMapShowFlag() == false) )
		{
			MouseInteractionInSpace();  // improove to exclude all render calls
		}
	}
	
	GUI_MANAGER->RunSession();   
}


void Player::SessionInKosmoport()
{
	cursor->UpdateMousePos();
	GUI_MANAGER->RunSession();        
}

void Player::RunSession(const TurnTimer& turn_timer)
{
	this->UpdateGlobal();     

       	switch(npc->GetPlaceTypeId())
       	{
       		case ENTITY::SPACE_ID: 	    	{ this->SessionInSpace(turn_timer); break; }
       		case ENTITY::KOSMOPORT_ID:  	{ this->SessionInKosmoport(); break; }
       	}        	
       	
       	Screen::Instance().Draw();
}

void Player::ForceStateMachineReset() const
{
	npc->GetStateMachine()->ForceReset();
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
        save_ptree.put(root+"unresolved.screen_pos_x", Screen::Instance().GetBottomLeftGlobalCoord().x);
        save_ptree.put(root+"unresolved.screen_pos_y", Screen::Instance().GetBottomLeftGlobalCoord().y);
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
        Screen::Instance().SetBottomLeftGlobalCoord(data_unresolved_player.screen_pos);
}		


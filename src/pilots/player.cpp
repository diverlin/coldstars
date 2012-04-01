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


Player::Player()
{ 
    	id = g_ID_GENERATOR.getNextId(); 
    	type_id = ENTITY::PLAYER_ID;
   	
    	npc  = NULL;
    	cursor = new Cursor(this);
    	screen = new Screen();
    	
    	GUI_MANAGER    = new GuiManager(this);
 	GUI_SPACE      = new GuiSpace(this);
 	GUI_KOSMOPORT  = new GuiKosmoport(this);
	GUI_MAP        = new GuiMap(this); 
	USERINPUT      = new UserInput(this); 
	
    	
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
	delete USERINPUT; 	
}  
            
void Player::Update_global()
{
	if (npc->GetAlive()  == true)
	{       	
		npc->GetVehicle()->GetWeaponComplex()->weapon_selector = weapon_selector;
	}
}  
               			
void Player::BindNpc(Npc* npc)
{
    	this->npc = npc;
    	npc->SetUpperControl(true);
    	cursor->getSlot()->SetOwnerVehicle(npc->GetVehicle());
}

void Player::ClearVisibleEntities()
{
        visible_STAR_vec.clear();
        visible_PLANET_vec.clear();
        visible_SPACESTATION_vec.clear();
        visible_SATELLITE_vec.clear();
        
        visible_ASTEROID_vec.clear();
        visible_MINERAL_vec.clear();
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

void Player::AddIfVisible(Mineral* mineral)
{
	if (IsObjectOnScreen(mineral->GetPoints()))
        {   
        	//if ( distBetweenPoints(mineral->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_MINERAL_vec.push_back(mineral);
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
        			visible_STAR_vec[i]->render_NEW(); 
    			}
    		disable_BLEND();
		npc->GetStarSystem()->RestoreSceneColor();
	screen->getFbo0()->deactivate();

	// POST PROCESS BLOOM (many FBO)
	screen->getBloom()->pass0(screen, screen->getFbo0()->getTexture(), visible_STAR_vec[0]->getBrightThreshold());
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
       				visible_PLANET_vec[i]->render_NEW(screen->getBottomLeftGlobalCoord()); 
    			}
    		
    			for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    			{ 
       				visible_ASTEROID_vec[i]->render_NEW(screen->getBottomLeftGlobalCoord()); 
    			}
    		disable_DEPTH();

    	          
		enable_BLEND();		
		    	for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    			{ 
    				visible_SPACESTATION_vec[i]->updateRenderStuff(); 
       				visible_SPACESTATION_vec[i]->render_inSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}
    			
    			for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
			{ 
        			visible_BLACKHOLE_vec[i]->render2D(); 
    			}  		
    			
    			for(unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
			{ 
        			visible_MINERAL_vec[i]->render2D(); 
    			}  
  			           
    			for(unsigned int i = 0; i < visible_CONTAINER_vec.size(); i++)
    			{ 
        			visible_CONTAINER_vec[i]->render2D(); 
    			} 	 
           

    			for(unsigned int i = 0; i < visible_SHIP_vec.size(); i++)
    			{ 
    				visible_SHIP_vec[i]->updateRenderStuff(); 
       				visible_SHIP_vec[i]->render_inSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}

			for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    			{ 
    				visible_SATELLITE_vec[i]->updateRenderStuff(); 
       				visible_SATELLITE_vec[i]->render_inSpace(); 
        			npc->GetStarSystem()->RestoreSceneColor();
    			}
    			
    			for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    			{ 
    			    	visible_ROCKET_vec[i]->updateRenderStuff();
       				visible_ROCKET_vec[i]->render_inSpace(); 
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
        		visible_STAR_vec[i]->render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_PLANET_vec.size(); i++) 
    		{ 
       			visible_PLANET_vec[i]->render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    		{ 
       			visible_ASTEROID_vec[i]->render_OLD(); 
    		}
        disable_DEPTH();

        enable_BLEND();
                for(unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
    		{ 
    			visible_SPACESTATION_vec[i]->updateRenderStuff(); 
       			visible_SPACESTATION_vec[i]->render_inSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
    		}
                        
            	for(unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
		{ 
        		visible_BLACKHOLE_vec[i]->render2D(); 
    		}  	
    			    			
    		for(unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
		{ 
        		visible_MINERAL_vec[i]->render2D(); 
    		}         
           
    		for(unsigned int i = 0; i < visible_CONTAINER_vec.size(); i++)
    		{ 
        		visible_CONTAINER_vec[i]->render2D(); 
    		} 	 
           
    		for(unsigned int i = 0; i < visible_SHIP_vec.size(); i++)
    		{ 
    		    	visible_SHIP_vec[i]->updateRenderStuff();
       			visible_SHIP_vec[i]->render_inSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
    		}

		for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    		{ 
    			visible_SATELLITE_vec[i]->updateRenderStuff(); 
       			visible_SATELLITE_vec[i]->render_inSpace(); 
        		npc->GetStarSystem()->RestoreSceneColor();
                }
                        
    		for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    		{ 
                        visible_ROCKET_vec[i]->updateRenderStuff();
       			visible_ROCKET_vec[i]->render_inSpace(); 
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

void Player::MouseInteraction_inOuterSpace() // all large objects must be cheked by last
{   
    	bool cursor_has_target = false;   
 
    	int mxvp = cursor->getMousePos().x                       + screen->getBottomLeftGlobalCoord().x;
    	int myvp = screen->getHeight() - cursor->getMousePos().y + screen->getBottomLeftGlobalCoord().y;

    	bool mlb = cursor->getMouseLeftButton();
    	bool mrb = cursor->getMouseRightButton();

	if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
	{
    		npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();                   				       
    		npc->GetVehicle()->GetWeaponComplex()->ResetDeselectedWeaponTargets();

        	npc->GetVehicle()->GetWeaponComplex()->RenderWeaponIcons();
        }


	/* NOTE: the intersection must be checked in order from small objects to huge */
	

    	if (cursor_has_target == false) 
    	{
        	for (unsigned int mi = 0; mi < visible_MINERAL_vec.size(); mi++)
        	{ 
            		float mineral_cursor_dist = distBetweenPoints(visible_MINERAL_vec[mi]->GetPoints().getCenter(), mxvp, myvp);
            		if (mineral_cursor_dist < visible_MINERAL_vec[mi]->GetCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_MINERAL_vec[mi]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

				if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
				{
               				if (mlb == true)
               				{
                   				npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_MINERAL_vec[mi]);
	       				}
	       				if (mrb == true)
	       				{
	       					if (npc->GetVehicle()->ableTo.GRAB == true)
	       					{
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_MINERAL_vec[mi]);
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();	       						
	       					}
	       				}
	       			}
	       			
               			break; 
            		}
       		}
    	}


    	if (cursor_has_target == false) 
    	{
        	for (unsigned int ci = 0; ci < visible_CONTAINER_vec.size(); ci++)
        	{ 
            		float container_cursor_dist = distBetweenPoints(visible_CONTAINER_vec[ci]->GetPoints().getCenter(), mxvp, myvp);
            		if (container_cursor_dist < visible_CONTAINER_vec[ci]->GetCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_CONTAINER_vec[ci]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

				if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
				{
               				if (mlb == true)
               				{
                   				npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();                   					    
                   				npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_CONTAINER_vec[ci]);
               				}
               				if (mrb == true)
	       				{
	       					if (npc->GetVehicle()->ableTo.GRAB == true)
	       					{
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_CONTAINER_vec[ci]);
	       						npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();
	       						printf("CONTAINER with id = %i HAS BEEN MARKED\n", visible_CONTAINER_vec[ci]->GetId());	       						
	       					}
	       				}
 				}
 					
               			break; 
            		}
        	}
    	}


	if (cursor_has_target == false) 
    	{
       		for (unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
       		{ 
            		float ship_cursor_dist = distBetweenPoints(visible_SATELLITE_vec[i]->GetPoints().getCenter(), mxvp, myvp);
            		if (ship_cursor_dist < visible_SATELLITE_vec[i]->GetCollisionRadius())
            		{ 
            			cursor_has_target = true;

                		visible_SATELLITE_vec[i]->RenderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 
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
                   					npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();
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
				
                		break; 
            		}
        	}
    	}

    
    	if (cursor_has_target == false) 
    	{
        	for (unsigned int ai = 0; ai < visible_ASTEROID_vec.size(); ai++)
        	{ 
            		float asteroid_cursor_dist = distBetweenPoints(visible_ASTEROID_vec[ai]->GetPoints().getCenter(), mxvp, myvp);
            		if (asteroid_cursor_dist < visible_ASTEROID_vec[ai]->GetCollisionRadius())
            		{   
                		cursor_has_target = true;

                		visible_ASTEROID_vec[ai]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 
                                
                                visible_ASTEROID_vec[ai]->getOrbit()->draw();

				if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
				{
                			if (mlb == true)
					{
                			
                			        if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_ASTEROID_vec[ai]);
                   				}
                   				else
                   				{
                   					npc->GetVehicle()->GetDriveComplex()->setTarget(visible_ASTEROID_vec[ai], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   					npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   				}
                   			}
                		}
                		
                		break; 
            		}
        	}
    	}

	if (cursor_has_target == false) 
    	{
       		for (unsigned int ki = 0; ki < visible_SHIP_vec.size(); ki++)
       		{ 
            		float ship_cursor_dist = distBetweenPoints(visible_SHIP_vec[ki]->GetPoints().getCenter(), mxvp, myvp);
            		if (ship_cursor_dist < visible_SHIP_vec[ki]->GetCollisionRadius())
            		{ 
            			cursor_has_target = true;

                		visible_SHIP_vec[ki]->RenderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 
                		visible_SHIP_vec[ki]->GetWeaponComplex()->RenderWeaponIcons();

                		visible_SHIP_vec[ki]->RenderRadarRange(); 
                		visible_SHIP_vec[ki]->GetWeaponComplex()->RenderWeaponsRange(); 
                		                                
                                visible_SHIP_vec[ki]->GetDriveComplex()->drawPath(); 
                
				if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                				if (npc->GetVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->GetVehicle()->GetWeaponComplex()->SetTarget(visible_SHIP_vec[ki]);
                   				}
                   				else
                   				{
                   					npc->GetVehicle()->GetDriveComplex()->setTarget(visible_SHIP_vec[ki], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   					npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
                   				}
					}

                			if (mrb == true)
                			{
                				if (GetShowGrappleRange() == true)
                				{
	       						if (npc->GetVehicle()->ableTo.GRAB == true)
	       						{
	       							npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_SHIP_vec[ki]);
	       							npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();	       						
	       						}
                   				}
                   				else
                   				{
                   				        if ( npc->CheckPossibilityToScan(visible_SHIP_vec[ki]) == true )
                   					{
                        					npc->SetScanTarget(visible_SHIP_vec[ki]);
                   					}

	       					}
	       				}
				}
				
                		break; 
            		}
        	}
    	}
    	


	if (cursor_has_target == false) 
    	{
        	for (unsigned int i = 0; i < visible_BLACKHOLE_vec.size(); i++)
        	{ 
            		float cursor_dist = distBetweenPoints(visible_BLACKHOLE_vec[i]->GetPoints().getCenter(), mxvp, myvp);
            		if (cursor_dist < visible_BLACKHOLE_vec[i]->GetCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_BLACKHOLE_vec[i]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

               			break; 
            		}
       		}
    	}


	if (cursor_has_target == false) 
    	{
       		for (unsigned int i = 0; i < visible_SPACESTATION_vec.size(); i++)
       		{ 
            		float ship_cursor_dist = distBetweenPoints(visible_SPACESTATION_vec[i]->GetPoints().getCenter(), mxvp, myvp);
            		if (ship_cursor_dist < visible_SPACESTATION_vec[i]->GetCollisionRadius())
            		{ 
            			cursor_has_target = true;

                		visible_SPACESTATION_vec[i]->RenderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 
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
                   					npc->GetVehicle()->GetWeaponComplex()->SelectWeapons();
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
				
                		break; 
            		}
        	}
    	}






    	if (cursor_has_target == false) 
    	{
        	for (unsigned int pi = 0; pi < visible_PLANET_vec.size(); pi++)
        	{ 
            		float planet_cursor_dist = distBetweenPoints(visible_PLANET_vec[pi]->GetPoints().getCenter(), mxvp, myvp);
            		//printf("1,2,3 = %f,%f,%f\n", visible_PLANET_vec[pi]->GetCollisionRadius(), visible_PLANET_vec[pi]->getPoints()->getCenter().x, visible_PLANET_vec[pi]->getPoints()->getCenter().y);
            		if (planet_cursor_dist < visible_PLANET_vec[pi]->GetCollisionRadius())
            		{   
                		cursor_has_target = true;

                		visible_PLANET_vec[pi]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

                                visible_PLANET_vec[pi]->getOrbit()->draw();
          
				if ( (npc->GetAlive() == true) and (npc->GetVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                    				//pPLAYER->GetVehicle()->getNavigator()->setTarget(visible_PLANET_vec[pi], DOCKING_NAVIGATOR_ACTION_ID);
                    				//pPLAYER->GetVehicle()->getNavigator()->Update_inSpace_inStatic();  
                    				npc->GetStateMachine()->setCurrentMicroTask(MICROSCENARIO_DOCKING, visible_PLANET_vec[pi]);
                			}   
				}
				
                		break; 
            		}
        	}
    	}




    	if (cursor_has_target == false) 
    	{
        	for (unsigned int si = 0; si < visible_STAR_vec.size(); si++)
        	{ 
            		float cursor_dist = distBetweenPoints(visible_STAR_vec[si]->GetPoints().getCenter(), mxvp, myvp);
            		if (cursor_dist < visible_STAR_vec[si]->GetCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_STAR_vec[si]->renderInfo_inSpace(screen->getBottomLeftGlobalCoord()); 

               			break; 
            		}
        	}
    	}



    	if (cursor_has_target == false) 
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
}


bool Player::IsObjectOnScreen(const Points& points) const
{
        float ob_centerx = points.getCenter().x;
        float ob_centery = points.getCenter().y;
        
        int ob_w = points.getWidth();
        int ob_h = points.getHeight();
        
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


void Player :: InOuterspace(GameTimer* TIMER)
{
	USERINPUT->Update_inSpace();

	cursor->updateMousePos();

	npc->GetStarSystem()->FindVisibleEntities_c(this);
	this->Render(TIMER->getTurnEnded(), GetShowAllOrbit(), GetShowAllPath()); 

	if (TIMER->getTurnEnded() == true)  
	{
		if ( (npc->GetScanTarget() == NULL) && (GetWorldMapShowFlag() == false) )
		{
			MouseInteraction_inOuterSpace();  // improove to exclude all render calls
		}
	}

	//////////// SCAN ///////////////
	if (GetNpc()->GetScanTarget() != NULL )
	{         
		GUI_MANAGER->updateInScan(false);
		GUI_MANAGER->renderInScan();                       
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


void Player::InKosmoport()
{
	USERINPUT->update_inKosmoport();
         
        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::ANGAR_ID)
        {
        	((Kosmoport*)npc->GetLand())->getAngar()->mouseControl(this);                                
               	((Kosmoport*)npc->GetLand())->getAngar()->Render(this);

		if (npc->GetScanTarget() != NULL) 
		{ 
			GUI_MANAGER->updateInScan(false);
			GUI_MANAGER->renderInScan(); 
		}
		else
		{
			((Kosmoport*)npc->GetLand())->getAngar()->RenderItemInfo(this);
		}
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::STORE_ID)
        {
        	if (npc->GetScanTarget() != npc->GetVehicle())
        	{
        		GetNpc()->SetScanTarget(npc->GetVehicle());
        	}
                                    
        	GUI_MANAGER->updateInStore();
                GUI_MANAGER->renderInStore(); 
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::SHOP_ID)
        {
        	((Kosmoport*)npc->GetLand())->getShop()->update();
                ((Kosmoport*)npc->GetLand())->getShop()->Render(this);
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::GALAXYMAP_ID)
        {
        	GUI_MAP->update();
        	clearScreen();
                GUI_MAP->Render();   
         }

         if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::GOVERMENT_ID)
         {
         	((Kosmoport*)npc->GetLand())->getGoverment()->update();
                ((Kosmoport*)npc->GetLand())->getGoverment()->Render(this);
         }

         GUI_KOSMOPORT->update(); 
         GUI_KOSMOPORT->Render(); 
}

void Player::RunSession(GameTimer* TIMER)
{
	this->Update_global();     

       	if (npc->GetPlaceTypeId() == ENTITY::SPACE_ID)
       	{  
        	this->InOuterspace(TIMER);
       	}

		
       	if (npc->GetPlaceTypeId() == ENTITY::KOSMOPORT_ID)
       	{
        	this->InKosmoport();
       	} 
       	
       	screen->update();           	
       	screen->display();
}     		

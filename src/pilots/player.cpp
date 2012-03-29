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


Player :: Player()
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
    
Player :: ~Player()
{
	delete cursor;
	delete screen;
	
	delete GUI_MANAGER;
 	delete GUI_SPACE;
 	delete GUI_KOSMOPORT;
	delete GUI_MAP;
	delete USERINPUT; 
	
}  
    
    
void Player :: setWorldMapShowFlag(bool _show_worldmap) { control.worldmap = _show_worldmap; }
          	
void Player :: setShowAllOrbit(bool show_all_orbit)     { this->show_all_orbit = show_all_orbit; }
void Player :: setShowAllPath(bool show_all_path)       { this->show_all_path = show_all_path; }
void Player :: setShowRadarRange(bool show_radar_range) { this->show_radar_range = show_radar_range; }
void Player :: setShowGrappleRange(bool show_grapple_range)  { this->show_grapple_range = show_grapple_range; }
          	
bool Player :: getWorldMapShowFlag() const { return control.worldmap; }         	
Npc* Player :: getNpc() const       { return npc; }
Cursor* Player :: getCursor() const { return cursor; }
Screen* Player :: getScreen() const { return screen; }
         
bool Player :: getShowAllOrbit() const     { return show_all_orbit; }
bool Player :: getShowAllPath() const      { return show_all_path; }
bool Player :: getShowRadarRange() const   { return show_radar_range; }
bool Player :: getShowGrappleRange() const { return show_grapple_range; }          	 
   
bool Player :: getNextTurnReady() const { return USERINPUT->getNextTurnReady(); }    
   
          
void Player :: update_global()
{
	if (npc->GetAlive()  == true)
	{       	
		npc->getVehicle()->GetWeaponComplex()->weapon_selector = weapon_selector;
	}
}  
               			
void Player :: bindNpc(Npc* npc)
{
    	this->npc = npc;
    	npc->setUpperControl(true);
    	cursor->getSlot()->SetOwnerVehicle(npc->getVehicle());
}

    


void Player :: clearVisibleEntities()
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
    		

void Player :: addIfVisible(Star* star)
{
        if (isObjectOnScreen(star->GetPoints()))
        {         
		visible_STAR_vec.push_back(star);
	}
}

void Player :: addIfVisible(Planet* planet)
{
        if (isObjectOnScreen(planet->GetPoints()))
        {  
		visible_PLANET_vec.push_back(planet);
	}
}

void Player :: addIfVisible(Asteroid* asteroid)     		
{
	if (isObjectOnScreen(asteroid->GetPoints()))
        {   	
                //if ( distBetweenPoints(asteroid->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_ASTEROID_vec.push_back(asteroid);
                }
        }
}

void Player :: addIfVisible(Mineral* mineral)
{
	if (isObjectOnScreen(mineral->GetPoints()))
        {   
        	//if ( distBetweenPoints(mineral->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_MINERAL_vec.push_back(mineral);
		}
	}
}

void Player :: addIfVisible(Container* container)     	
{
        if (isObjectOnScreen(container->GetPoints()))
        {    
        	//if ( distBetweenPoints(container->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
                	visible_CONTAINER_vec.push_back(container);
                }
	}
}

void Player :: addIfVisible(RocketBullet* rocket)  
{
        if (isObjectOnScreen(rocket->GetPoints()))  
        {  
             	//if ( distBetweenPoints(rocket->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
        		visible_ROCKET_vec.push_back(rocket);
        	}
        }
}

void Player :: addIfVisible(BlackHole* blackhole)  
{
        if (isObjectOnScreen(blackhole->GetPoints()))  
        {  
        	//if ( distBetweenPoints(blackhole->getPoints()->getCenter(), player_center) < player_vision_radius )
        	{
                	visible_BLACKHOLE_vec.push_back(blackhole);
		}
	}
}

void Player :: addIfVisible(SpaceStation* spacestation)  
{
        if (isObjectOnScreen(spacestation->GetPoints()))  
        {	  
                //if ( distBetweenPoints(spacestation->getPoints()->getCenter(), player_center) < player_vision_radius )
               	{
        		visible_SPACESTATION_vec.push_back(spacestation);
        	}
        }
}

void Player :: addIfVisible(Satellite* satellite) 
{
        if (isObjectOnScreen(satellite->GetPoints()))  
        {	  
        	//if ( distBetweenPoints(satellite->getPoints()->getCenter(), player_center) < player_vision_radius )
                {
        		visible_SATELLITE_vec.push_back(satellite);
        	}
        }
}

void Player :: addIfVisible(Ship* ship) 
{
        if (isObjectOnScreen(ship->GetPoints()))
        {	  
                //if ( distBetweenPoints(ship->getPoints()->getCenter(), player_center) < player_vision_radius )
               	{
			visible_SHIP_vec.push_back(ship);
		}
	}
}     		
        
void Player :: addIfVisible(ShockWaveEffect* effect)
{
	visible_effect_SHOCKWAVE_vec.push_back(effect);
}

void Player :: addIfVisible(LazerTraceEffect* effect)
{
	visible_effect_LAZERTRACE_vec.push_back(effect);
}
 
void Player :: addIfVisible(BaseParticleSystem* effect)
{
	visible_effect_PARTICLESYSTEM_vec.push_back(effect);
}

void Player :: addIfVisible(VerticalFlowText* effect)
{
	visible_text_DAMAGE_vec.push_back(effect);
}     		


   
void Player :: renderEntities_NEW()
{   
	int w = screen->getWidth();
	int h = screen->getHeight();

	screen->getFbo0()->activate(screen);
   
        	npc->GetStarSystem()->renderBackground(screen->getBottomLeftGlobalCoord());           
		camera(screen->getBottomLeftGlobalCoord().x, screen->getBottomLeftGlobalCoord().y);    
	        

		npc->GetStarSystem()->restoreDefaultColor();
		enable_BLEND();
			for(unsigned int i = 0; i < visible_STAR_vec.size(); i++) 
			{ 
        			visible_STAR_vec[i]->render_NEW(); 
    			}
    		disable_BLEND();
		npc->GetStarSystem()->restoreSceneColor();
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
        			npc->GetStarSystem()->restoreSceneColor();
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
        			npc->GetStarSystem()->restoreSceneColor();
    			}

			for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    			{ 
    				visible_SATELLITE_vec[i]->updateRenderStuff(); 
       				visible_SATELLITE_vec[i]->render_inSpace(); 
        			npc->GetStarSystem()->restoreSceneColor();
    			}
    			
    			for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    			{ 
    			    	visible_ROCKET_vec[i]->updateRenderStuff();
       				visible_ROCKET_vec[i]->render_inSpace(); 
       				npc->GetStarSystem()->restoreSceneColor();
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
    	
    	npc->GetStarSystem()->restoreSceneColor();    	          
}
    

	
  
void Player :: renderEntities_OLD()
{   
	glLoadIdentity();
        npc->GetStarSystem()->renderBackground(screen->getBottomLeftGlobalCoord());
	
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
        		npc->GetStarSystem()->restoreSceneColor();
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
        		npc->GetStarSystem()->restoreSceneColor();
    		}

		for(unsigned int i = 0; i < visible_SATELLITE_vec.size(); i++)
    		{ 
    			visible_SATELLITE_vec[i]->updateRenderStuff(); 
       			visible_SATELLITE_vec[i]->render_inSpace(); 
        		npc->GetStarSystem()->restoreSceneColor();
                }
                        
    		for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    		{ 
                        visible_ROCKET_vec[i]->updateRenderStuff();
       			visible_ROCKET_vec[i]->render_inSpace(); 
                        npc->GetStarSystem()->restoreSceneColor();
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
    		
                
    	npc->GetStarSystem()->restoreSceneColor();
}



void Player :: Render(bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{
    	
    	if (Config::Instance().MODERN_EFFECTS == true)
    	{
    		renderEntities_NEW();
    	}
    	else
    	{
        	renderEntities_OLD(); 
        }
                
        if (turn_ended == true)
        {
        	if (forceDraw_orbits == true)
        	{
                	npc->GetStarSystem()->drawOrbits();
        	}
        
        	if (forceDraw_path == true)
        	{
                	npc->GetStarSystem()->drawPath();
        	}
       	 	npc->getVehicle()->GetDriveComplex()->drawPath();
       		npc->getVehicle()->GetWeaponComplex()->RenderWeaponsRange();
       	
        	if (getShowRadarRange() == true)
        	{
        		npc->getVehicle()->RenderRadarRange();
        	}

        	if (getShowGrappleRange() == true)
        	{
        		npc->getVehicle()->RenderGrappleRange();
        	}
	}
} 



void Player :: mouseControl() // all large objects must be cheked by last
{   
    	bool cursor_has_target = false;   
 
    	int mxvp = cursor->getMousePos().x                       + screen->getBottomLeftGlobalCoord().x;
    	int myvp = screen->getHeight() - cursor->getMousePos().y + screen->getBottomLeftGlobalCoord().y;

    	bool mlb = cursor->getMouseLeftButton();
    	bool mrb = cursor->getMouseRightButton();

	if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
	{
    		npc->getVehicle()->GetWeaponComplex()->SelectWeapons();                   				       
    		npc->getVehicle()->GetWeaponComplex()->ResetDeselectedWeaponTargets();

        	npc->getVehicle()->GetWeaponComplex()->RenderWeaponIcons();
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

				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
               				if (mlb == true)
               				{
                   				npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
                   				npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_MINERAL_vec[mi]);
	       				}
	       				if (mrb == true)
	       				{
	       					if (npc->getVehicle()->ableTo.GRAB == true)
	       					{
	       						npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_MINERAL_vec[mi]);
	       						npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();	       						
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

				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
               				if (mlb == true)
               				{
                   				npc->getVehicle()->GetWeaponComplex()->SelectWeapons();                   					    
                   				npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_CONTAINER_vec[ci]);
               				}
               				if (mrb == true)
	       				{
	       					if (npc->getVehicle()->ableTo.GRAB == true)
	       					{
	       						npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_CONTAINER_vec[ci]);
	       						npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();
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
                
				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                				if (npc->getVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_SATELLITE_vec[i]);
                   				}
                   				else
                   				{
                   					npc->getVehicle()->GetDriveComplex()->setTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
                   					npc->getVehicle()->GetDriveComplex()->update_inSpace_inStatic();
                   				}
					}

                			if (mrb == true)
                			{
                				if (getShowGrappleRange() == true)
                				{
	       						//if (pPLAYER->getVehicle()->ableTo.GRAB == true)
	       						//{
	       							//pPLAYER->getVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_SATELLITE_vec[i]);
	       							//pPLAYER->getVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();	       						
	       						//}
                   				}
                   				else
                   				{
                   				        if ( npc->checkPossibilityToScan(visible_SATELLITE_vec[i]) == true )
                   					{
                        					npc->setScanTarget(visible_SATELLITE_vec[i]);
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

				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
                			if (mlb == true)
					{
                			
                			        if (npc->getVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_ASTEROID_vec[ai]);
                   				}
                   				else
                   				{
                   					npc->getVehicle()->GetDriveComplex()->setTarget(visible_ASTEROID_vec[ai], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   					npc->getVehicle()->GetDriveComplex()->update_inSpace_inStatic();
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
                
				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                				if (npc->getVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_SHIP_vec[ki]);
                   				}
                   				else
                   				{
                   					npc->getVehicle()->GetDriveComplex()->setTarget(visible_SHIP_vec[ki], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                   					npc->getVehicle()->GetDriveComplex()->update_inSpace_inStatic();
                   				}
					}

                			if (mrb == true)
                			{
                				if (getShowGrappleRange() == true)
                				{
	       						if (npc->getVehicle()->ableTo.GRAB == true)
	       						{
	       							npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->addTarget(visible_SHIP_vec[ki]);
	       							npc->getVehicle()->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();	       						
	       						}
                   				}
                   				else
                   				{
                   				        if ( npc->checkPossibilityToScan(visible_SHIP_vec[ki]) == true )
                   					{
                        					npc->setScanTarget(visible_SHIP_vec[ki]);
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
                
				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                				if (npc->getVehicle()->GetWeaponComplex()->IsAnyWeaponSelected() == true)
                				{
                   					npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
                   					npc->getVehicle()->GetWeaponComplex()->SetTarget(visible_SPACESTATION_vec[i]);
                   				}
                   				else
                   				{
                   					npc->getStateMachine()->setCurrentMicroTask(MICROSCENARIO_DOCKING, visible_SPACESTATION_vec[i]);
                   				}
					}

                			if (mrb == true)
                			{
                				if (getShowGrappleRange() == true)
                				{
	       						//if (pPLAYER->getVehicle()->ableTo.GRAB == true)
	       						//{
	       							//pPLAYER->getVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_STARBASE_vec[i]);
	       							//pPLAYER->getVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();	       						
	       						//}
                   				}
                   				else
                   				{
                   				        if ( npc->checkPossibilityToScan(visible_SPACESTATION_vec[i]) == true )
                   					{
                        					npc->setScanTarget(visible_SPACESTATION_vec[i]);
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
          
				if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
				{
                			if (mlb == true)
                			{
                    				//pPLAYER->getVehicle()->getNavigator()->setTarget(visible_PLANET_vec[pi], DOCKING_NAVIGATOR_ACTION_ID);
                    				//pPLAYER->getVehicle()->getNavigator()->update_inSpace_inStatic();  
                    				npc->getStateMachine()->setCurrentMicroTask(MICROSCENARIO_DOCKING, visible_PLANET_vec[pi]);
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
		if ( (npc->GetAlive() == true) and (npc->getVehicle() != NULL) )
		{
        		if (mlb == true)
        		{
            			npc->getVehicle()->GetDriveComplex()->setStaticTargetCoords(vec2f(mxvp, myvp));  
            			npc->getStateMachine()->reset();
        		}
        	}
   	}     
}







bool Player :: isObjectOnScreen(const Points& points) const
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



void Player :: outerspace(GameTimer* TIMER)
{
	USERINPUT->update_inSpace();

	cursor->updateMousePos();

	npc->GetStarSystem()->findVisibleEntities_c(this);
	this->Render(TIMER->getTurnEnded(), getShowAllOrbit(), getShowAllPath()); 

	if (TIMER->getTurnEnded() == true)  
	{
		if ( (npc->getScanTarget() == NULL) && (getWorldMapShowFlag() == false) )
		{
			mouseControl();  // improove to exclude all render calls
		}
	}

	//////////// SCAN ///////////////
	if (getNpc()->getScanTarget() != NULL )
	{         
		GUI_MANAGER->updateInScan(false);
		GUI_MANAGER->renderInScan();                       
	}

	//////////// WORLDMAP ///////////
	if (getWorldMapShowFlag() == true )  
	{
		GUI_MAP->update();   
		GUI_MAP->Render();   
	}

	GUI_SPACE->update();    
	GUI_SPACE->Render();
}

void Player :: kosmoport()
{
	USERINPUT->update_inKosmoport();
         
        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::ANGAR_ID)
        {
        	((Kosmoport*)npc->getLand())->getAngar()->mouseControl(this);                                
               	((Kosmoport*)npc->getLand())->getAngar()->Render(this);

		if (npc->getScanTarget() != NULL) 
		{ 
			GUI_MANAGER->updateInScan(false);
			GUI_MANAGER->renderInScan(); 
		}
		else
		{
			((Kosmoport*)npc->getLand())->getAngar()->RenderItemInfo(this);
		}
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::STORE_ID)
        {
        	if (npc->getScanTarget() != npc->getVehicle())
        	{
        		getNpc()->setScanTarget(npc->getVehicle());
        	}
                                    
        	GUI_MANAGER->updateInStore();
                GUI_MANAGER->renderInStore(); 
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::SHOP_ID)
        {
        	((Kosmoport*)npc->getLand())->getShop()->update();
                ((Kosmoport*)npc->getLand())->getShop()->Render(this);
	}

        if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::GALAXYMAP_ID)
        {
        	GUI_MAP->update();
        	clearScreen();
                GUI_MAP->Render();   
         }

         if (GUI_KOSMOPORT->getActiveScreenId() == GUI::SCREEN::GOVERMENT_ID)
         {
         	((Kosmoport*)npc->getLand())->getGoverment()->update();
                ((Kosmoport*)npc->getLand())->getGoverment()->Render(this);
         }

         GUI_KOSMOPORT->update(); 
         GUI_KOSMOPORT->Render(); 
}

void Player :: runSession(GameTimer* TIMER)
{
	this->update_global();     

       	if (npc->GetPlaceTypeId() == ENTITY::SPACE_ID)
       	{  
        	this->outerspace(TIMER);
       	}

		
       	if (npc->GetPlaceTypeId() == ENTITY::KOSMOPORT_ID)
       	{
        	this->kosmoport();
       	} 
       	
       	screen->update();           	
       	screen->display();
}     		

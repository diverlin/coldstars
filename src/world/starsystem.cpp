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



StarSystem :: StarSystem()
{ 
    	id = g_STARSYSTEM_ID_GENERATOR.getNextId();
    	type_id = STARSYSTEM_ID;
    	
    	is_CAPTURED = false;

    	calculation_per_turn_allowed = true;
    	calculation_per_turn_allowed_inDynamic = true;

    	detalied_simulation = false; // will be changing depending on player presence
}

StarSystem :: ~StarSystem()
{}
      

void StarSystem :: setPositionOnWorldMap(Rect rect) { rect_onMap = rect; }
void StarSystem :: setCapturedFlag(bool _captured) { is_CAPTURED = _captured; }
				
int StarSystem :: getId() const     { return id; }
int StarSystem :: getTypeId() const { return type_id; }
bool StarSystem :: getDetailedSimulationFlag() const { return detalied_simulation; }
bool StarSystem :: getCapturedFlag() const { return is_CAPTURED; }    
Rect StarSystem :: getRectOnMap() const { return rect_onMap; }  
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


Npc* StarSystem:: getEvilNpc(vec2f _center)
{
	std::vector<Npc*> _npc_vec;
	Npc* requested_npc;
	
	for (unsigned int i = 0; i < NPC_inSPACE_vec.size(); i++)
        {
                if ( (NPC_inSPACE_vec[i]->getRaceId() == RACE_6_ID) or (NPC_inSPACE_vec[i]->getRaceId() == RACE_7_ID) )
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
//

void StarSystem :: update_TRUE(int timer)
{
	if (PLAYER_vec.size() > 0)
	{
		detalied_simulation = true;
	}
	else
	{
		detalied_simulation = false;
	}




	if (timer > 0)
	{
		if (calculation_per_turn_allowed_inDynamic == true)
		{
                        postHyperJumpEvent();
			for (unsigned int i=0; i<PLANET_vec.size(); i++)
			{
				PLANET_vec[i]->launchingProcedure();
			}
			calculation_per_turn_allowed_inDynamic = false;
		}
		
     		asteroidManager(10); 

    		updateEntities_inDynamic_TRUE();
    		updateEffects();
    		
    		rocketCollision_TRUE();
    		asteroidCollision_TRUE();

    		manageDeadObjects(); 

		fireEvents_TRUE(timer);
		
		calculation_per_turn_allowed = true;
	}
	else
	{
	    	updateEffects();
	    		
		if (calculation_per_turn_allowed == true)
		{
			removeAllReferencesToDeadObjects();
			garbage.clear(); 
	    		
    			updateEntities_inStatic();     			

    			calculation_per_turn_allowed = false;
    			calculation_per_turn_allowed_inDynamic = true;
    		}    		
	}
}




void StarSystem :: update_FALSE(int timer)
{
	update_TRUE(timer);
    	//asteroidManager(10); 

    	//updateEntities_inDynamic_FALSE();
    	//manageEntities(); 

    	//if (getRandInt(1,10) == 1)
    	//{
        	//rocketCollision_FALSE();
        	//asteroidCollision_FALSE();

        	//fireEvents_FALSE(timer);
    	//}
}


void StarSystem :: rocketCollision_TRUE()
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                if (ROCKET_vec[ri]->getAlive() == true) 
                {
                	if (collide == false)
                	{
                		for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
                		{
                        		if (ROCKET_vec[ri]->getOwnerShipId() != SHIP_inSPACE_vec[ki]->getId())
                        		{                        
                        			collide = collideEvent_TRUE(ROCKET_vec[ri], SHIP_inSPACE_vec[ki]);
                        			if (collide == true) { break; }                        
                        		}
                		}
                	}
                	else  { continue; }
                

                	if (collide == false)
                	{
                        	for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
                        	{
                        		collide = collideEvent_TRUE(ROCKET_vec[ri], ASTEROID_vec[ai]);
                        		if (collide == true) { break; }
                        	}
                	}
                	else  { continue; }



                	if (collide == false)
                	{
                        	for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
                        	{
                        		collide = collideEvent_TRUE(ROCKET_vec[ri], MINERAL_vec[mi]);
                        		if (collide == true) { 	break; }
                        	}
                	}
                	else  { continue; }


                	if (collide == false)
                	{
                        	for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
                        	{
                        		collide = collideEvent_TRUE(ROCKET_vec[ri], CONTAINER_vec[ci]);
                        		if (collide == true) { 	break; }
                        	}
                	}
                	else  { continue; }
                }
        }
}





void StarSystem :: rocketCollision_FALSE()
{
	rocketCollision_TRUE();
	// use hit_FALSE()
}



void StarSystem :: asteroidCollision_TRUE()
{
	bool collide = false;
	
        for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
        {
                if (ASTEROID_vec[ai]->getAlive() == true) 
                {
                	if (collide == false)
                	{
                        	for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
                        	{
                                	collide = collideEvent_TRUE(ASTEROID_vec[ai], SHIP_inSPACE_vec[ki]);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	
                	
                	
                	if (collide == false)
                	{
                        	for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
                        	{
                                	collide = collideEvent_TRUE(ASTEROID_vec[ai], PLANET_vec[pi]);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                	
                	
                	
                	if (collide == false)
                	{
                        	for (unsigned int si = 0; si < STAR_vec.size(); si++)
                        	{
                                	collide = collideEvent_TRUE(ASTEROID_vec[ai], STAR_vec[si]);
                        		if (collide == true) { break; }
                        	}                        	
                	}
                	else { continue; }
                }
	}
}



void StarSystem :: asteroidCollision_FALSE()
{
       asteroidCollision_TRUE();
       // use hit_FALSE()
}


void StarSystem :: updateEntities_inDynamic_TRUE()
{
        for (unsigned int si = 0; si < STAR_vec.size(); si++)
        {
                STAR_vec[si]->update_inSpace_inDynamic(); 
	}
	
        for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
        {
                PLANET_vec[pi]->update_inSpace_inDynamic(); 
    	}
    	
        for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
        {
                MINERAL_vec[mi]->update_inSpace_inDynamic_TRUE(); 
     	}
     	
        for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
        {
                CONTAINER_vec[ci]->update_inSpace_inDynamic_TRUE(); 
	}
	
        for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++) 
        {
                ASTEROID_vec[ai]->update_inSpace_inDynamic_TRUE(); 
    	}
    	
        for (unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
        {
                NPC_inSPACE_vec[ni]->update_inDynamic_inSpace(); 
    	}
    	
        for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
        {
                SHIP_inSPACE_vec[ki]->update_inSpace_inDynamic_TRUE();         
    	}
    	
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                ROCKET_vec[ri]->update_inSpace_inDynamic(); 
        }
}  
      
     

void StarSystem :: updateEntities_inDynamic_FALSE()
{
        for (unsigned int si = 0; si < STAR_vec.size(); si++)
        {
                STAR_vec[si]->update_inSpace_inDynamic(); 
        }

        for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
        {
                PLANET_vec[pi]->update_inSpace_inDynamic(); 
        }
    
        for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
        {
                MINERAL_vec[mi]->update_inSpace_inDynamic_FALSE(); 
        }
     
        for (unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
        {
                CONTAINER_vec[ci]->update_inSpace_inDynamic_FALSE(); 
        }

        for (unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++) 
        {
                ASTEROID_vec[ai]->update_inSpace_inDynamic_FALSE(); 
        }
    
        for (unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
        {
                NPC_inSPACE_vec[ni]->update_inDynamic_inSpace(); 
        }

        for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
        {
                SHIP_inSPACE_vec[ki]->update_inSpace_inDynamic_FALSE(); 
        }
    
        for (unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
        {
                ROCKET_vec[ri]->update_inSpace_inDynamic(); 
        }
                

}  
  
 
      
void StarSystem :: updateEntities_inStatic()
{
     	// called once per TURN
     	for (unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
     	{
     		NPC_inSPACE_vec[ni]->getShip()->reloadWeapons();
     		if (NPC_inSPACE_vec[ni]->getControlledByPlayer() == false)
     		{
     			NPC_inSPACE_vec[ni]->thinkCommon_inSpace_inStatic();
         	}
     	}

     	for (unsigned int pi = 0; pi < PLANET_vec.size(); pi++)
     	{
         	PLANET_vec[pi]->update_inSpace_inStatic();
     	}
}


void StarSystem :: updateEffects()
{
        for(unsigned int i = 0; i<effect_LAZERTRACE_vec.size(); i++)
	{ 
		effect_LAZERTRACE_vec[i]->update(); 
	}

	for(unsigned int i = 0; i<effect_EXPLOSION_vec.size(); i++)
	{ 
		effect_EXPLOSION_vec[i]->update();
	}

	for(unsigned int i = 0; i<effect_DAMAGE_vec.size(); i++)
	{ 
		effect_DAMAGE_vec[i]->update();
	}
	
	for (unsigned int i = 0; i < effect_SHOCKWAVE_vec.size(); i++)
	{         
		effect_SHOCKWAVE_vec[i]->update();

	}
}
    		
      

void StarSystem :: findVisibleEntities()
{
        float startViewCoord_x = g_SCROLL_COORD_X + g_VIEW_WIDTH;
        float startViewCoord_y = g_SCROLL_COORD_Y + g_VIEW_HEIGHT;

        visible_STAR_vec.clear();
        visible_PLANET_vec.clear();
        //self.visible_SPUTNIK_list      = []
        visible_ASTEROID_vec.clear();
        visible_MINERAL_vec.clear();
        visible_CONTAINER_vec.clear();
        //self.visible_BOMB_list         = []
        visible_SHIP_vec.clear();
        visible_ROCKET_vec.clear();
        //self.visible_BLACKHOLE_list    = []

        //self.visible_effect_EXPLOSION_list = []
        //self.visible_effect_DAMAGE_list    = []

        for (unsigned int i = 0; i < STAR_vec.size(); i++)
        {
                if (isObjectVisible(STAR_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))
                {    
                        visible_STAR_vec.push_back(STAR_vec[i]);
                }
        }
    
        for (unsigned int i = 0; i < PLANET_vec.size(); i++)
        {
                if (isObjectVisible(PLANET_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))   
                {
                        visible_PLANET_vec.push_back(PLANET_vec[i]);
                }
        }
    
   
        //self.visible_SPUTNIK_list   = [s for s in self.SPUTNIK_list   if isObjectVisible((s.points.center[0], s.points.center[1]), (s.w, s.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
        for (unsigned int i = 0; i < ASTEROID_vec.size(); i++)
        {
                if (isObjectVisible(ASTEROID_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))
                {   
                        visible_ASTEROID_vec.push_back(ASTEROID_vec[i]); 
                }
        }
   
        for (unsigned int i = 0; i < MINERAL_vec.size(); i++)
        {
                if (isObjectVisible(MINERAL_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))
                {   
                        visible_MINERAL_vec.push_back(MINERAL_vec[i]);
                }  
        }
    
        for (unsigned int i = 0; i < CONTAINER_vec.size(); i++)
        {
                if (isObjectVisible(CONTAINER_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))
                {    
                        visible_CONTAINER_vec.push_back(CONTAINER_vec[i]);
                } 
    }

    //self.visible_BOMB_list      = [b for b in self.BOMB_list      if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    
    for (unsigned int i = 0; i < SHIP_inSPACE_vec.size(); i++)
    {
        if (isObjectVisible(SHIP_inSPACE_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))  
        {  
           visible_SHIP_vec.push_back(SHIP_inSPACE_vec[i]); 
        }
    }
    
    for (unsigned int i = 0; i < ROCKET_vec.size(); i++)
    {
        if (isObjectVisible(ROCKET_vec[i]->getPoints(), startViewCoord_x, startViewCoord_y))  
        {  
           visible_ROCKET_vec.push_back(ROCKET_vec[i]); 
        }
    }

    //self.visible_BLACKHOLE_list = [b for b in self.BLACKHOLE_list if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]

    //self.visible_effect_EXPLOSION_list = [e for e in self.effect_EXPLOSION_list if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    //self.visible_effect_DAMAGE_list    = [e for e in self.effect_DAMAGE_list    if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
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


void StarSystem :: renderBackground()
{   
	// HACK for point sprites
    	enable_POINTSPRITE();
    		distantStarBgEffect_vec[0]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
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
        		distantNebulaBgEffect_vec[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<distantStarBgEffect_vec.size(); i++)
    			{ 
       				distantStarBgEffect_vec[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    			}
    		disable_POINTSPRITE();
    	
		glDepthMask(true);
	disable_BLEND();
}
    
    
void StarSystem :: render()
{
    	findVisibleEntities();
    	if (USE_MODERN_HW == true)
    		renderEntities_NEW();
    	else
        	renderEntities_OLD(); 
} 

    
void StarSystem :: renderEntities_NEW()
{   
	int w = g_VIEW_WIDTH;
	int h = g_VIEW_HEIGHT;

	g_FBO0->activate();
   
        	renderBackground();           
		camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);    
	        

		restoreDefaultColor();
		enable_BLEND();
			for(unsigned int i = 0; i < visible_STAR_vec.size(); i++) 
			{ 
        			visible_STAR_vec[i]->render_NEW(); 
    			}
    		disable_BLEND();
		restoreSceneColor();
	g_FBO0->deactivate();

	// POST PROCESS BLOOM (many FBO)
	g_BLOOM->pass0(g_FBO0->getTexture(), STAR_vec[0]->getBrightThreshold());
	g_BLOOM->restPasses();
	g_BLOOM->combine(g_FBO0->getTexture());

	// RENDER to FBO1, VOLUMETRIC LIGHT
	g_FBO1->activate();
		glUseProgram(g_VOLUMETRICLIGHT_PROGRAM);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, g_BLOOM->pTo_fbo_final->getTexture());
			glUniform1i(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "FullSampler"), 0);

			glActiveTexture(GL_TEXTURE1);                                
			glBindTexture(GL_TEXTURE_2D, g_BLOOM->texture_blured);
			glUniform1i(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "BlurSampler"), 1);

			glUniform4f(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "sun_pos"), -float(g_SCROLL_COORD_X)/w, -float(g_SCROLL_COORD_Y)/h, -100.0, 1.0);
          
			glActiveTexture(GL_TEXTURE0);
			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
	g_FBO1->deactivate();


	g_FBO2->activate();
		drawFullScreenTexturedQuad(g_FBO1->getTexture(), w, h, -999.0);
           
          	camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);    
        
		enable_DEPTH();  
    			for(unsigned int i = 0; i < visible_PLANET_vec.size(); i++) 
    			{ 
       				visible_PLANET_vec[i]->render_NEW(); 
    			}
    		
    			for(unsigned int i = 0; i < visible_ASTEROID_vec.size(); i++)
    			{ 
       				visible_ASTEROID_vec[i]->render_NEW(); 
    			}

    		disable_DEPTH();

    	          
		enable_BLEND();
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
        			restoreSceneColor();
    			}

    			for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    			{ 
    			    	visible_ROCKET_vec[i]->updateRenderStuff();
       				visible_ROCKET_vec[i]->render_inSpace(); 
       				restoreSceneColor();
    			}    	
		disable_BLEND();
		
    	g_FBO2->deactivate();


	// POST PROCESS WAVE SHOCK into FBO2
	g_FBO3->activate();

		float center_array[10][2];
		float xyz_array[10][3];
		float time_array[10];

		for (unsigned int i = 0; i < effect_SHOCKWAVE_vec.size(); i++)
		{         
			center_array[i][0] = effect_SHOCKWAVE_vec[i]->center.x - float(g_SCROLL_COORD_X)/g_VIEW_WIDTH;
			center_array[i][1] = effect_SHOCKWAVE_vec[i]->center.y - float(g_SCROLL_COORD_Y)/g_VIEW_HEIGHT;
			xyz_array[i][0] = effect_SHOCKWAVE_vec[i]->parameter.x;
			xyz_array[i][1] = effect_SHOCKWAVE_vec[i]->parameter.y;
			xyz_array[i][2] = effect_SHOCKWAVE_vec[i]->parameter.z;
				
			time_array[i] = effect_SHOCKWAVE_vec[i]->time;
		}
       

		glUseProgram(g_SHOCKWAVE_PROGRAM);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, g_FBO2->getTexture());
			glUniform1i (glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "sceneTex"), 0);

			int len_effect_SHOCKWAVE_list = effect_SHOCKWAVE_vec.size();
			glUniform1i (glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "imax"),        len_effect_SHOCKWAVE_list);
			glUniform2fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "center"),      len_effect_SHOCKWAVE_list, *center_array);
			glUniform3fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "shockParams"), len_effect_SHOCKWAVE_list, *xyz_array);
			glUniform1fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "time"),        len_effect_SHOCKWAVE_list, time_array);

			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
	
	g_FBO3->deactivate();


	// render from FBO
	glEnable(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);      // unbind fbo

	clearScreen();
	resetRenderTransformation();

	drawFullScreenTexturedQuad(g_FBO3->getTexture(), w, h, -999.0);
	//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug

	camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);
	
	enable_BLEND();
		for(unsigned int i = 0; i<effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		effect_LAZERTRACE_vec[i]->render(); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<effect_EXPLOSION_vec.size(); i++)
    			{ 
        			effect_EXPLOSION_vec[i]->render(); 
    			}

    			for(unsigned int i = 0; i<effect_DAMAGE_vec.size(); i++)
    			{ 
        			effect_DAMAGE_vec[i]->render(); 
    			}
    		disable_POINTSPRITE();
    		
    		for(unsigned int i = 0; i<text_DAMAGE_vec.size(); i++)
    		{ 
    		        text_DAMAGE_vec[i]->update(); 
        		text_DAMAGE_vec[i]->render(); 
    		}    		
    		
    	disable_BLEND();
    	
    	restoreSceneColor();    	          
}
    










    
void StarSystem :: renderEntities_OLD()
{   
	glLoadIdentity();
        renderBackground();
	
        camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);
        
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
        		restoreSceneColor();
    		}

    		for(unsigned int i = 0; i < visible_ROCKET_vec.size(); i++)
    		{ 
                        visible_ROCKET_vec[i]->updateRenderStuff();
       			visible_ROCKET_vec[i]->render_inSpace(); 
                        restoreSceneColor();
    		}

    		for(unsigned int i = 0; i<effect_LAZERTRACE_vec.size(); i++)
    		{ 
        		effect_LAZERTRACE_vec[i]->render(); 
    		}
    	disable_BLEND();


	enable_BLEND();
        enable_POINTSPRITE();
    		for(unsigned int i = 0; i<effect_EXPLOSION_vec.size(); i++)
    		{ 
        		effect_EXPLOSION_vec[i]->render(); 
    		}

    		for(unsigned int i = 0; i<effect_DAMAGE_vec.size(); i++)
    		{ 
        		effect_DAMAGE_vec[i]->render(); 
    		}
        disable_POINTSPRITE();
        disable_BLEND();

        for(unsigned int i = 0; i<text_DAMAGE_vec.size(); i++)
    	{ 
    	        text_DAMAGE_vec[i]->update(); 
        	text_DAMAGE_vec[i]->render(); 
    	}    		
    		
                
    	restoreSceneColor();
}
    


void StarSystem :: asteroidManager(int num)
{
        while (ASTEROID_vec.size() < num)
        {
                Asteroid* _asteroid = createAsteroid();
                add(_asteroid);
                break;
        }
}


void StarSystem :: add(Star* _star)
{
        _star->setStarSystem(this);
        STAR_vec.push_back(_star);
}

void StarSystem :: add(Planet* _planet)
{
        _planet->setStarSystem(this);
        PLANET_vec.push_back(_planet);
}
                
void StarSystem :: add(Asteroid* _asteroid)
{   
        _asteroid->setStarSystem(this);
        ASTEROID_vec.push_back(_asteroid);
}

void StarSystem :: add(Mineral* _mineral)
{
	_mineral->setStarSystem(this);
        MINERAL_vec.push_back(_mineral);
}

void StarSystem :: add(Container* _container)
{
	_container->setStarSystem(this);
        CONTAINER_vec.push_back(_container);
}


void StarSystem :: add(RocketBullet* _rocket)
{
	_rocket->setStarSystem(this);
	ROCKET_vec.push_back(_rocket);
}    

	

void StarSystem :: add(ShockWaveEffect* _shockWave)
{
	effect_SHOCKWAVE_vec.push_back(_shockWave);
}

void StarSystem :: add(LazerTraceEffect* _lazerTraceEffect)
{
	effect_LAZERTRACE_vec.push_back(_lazerTraceEffect);
}

void StarSystem :: add(ExplosionEffect* _explosionEffect)
{
	effect_EXPLOSION_vec.push_back(_explosionEffect);
}

void StarSystem :: add(DamageEffect* _damageEffect)
{
	effect_DAMAGE_vec.push_back(_damageEffect);
}
    
void StarSystem :: add(VerticalFlowText* _text)
{
	text_DAMAGE_vec.push_back(_text);
}
    	
    		
void StarSystem :: add(DistantNebulaBgEffect* dn)
{
	distantNebulaBgEffect_vec.push_back(dn);
}

void StarSystem :: add(DistantStarBgEffect* ds)
{
	distantStarBgEffect_vec.push_back(ds);
}
    		

    		
void StarSystem :: manageDeadObjects()
{  
	{
	
   	for(unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
    	{
               	if (SHIP_inSPACE_vec[ki]->getAlive() == false)
        	{           
            		SHIP_inSPACE_vec[ki]->getNpc()->setAlive(false);
               
            		garbage.add(SHIP_inSPACE_vec[ki]);
            		SHIP_inSPACE_vec.erase(SHIP_inSPACE_vec.begin() + ki);
        	} 
    	}
    	for(unsigned int ni = 0; ni < NPC_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		garbage.add(NPC_inSPACE_vec[ni]);
            		NPC_inSPACE_vec.erase(NPC_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	//
    	for(unsigned int ni = 0; ni < NPC_RANGER_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_RANGER_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		NPC_RANGER_inSPACE_vec.erase(NPC_RANGER_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_WARRIOR_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_WARRIOR_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		NPC_WARRIOR_inSPACE_vec.erase(NPC_WARRIOR_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	    	
    	for(unsigned int ni = 0; ni < NPC_TRADER_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_TRADER_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		NPC_TRADER_inSPACE_vec.erase(NPC_TRADER_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_PIRAT_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_PIRAT_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		NPC_PIRAT_inSPACE_vec.erase(NPC_PIRAT_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	
    	for(unsigned int ni = 0; ni < NPC_DIPLOMAT_inSPACE_vec.size(); ni++)
    	{
	        if (NPC_DIPLOMAT_inSPACE_vec[ni]->getAlive() == false)
        	{   
            		NPC_DIPLOMAT_inSPACE_vec.erase(NPC_DIPLOMAT_inSPACE_vec.begin() + ni);
            		
        	} 
    	}
    	//
    	
    	}

    	


    	for(unsigned int i = 0; i < ASTEROID_vec.size(); i++)
    	{
        	if (ASTEROID_vec[i]->getAlive() == false)
        	{
            		garbage.add(ASTEROID_vec[i]);
            		ASTEROID_vec.erase(ASTEROID_vec.begin() + i );
            	}
        } 
    

    	for(unsigned int i = 0; i < MINERAL_vec.size(); i++)
    	{
        	if (MINERAL_vec[i]->getAlive() == false)
        	{  
            		garbage.add(MINERAL_vec[i]);
            		MINERAL_vec.erase(MINERAL_vec.begin() + i );
        	} 
    	}
    
    	for(unsigned int i = 0; i < CONTAINER_vec.size(); i++)
    	{
        	if (CONTAINER_vec[i]->getAlive() == false)
        	{   
            		garbage.add(CONTAINER_vec[i]);
            		CONTAINER_vec.erase(CONTAINER_vec.begin() + i );
        	}	 
    	}

    	for(unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
    	{
        	if (ROCKET_vec[ri]->getAlive() == false)
        	{   
            		garbage.add(ROCKET_vec[ri]);
            		ROCKET_vec.erase(ROCKET_vec.begin() + ri );
        	} 
    	}
    
    
    
    
    
    	// effects
    	for (unsigned int wi = 0; wi < effect_SHOCKWAVE_vec.size(); wi++)
    	{
    		if (effect_SHOCKWAVE_vec[wi]->is_alive == false)
    		{
    			garbage.add(effect_SHOCKWAVE_vec[wi]);
    	   		effect_SHOCKWAVE_vec.erase(effect_SHOCKWAVE_vec.begin() + wi);
    		}
    	}


    	for (unsigned int lei = 0; lei < effect_LAZERTRACE_vec.size(); lei++)
    	{
         	if (effect_LAZERTRACE_vec[lei]->getAlive() == false)
         	{   
           		garbage.add(effect_LAZERTRACE_vec[lei]);
            		effect_LAZERTRACE_vec.erase(effect_LAZERTRACE_vec.begin() + lei);
         	} 
    	}


    	for(unsigned int i = 0; i<effect_EXPLOSION_vec.size(); i++)  
    	{
        	if (effect_EXPLOSION_vec[i]->getAlive() == false)
        	{   
            		garbage.add(effect_EXPLOSION_vec[i]);
            		effect_EXPLOSION_vec.erase(effect_EXPLOSION_vec.begin() + i );
        	} 
    	}

    	for(unsigned int edi = 0; edi < effect_DAMAGE_vec.size(); edi++)    
    	{
        	if (effect_DAMAGE_vec[edi]->getAlive() == false)
        	{   
            		garbage.add(effect_DAMAGE_vec[edi]);
            		effect_DAMAGE_vec.erase(effect_DAMAGE_vec.begin() + edi);
        	} 
    	}

    	for(unsigned int ti = 0; ti < text_DAMAGE_vec.size(); ti++)    
    	{
        	if (text_DAMAGE_vec[ti]->getAlive() == false)
        	{   
            		garbage.add(text_DAMAGE_vec[ti]);
            		text_DAMAGE_vec.erase(text_DAMAGE_vec.begin() + ti);
        	} 
    	}

        // effects
}

     


void StarSystem :: removeAllReferencesToDeadObjects()
{
    	for(unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
    	{ 
		SHIP_inSPACE_vec[ki]->removeWeaponSlotDeadTargets(); 
	}

}	
     
     
               


void StarSystem :: mouseControl()
{   
    	bool cursor_has_target = false;   
 
    	int mxvp = g_MOUSE_POS_X                 + g_SCROLL_COORD_X;
    	int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y + g_SCROLL_COORD_Y;

    	bool mlb = g_MOUSE_LEFT_BUTTON;
    	bool mrb = g_MOUSE_RIGHT_BUTTON;

	if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
	{
    		pPLAYER->getShip()->selectWeapons();                   				       
    		pPLAYER->getShip()->resetDeselectedWeaponTargets();

        	pPLAYER->getShip()->renderWeaponIcons();
        }


	/* NOTE: the intersection must be checked in order from small objects to huge */
	

    	if (cursor_has_target == false) 
    	{
        	for (unsigned int mi = 0; mi < visible_MINERAL_vec.size(); mi++)
        	{ 
            		float mineral_cursor_dist = distBetweenCenters(visible_MINERAL_vec[mi]->getPoints()->getCenter(), mxvp, myvp);
            		if (mineral_cursor_dist < visible_MINERAL_vec[mi]->getCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_MINERAL_vec[mi]->updateInfo(); 
               			visible_MINERAL_vec[mi]->renderInfo(); 

				if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
				{
               				if (mlb == true)
               				{
                   				pPLAYER->getShip()->selectWeapons();
                   				pPLAYER->getShip()->setWeaponsTarget(visible_MINERAL_vec[mi]);

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
            		float container_cursor_dist = distBetweenCenters(visible_CONTAINER_vec[ci]->getPoints()->getCenter(), mxvp, myvp);
            		if (container_cursor_dist < visible_CONTAINER_vec[ci]->getCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_CONTAINER_vec[ci]->renderInfo(); 

				if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
				{
               				if (mlb == true)
               				{
                   				pPLAYER->getShip()->selectWeapons();                   					    
                   				pPLAYER->getShip()->setWeaponsTarget(visible_CONTAINER_vec[ci]);
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
            		float asteroid_cursor_dist = distBetweenCenters(visible_ASTEROID_vec[ai]->getPoints()->getCenter(), mxvp, myvp);
            		if (asteroid_cursor_dist < visible_ASTEROID_vec[ai]->getCollisionRadius())
            		{   
                		cursor_has_target = true;

                		visible_ASTEROID_vec[ai]->updateInfo(); 
                		visible_ASTEROID_vec[ai]->renderInfo(); 

				if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
				{
                			if (mlb == true)
                			{ 
                   				pPLAYER->getShip()->selectWeapons();                   					    
                   				pPLAYER->getShip()->setWeaponsTarget(visible_ASTEROID_vec[ai]);
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
            		float ship_cursor_dist = distBetweenCenters(visible_SHIP_vec[ki]->getPoints()->getCenter(), mxvp, myvp);
            		if (ship_cursor_dist < visible_SHIP_vec[ki]->getCollisionRadius())
            		{ 
                		cursor_has_target = true;

                		visible_SHIP_vec[ki]->renderInfo(); 
                		visible_SHIP_vec[ki]->renderWeaponIcons();
                
				if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
				{
                			if (mlb == true)
                			{
                   				pPLAYER->getShip()->selectWeapons();
                   				pPLAYER->getShip()->setWeaponsTarget(visible_SHIP_vec[ki]);
					}

                			if (mrb == true)
                			{
                   				if ( pPLAYER->getPilot()->checkPossibilityToScan(visible_SHIP_vec[ki]) == true )
                   				{
                        				pPLAYER->getPilot()->setScanTarget(visible_SHIP_vec[ki]);
                        				pPLAYER->setScanFlag(true);
                        				pSHIP_GUI->configure(pPLAYER->getPilot()->getScanShip(), false, false);   
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
            		float planet_cursor_dist = distBetweenCenters(visible_PLANET_vec[pi]->getPoints()->getCenter(), mxvp, myvp);
            		if (planet_cursor_dist < visible_PLANET_vec[pi]->getCollisionRadius())
            		{   
                		cursor_has_target = true;

                		visible_PLANET_vec[pi]->updateInfo(); 
                		visible_PLANET_vec[pi]->renderInfo(); 

				if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
				{
                			if (mlb == true)
                			{
                    				pPLAYER->getShip()->getNavigator()->setTarget(visible_PLANET_vec[pi]);  
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
            		float cursor_dist = distBetweenCenters(visible_STAR_vec[si]->getPoints()->getCenter(), mxvp, myvp);
            		if (cursor_dist < visible_STAR_vec[si]->getCollisionRadius())
            		{   
               			cursor_has_target = true;

               			visible_STAR_vec[si]->updateInfo(); 
               			visible_STAR_vec[si]->renderInfo(); 

               			break; 
            		}
        	}
    	}



    	if (cursor_has_target == false) 
    	{
		if ( (pPLAYER->getAlive() == true) and (pPLAYER->getShip() != NULL) )
		{
        		if (mlb == true)
        		{
            			pPLAYER->getShip()->getNavigator()->setStaticTargetCoords(vec2f(mxvp, myvp));  
        		}
        	}
   	}     
}





void StarSystem :: fireEvents_TRUE(int timer)
{
     for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
         SHIP_inSPACE_vec[ki]->weaponsFire_TRUE(timer);
}

void StarSystem :: fireEvents_FALSE(int timer)
{
     for (unsigned int ki = 0; ki < SHIP_inSPACE_vec.size(); ki++)
         SHIP_inSPACE_vec[ki]->weaponsFire_FALSE(timer);
}







//// ******* TRANSITION ******* 
void StarSystem :: addToHyperJumpQueue(Npc* _npc)
{
        NPC_appear_vec.push_back(_npc);
}

void StarSystem :: postHyperJumpEvent()
{
        for (unsigned int i = 0; i<NPC_appear_vec.size(); i++)
        {
                NPC_appear_vec[i]->setDoNothing();
                
                moveToSpace(NPC_appear_vec[i]);
                moveToSpace(NPC_appear_vec[i]->getShip());                
        }
              
        NPC_appear_vec.clear();  
}

void StarSystem :: moveToSpace(Ship* _ship)
{
     	_ship->setPlaceTypeId(SPACE_ID);
     	_ship->setStarSystem(this);  

     	SHIP_inSPACE_vec.push_back(_ship);
}

void StarSystem :: moveToSpace(Npc* _npc)
{
     	int _race_id = _npc->getRaceId();
     	int _subtype_id = _npc->getSubTypeId();

     	_npc->setPlaceTypeId(SPACE_ID);
     	_npc->setStarSystem(this);  

     	NPC_inSPACE_vec.push_back(_npc);

     	if (_subtype_id == RANGER_ID)
         	NPC_RANGER_inSPACE_vec.push_back(_npc);
     	if (_subtype_id == WARRIOR_ID)
         	NPC_WARRIOR_inSPACE_vec.push_back(_npc);
     	if (_subtype_id == TRADER_ID)
         	NPC_TRADER_inSPACE_vec.push_back(_npc);
     	if (_subtype_id == PIRAT_ID)
         	NPC_PIRAT_inSPACE_vec.push_back(_npc);
     	if (_subtype_id == DIPLOMAT_ID)
         	NPC_DIPLOMAT_inSPACE_vec.push_back(_npc);
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

        if (_subtype_id == RANGER_ID)
                removeFromTheListById(&NPC_RANGER_inSPACE_vec, _id);
        if (_subtype_id == WARRIOR_ID)
                removeFromTheListById(&NPC_WARRIOR_inSPACE_vec, _id);
        if (_subtype_id == TRADER_ID)
                removeFromTheListById(&NPC_TRADER_inSPACE_vec, _id);
        if (_subtype_id == PIRAT_ID)
                removeFromTheListById(&NPC_PIRAT_inSPACE_vec, _id);
        if (_subtype_id == DIPLOMAT_ID)
                removeFromTheListById(&NPC_DIPLOMAT_inSPACE_vec, _id);
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



void StarSystem :: debug__()
{
        if (MINERAL_vec.size() > 1000)
        {
                for (unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
                {
                        MINERAL_vec[mi]->hit_TRUE(100);
                }
        }
}





template <typename AGRESSOR, typename VICTIM>
bool collideEvent_TRUE(AGRESSOR* agressor,  VICTIM* victim)
{
	if (collisionBetweenCenters(agressor->getPoints(), victim->getPoints(), victim->getCollisionRadius()) == true)
        {
        	victim->hit_TRUE(agressor->getDamage());
                agressor->collision_TRUE();
                
                return true;
        }
        else
        {
        	return false;
        }
}





bool collisionBetweenCenters(Points* points1, Points* points2, float collision_radius)
{
    if(abs(points1->getCenter().x - points2->getCenter().x) > collision_radius)
       return false;
    if(abs(points1->getCenter().y - points2->getCenter().y) > collision_radius)
       return false;

    return true;
}

bool collisionBetweenCenters(Points* points1, float center2_x, float center2_y, float collision_radius)
{
    if(abs(points1->getCenter().x - center2_x) > collision_radius)
       return false;
    if(abs(points1->getCenter().y - center2_y) > collision_radius)
       return false;

    return true;
}











bool isObjectVisible(Points* points, float startViewCoord_x, float startViewCoord_y)    
{
        float ob_centerx = points->getCenter().x;
        float ob_centery = points->getCenter().y;
        
        int ob_w = points->getWidth();
        int ob_h = points->getHeight();
        
        if (ob_centerx < (g_SCROLL_COORD_X - ob_w))
                return false;
        if (ob_centerx > (startViewCoord_x + ob_w))
                return false;
        if (ob_centery < (g_SCROLL_COORD_Y - ob_h))
                return false;
        if (ob_centery > (startViewCoord_y + ob_h))
                return false;

        return true;
}


bool isObjectVisible(float ob_centerx, float ob_centery, int ob_w, int ob_h, float startViewCoord_x, float startViewCoord_y)    
{
    	if (ob_centerx < (g_SCROLL_COORD_X - ob_w))
       		return false;
    	if (ob_centerx > (startViewCoord_x + ob_w))
       		return false;
   	if (ob_centery < (g_SCROLL_COORD_Y - ob_h))
       		return false;
    	if (ob_centery > (startViewCoord_y + ob_h))
       		return false;

    	return true;
}




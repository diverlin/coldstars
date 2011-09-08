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


#include "starsystem.h"
#include <GL/glew.h>

StarSystem :: StarSystem()
{ 
    id = g_ENTITY_ID_GENERATOR.returnNextId();
    is_CAPTURED = false;
}

StarSystem :: ~StarSystem()
{}
      

void StarSystem ::setPositionOnWorldMap(Rect rect)
{
     rect_onMap = rect;
}



void StarSystem :: rocketCollision_TRUE()
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_pList.size(); ri++)
        {
                for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
                {
                        if (ROCKET_pList[ri]->owner_id != SHIP_pList[ki]->id)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), SHIP_pList[ki]->getPoints(), SHIP_pList[ki]->collision_radius) == true)
                                {
                                        SHIP_pList[ki]->hit_TRUE(ROCKET_pList[ri]->damage);
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                if (collide == false)
                {
                        for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), ASTEROID_pList[ai]->getPoints(), ASTEROID_pList[ai]->getCollisionRadius()) == true)
                                {   
                                        ASTEROID_pList[ai]->hit_TRUE(ASTEROID_pList[ai]->getArmor());
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                if (collide == false)
                {
                        for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), MINERAL_pList[mi]->getPoints(), MINERAL_pList[mi]->w) == true)
                                {   
                                        MINERAL_pList[mi]->death_TRUE();
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                //if collide == False:
                        //for sp in self.SPUTNIK_list:
                                //if collisionBetweenCenters(r.points.center, sp.points.center, sp.collision_threshold):
                                        //sp.hit(r.owner, r)
                                        //r.hit(r.owner, r)
                                        //collide = True
                                        //break

                if (collide == false)
                {
                        for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), CONTAINER_pList[ci]->getPoints(), CONTAINER_pList[ci]->w) == true)
                                {   
                                        CONTAINER_pList[ci]->death_TRUE();
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }
                
                //if collide == False:
                        //for b in self.BOMB_list:
                                //if collisionBetweenCenters(r.points.center, b.points.center, b.collision_threshold):
                                        //b.hit(r.owner, r)
                                        //r.hit(r.owner, r)
                                        //collide = True
                                        //break
        }
}





void StarSystem :: rocketCollision_FALSE()
{
        bool collide = false;
        for (unsigned int ri = 0; ri < ROCKET_pList.size(); ri++)
        {
                for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
                {
                        if (ROCKET_pList[ri]->owner_id != SHIP_pList[ki]->id)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), SHIP_pList[ki]->getPoints(), SHIP_pList[ki]->collision_radius) == true)
                                {
                                        SHIP_pList[ki]->hit_FALSE(ROCKET_pList[ri]->damage);
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                if (collide == false)
                {
                        for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), ASTEROID_pList[ai]->getPoints(), ASTEROID_pList[ai]->getCollisionRadius()) == true)
                                {   
                                        ASTEROID_pList[ai]->hit_TRUE(ASTEROID_pList[ai]->getArmor());
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                if (collide == false)
                {
                        for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), MINERAL_pList[mi]->getPoints(), MINERAL_pList[mi]->w) == true)
                                {   
                                        MINERAL_pList[mi]->death_FALSE();
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }


                //if collide == False:
                        //for sp in self.SPUTNIK_list:
                                //if collisionBetweenCenters(r.points.center, sp.points.center, sp.collision_threshold):
                                        //sp.hit(r.owner, r)
                                        //r.hit(r.owner, r)
                                        //collide = True
                                        //break

                if (collide == false)
                {
                        for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
                        {
                                if (collisionBetweenCenters(ROCKET_pList[ri]->getPoints(), CONTAINER_pList[ci]->getPoints(), CONTAINER_pList[ci]->w) == true)
                                {   
                                        CONTAINER_pList[ci]->death_FALSE();
                                        ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                                        collide = true;
                                        break;
                                }
                        }
                }

                //if collide == False:
                        //for b in self.BOMB_list:
                                //if collisionBetweenCenters(r.points.center, b.points.center, b.collision_threshold):
                                        //b.hit(r.owner, r)
                                        //r.hit(r.owner, r)
                                        //collide = True
                                        //break
     }
}



void StarSystem :: asteroidCollision_TRUE()
{
    for(unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
    {
        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), SHIP_pList[ki]->getPoints(), SHIP_pList[ki]->collision_radius) )
               {
                   ASTEROID_pList[ai]->hit_TRUE(ASTEROID_pList[ai]->getArmor());
                   SHIP_pList[ki]->hit_TRUE( (ASTEROID_pList[ai]->getArmor()) * 10 );
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   break;
               }

        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), PLANET_pList[pi]->getPoints(), PLANET_pList[pi]->getCollisionRadius()) == true )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->hit_TRUE(ASTEROID_pList[ai]->getArmor());
                   break;
               }
                
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(a.points.center, sp.points.cente, sp.collision_threshold):
                        //sp.hit(a, a)
                        //a.hit(a, a)
                        //break

        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int si = 0; si < STAR_pList.size(); si++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), STAR_pList[si]->getPoints(), STAR_pList[si]->getCollisionRadius() ) == true )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->hit_TRUE(ASTEROID_pList[ai]->getArmor());
                   break;
               }
                        
    }

}



void StarSystem :: asteroidCollision_FALSE()
{
    for(unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
    {
        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), SHIP_pList[ki]->getPoints(), SHIP_pList[ki]->collision_radius) )
               {
                   ASTEROID_pList[ai]->hit_FALSE(ASTEROID_pList[ai]->getArmor());
                   SHIP_pList[ki]->hit_FALSE( (ASTEROID_pList[ai]->getArmor()) * 10 );
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   break;
               }

        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), PLANET_pList[pi]->getPoints(), PLANET_pList[pi]->getCollisionRadius()) == true )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->hit_FALSE(ASTEROID_pList[ai]->getArmor());
                   break;
               }
                
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(a.points.center, sp.points.cente, sp.collision_threshold):
                        //sp.hit(a, a)
                        //a.hit(a, a)
                        //break

        if (ASTEROID_pList[ai]->getAlive() == true)   
           for (unsigned int si = 0; si < STAR_pList.size(); si++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->getPoints(), STAR_pList[si]->getPoints(), STAR_pList[si]->getCollisionRadius()) == true )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->hit_FALSE(ASTEROID_pList[ai]->getArmor());
                   break;
               }
                        
    }

}


void StarSystem :: updateEntities_inDynamic_TRUE()
{
    for (unsigned int si = 0; si < STAR_pList.size(); si++)
        STAR_pList[si]->update_inSpace_inDynamic(); 

    for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
        PLANET_pList[pi]->update_inSpace_inDynamic(); 
    
    for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
        MINERAL_pList[mi]->update_inSpace_inDynamic_TRUE(); 
     
    for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
        CONTAINER_pList[ci]->update_inSpace_inDynamic_TRUE(); 

    for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++) 
        ASTEROID_pList[ai]->update_inSpace_inDynamic_TRUE(); 
    
    pTo_PLAYER->update_inSpace_inDynamic();
    for (unsigned int ni = 0; ni < NPC_pList.size(); ni++)
        NPC_pList[ni]->taskExecution_inDynamic(); 
    
    for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
        SHIP_pList[ki]->update_inSpace_inDynamic_TRUE(); 
    
    for (unsigned int ri = 0; ri < ROCKET_pList.size(); ri++)
        ROCKET_pList[ri]->update_inSpace_inDynamic(); 



    //for (unsigned int ki = 0; ki < SHIP_forLandingEvent_pList.size(); ki++)
    //{
        //if (SHIP_forLandingEvent_pList[ki]->owner_type_id == PLAYER_ID)
            //SHIP_forLandingEvent_pList[ki]->pTo_playerOwner->landingEvent();
    //}
}  
      
     

void StarSystem :: updateEntities_inDynamic_FALSE()
{
    for (unsigned int si = 0; si < STAR_pList.size(); si++)
        STAR_pList[si]->update_inSpace_inDynamic(); 

    for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
        PLANET_pList[pi]->update_inSpace_inDynamic(); 
    
    for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
        MINERAL_pList[mi]->update_inSpace_inDynamic_FALSE(); 
     
    for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
        CONTAINER_pList[ci]->update_inSpace_inDynamic_FALSE(); 

    for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++) 
        ASTEROID_pList[ai]->update_inSpace_inDynamic_FALSE(); 
    
    pTo_PLAYER->update_inSpace_inDynamic(); // remove
    for (unsigned int ni = 0; ni < NPC_pList.size(); ni++)
        NPC_pList[ni]->taskExecution_inDynamic(); 

    for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
        SHIP_pList[ki]->update_inSpace_inDynamic_FALSE(); 
    
    for (unsigned int ri = 0; ri < ROCKET_pList.size(); ri++)
        ROCKET_pList[ri]->update_inSpace_inDynamic(); 
}  
  
 
      
void StarSystem :: updateEntities_inStatic()
{
     // called once per TURN
     for(unsigned int ni = 0; ni < NPC_pList.size(); ni++)
     {
         NPC_pList[ni]->thinkCommon_inSpace_inStatic();
         NPC_pList[ni]->thinkUnique_inSpace_inStatic();
     }

     for(unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
     {
         PLANET_pList[pi]->update_inSpace_inStatic();
     }
}

      

void StarSystem :: findVisibleEntities()
{
    float startViewCoord_x = g_SCROLL_COORD_X + g_VIEW_WIDTH;
    float startViewCoord_y = g_SCROLL_COORD_Y + g_VIEW_HEIGHT;

    visible_STAR_pList.clear();
    visible_PLANET_pList.clear();
    //self.visible_SPUTNIK_list      = []
    visible_ASTEROID_pList.clear();
    visible_MINERAL_pList.clear();
    visible_CONTAINER_pList.clear();
    //self.visible_BOMB_list         = []
    visible_SHIP_pList.clear();
    visible_ROCKET_pList.clear();
    //self.visible_BLACKHOLE_list    = []

    //self.visible_effect_EXPLOSION_list = []
    //self.visible_effect_DAMAGE_list    = []

    for (unsigned int i = 0; i < STAR_pList.size(); i++)
    {
        if (isObjectVisible(STAR_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_STAR_pList.push_back(STAR_pList[i]); 
    }
    
    for (unsigned int i = 0; i < PLANET_pList.size(); i++)
    {
        if (isObjectVisible(PLANET_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_PLANET_pList.push_back(PLANET_pList[i]);  
    }
    
   
    //self.visible_SPUTNIK_list   = [s for s in self.SPUTNIK_list   if isObjectVisible((s.points.center[0], s.points.center[1]), (s.w, s.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    for (unsigned int i = 0; i < ASTEROID_pList.size(); i++)
    {
        if (isObjectVisible(ASTEROID_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_ASTEROID_pList.push_back(ASTEROID_pList[i]); 
    }
   
    for (unsigned int i = 0; i < MINERAL_pList.size(); i++)
    {
        if (isObjectVisible(MINERAL_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_MINERAL_pList.push_back(MINERAL_pList[i]);  
    }
    
    for (unsigned int i = 0; i < CONTAINER_pList.size(); i++)
    {
       // if (isObjectVisible(CONTAINER_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_CONTAINER_pList.push_back(CONTAINER_pList[i]);  
    }

    //self.visible_BOMB_list      = [b for b in self.BOMB_list      if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    
    for (unsigned int i = 0; i < SHIP_pList.size(); i++)
    {
        if (isObjectVisible(SHIP_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_SHIP_pList.push_back(SHIP_pList[i]); 
    }
    
    for (unsigned int i = 0; i < ROCKET_pList.size(); i++)
    {
        if (isObjectVisible(ROCKET_pList[i]->getPoints(), startViewCoord_x, startViewCoord_y))    
           visible_ROCKET_pList.push_back(ROCKET_pList[i]); 
    }

    //self.visible_BLACKHOLE_list = [b for b in self.BLACKHOLE_list if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]

    //self.visible_effect_EXPLOSION_list = [e for e in self.effect_EXPLOSION_list if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    //self.visible_effect_DAMAGE_list    = [e for e in self.effect_DAMAGE_list    if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
}

      

//void StarSystem :: setSceneColor(Color _color)
//{
//	color = _color;
	//if (_pTo_texOb->color_id == YELLOW_COLOR_ID)
	//{
		//color.r = 255/255.0;
		//color.g = 255/255.0;
		//color.b = 255/220.0;
		//color.a = 1.0;
	//}
	
	//if (_pTo_texOb->color_id == BLUE_COLOR_ID)
	//{
		//color.r = 220/255.0;
		//color.g = 255/255.0;
		//color.b = 255/255.0;
		//color.a = 1.0;
	//}
//}
      
void StarSystem :: restoreSceneColor()
{
        setColor(STAR_pList[0]->getColor());
}     

void StarSystem :: restoreDefaultColor()
{
	Color _color;
	_color.r = 1.0;
	_color.g = 1.0;
	_color.b = 1.0;
	_color.a = 1.0;
	
	setColor(_color);
}


void StarSystem :: renderBackground()
{   
	// HACK for point sprites
    	enable_POINTSPRITE();
    		distantStarBgEffect_pList[0]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    	disable_POINTSPRITE();
    	// HACK for point sprites

	clearScreen();

        restoreSceneColor();

    	enable_BLEND();
		glDepthMask(false);

    		for(unsigned int i = 0; i<distantNebulaBgEffect_pList.size(); i++)
    		{ 
       			distantNebulaBgEffect_pList[i]->update(); 
        		distantNebulaBgEffect_pList[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<distantStarBgEffect_pList.size(); i++)
    			{ 
       				distantStarBgEffect_pList[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    			}
    		disable_POINTSPRITE();
    	
		glDepthMask(true);
	disable_BLEND();
}
    
void StarSystem :: createPostProcessStuff()
{
	int w = g_VIEW_WIDTH;
	int h = g_VIEW_HEIGHT;

	pTo_fbo0 = new FBO(w,h);
	pTo_fbo1 = new FBO(w,h);	
	pTo_fbo2 = new FBO(w,h);
	pTo_fbo3 = new FBO(w,h);
	pTo_bloom = new BloomEffect(w, h, g_BLUR_PROGRAM, g_EXTRACT_BRIGHT_PROGRAM, g_COMBINE_PROGRAM, 1, 1);
}

    
void StarSystem :: renderEntities_NEW()
{   
	int w = g_VIEW_WIDTH;
	int h = g_VIEW_HEIGHT;


	//######### EFFECT DEMONSTRATION
	//if lb == True:
	//#for x in xrange(0, 10):
		//#addExplosion(player)
	//pass
 
	//if rb == True:
	//self.shockwaveEffect_list = []
	//self.shockwaveEffect_remove_queue = []
	//######### EFFECT DEMONSTRATION


	pTo_fbo0->activate();
   
        	renderBackground();           
		camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);    
	        

		restoreDefaultColor();
		enable_BLEND();
			for(unsigned int i = 0; i < visible_STAR_pList.size(); i++) 
			{ 
        			visible_STAR_pList[i]->render_NEW(); 
    			}
    		disable_BLEND();
		restoreSceneColor();
	pTo_fbo0->deactivate();

	// POST PROCESS BLOOM (many FBO)
	pTo_bloom->pass0(pTo_fbo0->texture, STAR_pList[0]->getBrightThreshold());
	pTo_bloom->restPasses();
	pTo_bloom->combine(pTo_fbo0->texture);

	// RENDER to FBO1, VOLUMETRIC LIGHT
	pTo_fbo1->activate();
		glUseProgram(g_VOLUMETRICLIGHT_PROGRAM);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, pTo_bloom->pTo_fbo_final->texture);
			glUniform1i(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "FullSampler"), 0);

			glActiveTexture(GL_TEXTURE1);                                
			glBindTexture(GL_TEXTURE_2D, pTo_bloom->texture_blured);
			glUniform1i(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "BlurSampler"), 1);

			glUniform4f(glGetUniformLocation(g_VOLUMETRICLIGHT_PROGRAM, "sun_pos"), -float(g_SCROLL_COORD_X)/w, -float(g_SCROLL_COORD_Y)/h, -100.0, 1.0);
          
			glActiveTexture(GL_TEXTURE0);
			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
	pTo_fbo1->deactivate();


	pTo_fbo2->activate();
		drawFullScreenTexturedQuad(pTo_fbo1->texture, w, h, -999.0);
           
          	camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);    
        
		enable_DEPTH();  
    			for(unsigned int i = 0; i < visible_PLANET_pList.size(); i++) 
    			{ 
       				visible_PLANET_pList[i]->render_NEW(); 
    			}
    		
    			for(unsigned int i = 0; i < visible_ASTEROID_pList.size(); i++)
    			{ 
       				visible_ASTEROID_pList[i]->render_NEW(); 
    			}

    		disable_DEPTH();

    	          
		enable_BLEND();
    			for(unsigned int i = 0; i < visible_MINERAL_pList.size(); i++)
			{ 
        			visible_MINERAL_pList[i]->render2D(); 
    			}  
           
    			for(unsigned int i = 0; i < visible_CONTAINER_pList.size(); i++)
    			{ 
        			visible_CONTAINER_pList[i]->render2D(); 
    			} 	 
           

    			for(unsigned int i = 0; i < visible_SHIP_pList.size(); i++)
    			{ 
       				visible_SHIP_pList[i]->renderInSpace(); 
        			restoreSceneColor();
    			}

    			for(unsigned int i = 0; i < visible_ROCKET_pList.size(); i++)
    			{ 
       				visible_ROCKET_pList[i]->renderInSpace(); 
       				restoreSceneColor();
    			}    	
		disable_BLEND();
		
    	pTo_fbo2->deactivate();


	// POST PROCESS WAVE SHOCK into FBO2
	pTo_fbo3->activate();

		float center_array[10][2];
		float xyz_array[10][3];
		float time_array[10];

		for (unsigned int i = 0; i < effect_SHOCKWAVE_pList.size(); i++)
		{         
			effect_SHOCKWAVE_pList[i]->update();
	
			center_array[i][0] = effect_SHOCKWAVE_pList[i]->center_x - float(g_SCROLL_COORD_X)/g_VIEW_WIDTH;
			center_array[i][1] = effect_SHOCKWAVE_pList[i]->center_y - float(g_SCROLL_COORD_Y)/g_VIEW_HEIGHT;
			xyz_array[i][0] = effect_SHOCKWAVE_pList[i]->x;
			xyz_array[i][1] = effect_SHOCKWAVE_pList[i]->y;
			xyz_array[i][2] = effect_SHOCKWAVE_pList[i]->z;
				
			time_array[i] = effect_SHOCKWAVE_pList[i]->time;
		}
       

		glUseProgram(g_SHOCKWAVE_PROGRAM);
			glActiveTexture(GL_TEXTURE0);                                
			glBindTexture(GL_TEXTURE_2D, pTo_fbo2->texture);
			glUniform1i (glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "sceneTex"), 0);

			int len_effect_SHOCKWAVE_list = effect_SHOCKWAVE_pList.size();
			glUniform1i (glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "imax"),        len_effect_SHOCKWAVE_list);
			glUniform2fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "center"),      len_effect_SHOCKWAVE_list, *center_array);
			glUniform3fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "shockParams"), len_effect_SHOCKWAVE_list, *xyz_array);
			glUniform1fv(glGetUniformLocation(g_SHOCKWAVE_PROGRAM, "time"),        len_effect_SHOCKWAVE_list, time_array);

			drawFullScreenQuad(w, h, -999.0);
		glUseProgram(0);
	
	pTo_fbo3->deactivate();


	// render from FBO
	glEnable(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);      // unbind fbo

	clearScreen();

	drawFullScreenTexturedQuad(pTo_fbo3->texture, w, h, -999.0);
	//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug

	camera(g_SCROLL_COORD_X, g_SCROLL_COORD_Y);
	
	enable_BLEND();
		for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)
    		{ 
       			effect_LAZERTRACE_pList[i]->update(); 
        		effect_LAZERTRACE_pList[i]->render(); 
    		}

    		enable_POINTSPRITE();
    			for(unsigned int i = 0; i<effect_EXPLOSION_pList.size(); i++)
    			{ 
       				effect_EXPLOSION_pList[i]->update();
        			effect_EXPLOSION_pList[i]->render(); 
    			}

    			for(unsigned int i = 0; i<effect_DAMAGE_pList.size(); i++)
    			{ 
       				effect_DAMAGE_pList[i]->update();
        			effect_DAMAGE_pList[i]->render(); 
    			}
    		disable_POINTSPRITE();
    		
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
		for(unsigned int i = 0; i < visible_STAR_pList.size(); i++) 
		{ 
        		visible_STAR_pList[i]->render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_PLANET_pList.size(); i++) 
    		{ 
       			visible_PLANET_pList[i]->render_OLD(); 
    		}

    		for(unsigned int i = 0; i < visible_ASTEROID_pList.size(); i++)
    		{ 
       			visible_ASTEROID_pList[i]->render_OLD(); 
    		}
        disable_DEPTH();

        enable_BLEND();
    		for(unsigned int i = 0; i < visible_MINERAL_pList.size(); i++)
		{ 
        		visible_MINERAL_pList[i]->render2D(); 
    		}  
           
    		for(unsigned int i = 0; i < visible_CONTAINER_pList.size(); i++)
    		{ 
        		visible_CONTAINER_pList[i]->render2D(); 
    		} 	 
           
    		for(unsigned int i = 0; i < visible_SHIP_pList.size(); i++)
    		{ 
       			visible_SHIP_pList[i]->renderInSpace(); 
        		restoreSceneColor();
    		}

    		for(unsigned int i = 0; i < visible_ROCKET_pList.size(); i++)
    		{ 
       			visible_ROCKET_pList[i]->renderInSpace(); 
    		}

    		for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)
    		{ 
       			effect_LAZERTRACE_pList[i]->update(); 
        		effect_LAZERTRACE_pList[i]->render(); 
    		}
    	disable_BLEND();


	enable_BLEND();
        enable_POINTSPRITE();
    		for(unsigned int i = 0; i<effect_EXPLOSION_pList.size(); i++)
    		{ 
       			effect_EXPLOSION_pList[i]->update();
        		effect_EXPLOSION_pList[i]->render(); 
    		}

    		for(unsigned int i = 0; i<effect_DAMAGE_pList.size(); i++)
    		{ 
       			effect_DAMAGE_pList[i]->update();
        		effect_DAMAGE_pList[i]->render(); 
    		}
        disable_POINTSPRITE();
        disable_BLEND();

    	restoreSceneColor();
}
    


void StarSystem :: asteroidManager(int num)
{
        while (ASTEROID_pList.size() < num)
        {
                Asteroid* _asteroid = createAsteroid();
                addAsteroid(_asteroid);
        }
}


bool StarSystem :: addStar(Star* _star)
{
        _star->setStarSystem(this);
        STAR_pList.push_back(_star);
        
        return true;           
}

bool StarSystem :: addPlanet(Planet* _planet)
{
        _planet->setStarSystem(this);
        PLANET_pList.push_back(_planet);
        
        return true;        
}
                
bool StarSystem :: addAsteroid(Asteroid* _asteroid)
{   
        _asteroid->setStarSystem(this);
        ASTEROID_pList.push_back(_asteroid);
        
        return true;
}

bool StarSystem :: addMineral(Mineral* _mineral)
{
	_mineral->setStarSystem(this);
        MINERAL_pList.push_back(_mineral);
        
        return true;
}

bool StarSystem :: addContainer(Container* _container)
{
	_container->setStarSystem(this);
        CONTAINER_pList.push_back(_container);
        
        return true;
}


bool addRocket(RocketBullet* rocket);
{
	ROCKET_pList.push_back(rocket);
	return true;
}    

bool StarSystem :: addExplosion(ExplosionEffect* _explosion)
{
	_explosion->setStarSystem(this);
	effect_EXPLOSION_pList.push_back(_explosion);
        
        return true;
}

		

bool StarSystem :: addShockWave(ShockWaveEffect* _shockWave)
{
	_shockWave->setStarSystem(this);
	effect_SHOCKWAVE_pList.push_back(_shockWave);
        
        return true;
}

bool StarSystem :: addDistantNebula(DistantNebulaBgEffect* dn)
{
	distantNebulaBgEffect_pList.push_back(dn);
        return true;
}

bool StarSystem :: addDistantStar(DistantStarBgEffect* ds)
{
	distantStarBgEffect_pList.push_back(ds);
	return true;

}
    		
		

    		
void StarSystem :: manageEntities()
{  

    for (unsigned int wi = 0; wi < effect_SHOCKWAVE_pList.size(); wi++)
    {
    	if (effect_SHOCKWAVE_pList[wi]->is_alive == false)
    	   effect_SHOCKWAVE_pList.erase(effect_SHOCKWAVE_pList.begin() + wi);
    }

    for(unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
    {
        //if (SHIP_pList[ki]->is_alive == true)
        //{
           //for (unsigned int lei = 0; lei < SHIP_pList[ki]->effect_LAZERTRACE_pList.size(); lei++)
           //{
               //if (SHIP_pList[ki]->effect_LAZERTRACE_pList[lei]->is_alive == false)
               //{   
                   //delete SHIP_pList[ki]->effect_LAZERTRACE_pList[lei];
                   //SHIP_pList[ki]->effect_LAZERTRACE_pList.erase(SHIP_pList[ki]->effect_LAZERTRACE_pList.begin() + lei);
               //} 
           //}
        //}

        //if (SHIP_pList[ki]->in_SPACE == false)
        //{        
        //   SHIP_pList.erase(SHIP_pList.begin() + ki);
        //}   

        //if (SHIP_pList[ki]->isReadyFor_JUMPEVENT == true)
        //{        
            //if (SHIP_pList[ki]->owner_type_id == NPC_ID)
                //SHIP_pList[ki]->pTo_npc_owner->isReadyFor_JUMPEVENT = true;
                   
            ////SHIP_forJumpEvent_pList.push_back(SHIP_pList[ki]);
            //SHIP_pList.erase(SHIP_pList.begin() + ki);
            //break;
        //}   
        
        if (SHIP_pList[ki]->is_alive == false)
        {           
            //if (SHIP_pList[ki]->owner_type_id == NPC_ID)
            SHIP_pList[ki]->pTo_npc_owner->is_alive = false;
               
            SHIP_remove_queue_pList.push_back(SHIP_pList[ki]);
            SHIP_pList.erase(SHIP_pList.begin() + ki);
            break;
        } 
    }


    for(unsigned int ni = 0; ni < NPC_pList.size(); ni++)
    {
        //if (NPC_pList[ni]->in_SPACE == false)
        //{   
        //    NPC_pList.erase(NPC_pList.begin() + ni);
        //} 
       
        //if (NPC_pList[ni]->isReadyFor_JUMPEVENT == true)
        //{   
            ////NPC_forJumpEvent_pList.push_back(NPC_pList[ni]);
            //NPC_pList.erase(NPC_pList.begin() + ni);
            //break;
        //} 
         
        if (NPC_pList[ni]->is_alive == false)
        {   
            NPC_remove_queue_pList.push_back(NPC_pList[ni]);
            NPC_pList.erase(NPC_pList.begin() + ni);
            break;
        } 
    }

    for (unsigned int lei = 0; lei < effect_LAZERTRACE_pList.size(); lei++)
    {
         if (effect_LAZERTRACE_pList[lei]->is_alive == false)
         {   
            delete effect_LAZERTRACE_pList[lei];
            effect_LAZERTRACE_pList.erase(effect_LAZERTRACE_pList.begin() + lei);
         } 
    }


    for(unsigned int i = 0; i < ASTEROID_pList.size(); i++)
    {
        if (ASTEROID_pList[i]->getAlive() == false)
        {   //printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[i]).id);
            ASTEROID_remove_queue_pList.push_back(ASTEROID_pList[i]);
            ASTEROID_pList.erase(ASTEROID_pList.begin() + i );
        } 
    }
    

    for(unsigned int i = 0; i < MINERAL_pList.size(); i++)
    {
        if (MINERAL_pList[i]->is_alive == false)
        {   //printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[i]).id);
            MINERAL_remove_queue_pList.push_back(MINERAL_pList[i]);
            MINERAL_pList.erase(MINERAL_pList.begin() + i );
        } 
    }
    
    for(unsigned int i = 0; i < CONTAINER_pList.size(); i++)
    {
        if (CONTAINER_pList[i]->is_alive == false)
        {   //printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[i]).id);
            CONTAINER_remove_queue_pList.push_back(CONTAINER_pList[i]);
            CONTAINER_pList.erase(CONTAINER_pList.begin() + i );
        } 
    }

    for(unsigned int ri = 0; ri < ROCKET_pList.size(); ri++)
    {
        if (ROCKET_pList[ri]->is_alive == false)
        {   //printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[i]).id);
            ROCKET_remove_queue_pList.push_back(ROCKET_pList[ri]);
            ROCKET_pList.erase(ROCKET_pList.begin() + ri );
        } 
    }

    for(unsigned int i = 0; i<effect_EXPLOSION_pList.size(); i++)   // move this to removeDead
    {
        if (effect_EXPLOSION_pList[i]->is_alive == false)
        {   //printf("explosion to remove ==> \n");
            delete effect_EXPLOSION_pList[i];
            effect_EXPLOSION_pList.erase(effect_EXPLOSION_pList.begin() + i );
        } 
    }

    for(unsigned int edi = 0; edi < effect_DAMAGE_pList.size(); edi++)    // move this to removeDead
    {
        if (effect_DAMAGE_pList[edi]->is_alive == false)
        {   //printf("explosion to remove ==> \n");
            delete effect_DAMAGE_pList[edi];
            effect_DAMAGE_pList.erase(effect_DAMAGE_pList.begin() + edi);
        } 
    }
}

              
void StarSystem :: removeDeadEntities()
{  

    for(unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
    { 
        SHIP_pList[ki]->removeWeaponSlotDeadTargets(); 
    }


    for(unsigned int ki = 0; ki < SHIP_remove_queue_pList.size(); ki++)
    { 
       delete SHIP_remove_queue_pList[ki];
       SHIP_remove_queue_pList.erase(SHIP_remove_queue_pList.begin() + ki);
    }

    for(unsigned int ni = 0; ni < NPC_remove_queue_pList.size(); ni++)
    { 
       delete NPC_remove_queue_pList[ni];
       NPC_remove_queue_pList.erase(NPC_remove_queue_pList.begin() + ni);
    }



    for(unsigned int ri = 0; ri < ROCKET_remove_queue_pList.size(); ri++)
    { 
       delete ROCKET_remove_queue_pList[ri];
       ROCKET_remove_queue_pList.erase(ROCKET_remove_queue_pList.begin() + ri);
    }


    for(unsigned int ai = 0; ai < ASTEROID_remove_queue_pList.size(); ai++)
    {
       //printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[i]).id);
       delete ASTEROID_remove_queue_pList[ai];
       ASTEROID_remove_queue_pList.erase(ASTEROID_remove_queue_pList.begin() + ai);
    }

    for(unsigned int mi = 0; mi < MINERAL_remove_queue_pList.size(); mi++)
    {
       //printf("mineral id to remove ==> %i\n",(*Asteroid_pList[i]).id);

       delete MINERAL_remove_queue_pList[mi];
       MINERAL_remove_queue_pList.erase(MINERAL_remove_queue_pList.begin() + mi);
    }

    for(unsigned int ci = 0; ci < CONTAINER_remove_queue_pList.size(); ci++)
    {
       //printf("mineral id to remove ==> %i\n",(*Asteroid_pList[i]).id);

       delete CONTAINER_remove_queue_pList[ci];
       CONTAINER_remove_queue_pList.erase(CONTAINER_remove_queue_pList.begin() + ci);
    }

}

/*
void StarSystem :: removeDeadEntities2()
{  
   VEC_int_type iterators_remove_queue;

   for(unsigned int i = 0; i<Asteroid_pList_removeQueue.size(); i++)
      {
         for(unsigned int j = 0; j < Asteroid_pList.size(); j++)
            { if ((*Asteroid_pList_removeQueue[i]).id == (*Asteroid_pList[j]).id)
                 { printf("asteroid id to remove ==> %i\n",(*Asteroid_pList[j]).id);
                   printf("iterators_remove_queue.push_back(j) = %i\n", j); 
                   iterators_remove_queue.push_back(j);
                   break;
                 } 
            }
      }

   for(unsigned int i=0; i<iterators_remove_queue.size(); i++)
      {  printf("iterators_remove = %i\n", iterators_remove_queue[i]); 
         Asteroid_pList.erase(Asteroid_pList.begin() + iterators_remove_queue[i]-1);     
         printf("asteroid removed // MEMORY LEACK \n"); 
      }

   Asteroid_pList_removeQueue.clear();
   
}*/
                


void StarSystem :: mouseControl()
{   
    bool cursor_has_target = false;   
 
    int mxvp = g_MOUSE_POS_X                 + g_SCROLL_COORD_X;
    int myvp = g_VIEW_HEIGHT - g_MOUSE_POS_Y + g_SCROLL_COORD_Y;

    bool mlb = g_MOUSE_LEFT_BUTTON;
    bool mrb = g_MOUSE_RIGHT_BUTTON;


    pTo_PLAYER->pTo_ship->selectWeapons(pTo_PLAYER->weapon_slot_1_SELECTED, 
        				pTo_PLAYER->weapon_slot_2_SELECTED, 
                   			pTo_PLAYER->weapon_slot_3_SELECTED, 
                   			pTo_PLAYER->weapon_slot_4_SELECTED, 
                   			pTo_PLAYER->weapon_slot_5_SELECTED);
                   				       
    pTo_PLAYER->pTo_ship->resetDeselectedWeaponTargets();



    if (cursor_has_target == false) 
    {
        for (unsigned int i = 0; i < visible_STAR_pList.size(); i++)
        { 
            float cursor_dist = distBetweenCenters(visible_STAR_pList[i]->getPoints(), mxvp, myvp);
            if (cursor_dist < 10.0)
            {   
               cursor_has_target = true;

               visible_STAR_pList[i]->updateInfo(); 
               visible_STAR_pList[i]->renderInfo(); 

               break; 
            }
        }
    }




    if (cursor_has_target == false) 
    {
        for (unsigned int mi = 0; mi < visible_MINERAL_pList.size(); mi++)
        { 
            float mineral_cursor_dist = distBetweenCenters(visible_MINERAL_pList[mi]->getPoints(), mxvp, myvp);
            if (mineral_cursor_dist < 10.0)
            {   
               cursor_has_target = true;

               visible_MINERAL_pList[mi]->updateInfo(); 
               visible_MINERAL_pList[mi]->renderInfo(); 

               if (mlb == true)
               {
                   pTo_PLAYER->pTo_ship->selectWeapons(pTo_PLAYER->weapon_slot_1_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_2_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_3_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_4_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_5_SELECTED);
                   					    
                   pTo_PLAYER->pTo_ship->setWeaponsTarget(visible_MINERAL_pList[mi]);

	       }
               break; 
            }
        }
    }


    if (cursor_has_target == false) 
    {
        for (unsigned int ci = 0; ci < visible_CONTAINER_pList.size(); ci++)
        { 
            float container_cursor_dist = distBetweenCenters(visible_CONTAINER_pList[ci]->getPoints(), mxvp, myvp);
            if (container_cursor_dist < 10.0)
            {   
               cursor_has_target = true;

               visible_CONTAINER_pList[ci]->renderInfo(); 

               if (mlb == true)
               {
                   pTo_PLAYER->pTo_ship->selectWeapons(pTo_PLAYER->weapon_slot_1_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_2_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_3_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_4_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_5_SELECTED);
                   					    
                   pTo_PLAYER->pTo_ship->setWeaponsTarget(visible_CONTAINER_pList[ci]);
               }
 
               break; 
            }
        }
    }


    if (cursor_has_target == false) 
    {
       for (unsigned int ki = 0; ki < visible_SHIP_pList.size(); ki++)
       { 
            float ship_cursor_dist = distBetweenCenters(visible_SHIP_pList[ki]->getPoints(), mxvp, myvp);
            if (ship_cursor_dist < 50.0)
            { 
                cursor_has_target = true;

                visible_SHIP_pList[ki]->updateInfo(); 
                visible_SHIP_pList[ki]->renderInfo(visible_SHIP_pList[ki]->getPoints()->getCenter().x, visible_SHIP_pList[ki]->getPoints()->getCenter().y, g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 

                if (mlb == true)
                {
                   pTo_PLAYER->pTo_ship->selectWeapons(pTo_PLAYER->weapon_slot_1_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_2_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_3_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_4_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_5_SELECTED);
                   					    
                   pTo_PLAYER->pTo_ship->setWeaponsTarget(visible_SHIP_pList[ki]);
		}

                if (mrb == true)
                {
                   if ( pTo_PLAYER->pTo_npc->isScanTargetPossible(visible_SHIP_pList[ki]) == true )
                   {
                       pTo_PLAYER->pTo_npc->setScanTarget(visible_SHIP_pList[ki]);
                       pTo_PLAYER->is_SCANNING = true;
                   }
                }

                break; 
            }
        }
    }

    if (cursor_has_target == false) 
    {
        for (unsigned int ai = 0; ai < visible_ASTEROID_pList.size(); ai++)
        { 
            float asteroid_cursor_dist = distBetweenCenters(visible_ASTEROID_pList[ai]->getPoints(), mxvp, myvp);
            if (asteroid_cursor_dist < 50.0)
            {   
                cursor_has_target = true;

                visible_ASTEROID_pList[ai]->updateInfo(); 
                visible_ASTEROID_pList[ai]->renderInfo(); 

                if (mlb == true)
                { 
                   pTo_PLAYER->pTo_ship->selectWeapons(pTo_PLAYER->weapon_slot_1_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_2_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_3_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_4_SELECTED, 
                   				       pTo_PLAYER->weapon_slot_5_SELECTED);
                   					    
                   pTo_PLAYER->pTo_ship->setWeaponsTarget(visible_ASTEROID_pList[ai]);
                } 
                break; 
            }
        }
    }



    if (cursor_has_target == false) 
    {
        for (unsigned int pi = 0; pi < visible_PLANET_pList.size(); pi++)
        { 
            float planet_cursor_dist = distBetweenCenters(visible_PLANET_pList[pi]->getPoints(), mxvp, myvp);
            if (planet_cursor_dist < 50.0)
            {   
                cursor_has_target = true;

                visible_PLANET_pList[pi]->updateInfo(); 
                visible_PLANET_pList[pi]->renderInfo(); 

                if (mlb == true)
                {
                    pTo_PLAYER->pTo_ship->pTo_npc_owner->clearAIfuncSequence();
                    pTo_PLAYER->pTo_ship->pTo_navigator->setTargetPlanet(visible_PLANET_pList[pi]);  
                    pTo_PLAYER->pTo_ship->pTo_npc_owner->createDockingSequence();
                }   

                break; 
            }
        }
    }



    if (cursor_has_target == false) 
        if (mlb == true)
        {
            pTo_PLAYER->pTo_ship->pTo_navigator->setStaticTargetCoords(vec2f(mxvp, myvp));  
            pTo_PLAYER->pTo_ship->pTo_npc_owner->clearAIfuncSequence();
        }     
}


 //def mouseInteraction(self, timer, (mx, my), (vpCoordinate_x, vpCoordinate_y), (slot_1_SELECTED, slot_2_SELECTED, slot_3_SELECTED, slot_4_SELECTED, slot_5_SELECTED), show_RADAR, grapple_SELECTED, (lb, rb)):
          //CURSOR_INTERSECT_OBJECT = False

          //player_cursor_dist = lengthBetweenPoints((player.points.center[0], player.points.center[1]), (mxvp, myvp))
          //if player_cursor_dist < player.points.w/4.0:
             //CURSOR_INTERSECT_OBJECT = True
             //player.renderInfo()

             //if lb == True:
                //player.in_INVERTAR = True

          //#####################################################################################################
          //if CURSOR_INTERSECT_OBJECT != True:

             //for k in self.visible_SHIP_list:

                 //if ship_cursor_dist < player.points.w/4.0:
                    //CURSOR_INTERSECT_OBJECT = True
                    //k.renderInfo()
                    //k.calculateWayVisualisation()
                    //k.renderDirection()





void StarSystem :: fireEvents_TRUE(int timer)
{
     for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
         SHIP_pList[ki]->weaponsFire_TRUE(timer);
}

void StarSystem :: fireEvents_FALSE(int timer)
{
     for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
         SHIP_pList[ki]->weaponsFire_FALSE(timer);
}







//// ******* TRANSITION ******* 
bool StarSystem :: addShip(Ship* _pTo_ship)
{
     _pTo_ship->in_SPACE = true;
     _pTo_ship->starsystem = this;  

     SHIP_pList.push_back(_pTo_ship);
     return true;
}

bool StarSystem :: addNpc(Npc* _pTo_npc)
{
     int _race_id = _pTo_npc->race_id;
     int _subtype_id = _pTo_npc->subtype_id;

     _pTo_npc->in_SPACE = true;
     _pTo_npc->pTo_starsystem = this;  

     NPC_pList.push_back(_pTo_npc);

     if (_subtype_id == RANGER_ID)
         NPC_RANGER_pList.push_back(_pTo_npc);
     if (_subtype_id == WARRIOR_ID)
         NPC_WARRIOR_pList.push_back(_pTo_npc);
     if (_subtype_id == TRADER_ID)
         NPC_TRADER_pList.push_back(_pTo_npc);
     if (_subtype_id == PIRAT_ID)
         NPC_PIRAT_pList.push_back(_pTo_npc);
     if (_subtype_id == DIPLOMAT_ID)
         NPC_DIPLOMAT_pList.push_back(_pTo_npc);
     

     return true;
}

bool StarSystem :: removeShipById(int _id)
{
     bool is_removed = false;
     for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
         if (SHIP_pList[ki]->id == _id)
         {
            SHIP_pList.erase(SHIP_pList.begin() + ki);
            is_removed = true; 
         }
     return is_removed;
}

bool StarSystem :: removeNpc(int _id, int _race_id, int _subtype_id)
{
     removeNpcFromTheListById(&NPC_pList, _id);

     if (_subtype_id == RANGER_ID)
        removeNpcFromTheListById(&NPC_RANGER_pList, _id);
     if (_subtype_id == WARRIOR_ID)
        removeNpcFromTheListById(&NPC_WARRIOR_pList, _id);
     if (_subtype_id == TRADER_ID)
        removeNpcFromTheListById(&NPC_TRADER_pList, _id);
     if (_subtype_id == PIRAT_ID)
        removeNpcFromTheListById(&NPC_PIRAT_pList, _id);
     if (_subtype_id == DIPLOMAT_ID)
        removeNpcFromTheListById(&NPC_DIPLOMAT_pList, _id);
}


     bool StarSystem :: removeNpcFromTheListById(std::vector<Npc*>* pTo_npc_pList, int _id)
     {
          bool is_removed = false;
          for (unsigned int ni = 0; ni < pTo_npc_pList->size(); ni++)
              if ((*pTo_npc_pList)[ni]->id == _id)
              {
                 pTo_npc_pList->erase(pTo_npc_pList->begin() + ni);
                 is_removed = true;
              }
          return is_removed; 
     }

//// ******* TRANSITION ******* 







Planet* StarSystem :: returnClosestPlanet(vec2f _pos)
{
     return PLANET_pList[randIntInRange(0, PLANET_pList.size()-1)];
     //p = self.returnClosestInhabitedPlanet(ship)
     //if p == None:
             //p = self.returnClosestUninhabitedPlanet(ship)
          //return p
}


//bool returnClosestInhabitedPlanet()
//{
          //planet_with_distance_tuples = []
          //for p in self.PLANET_list:
              //if p.kosmoport != None:
                 //ship_planet_dist = lengthBetweenPoints((ship.points.center[0], ship.points.center[1]), (p.points.center[0], p.points.center[1]))
                 //planet_with_distance_tuples.append((p, ship_planet_dist))

          //planet_with_distance_tuples_sorted = sorted(planet_with_distance_tuples, key=itemgetter(1))
          //if len(planet_with_distance_tuples_sorted) > 0:
             //(p_closest, ship_planet_dist) = planet_with_distance_tuples_sorted[0]
             //return p_closest
          //else:
             //return None

      //def returnClosestUninhabitedPlanet(self, ship):
          //planet_with_distance_tuples = []
          //for p in self.PLANET_list:
              //if p.kosmoport == None:
                 //ship_planet_dist = lengthBetweenPoints((ship.points.center[0], ship.points.center[1]), (p.points.center[0], p.points.center[1]))
                 //planet_with_distance_tuples.append((p, ship_planet_dist))

          //planet_with_distance_tuples_sorted = sorted(planet_with_distance_tuples, key=itemgetter(1))
          //if len(planet_with_distance_tuples_sorted) > 0:
             //(p_closest, ship_planet_dist) = planet_with_distance_tuples_sorted[0]
             //return p_closest
          //else:
             //return None



void StarSystem :: debug__()
{
     if (MINERAL_pList.size() > 1000)
     {
        for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
            MINERAL_pList[mi]->death_FALSE();          
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




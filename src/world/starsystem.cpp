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

    //color.r = 1.0f;
    //color.g = 1.0f;
    //color.b = 0.8f;
    //color.a = 1.0f;
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
             if (ROCKET_pList[ri]->owner_id != SHIP_pList[ki]->id)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, SHIP_pList[ki]->points.center_x, SHIP_pList[ki]->points.center_y, SHIP_pList[ki]->collision_radius) == true)
                {
                    SHIP_pList[ki]->hit_TRUE(ROCKET_pList[ri]->damage);
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }

         if (collide == false)
            for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, ASTEROID_pList[ai]->w) == true)
                {   
                    ASTEROID_pList[ai]->death_TRUE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }

         if (collide == false)
            for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, MINERAL_pList[mi]->points.center_x, MINERAL_pList[mi]->points.center_y, MINERAL_pList[mi]->w) == true)
                {   
                    MINERAL_pList[mi]->death_TRUE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }


              //if collide == False:
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(r.points.center, sp.points.center, sp.collision_threshold):
                        //sp.hit(r.owner, r)
                        //r.hit(r.owner, r)
                        //collide = True
                        //break

         if (collide == false)
            for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, CONTAINER_pList[ci]->points.center_x, CONTAINER_pList[ci]->points.center_y, CONTAINER_pList[ci]->w) == true)
                {   
                    CONTAINER_pList[ci]->death_TRUE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
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
             if (ROCKET_pList[ri]->owner_id != SHIP_pList[ki]->id)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, SHIP_pList[ki]->points.center_x, SHIP_pList[ki]->points.center_y, SHIP_pList[ki]->collision_radius) == true)
                {
                    SHIP_pList[ki]->hit_FALSE(ROCKET_pList[ri]->damage);
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }

         if (collide == false)
            for (unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, ASTEROID_pList[ai]->w) == true)
                {   
                    ASTEROID_pList[ai]->death_FALSE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }

         if (collide == false)
            for (unsigned int mi = 0; mi < MINERAL_pList.size(); mi++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, MINERAL_pList[mi]->points.center_x, MINERAL_pList[mi]->points.center_y, MINERAL_pList[mi]->w) == true)
                {   
                    MINERAL_pList[mi]->death_FALSE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
                }


              //if collide == False:
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(r.points.center, sp.points.center, sp.collision_threshold):
                        //sp.hit(r.owner, r)
                        //r.hit(r.owner, r)
                        //collide = True
                        //break

         if (collide == false)
            for (unsigned int ci = 0; ci < CONTAINER_pList.size(); ci++)
                if (collisionBetweenCenters(ROCKET_pList[ri]->points.center_x, ROCKET_pList[ri]->points.center_y, CONTAINER_pList[ci]->points.center_x, CONTAINER_pList[ci]->points.center_y, CONTAINER_pList[ci]->w) == true)
                {   
                    CONTAINER_pList[ci]->death_FALSE();
                    ROCKET_pList[ri]->hit(ROCKET_pList[ri]->armor);
                    collide = true;
                    break;
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
        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, SHIP_pList[ki]->points.center_x, SHIP_pList[ki]->points.center_y, SHIP_pList[ki]->collision_radius) )
               {
                   ASTEROID_pList[ai]->death_TRUE();
                   SHIP_pList[ki]->hit_TRUE( (ASTEROID_pList[ai]->armor) * 10 );
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   break;
               }

        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, PLANET_pList[pi]->points.center_x, PLANET_pList[pi]->points.center_y, PLANET_pList[pi]->collision_radius) )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->death_TRUE();
                   break;
               }
                
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(a.points.center, sp.points.cente, sp.collision_threshold):
                        //sp.hit(a, a)
                        //a.hit(a, a)
                        //break

        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int si = 0; si < STAR_pList.size(); si++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, STAR_pList[si]->pos_x, STAR_pList[si]->pos_y, STAR_pList[si]->collision_radius) )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->death_TRUE();
                   break;
               }
                        
    }

}



void StarSystem :: asteroidCollision_FALSE()
{
    for(unsigned int ai = 0; ai < ASTEROID_pList.size(); ai++)
    {
        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int ki = 0; ki < SHIP_pList.size(); ki++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, SHIP_pList[ki]->points.center_x, SHIP_pList[ki]->points.center_y, SHIP_pList[ki]->collision_radius) )
               {
                   ASTEROID_pList[ai]->death_FALSE();
                   SHIP_pList[ki]->hit_FALSE( (ASTEROID_pList[ai]->armor) * 10 );
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   break;
               }

        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int pi = 0; pi < PLANET_pList.size(); pi++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, PLANET_pList[pi]->points.center_x, PLANET_pList[pi]->points.center_y, PLANET_pList[pi]->collision_radius) )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->death_FALSE();
                   break;
               }
                
                 //for sp in self.SPUTNIK_list:
                     //if collisionBetweenCenters(a.points.center, sp.points.cente, sp.collision_threshold):
                        //sp.hit(a, a)
                        //a.hit(a, a)
                        //break

        if (ASTEROID_pList[ai]->is_alive == true)   
           for (unsigned int si = 0; si < STAR_pList.size(); si++)
               if ( collisionBetweenCenters(ASTEROID_pList[ai]->points.center_x, ASTEROID_pList[ai]->points.center_y, STAR_pList[si]->pos_x, STAR_pList[si]->pos_y, STAR_pList[si]->collision_radius) )
               {
                   //printf("collision, asteroid_id = %i\n", (*Asteroid_pList[i]).id);
                   ASTEROID_pList[ai]->death_FALSE();
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
    int startViewCoord_x = g_SCROLL_COORD_X + g_VIEW_WIDTH;
    int startViewCoord_y = g_SCROLL_COORD_Y + g_VIEW_HEIGHT;

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
        if (isObjectVisible((*STAR_pList[i]).pos_x, (*STAR_pList[i]).pos_y, (*STAR_pList[i]).w, (*STAR_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_STAR_pList.push_back(STAR_pList[i]); 
    }
    
    for (unsigned int i = 0; i < PLANET_pList.size(); i++)
    {
        if (isObjectVisible((*PLANET_pList[i]).points.center_x, (*PLANET_pList[i]).points.center_y, (*PLANET_pList[i]).w, (*PLANET_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_PLANET_pList.push_back(PLANET_pList[i]);  
    }
    
   
    //self.visible_SPUTNIK_list   = [s for s in self.SPUTNIK_list   if isObjectVisible((s.points.center[0], s.points.center[1]), (s.w, s.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    for (unsigned int i = 0; i < ASTEROID_pList.size(); i++)
    {
        if (isObjectVisible((*ASTEROID_pList[i]).points.center_x, (*ASTEROID_pList[i]).points.center_y, (*ASTEROID_pList[i]).w, (*ASTEROID_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_ASTEROID_pList.push_back(ASTEROID_pList[i]); 
    }
   
    for (unsigned int i = 0; i < MINERAL_pList.size(); i++)
    {
        if (isObjectVisible((*MINERAL_pList[i]).points.center_x, (*MINERAL_pList[i]).points.center_y, (*MINERAL_pList[i]).w, (*MINERAL_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_MINERAL_pList.push_back(MINERAL_pList[i]);  
    }
    
    for (unsigned int i = 0; i < CONTAINER_pList.size(); i++)
    {
        if (isObjectVisible((*CONTAINER_pList[i]).points.center_x, (*CONTAINER_pList[i]).points.center_y, (*CONTAINER_pList[i]).w, (*CONTAINER_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_CONTAINER_pList.push_back(CONTAINER_pList[i]);  
    }

    //self.visible_BOMB_list      = [b for b in self.BOMB_list      if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    
    for (unsigned int i = 0; i < SHIP_pList.size(); i++)
    {
        if (isObjectVisible((*SHIP_pList[i]).points.center_x, (*SHIP_pList[i]).points.center_y, (*SHIP_pList[i]).w, (*SHIP_pList[i]).h, startViewCoord_x, startViewCoord_y))    
           visible_SHIP_pList.push_back(SHIP_pList[i]); 
    }
    
    for (unsigned int i = 0; i < ROCKET_pList.size(); i++)
    {
        if (isObjectVisible(ROCKET_pList[i]->points.center_x, ROCKET_pList[i]->points.center_y, ROCKET_pList[i]->w, ROCKET_pList[i]->h, startViewCoord_x, startViewCoord_y))    
           visible_ROCKET_pList.push_back(ROCKET_pList[i]); 
    }

    //self.visible_BLACKHOLE_list = [b for b in self.BLACKHOLE_list if isObjectVisible((b.points.center[0], b.points.center[1]), (b.w, b.h), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]

    //self.visible_effect_EXPLOSION_list = [e for e in self.effect_EXPLOSION_list if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
    //self.visible_effect_DAMAGE_list    = [e for e in self.effect_DAMAGE_list    if isObjectVisible((e.center[0], e.center[1]), (300, 300), (vpCoordinate_x, vpCoordinate_y), (x_startViewCoord, y_startViewCoord))]
}

      

void StarSystem :: defineSceneColor(TextureOb* _pTo_texOb)
{
	if (_pTo_texOb->color_id == YELLOW_COLOR_ID)
	{
		color.r = 255/255.0;
		color.g = 255/255.0;
		color.b = 255/220.0;
		color.a = 1.0;
	}
	
	if (_pTo_texOb->color_id == BLUE_COLOR_ID)
	{
		color.r = 220/255.0;
		color.g = 255/255.0;
		color.b = 255/255.0;
		color.a = 1.0;
	}
}
      
void StarSystem :: setSceneColor()
{
	glColor4f(color.r, color.g, color.b, color.a);
}      


void StarSystem :: renderBackground()
{   
	// HACK for point sprites
    	glEnable(GL_POINT_SPRITE);
    	distantStarBgEffect_pList[0]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    	glDisable(GL_POINT_SPRITE);
    	// HACK for point sprites

    	// Clear color and depth buffer
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glLoadIdentity();

        setSceneColor();

    	glDisable(GL_DEPTH_TEST);
    	glEnable(GL_BLEND);
glDepthMask(false);

    	for(unsigned int i = 0; i<distantNebulaBgEffect_pList.size(); i++)
    	{ 
       		distantNebulaBgEffect_pList[i]->update(); 
        	distantNebulaBgEffect_pList[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    	}

    	glEnable(GL_POINT_SPRITE);
    	for(unsigned int i = 0; i<distantStarBgEffect_pList.size(); i++)
    	{ 
       		distantStarBgEffect_pList[i]->render(g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 
    	}
    	glDisable(GL_POINT_SPRITE);
    	
glDepthMask(true);
glDisable(GL_BLEND);
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

glEnable(GL_BLEND);
glDepthMask(true);

pTo_fbo0->activate();
     
        renderBackground();
           
	glLoadIdentity();
	glTranslatef(-g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, 0.0);    // camera
        
glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
		for(unsigned int i = 0; i < visible_STAR_pList.size(); i++) 
		{ 
        		visible_STAR_pList[i]->render_NEW(); 
    		}
    	glDisable(GL_DEPTH_TEST);
setSceneColor();
pTo_fbo0->deactivate();

// POST PROCESS BLOOM (many FBO)
pTo_bloom->pass0(pTo_fbo0->texture, STAR_pList[0]->pTo_texOb->brightThreshold);
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
/* */pTo_fbo1->deactivate();


/* */pTo_fbo2->activate();
//renderBackground();

/* */glEnable(GL_BLEND);
//* */glDepthMask(false);

//glUseProgram(g_BLACK2ALPHA_PROGRAM);
//glActiveTexture(GL_TEXTURE0);                                
//glBindTexture(GL_TEXTURE_2D, pTo_fbo1->texture);
//glUniform1i(glGetUniformLocation(g_BLACK2ALPHA_PROGRAM, "sceneTex"), 0);
//drawFullScreenQuad(w, h, -999.0); 
//glUseProgram(0);    
drawFullScreenTexturedQuad(pTo_fbo1->texture, w, h, -999.0);
           
          
glTranslatef(-g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, 0.0);    // camera
        

	glEnable(GL_DEPTH_TEST);  
    		for(unsigned int i = 0; i < visible_PLANET_pList.size(); i++) 
    		{ 
       			visible_PLANET_pList[i]->render_NEW(); 
    		}

    	glDisable(GL_DEPTH_TEST);
glDepthMask(false); 
    	          
    	glEnable(GL_BLEND);
    	for(unsigned int i = 0; i < visible_MINERAL_pList.size(); i++)
	{ 
        	visible_MINERAL_pList[i]->render2D(); 
    	}  
           
    	for(unsigned int i = 0; i < visible_CONTAINER_pList.size(); i++)
    	{ 
        	visible_CONTAINER_pList[i]->render2D(); 
    	} 	 
           
    	for(unsigned int i = 0; i < visible_ASTEROID_pList.size(); i++)
    	{ 
       		visible_ASTEROID_pList[i]->render2D(); 
    	}

    	for(unsigned int i = 0; i < visible_SHIP_pList.size(); i++)
    	{ 
       		visible_SHIP_pList[i]->renderInSpace(); 
        	setSceneColor();
    	}

    	for(unsigned int i = 0; i < visible_ROCKET_pList.size(); i++)
    	{ 
       		visible_ROCKET_pList[i]->renderInSpace(); 
    	}

      	setSceneColor();
    	
    	glDisable(GL_BLEND);
//glDepthMask(true);

    	
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

// DRAW full size w,h texture_scene
drawFullScreenQuad(w, h, -999.0);
glUseProgram(0);

pTo_fbo3->deactivate();





// render from FBO
glEnable(GL_TEXTURE_2D);
//glBindFramebuffer(GL_FRAMEBUFFER, 0);          // unbind fbo

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
glLoadIdentity();

/* */glEnable(GL_BLEND);
drawFullScreenTexturedQuad(pTo_fbo3->texture, w, h, -999.0);
//drawFullScreenTexturedQuad(pTo_fbo0->texture, w, h, -999.0);  // debug

	glTranslatef(-g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, 0.0);    // camera
	glEnable(GL_BLEND);
		for(unsigned int i = 0; i<effect_LAZERTRACE_pList.size(); i++)
    		{ 
       			effect_LAZERTRACE_pList[i]->update(); 
        		effect_LAZERTRACE_pList[i]->render(); 
    		}

    		glEnable(GL_POINT_SPRITE);
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
    		glDisable(GL_POINT_SPRITE);
    		
    	glEnable(GL_BLEND);
    	          
}
    










    
void StarSystem :: renderEntities_OLD()
{   
	glLoadIdentity();
        renderBackground();
	glTranslatef(-g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, 0.0);
        
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	for(unsigned int i = 0; i < visible_STAR_pList.size(); i++) 
	{ 
        	visible_STAR_pList[i]->render_NEW(); 
    	}

    	for(unsigned int i = 0; i < visible_PLANET_pList.size(); i++) 
    	{ 
       		visible_PLANET_pList[i]->render_NEW(); 
    	}


    	glDisable(GL_DEPTH_TEST);
    	glEnable(GL_BLEND);
    	for(unsigned int i = 0; i < visible_MINERAL_pList.size(); i++)
	{ 
        	visible_MINERAL_pList[i]->render2D(); 
    	}  
           
    	for(unsigned int i = 0; i < visible_CONTAINER_pList.size(); i++)
    	{ 
        	visible_CONTAINER_pList[i]->render2D(); 
    	} 	 
           
    	for(unsigned int i = 0; i < visible_ASTEROID_pList.size(); i++)
    	{ 
       		visible_ASTEROID_pList[i]->render2D(); 
    	}

    	for(unsigned int i = 0; i < visible_SHIP_pList.size(); i++)
    	{ 
       		visible_SHIP_pList[i]->renderInSpace(); 
        	setSceneColor();
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


    	glEnable(GL_POINT_SPRITE);
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
    	glDisable(GL_POINT_SPRITE);

    	glDisable(GL_BLEND);
    	glEnable(GL_DEPTH_TEST);
    	setSceneColor();
}
    













void StarSystem :: addExplosion(float _center_x, float _center_y, int obSize)
{
	//obSize = randIntInRange(1, 9);  	// DEBUG

	int   _num_particles; 
	float _pSize;        

	TextureOb* pTo_particleTexOb; 
	ExplosionEffect* pEE;
    
	float _velocity_start = randIntInRange(13,17) * 0.1;
	float _d_velocity    = 0;

	float _alpha_start   = 1.0;
	float _alpha_end     = 0.1;
	float _d_alpha       = randIntInRange(5,8) * 0.001;

	float _d_pSize       = randIntInRange(60,80) * 0.01;
 
    
    
	if (obSize < 4)
	{
		_num_particles = randIntInRange(10 * obSize, 15 * obSize);    
		_pSize         = 25 * obSize;                                 

		pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		pEE = new ExplosionEffect(pTo_particleTexOb, this, _center_x, _center_y, _num_particles, _pSize, _d_pSize, _velocity_start, _alpha_start, _alpha_end, _d_alpha);
		effect_EXPLOSION_pList.push_back(pEE);
	}
    	else    
	{
		_num_particles = 40;
		_pSize         = 25 * obSize;
		pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		pEE = new ExplosionEffect(pTo_particleTexOb, this, _center_x, _center_y, _num_particles, _pSize, _d_pSize, _velocity_start, _alpha_start, _alpha_end, _d_alpha);
		effect_EXPLOSION_pList.push_back(pEE);
       

		_num_particles = 50;
		_pSize         = 25 * (obSize-1);
		pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(YELLOW_COLOR_ID);
		pEE = new ExplosionEffect(pTo_particleTexOb, this, _center_x, _center_y, _num_particles, _pSize, _d_pSize, _velocity_start, _alpha_start, _alpha_end, _d_alpha);
		effect_EXPLOSION_pList.push_back(pEE);
       
		_num_particles = 100;                              
		_pSize         = 25 * (obSize-2);
		pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		pEE = new ExplosionEffect(pTo_particleTexOb, this, _center_x, _center_y, _num_particles, _pSize, _d_pSize, _velocity_start, _alpha_start, _alpha_end, _d_alpha);
		effect_EXPLOSION_pList.push_back(pEE);
	} 	       
 
	addShockWave(_center_x, _center_y, obSize);
	//explosion.play()
}


void StarSystem :: addShockWave(float _center_x, float _center_y, int obSize)
{
	if ( (obSize > 3) && (effect_SHOCKWAVE_pList.size() < 10) )
	{
		int w = g_VIEW_WIDTH;
		int h = g_VIEW_HEIGHT;      
        
		float x = 10;
		float y = 1.8;
		float z = 0.13;
		float time = 0.0; 
		float dx = 0;
		float dy = 0.02;
		float dz = 0.0005;
		float dtime = -(0.002 + 0.3 * obSize * 0.001);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004 
        
		ShockWaveEffect* pTo_shockWave = new ShockWaveEffect(this, _center_x/float(w), _center_y/float(h), x, y, z, time, dx, dy, dz, dtime);  
       
		effect_SHOCKWAVE_pList.push_back(pTo_shockWave);
	}
}

void StarSystem :: asteroidManager(int num)
{
    while (ASTEROID_pList.size() < num)
       addAsteroid(); 
}


void StarSystem :: addAsteroid()
{
    float tmp_size = 50;
    float tmp_orbit_center_x = 0;
    float tmp_orbit_center_y = 0;
    int tmp_radius_A = randIntInRange(300, 1200);
    int tmp_radius_B = randIntInRange(300, 1200);
    float tmp_orbitPhiInDegree = randIntInRange(0, 360);
    float tmp_speed = 0.1;

    TextureOb* pTo_aTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.asteroid_texOb_pList); 
    Asteroid *pA = new Asteroid(pTo_aTexOb, this, tmp_size, tmp_orbit_center_x, tmp_orbit_center_y, tmp_radius_A, tmp_radius_B, tmp_orbitPhiInDegree, tmp_speed);
    pA->update_inSpace_inDynamic_FALSE();
    ASTEROID_pList.push_back(pA);

    //printf("___NEW___ Asteroid, asteroid_id/asteroid_ss_id = %i/%i\n", (*pA).id, id);
    //printf("len Asteroid_pList = %i , ss_id = %i\n", Asteroid_pList.size(), id);
}
    

void StarSystem :: addNumMinerals(float center_x, float center_y, int num)
{
    float alpha = randIntInRange(0, 360) / 57.0;
    float d_alpha = 2*PI / num;
    float len, target_x, target_y;
    
    for (int i = 0; i<num; i++)
    {
        len = randIntInRange(60, 100);
        target_x = center_x + sin(alpha) * len;
        target_y = center_y + cos(alpha) * len;

        TextureOb* pTo_mTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.mineral_texOb_pList); 
        Mineral *pTo_mineral = new Mineral(pTo_mTexOb, this, center_x, center_y, target_x, target_y);
        MINERAL_pList.push_back(pTo_mineral);
        alpha += d_alpha;
    }
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
        if (ASTEROID_pList[i]->is_alive == false)
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


    pTo_PLAYER->pTo_ship->resetDeselectedWeaponTargets(pTo_PLAYER->weapon_slot_1_SELECTED, pTo_PLAYER->weapon_slot_2_SELECTED, pTo_PLAYER->weapon_slot_3_SELECTED, pTo_PLAYER->weapon_slot_4_SELECTED, pTo_PLAYER->weapon_slot_5_SELECTED);


    if (cursor_has_target == false) 
    {
        for (unsigned int mi = 0; mi < visible_MINERAL_pList.size(); mi++)
        { 
            float mineral_cursor_dist = lengthBetweenPoints(visible_MINERAL_pList[mi]->points.center_x, visible_MINERAL_pList[mi]->points.center_y, mxvp, myvp);
            if (mineral_cursor_dist < 10.0)
            {   
               cursor_has_target = true;

               visible_MINERAL_pList[mi]->updateInfo(); 
               visible_MINERAL_pList[mi]->renderInfo(); 

               if (mlb == true)
                  pTo_PLAYER->pTo_ship->setWeaponsToMineralTarget(visible_MINERAL_pList[mi], pTo_PLAYER->weapon_slot_1_SELECTED, pTo_PLAYER->weapon_slot_2_SELECTED, pTo_PLAYER->weapon_slot_3_SELECTED, pTo_PLAYER->weapon_slot_4_SELECTED, pTo_PLAYER->weapon_slot_5_SELECTED);

               break; 
            }
        }
    }


    if (cursor_has_target == false) 
    {
        for (unsigned int ci = 0; ci < visible_CONTAINER_pList.size(); ci++)
        { 
            float container_cursor_dist = lengthBetweenPoints(visible_CONTAINER_pList[ci]->points.center_x, visible_CONTAINER_pList[ci]->points.center_y, mxvp, myvp);
            if (container_cursor_dist < 10.0)
            {   
               cursor_has_target = true;

               visible_CONTAINER_pList[ci]->renderInfo(); 

               if (mlb == true)
                  pTo_PLAYER->pTo_ship->setWeaponsToContainerTarget(visible_CONTAINER_pList[ci], pTo_PLAYER->weapon_slot_1_SELECTED, pTo_PLAYER->weapon_slot_2_SELECTED, pTo_PLAYER->weapon_slot_3_SELECTED, pTo_PLAYER->weapon_slot_4_SELECTED, pTo_PLAYER->weapon_slot_5_SELECTED);

               break; 
            }
        }
    }


    if (cursor_has_target == false) 
    {
       for (unsigned int ki = 0; ki < visible_SHIP_pList.size(); ki++)
       { 
            float ship_cursor_dist = lengthBetweenPoints(visible_SHIP_pList[ki]->points.center_x, visible_SHIP_pList[ki]->points.center_y, mxvp, myvp);
            if (ship_cursor_dist < 50.0)
            { 
                cursor_has_target = true;

                visible_SHIP_pList[ki]->updateInfo(); 
                visible_SHIP_pList[ki]->renderInfo(visible_SHIP_pList[ki]->points.center_x, visible_SHIP_pList[ki]->points.center_y, g_SCROLL_COORD_X, g_SCROLL_COORD_Y); 

                if (mlb == true)
                   pTo_PLAYER->pTo_ship->setWeaponsToShipTarget(visible_SHIP_pList[ki], pTo_PLAYER->weapon_slot_1_SELECTED, pTo_PLAYER->weapon_slot_2_SELECTED, pTo_PLAYER->weapon_slot_3_SELECTED, pTo_PLAYER->weapon_slot_4_SELECTED, pTo_PLAYER->weapon_slot_5_SELECTED);

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
            float asteroid_cursor_dist = lengthBetweenPoints(visible_ASTEROID_pList[ai]->points.center_x, visible_ASTEROID_pList[ai]->points.center_y, mxvp, myvp);
            if (asteroid_cursor_dist < 50.0)
            {   
                cursor_has_target = true;

                visible_ASTEROID_pList[ai]->updateInfo(); 
                visible_ASTEROID_pList[ai]->renderInfo(); 

                if (mlb == true)
                   pTo_PLAYER->pTo_ship->setWeaponsToAsteroidTarget(visible_ASTEROID_pList[ai], pTo_PLAYER->weapon_slot_1_SELECTED, pTo_PLAYER->weapon_slot_2_SELECTED, pTo_PLAYER->weapon_slot_3_SELECTED, pTo_PLAYER->weapon_slot_4_SELECTED, pTo_PLAYER->weapon_slot_5_SELECTED);

                break; 
            }
        }
    }



    if (cursor_has_target == false) 
    {
        for (unsigned int pi = 0; pi < visible_PLANET_pList.size(); pi++)
        { 
            float planet_cursor_dist = lengthBetweenPoints(visible_PLANET_pList[pi]->points.center_x, visible_PLANET_pList[pi]->points.center_y, mxvp, myvp);
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
            pTo_PLAYER->pTo_ship->pTo_navigator->setStaticTargetCoords(mxvp, myvp);  
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
     _pTo_ship->pTo_starsystem = this;  

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


     bool StarSystem :: removeNpcFromTheListById(VEC_pNpc_type* pTo_npc_pList, int _id)
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

bool StarSystem  :: addPlanet(Planet* _pTo_planet)
{
     _pTo_planet->pTo_starsystem = this;  // ???

     PLANET_pList.push_back(_pTo_planet);
     return true;

}
//// ******* TRANSITION ******* 







Planet* StarSystem :: returnClosestPlanet(int _pos_x, int _pos_y)
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


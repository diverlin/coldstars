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


#include "planet.h"

Planet :: Planet(int _subtype_id, TextureOb* _pTo_texOb, TextureOb* _pTo_atmoshereTexOb, ObjMeshInstance* _pTo_mesh, float _size, float _orbit_center_x, float _orbit_center_y, int _radius, float _speed)
{ 
      id = g_ENTITY_ID_GENERATOR.returnNextId();
      type_id = PLANET_ID;
      subtype_id = _subtype_id;

      pTo_texOb      = _pTo_texOb;
      pTo_atmosphereTexOb = _pTo_atmoshereTexOb;
      
      orbit_center_x = _orbit_center_x;
      orbit_center_y = _orbit_center_y;
      radius         = _radius;
      speed          = _speed;    
     
      scale = _size;
      pos_z = -500.0f;

      // !!!!
      float rate = 5.4;                                            
      w = rate * scale;
      h = rate * scale;
      collision_radius = (w + h)/2; 
      // !!!!
      
      
      step           = 0;
      angle_x        = randIntInRange(10, 40);
      angle_y        = randIntInRange(10, 40);
      angle_z        = 0.0;

      texture = pTo_texOb->texture;
     
      pTo_mesh = _pTo_mesh; 

      //////
      points = Points();

      points.initCenterPoint();
      points.addCenterPoint();
      //////

      detailedOrbitFormation();
      updatePosition(); 
      
      pTo_kosmoport = NULL;
      pTo_land      = NULL;
      if (subtype_id == INHABITED_ID)
         createKosmoport();
      if (subtype_id == UNINHABITED_ID)
         createLand();
}

    
Planet :: ~Planet()
{}
    
   
void Planet :: detailedOrbitFormation()
{   
     float d_rad_angle = speed / 57.295779;
        
     for (float rad_angle = 0; rad_angle < 2*PI ; rad_angle+=d_rad_angle) 
     { 
          orbit_vector_x.push_back(orbit_center_x + radius * cos(rad_angle));
          orbit_vector_y.push_back(orbit_center_y + radius * sin(rad_angle));
     }           
}    
        

void Planet :: update_inSpace_inDynamic()
{      
     updatePosition();  
}
  
void Planet :: updatePosition()
{ 
      if (step < orbit_vector_x.size())
      { 
          points.setCenter(orbit_vector_x[step], orbit_vector_y[step]);
          step += 1;
      }
      else
          step = 0;
}    
 

void Planet :: update_inSpace_inStatic()
{      
     if (subtype_id == INHABITED_ID)
        for (unsigned int ni = 0; ni < pTo_kosmoport->NPC_pList.size(); ni++)
            pTo_kosmoport->NPC_pList[ni]->thinkCommon_inKosmoport_inStatic();

     if (subtype_id == UNINHABITED_ID)
        for (unsigned int ni = 0; ni < pTo_kosmoport->NPC_pList.size(); ni++)
            pTo_kosmoport->NPC_pList[ni]->thinkCommon_inLand_inStatic();
}
         

void Planet :: updateInfo()
{
    info_title_pList.clear();
    info_value_pList.clear();

    info_title_0 = "PLANET";

    info_title_1 = "id/ss_id:";
    info_value_1 = int2str(id) + " / " + int2str(pTo_starsystem->id);

    info_title_pList.push_back(&info_title_0);  
    info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
}


void Planet :: renderInfo()
{  
     drawInfoIn2Column(&info_title_pList, &info_value_pList, points.center_x, points.center_y ); 
}

        
void Planet :: createKosmoport()
{   
    pTo_kosmoport = new Kosmoport(RACE_0_ID);   
}


void Planet :: createLand()
{   
    pTo_land = new Land();   
}


//// ******* TRANSITION ******* 
bool Planet :: addShip(Ship* _pTo_ship)
{
     if (subtype_id == INHABITED_ID)
         return pTo_kosmoport->addShip(_pTo_ship);
     if (subtype_id == UNINHABITED_ID)
         return pTo_land->addShip(_pTo_ship);
}

bool Planet :: addNpc(Npc* _pTo_npc)
{
     if (subtype_id == INHABITED_ID)
         return pTo_kosmoport->addNpc(_pTo_npc);
     if (subtype_id == UNINHABITED_ID)
         return pTo_land->addNpc(_pTo_npc);
}

bool Planet :: removeShipById(int _id)
{
     if (subtype_id == INHABITED_ID)
         return pTo_kosmoport->removeShipById(_id);
     if (subtype_id == UNINHABITED_ID)
         return pTo_land->removeShipById(_id);
}

bool Planet :: removeNpcById(int _id)
{
     if (subtype_id == INHABITED_ID)
         return pTo_kosmoport->removeNpcById(_id);
     if (subtype_id == UNINHABITED_ID)
         return pTo_land->removeNpcById(_id);
}
//// ******* TRANSITION ******* 


void Planet :: render_NEW()
{
     glUseProgram(g_LIGHT_PROGRAM);
     //printProgramInfoLog(g_LIGHT_PROGRAM);

     //if (glGetUniformLocation(g_LIGHT_PROGRAM, "lightPos") == -1)
         //printf("shader lightPos fail\n"); 
     //if (glGetUniformLocation(g_LIGHT_PROGRAM, "eyePos") == -1)
         //printf("shader eyePos fail\n"); 
     //if (glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0") == -1)
         //printf("shader Texture_0 fail\n"); 

     glUniform4f(glGetUniformLocation(g_LIGHT_PROGRAM, "lightPos"), -g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, -200.0, 0.0);
     glUniform4f(glGetUniformLocation(g_LIGHT_PROGRAM, "eyePos"), -g_SCROLL_COORD_X, -g_SCROLL_COORD_Y, -200.0, 0.0);

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, texture);
     glUniform1i(glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0"), 0);
      
     glPushMatrix();
       glTranslatef(points.center_x, points.center_y, pos_z);
       glScalef(scale, scale, scale); 
       glRotatef(-angle_x, 1.0, 0.0, 0.0); 
       glRotatef(-angle_y, 0.0, 1.0, 0.0); 
       glRotatef(-angle_z, 0.0, 0.0, 1.0); 

       glCallList(pTo_mesh->glList);
       //g_model.render(); 
       angle_z += 0.6; 
     glPopMatrix();

     //// render atmosphere
     //glEnable(GL_BLEND);
     //glActiveTexture(GL_TEXTURE0);                                
     //glBindTexture(GL_TEXTURE_2D, pTo_atmosphereTexOb->texture);
     //glUniform1i(glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0"), 0);

     //glPushMatrix();
       //glTranslatef(points.center_x, points.center_y, pos_z);
       //glScalef(scale*1.05, scale*1.05, scale*1.05);
       //glRotatef(angle_x, 1.0, 0.0, 0.0); 
       //glRotatef(angle_y, 0.0, 1.0, 0.0); 
       //glRotatef(angle_z, 0.0, 0.0, 1.0); 

       //glCallList(pTo_mesh->glList);
       ////g_model.render(); 
     //glPopMatrix();
     //glDisable(GL_BLEND);
     //// render atmosphere

     glUseProgram(0);
     glActiveTexture(GL_TEXTURE0);
}

void Planet :: render_OLD()
{   
     glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, texture);   
       glTranslatef(points.center_x, points.center_y, pos_z);
       glScalef(scale, scale, scale); 
       glRotatef(angle_x, 1.0, 0.0, 0.0); 
       glRotatef(angle_y, 0.0, 1.0, 0.0); 
       glRotatef(angle_z, 0.0, 0.0, 1.0); 

       glCallList(pTo_mesh->glList);
       angle_z += 0.6; 
     glPopMatrix();
}



bool Planet :: getPermissionToLand()
{
     if (subtype_id == INHABITED_ID)
     {
        if (pTo_kosmoport->pTo_angar->returnFreelandingAreaNum() > 0)
            return true;
        else
            return false;       
     }
     if (subtype_id == UNINHABITED_ID)
        return true;
}

        



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



void initGL(int width, int height)
{   
  // Set color and depth clear value
  //glClearDepth(1.f);
  glClearColor(0.f, 0.f, 0.f, 0.f);

  // Enable Z-buffer read and write
  //glEnable(GL_DEPTH_TEST);
  //glDepthMask(GL_TRUE);

  // Setup a perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(90.f, 1.f, 1.f, 500.f);
  glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
            
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  
      //glShadeModel(GL_SMOOTH);
      //glDisable(GL_LIGHTING);  
}   


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


#include "fbo.hpp"


FBO :: FBO(int _w, int _h)
{
	w = _w;
      	h = _h;
      	// create a color texture
      	glGenTextures(1, &texture);
      	glBindTexture(GL_TEXTURE_2D, texture);
      	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  w, h, 0, GL_RGBA, GL_INT, NULL); // no data transferred


      	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      	glBindTexture(GL_TEXTURE_2D, 0);

      	// create depth renderbuffer
      	glGenRenderbuffers(1, &depth_buffer); // putcom
      	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buffer);
      	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32, w, h);

      	// create FBO
      	glGenFramebuffers(1, &fbo);   // putcom
      	glBindFramebuffer(GL_FRAMEBUFFER, fbo);  // putcom     // switch to our fbo so we can bind stuff to it
      	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture, 0);
      	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

      	// Go back to regular frame buffer rendering
      	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}


GLuint FBO :: getTexture() const { return texture; }
		
		
void FBO :: activate()
{
     	glBindTexture(GL_TEXTURE_2D, 0);            // unbind texture
     	glBindFramebuffer(GL_FRAMEBUFFER, fbo);    // putcom // bind fbo

     	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     	glLoadIdentity();

     	glPushAttrib(GL_VIEWPORT_BIT);               // viewport is shared with the main context
     	glViewport(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
}

void FBO :: deactivate()
{
     	glActiveTexture(GL_TEXTURE0);                // debug
     	glPopAttrib();                               // restore viewport
}



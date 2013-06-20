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

#include "Fbo.hpp"

Fbo::Fbo()
{}

void Fbo::Create()
{
      	glGenTextures(1, &texture); 		// create a color texture
      	glGenRenderbuffers(1, &depth_buffer); 	// create depth renderbuffer
     	glGenFramebuffers(1, &fbo);        	// create Fbo
}

Fbo::~Fbo()
{}
	
	
void Fbo::Resize(int w, int h)
{
      	// color texture manipulation
      	glBindTexture(GL_TEXTURE_2D, texture);
      	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  w, h, 0, GL_RGBA, GL_INT, nullptr); // no data transferred

      	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      	glBindTexture(GL_TEXTURE_2D, 0);

      	// depth renderbuffer manipulation
      	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buffer);
      	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32, w, h);

      	// Fbo manipulation
      	glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
      	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture, 0);
      	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

      	// Go back to regular frame buffer rendering
      	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}      		

void Fbo::Activate(int width, int height)
{
     	glBindTexture(GL_TEXTURE_2D, 0);            // unbind texture
     	glBindFramebuffer(GL_FRAMEBUFFER, fbo);     // bind fbo

     	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     	glLoadIdentity();

     	glPushAttrib(GL_VIEWPORT_BIT);               // viewport is shared with the main context
     	glViewport(0, 0, width, height);
}

void Fbo::Deactivate()
{
     	glActiveTexture(GL_TEXTURE0);                // debug
     	glPopAttrib();                               // restore viewport
}



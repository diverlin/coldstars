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


Screen :: Screen()
{
      	width     = SCREEN_WIDTH_MIN; 
      	height    = SCREEN_HEIGHT_MIN;
      	bpp       = 32;
      	fps_max   = 60;
      	vert_sync = true;
      	
      	initGl();
      	resizeGl();
      	
      	fbo0  = NULL;
	fbo1  = NULL;	
	fbo2  = NULL;
	fbo3  = NULL;
	bloom = NULL;
	
	fps = new Fps();
}

Screen :: ~Screen()
{
	delete fbo0;
	delete fbo1;	
	delete fbo2;
	delete fbo3;
	delete bloom;
	
	delete fps;
}
        
void Screen :: resize(int width, int height)
{
	this->width  = width;
	this->height = height;
	
	//sf::View newView = g_APP.GetView( );
				
	g_APP.SetSize(width, height);
	//glViewport(0, 0, width, height);
	
	//sf::View view(sf::FloatRect(0, 0, width, height));
	//sf::View view(sf::FloatRect(-500, -500, 500, 500));
	//g_APP.SetView(view);
		
	//g_APP.SetView(g_APP.GetDefaultView());
	//g_APP.Create(sf::VideoMode(width, height, g_BPP), "SFML Window");
	    	
	resizeGl();
		
	if (g_USE_MODERN_HW == true)
	{
		resizePostProcess();
	}
}


int Screen :: getWidth() const  { return width; }
int Screen :: getHeight() const { return height; }

const vec2f& Screen :: getTopRightGlobalCoord()   const { return topRight_globalCoord; }
const vec2f& Screen :: getBottomLeftGlobalCoord() const { return bottomLeft_globalCoord; }
        	
FBO* Screen :: getFbo0() const { return fbo0; }
FBO* Screen :: getFbo1() const { return fbo1; }
FBO* Screen :: getFbo2() const { return fbo2; }
FBO* Screen :: getFbo3() const { return fbo3; }

BloomEffect* Screen :: getBloom() const { return bloom; }
	
void Screen :: bottomLeftGlobalCoordIncrease(vec2f delta)
{
	bottomLeft_globalCoord += delta;
	topRight_globalCoord.set(bottomLeft_globalCoord.x + width, bottomLeft_globalCoord.y + height);
}

void Screen :: update()
{
	fps->update(); 
}

void Screen :: display()		
{
	fps->draw(); 
        g_APP.Display();
}


void Screen :: initGl()
{   
  	// Set color and depth clear value
  	//glClearDepth(1.f);
  	glClearColor(0.f, 0.f, 0.f, 0.f);

  	// Enable Z-buffer read and write
  	//glEnable(GL_DEPTH_TEST);
  	//glDepthMask(GL_TRUE);

            
  	glEnable(GL_TEXTURE_2D);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  
      	glShadeModel(GL_SMOOTH);
      	//glDisable(GL_LIGHTING);  
}   



void Screen :: resizePostProcess()
{
	delete fbo0;
	delete fbo1;	
	delete fbo2;
	delete fbo3;
	delete bloom;
	
	fbo0  = new FBO(width, height);
	fbo1  = new FBO(width, height);	
	fbo2  = new FBO(width, height);
	fbo3  = new FBO(width, height);
	bloom = new BloomEffect(width, height, g_SHADERS.blur, g_SHADERS.extractbright, g_SHADERS.combine, 1, 1);
}


void Screen :: resizeGl()
{
  	// Setup a perspective projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	//gluPerspective(90.f, 1.f, 1.f, 500.f);
  	glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  	
  	glMatrixMode(GL_MODELVIEW);
}

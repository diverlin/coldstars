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


Screen::Screen()
{
      	fbo0  = NULL;
	fbo1  = NULL;	
	fbo2  = NULL;
	fbo3  = NULL;
	bloom = NULL;
	
	width     = Config::Instance().SCREEN_WIDTH; 
      	height    = Config::Instance().SCREEN_HEIGHT;
      	bpp       = Config::Instance().BPP;
      	vert_sync = Config::Instance().VSYNC;
      	
      	InitGl();
      	Resize(width, height);
}

Screen::~Screen()
{
	delete fbo0;
	delete fbo1;	
	delete fbo2;
	delete fbo3;
	delete bloom;
}
        
void Screen::Resize(int width, int height)
{
	this->width  = width;
	this->height = height;
	
	Gui::GetWindow().SetFramerateLimit(Config::Instance().FPS_LIMIT); 
    	Gui::GetWindow().PreserveOpenGLStates(true);
    	Gui::GetWindow().UseVerticalSync(Config::Instance().VSYNC);

	view.SetFromRect(sf::FloatRect(0, 0, width, height));
	Gui::GetWindow().SetView(view);	
	Gui::GetWindow().SetSize(width, height);
	    	
	ResizeGl();
		
	if (Config::Instance().MODERN_EFFECTS == true)
	{
		ResizePostProcess();
	}
}
	
void Screen::MovingBy(vec2f delta)
{
	bottomLeft_globalCoord += delta;
	UpdateOnEvent();
}

void Screen::UpdateOnEvent()
{
	topRight_globalCoord.Set(bottomLeft_globalCoord.x + width, bottomLeft_globalCoord.y + height);
}

void Screen::Display()
{
  	Gui::Update();
  	Gui::GetWindow().Display();
}

void Screen::InitGl()
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

void Screen::ResizePostProcess()
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

void Screen::ResizeGl()
{
  	// Setup a perspective projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	//gluPerspective(90.f, 1.f, 1.f, 500.f);
  	glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  	
  	glMatrixMode(GL_MODELVIEW);
}

#include "Window.hpp"
#include <boost/lexical_cast.hpp>
#include "../config/config.hpp"

Screen& Screen::Instance()
{
	static Screen instance;
      	return instance;
}
    
//Screen::Screen():general_window(sf::VideoMode(Config::Instance().SCREEN_WIDTH, Config::Instance().SCREEN_HEIGHT, Config::Instance().BPP), GAME_TITLE){}
Screen::Screen():render_window(sf::VideoMode(800, 600, 32), "init")
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

void Screen::Update()
{
	DrawFsp();
}

void Screen::DrawFsp()
{
	float fps = 1.f / render_window.GetFrameTime();
      	sf::String _str(std::string(	"FPS:" + 
                                  	boost::lexical_cast<std::string>( (int)fps) ),
                                  	font, 14);
      	_str.SetColor(sf::Color(255, 255, 255));
      	_str.SetPosition(100, 15);
      	render_window.Draw(_str);
}
    
    
     
void Screen::Resize(int width, int height)
{
	this->width  = width;
	this->height = height;
	
	render_window.SetFramerateLimit(Config::Instance().FPS_LIMIT); 
    	render_window.PreserveOpenGLStates(true);
    	render_window.UseVerticalSync(Config::Instance().VSYNC);

	view.SetFromRect(sf::FloatRect(0, 0, width, height));
	render_window.SetView(view);	
	render_window.SetSize(width, height);
	    	
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
  	Update();
  	render_window.Display();
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

   

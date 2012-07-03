#include "Screen.hpp"
#include <boost/lexical_cast.hpp>

#include "../render/glsl.hpp"


Screen& Screen::Instance()
{
	static Screen instance;
      	return instance;
}
    
Screen::Screen()
{
std::cout<<"Olololo 0/n";
}

Screen::~Screen()
{
	delete bloom;
}


void Screen::InitBasic(int width, int height, int bpp, bool vert_sync, const std::string& title)
{	
      	this->bpp = bpp;
      	this->vert_sync = vert_sync;
      	
      	render_window.Create(sf::VideoMode(width, height, bpp), title);
      	render_window.SetFramerateLimit(Config::Instance().FPS_LIMIT); 
    	render_window.UseVerticalSync(vert_sync);
    	render_window.PreserveOpenGLStates(true);
    	 	
      	initGl(width, height);
 
	bloom = NULL;	
}

void Screen::InitPostEffects(int width, int height)
{
 	fbo0.Create();
	fbo1.Create();	
	fbo2.Create();
	fbo3.Create();
	
	ResizePostEffects(width, height);
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
	view.SetFromRect(sf::FloatRect(0, 0, width, height));
	render_window.SetView(view);	
	render_window.SetSize(width, height);
	    	
	resizeGl(width, height);
	
	if (Config::Instance().MODERN_EFFECTS == true)
	{
		ResizePostEffects(width, height);
	}
}
	
void Screen::MovingBy(vec2f delta)
{
	bottomLeft_globalCoord += delta;
	UpdateOnEvent();
}

void Screen::UpdateOnEvent()
{
	topRight_globalCoord.Set(bottomLeft_globalCoord.x + render_window.GetWidth(), bottomLeft_globalCoord.y + render_window.GetHeight());
}

void Screen::Display()
{
	UpdateOnEvent();
  	Update();
  	render_window.Display();
}


void Screen::ResizePostEffects(int width, int height)
{
	//delete bloom;
	
	fbo0.Resize(width, height);
	fbo1.Resize(width, height);	
	fbo2.Resize(width, height);
	fbo3.Resize(width, height);
	
	bloom = new BloomEffect(width, height);
	bloom->BindShaderPrograms(g_SHADERS.blur, g_SHADERS.extractbright, g_SHADERS.combine);
}

   

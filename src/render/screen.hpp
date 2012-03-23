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



#ifndef SCREEN_H
#define SCREEN_H


class Screen
{
  	public:
        	Screen();
        	~Screen();   
        	
        	void resize(int, int);
        	int getWidth() const;
        	int getHeight() const;
        	     	
        	const vec2f& getTopRightGlobalCoord() const;
        	const vec2f& getBottomLeftGlobalCoord() const;
        	     			
        	FBO* getFbo0() const;
		FBO* getFbo1() const;
		FBO* getFbo2() const;
		FBO* getFbo3() const;

		BloomEffect* getBloom() const;	
		
		void bottomLeftGlobalCoordIncrease(vec2f);
				
		void update();
		void display();	

	private:
      		int width, height;
      		int bpp;
      		int fps_max;
      		bool vert_sync;
      		
      		FBO* fbo0;
		FBO* fbo1;
		FBO* fbo2;
		FBO* fbo3;

		BloomEffect* bloom;
      		
      		Fps* fps;
      		
      		vec2f topRight_globalCoord;
      		vec2f bottomLeft_globalCoord;
      		
      		sf::View* view;
      		
      		void initGl();
      		void resizeGl();
      		
      		void resizePostProcess();
}; 

#endif 

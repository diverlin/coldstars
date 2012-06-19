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
        	
        	void SetBottomLeftGlobalCoord(vec2f bottomLeft_globalCoord) {this->bottomLeft_globalCoord = bottomLeft_globalCoord; UpdateOnEvent(); };
        	
        	int GetWidth() const  { return width; };
        	int GetHeight() const { return height; };
        	     	
        	const vec2f& GetTopRightGlobalCoord()   const { return topRight_globalCoord; };
        	const vec2f& GetBottomLeftGlobalCoord() const { return bottomLeft_globalCoord; };
        	     			
        	FBO* GetFbo0() const { return fbo0; };
		FBO* GetFbo1() const { return fbo1; };
		FBO* GetFbo2() const { return fbo2; };
		FBO* GetFbo3() const { return fbo3; }

		BloomEffect* GetBloom() const { return bloom; };	
		
		void MovingBy(vec2f);

        	void Resize(int, int);
        					
		void Display();	

	private:
      		int width, height;
      		int bpp;
      		bool vert_sync;
      		
      		FBO* fbo0;
		FBO* fbo1;
		FBO* fbo2;
		FBO* fbo3;

		BloomEffect* bloom;
      		
      		vec2f topRight_globalCoord;
      		vec2f bottomLeft_globalCoord;
      		
      		sf::View view;
      		
      		void InitGl();
      		void ResizeGl();
      		
      		void ResizePostProcess();
		void UpdateOnEvent();
}; 

#endif 

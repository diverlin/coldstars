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


#ifndef RECT_H
#define RECT_H

class Rect
{  
	public:
	    	Rect();
	    	Rect(float, float, int, int);
      		Rect(vec2f, int, int);
      		~Rect();
      		
      		void Set(float, float, int, int);

      		void SetCenter(vec2f);
      		void SetCenter(float, float);
      		void SetBottomLeft(vec2f);
      		void SetBottomLeft(float, float);
      		      		
		const vec2f& GetCenter() const     { return center; }
		const vec2f& GetBottomLeft() const { return bottomLeft; }
		int GetWidth() const 	    { return w; }
		int GetHeight() const 	    { return h; }  
      
      		void Resize(int, int);
      		      		
      	private:
      		vec2f bottomLeft;    
      		vec2f center;  
      		int w, h;

      		void UpdateCenter();
};


#endif 

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

#include "myVector.hpp"

class Rect
{  
	public:
	    	Rect();
	    	Rect(float, float, float, float);
      		Rect(const vec2f&, float, float);
      		Rect(const Rect&);
      		~Rect();
	
		void Scale(float);
		void Scale(const vec2f&);
		
      		bool CheckInteraction(int, int) const;
      		       		
      		void Set(float, float, float, float);
      		void Set(const vec2f&, float, float);
      		void Set(const Rect&);
      			
      		void SetCenter(const vec2f&);
      		void SetCenter(float, float);
      		void SetBottomLeftX(float);
      		void SetBottomLeft(const vec2f&);
      		void SetBottomLeft(float, float);
      		      		
		const vec2f& GetCenter() const     { return center; }
		const vec2f& GetBottomLeft() const { return bottomLeft; }
		const vec2f& GetTopRight() const { return topRight; }
		float GetWidth() const 	    { return w; }
		float GetHeight() const     { return h; }  
      
      		void SetSize(float, float);
      		void MovingBy(const vec2f&);
      		      		
      	private:
      		vec2f bottomLeft;    
      		vec2f center;  
      		vec2f topRight;
      		
      		float w, h;

      		void UpdateCenter();
      		void UpdateTopRight();
};


#endif 

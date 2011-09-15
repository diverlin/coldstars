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
	    	Rect(float _bottomLeft_x, float _bottomLeft_y, int _w, int _h);
      		Rect(vec2f _bottomLeft, int _w, int _h);
      		~Rect();
      		
      		vec2f getCenter() const;
      		vec2f getBottomLeft() const;
      		int getWidth() const;
      		int getHeight() const;
      
      		void calcCenter();
      		void setNewCenter(vec2f _center);
      		void setNewCenter(float _center_x, float _center_y);
      		void setNewBottomLeftPos(vec2f _bottomLeft);
      		
      	private:
      		vec2f bottomLeft;    
      		vec2f center;  
      		int w, h;		
};


#endif /* RECT_H */

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

#include "../math/myVector.hpp"

class Rect
{  
	public:
		Rect();
		Rect(float, float, float, float);
		Rect(const Vec2<float>&, float, float);
		Rect(const Rect&);
		~Rect();
		
		void Scale(float);
		void Scale(const Vec2<float>&);
		
		bool CheckInteraction(float, float) const;
		bool CheckInteraction(const Vec2<float>&) const;
							
		void Set(float, float, float, float);
		void Set(const Vec2<float>&, float, float);
		void Set(const Rect&);
			
		void SetCenter(const Vec2<float>&);
		void SetCenter(float, float);
		void SetBottomLeftX(float);
		void SetBottomLeft(const Vec2<float>&);
		void SetBottomLeft(float, float);
					
		const Vec2<float>& GetCenter() const     { return center; }
		const Vec2<float>& GetBottomLeft() const { return bottomLeft; }
		const Vec2<float>& GetTopRight() const { return topRight; }
		float GetWidth() const 	    { return w; }
		float GetHeight() const     { return h; }  
		
		void SetSize(float, float);
		void MovingBy(const Vec2<float>&);
      		      		
	private:
		Vec2<float> bottomLeft;    
		Vec2<float> center;  
		Vec2<float> topRight;
		
		float w, h;
		
		void UpdateCenter();
		void UpdateTopRight();
};


#endif 

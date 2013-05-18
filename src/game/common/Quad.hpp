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

#ifndef QUAD_H
#define QUAD_H

#include "../math/Vec2.hpp"
class Rect; //tmp  hack

class Quad
{  
	public:
	    	Quad();
      		Quad(const Vec2<float>&, const Vec2<float>&);
      		Quad(const Vec2<float>&, float, float);
	    	Quad(float, float, float, float);
      		Quad(const Quad&);
      		Quad(const Rect&); // tmp hack
      		~Quad();

      		void Set(const Vec2<float>&, const Vec2<float>&);
      		void Set(const Vec2<float>&, float, float);      		       		
      		void Set(float, float, float, float);
      		void Set(const Quad&);
      			
      		void SetCenter(const Vec2<float>& center) { this->center = center; }
      		void SetCenter(float center_x, float center_y) { this->center.Set(center_x, center.y); }
      		
      		void SetSize(const Vec2<float>& size) { this->size = size; }      		      
      		void SetSize(float size_x, float size_y) { this->size.Set(size_x, size_y); }
      		
      		void SetAngle(float angle) { this->angle = angle; }

      		const Vec2<float> GetCenter() const { return center; }      		      
      		const Vec2<float> GetSize() const { return size; }
      		
      		float GetAngle() const {return angle; }

      		bool CheckInteraction(const Vec2<float>&) const;		
      		bool CheckInteraction(float, float) const;
      		      		      		
      	private:
      		Vec2<float> center;  
      		Vec2<float> size; 
      		
      		float angle;
};


#endif 

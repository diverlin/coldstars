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
#include "../math/Vec3.hpp"
class Rect; //tmp  hack

const float ZSIZE = 1;

class Box
{  
	public:
		Box();
		Box(const Vec3<float>&);
		Box(const Vec3<float>&, const Vec3<float>&);
		Box(const Box&);
		Box(const Rect&); // tmp hack
		~Box();
		
		void Set(const Box&);
		
		void SetCenter(const Vec3<float>& center)	{ this->center = center; } 
		void SetSize(const Vec3<float>& size)		{ this->size = size; } 
		void SetScale(const Vec3<float>& scale)		{ this->scale = scale; }
		void SetAngle(const Vec3<float>& angle)		{ this->angle = angle; }
		
		const Vec3<float>& GetCenter() const	{ return center; }      		      
		const Vec3<float>& GetSize() const		{ return size; }
		const Vec3<float>& GetScale() const		{ return scale; }
		const Vec3<float>& GetAngle() const		{ return angle; }
		
		bool CheckInteraction(const Vec2<float>&) const;	
      		      		      		
	private:
		Vec3<float> center;  
		Vec3<float> size;
		Vec3<float> angle;
		
		Vec3<float> scale;      		      		
};


#endif 

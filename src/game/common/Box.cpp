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

#include "Box.hpp"
#include "Collision.hpp"
#include "rect.hpp"

Box::Box()
{
	Set(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Box::Box(const Vec3<float>& center, const Vec3<float>& size)
{
	Set(center, size);
}

Box::Box(const Box& rhs)
{
	Set(rhs);
}

Box::Box(const Rect& rect)
{
	Set(rect.GetCenter().x, rect.GetCenter().y, -1.0, rect.GetWidth(), rect.GetHeight(), 1.0);
}

Box::~Box()
{}


bool Box::CheckInteraction(const Vec2<float>& point) const
{       	
	return CheckInteraction(point.x, point.y);
}
     	
bool Box::CheckInteraction(float x, float y) const
{       	
	return collisionDotCircle2D_FAST(center.GetXY(), x, y, (size.x + size.y)/2);
}

void Box::Set(const Vec3<float>& center, const Vec3<float>& size)
{
	this->center.Set(center);
	this->size.Set(size);
}
        
void Box::Set(float center_x, float center_y, float center_z, float size_x, float size_y, float size_z)
{
	center.Set(center_x, center_y, center_z);
	size.Set(size_x, size_y, size_z);
}
      	
void Box::Set(const Box& quad)
{
	center.Set(quad.GetCenter());
	size.Set(quad.GetSize());
	
	angle = quad.GetAngle();
}


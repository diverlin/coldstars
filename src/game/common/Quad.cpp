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

#include "Quad.hpp"
#include "Collision.hpp"

Quad::Quad()
:angle(0.0)
{
	Set(0.0f, 0.0f, 0.0f, 0.0f);
}

Quad::Quad(const Vec2<float>& center, const Vec2<float>& size)
:angle(0.0)
{
	Set(center, size);
}

Quad::Quad(const Vec2<float>& center, float size_x, float size_y)
:angle(0.0)
{
	Set(center, size_x, size_y);
}

Quad::Quad(float center_x, float center_y, float size_x, float size_y)
:angle(0.0)
{
	Set(center_x, center_y, size_x, size_y);
}

Quad::Quad(const Quad& rhs)
:angle(0.0)
{
	Set(rhs);
}

Quad::~Quad()
{}


bool Quad::CheckInteraction(const Vec2<float>& point) const
{       	
	return CheckInteraction(point.x, point.y);
}
     	
bool Quad::CheckInteraction(float x, float y) const
{       	
	return collisionDotCircle_FAST(center, x, y, (size.x + size.y)/2);
}

void Quad::Set(const Vec2<float>& center, const Vec2<float>& size)
{
	this->center.Set(center);
	this->size.Set(size);
}

void Quad::Set(const Vec2<float>& center, float size_x, float size_y)
{
	this->center.Set(center);
	size.Set(size_x, size_y);
}
        
void Quad::Set(float center_x, float center_y, float size_x, float size_y)
{
	center.Set(center_x, center_y);
	size.Set(size_x, size_y);
}
      	
void Quad::Set(const Quad& quad)
{
	center.Set(quad.GetCenter());
	size.Set(quad.GetSize());
}


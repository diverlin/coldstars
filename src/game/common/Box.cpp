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
{}

Box::Box(const Vec3<float>& size)
{
	SetSize(size);
}

Box::Box(const Vec3<float>& center, const Vec3<float>& size)
{
	SetCenter(center);
	SetSize(size);	
}

Box::Box(const Box& rhs)
{
	Set(rhs);
}

Box::Box(const Rect& rect)
{
	SetCenter(Vec3<float>(rect.GetCenter().x, rect.GetCenter().y, -1.0));
	SetSize(Vec3<float>(rect.GetWidth(), rect.GetHeight(), 1.0));
}

Box::~Box()
{}

bool Box::CheckInteraction(const Vec2<float>& point) const
{       	
	return checkCollisionDotWithRectangle(point, center, size*scale);
}
           	
void Box::Set(const Box& box)
{
	SetCenter(box.GetCenter());
	SetSize(box.GetSize());
}


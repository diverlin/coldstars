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



Rect::Rect()
{
	Set(0, 0, 0, 0);
}

Rect::Rect(float _bottomLeft_x, float _bottomLeft_y, int _w, int _h)
{
	Set(_bottomLeft_x, _bottomLeft_y, _w, _h);
}

Rect::Rect(const vec2f& _bottomLeft, int _w, int _h)
{
	Set(_bottomLeft.x, _bottomLeft.y, _w, _h);
}

Rect::~Rect()
{}

bool Rect::CheckInteraction(int x, int y) const
{        
    	float dist = distBetweenPoints(center, x, y);
    	if (dist < w/2)
        	return true;
    	else
        	return false;    
}
        
void Rect::Set(float _bottomLeft_x, float _bottomLeft_y, int _w, int _h)
{
	bottomLeft.x = _bottomLeft_x;
	bottomLeft.y = _bottomLeft_y;

	w = _w;
	h = _h;

	UpdateCenter();
}

void Rect::Set(const vec2f& vbl, int _w, int _h)
{
	Set(vbl.x, vbl.y, _w , _h);
}
      		
void Rect::SetCenter(const vec2f& _center)
{
	SetCenter(_center.x, _center.y);
}

void Rect::SetCenter(float _center_x, float _center_y)
{
	float dx = center.x - _center_x;
	float dy = center.y - _center_y;

	bottomLeft.x -= dx;
	bottomLeft.y -= dy; 

	center.x = _center_x;
	center.y = _center_y;
}

void Rect::SetBottomLeft(const vec2f& _bottomLeft)
{
	SetBottomLeft(_bottomLeft.x, _bottomLeft.y);
}

void Rect::SetBottomLeft(float _pos_x, float _pos_y)
{
	bottomLeft.x = _pos_x;
	bottomLeft.y = _pos_y;

	UpdateCenter();
}

void Rect::Resize(int _w, int _h)
{
	w = _w;
	h = _h;

	bottomLeft.x = center.x - w/2;
	bottomLeft.y = center.y - h/2;
}

void Rect::UpdateCenter()
{
	center.x = bottomLeft.x + w/2;
	center.y = bottomLeft.y + h/2;
}


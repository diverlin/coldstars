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

Color4f :: Color4f()
{
	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;
}


Color4i :: Color4i()
{
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}



LifeData :: LifeData()
{
        is_alive = true;
        int armor = 1;
        	
        bool is_dying = false;
        int dying_time = 0;
        
        bool is_explosed = false;
}	


ControlWord :: ControlWord()
{
	scan = false;
	grapple = false;

	worldmap = false;
	ship_info = false;
	planet_info = false;	
	planet_orbits = false;
	radar_radius = false;
}

ControlWord :: ~ControlWord()
{}



AngleData :: AngleData()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	d_x = 0.0;
	d_y = 0.0;
	d_z = 0.0;
}

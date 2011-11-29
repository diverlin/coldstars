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


Fps :: Fps(): str("")
{}

Fps :: ~Fps()
{}
        	
void Fps :: update()
{
	float fps = 1.f / g_APP.GetFrameTime();
	
	if (getRandInt(0, 20) == 1)
       	{
        	str = "FPS:" + int2str((int)fps);
        }
}

void Fps :: draw() const
{
       	sf::String _str(str, g_FONT, 14);
       	_str.SetColor(sf::Color(255, 255, 255));
       	_str.SetPosition(100, 15); 
       	
       	g_APP.Draw(_str);
}

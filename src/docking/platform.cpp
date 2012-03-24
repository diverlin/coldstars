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

Platform :: Platform(TextureOb* _texOb, float _center_x, float _center_y, int _w, int _h)
{   
    	texOb = _texOb;

    	rect = Rect(_center_x - _w/2, _center_y - _h/2, _w, _h);
}
   
Platform :: ~Platform()
{}

Vehicle* Platform :: getVehicle()      { return vehicle; }
Rect Platform :: getRect() const { return rect; }
      
                          
void Platform :: insert(Vehicle* vehicle)
{
        this->vehicle = vehicle;
        
        vehicle->getPoints()->setAngle(0);
       	vehicle->getPoints()->setCenter(rect.getCenter().x, rect.getCenter().y);
        vehicle->getPoints()->update();
}

void Platform :: free()
{
        vehicle = NULL;
} 




void Platform :: render() const
{
     	drawTexturedRect(texOb, rect, -1);
     	if (vehicle != NULL)
     	{
     	       	((Ship*)vehicle)->render_atPlanet();
	}
}


void Platform :: renderInfo() const
{
	vehicle->renderInfo(rect.getCenter().x, rect.getCenter().y, 0, 0);
}

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


#ifndef TURREL_H
#define TURREL_H

class Turrel
{
   public:
       Ship* pTo_korpus;

       TextureOb* pTo_texOb;
       GLuint texture;
       int w, h;

       Points points;

       float pos_z;

       Turrel();
       void setTexOb(TextureOb* _pTo_texOb);
       ~Turrel();

       void update(float _center_x, float _center_y, float _angle_inD);
       void render();
}; 

#endif 

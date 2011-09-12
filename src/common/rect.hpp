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


#ifndef RECT_H
#define RECT_H

class Rect
{  public:

      float bottomLeft_x;
      float bottomLeft_y;
      int w,h;

      float center_x;
      float center_y;


      Rect();
      Rect(float _bottomLeft_x, float _bottomLeft_y, int _w, int _h);
      void calcCenter();
      void setNewCenter(float _center_x, float _center_y);
      void setNewBottomLeftPos(float _bottomLeft_x, float _bottomLeft_y);

      ~Rect();
};


#endif /* RECT_H */

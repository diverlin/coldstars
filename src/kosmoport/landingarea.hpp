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


#ifndef LANDINGAREA_H
#define LANDINGAREA_H


class LandingArea
{
        public:
                LandingArea(TextureOb* _pTo_texOb, float _center_x, float _center_y, int _w, int _h);
                ~LandingArea();
        
                Ship* getShip();
                Rect getRect() const;
                bool getBusyFlag() const;
                bool getCursoredFlag() const;
                
                void setBusyFlag(bool);
                void setCursoredFlag(bool);
                
                void placeShip(Ship*);
                void removeShip(); 
        
                void renderArea();
                void renderInternals();
                void renderInfo();
                
        private:
                bool is_BUSY;
                bool is_CURSORED;
                  
                TextureOb* texOb;
                        
                Ship* ship;                
                Rect rect;
        
}; 

#endif

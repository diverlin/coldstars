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


#ifndef ANGAR_H
#define ANGAR_H


class Angar
{
        public: 
                Angar(TextureOb*, TextureOb*);
                ~Angar();
                
                bool addShip(Ship*);
                bool removeShipFromlandingAreaById(int);

                void update();

                void render() const;
                void renderItemInfo() const;

                int getNumFreelandingArea();
                
        private:
                TextureOb* texOb_background;
                
                std::vector<LandingArea*> landingArea_vec;

                void renderBackground() const;
                void renderInternals() const;
                
                void resetSlotsRenderInfoFlag();
                void mouseControl();
        
};

#endif 

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


class ItemSlot; //#include "../spaceobjects/ItemSlot.hpp"
#include "../spaceobjects/BaseGameEntity.hpp"

class Turrel
{
        public:
                Turrel(ItemSlot*);
                ~Turrel();

                void SetTextureOb(TextureOb* textureOb)	{ this->textureOb = textureOb; };
                              
                void SetTarget(BaseGameEntity* target) 	{ this->target = target; };
                void SetSelectedStatus(bool selected) 	{ is_SELECTED = selected; };
                
                bool GetSelectedStatus() const	{ return is_SELECTED; };
                Points& GetPoints()		{ return points; };
                
                BaseGameEntity* GetTarget() const { return target; };
       
                void ResetTarget() { target = NULL; };
                       
                void CheckTarget();                
                bool CheckAmmo() const;
                
                bool FireEvent(int, bool);

                void Render(float);                 
               
        private:
                TextureOb* textureOb;
                        
                ItemSlot* slot;
                BaseGameEntity* target;
                
                bool is_SELECTED;                        
               
                Points points;         
}; 

#endif 

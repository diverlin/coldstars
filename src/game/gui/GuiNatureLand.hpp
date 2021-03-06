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

#ifndef GUINATURELAND_H
#define GUINATURELAND_H

#include "BaseGuiElement.hpp"
class NatureLand;
class ItemSlot;
#include "GuiPair.hpp"
#include "../common/rect.hpp"
#include "MouseData.hpp"

class GuiNatureLand : public BaseGuiElement
{
        public:
               GuiNatureLand();
               ~GuiNatureLand();
        
        void BindNatureLand(NatureLand*);
        
               bool UpdateMouseInteractionWithEquipedItemSlots(const MouseData&);

               void ButtonsAction() const;   
             
             void RenderBackground(const Rect& rect) const;
                void RenderEquipedItemSlots() const;
                             
           private:
                   NatureLand* natureland;
                           
                     std::vector<GuiPair<Rect, ItemSlot*>> rect_itemslot_vec;
};


#endif 

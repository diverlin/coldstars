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
             
#include "ButtonItemSlot2.hpp"
#include <core/slot/ItemSlot.hpp>
    
namespace gui {

ButtonItemSlot2::ButtonItemSlot2(slot::Item* slot)
    :
      BaseButtonItemSlot(slot)
{
}

ButtonItemSlot2::~ButtonItemSlot2()
{
}

void ButtonItemSlot2::onPressEventMBL(client::Player* player)
{
    if (!isLocked()) {
        _setIsPressed(!isPressed());
    } else {
        _setIsPressed(false);
    }
        
    if (itemSlot()) // !!!
    {        
//        if (GetPressed() == true)
//        {
//            if (GetItemSlot()->isSelected() == false)
//            {
//                GetItemSlot()->SelectEvent();
//            }
//        }
//        else
//        {
//            if (GetItemSlot()->isSelected() == true)
//            {
//                GetItemSlot()->DeselectEvent();
//            }
//        }
    }
}

/* virtual override final */
void ButtonItemSlot2::resetState()
{
    _setIsPressed(false);
    if (itemSlot() != nullptr)
    {  
//        if (GetItemSlot()->isSelected() == true)
//        {
//            GetItemSlot()->DeselectEvent();
//        }
    }
}
        
/* virtual override final */    
void ButtonItemSlot2::_updateUnique(client::Player* player)
{
    _createItemView();
    _updateAnimation();
            
    if (!hasAnimation()) {
        if (itemSlot()) {
            if (isPressed()) {
                box().setScale(1.5, 1.5);
            } else {
                box().setScale(1.0, 1.0);
            }
        }
    } else {
        if (isPressed()){
            resetState();
        }
    }
}

/*virtual override final*/
void ButtonItemSlot2::_renderUnique(const jeti::Render& render, client::Player*) const
{
    _drawSlot(render);
    _drawItem(render);
}        

} // namespace gui

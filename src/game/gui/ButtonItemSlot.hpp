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


#ifndef BUTTONITEMSLOT_HPP
#define BUTTONITEMSLOT_HPP

#include "BaseButtonItemSlot.hpp"


class ButtonItemSlot : public BaseButtonItemSlot
{
    public:
        ButtonItemSlot(TYPE::GUI subtype_id, const std::string& info)
        :
        BaseButtonItemSlot(TYPE::GUI::BUTTON_ITEMSLOT_ID, subtype_id, info)
        {}
               
        virtual ~ButtonItemSlot() final {};  

        virtual void OnPressEventMBL(Player*) override final;
        virtual void OnPressEventMBR(Player*) override final;
                                
    private:
        virtual void UpdateUnique(Player*) override final;    
        
        virtual void RenderInfo() const override final;  
        virtual void RenderUnique(Player*) const override final;
};

#endif

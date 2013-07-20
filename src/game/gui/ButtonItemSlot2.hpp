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

#ifndef BUTTONITEMSLOT2_HPP
#define BUTTONITEMSLOT2_HPP

#include "BaseButton.hpp"
class ItemSlot;

class ButtonItemSlot2 : public BaseButton
{
	public:
        ButtonItemSlot2(GUI::eTYPE subtype_id, const std::string& info, ItemSlot* itemslot)
        :
        BaseButton(subtype_id, info), 
        m_ItemSlot(itemslot) 
        {}
               
        virtual ~ButtonItemSlot2() override final {};  

        virtual void PressEvent(Player*) override final;
        virtual void UpdateUnique(Player*) override final;
        
        virtual void RenderUnique(Player*) const override final; 
        
	private:
        ItemSlot* m_ItemSlot;
};

#endif

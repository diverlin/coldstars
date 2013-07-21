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

#include "BaseButton.hpp"
class ItemSlot;

class ButtonItemSlot : public BaseButton
{
	public:
        ButtonItemSlot(GUI::eTYPE subtype_id, const std::string& info)
        :
        BaseButton(subtype_id, info), 
        m_ItemSlot(nullptr) 
        {}
               
        virtual ~ButtonItemSlot() final {};  
        
        bool GetEquiped() const;
        
        void SetItemSlot(ItemSlot* itemslot) { m_ItemSlot = itemslot; }

        virtual void PressEvent(Player*) override final;
        
        virtual void RenderInfo() const override final;  
        virtual void RenderUnique(Player*) const override final;
         
        void RenderMark(const Box&, TextureOb*) const;
                
	private:
        ItemSlot* m_ItemSlot;
};

#endif

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


#ifndef BASEBUTTONITEMSLOT_HPP
#define BASEBUTTONITEMSLOT_HPP

#include "BaseButton.hpp"
class ItemSlot;


class BaseButtonItemSlot : public BaseButton
{
    public:
        BaseButtonItemSlot(TYPE::GUI type_id, TYPE::GUI subtype_id, const std::string& info)
        :
        BaseButton(type_id, subtype_id, info), 
        m_ItemSlot(nullptr) 
        {}
               
        virtual ~BaseButtonItemSlot() {};  
        
        bool GetEquiped() const;
        
        void SetItemSlot(ItemSlot* item_slot) { m_ItemSlot = item_slot; }
                   
    protected:
        ItemSlot* const GetItemSlot() const { return m_ItemSlot; }

        void UpdateAnimationProgram();

        void RenderMarkEmptySlot(const glm::vec2&, TYPE::GUI) const;
        void RenderMarkTarget() const;
                        
    private:
        ItemSlot* m_ItemSlot;    
    
};

#endif

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

#ifndef BUTTONTRIGGER_HPP
#define BUTTONTRIGGER_HPP

#include "BaseButton.hpp"

class ButtonTrigger : public BaseButton
{
    public:
        ButtonTrigger(TYPE::GUI subtype_id, const std::string& info, void (*pAction)(Player*), TextureOb* textureOb)
        :
        BaseButton(TYPE::GUI::BUTTON_TRIGGER_ID, subtype_id, info, pAction, textureOb) {};
               
        virtual ~ButtonTrigger() override final {};  

        virtual void OnPressEventMBL(Player*) override final;
        virtual void UpdateUnique(Player*) override final;
        
    private:
};

#endif

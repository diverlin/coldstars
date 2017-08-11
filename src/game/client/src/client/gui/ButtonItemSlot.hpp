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


#pragma once

#include "BaseButtonItemSlot.hpp"

class Renderer;

class ButtonItemSlot : public BaseButtonItemSlot
{
public:
    ButtonItemSlot(gui::type group, const std::string& info)
        :
          BaseButtonItemSlot(gui::type::BUTTON_ITEMSLOT, group, info)
    {}

    virtual ~ButtonItemSlot() final {}

    virtual void OnPressEventMBL(Player*) override final;
    virtual void OnPressEventMBR(Player*) override final;

private:
    virtual void UpdateUnique(Player*) override final;

    virtual void RenderInfo(const jeti::Render&) const override final;
    virtual void RenderUnique(const jeti::Render&, Player*) const override final;
};



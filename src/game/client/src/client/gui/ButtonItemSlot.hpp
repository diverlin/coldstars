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

namespace gui {

class ButtonItemSlot : public BaseButtonItemSlot
{
public:
    ButtonItemSlot(Type group, const std::string& info)
        :
          BaseButtonItemSlot(Type::BUTTON_ITEMSLOT, group, info)
    {}

    virtual ~ButtonItemSlot() final {}

    virtual void onPressEventMBL(client::Player*) override final;
    virtual void onPressEventMBR(client::Player*) override final;

private:
    virtual void _updateUnique(client::Player*) override final;

    virtual void renderInfo(const jeti::Render&) const override final;
    virtual void _renderUnique(const jeti::Render&, client::Player*) const override final;
};

} // namespace gui


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

#include "BaseButton.hpp"

namespace gui {

class ButtonSingle : public BaseButton
{
public:
    ButtonSingle(Type group,
                 const std::string& info,
                 void (*pAction)(client::Player*),
                 jeti::model::Material* material)
        :
          BaseButton(Type::BUTTON_SINGLE,
                     group,
                     info,
                     pAction,
                     material)
    {}

    virtual ~ButtonSingle() {}

    virtual void onPressEventMBL(client::Player*) override final;
    virtual void _updateUnique(client::Player*) override final;
};

} // namespace gui

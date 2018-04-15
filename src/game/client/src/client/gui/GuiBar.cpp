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

#include "GuiBar.hpp"

#include <client/session/Shortcuts.hpp>
#include <jeti/Screen.hpp>

namespace gui {

Bar::Bar(jeti::MaterialModel* material, Orientation orientation)
    :
      Base(Type::NONE,
           Type::NONE,
           "",
           material)
    , m_orientation(orientation)
{}

Bar::~Bar()
{}

void Bar::_updateUnique(client::Player* player)
{
//    int screen_w = client::shortcuts::screen()->width();
//    int screen_h = client::shortcuts::screen()->height();

//    // main gui frame
//    box().setSize(screen_w, BAR_HEIGHT);
//    if (m_orientation == Orientation::bottom) {
//        box().setOffset(0, -screen_h/2 + box().size().y);
//    } else {
//        box().setOffset(0, +screen_h/2 - box().size().y);
//    }
}

} // namespace gui

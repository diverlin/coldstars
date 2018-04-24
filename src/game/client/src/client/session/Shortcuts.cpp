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

#include "Shortcuts.hpp"

#include <core/session/Sessions.hpp>
#include <core/session/Session.hpp>

#include <client/gui/UserInputManagerInSpace.hpp>

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Screen.hpp>

namespace client {
namespace shortcuts {

jeti::Render* render() {
    return core::Sessions::get().session()->render();
}

jeti::Camera* camera() {
    return core::Sessions::get().session()->camera();
}

jeti::Screen* screen() {
    return core::Sessions::get().session()->screen();
}

gui::UserInputInSpace* inputs() {
    return core::Sessions::get().session()->inputs();
}

view::StarSystem* view() {
    return core::Sessions::get().session()->view();
}

client::Player* player() {
    return core::Sessions::get().session()->player();
}

} // namespace shortcuts
} // client

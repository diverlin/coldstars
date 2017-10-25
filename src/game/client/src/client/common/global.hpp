
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

#include <cassert>

class UserInputInSpace;

namespace type {
class Collector;
} // namespace type

namespace jeti {
//class Screen;
//class Render;
class Camera;
} // namespace jeti

namespace view {
class StarSystem;
} // namespace view

namespace client {

namespace comm {
class TelegramHandler;
} // namespace comm

class global
{
public:
    static global& get();

    void init();

    void setView(view::StarSystem* view) { m_view = view; }

    type::Collector& types() { return *m_types; }
//    jeti::Screen& screen() { return *m_screen; }
//    jeti::Camera& camera() { return *m_camera; }
    view::StarSystem& view() { return *m_view; }

    UserInputInSpace& input() { return *m_inputsManager; }

private:
    global();
    global(const global&) = delete;
    ~global();
    global& operator=(const global&) = delete;

    type::Collector* m_types = nullptr;
//    jeti::Screen* m_screen = nullptr;
//    jeti::Camera* m_camera = nullptr;
    view::StarSystem* m_view = nullptr;

    UserInputInSpace* m_inputsManager = nullptr;

    bool m_init = false;
};

} // namespace client

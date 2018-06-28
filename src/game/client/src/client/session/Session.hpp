
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

# pragma once

#include <core/session/Session.hpp>

namespace gui {
class UserInputInSpace;
}

namespace type {
class Collector;
} // namespace type

namespace jeti {
class Render;
class Camera;
class Screen;
} // namespace jeti

namespace view {
class StarSystem;
} // namespace view

class ClientSession : public core::BaseSession {
public:
    ClientSession(int);
    ~ClientSession() override;

    void init(bool) override final;

    jeti::Render* render() const override final { return m_render; }
    jeti::Camera* camera() const override final { return m_camera; }
    jeti::Screen* screen() const override final { return m_screen; }
    view::StarSystem* view() const override final { return m_view; }
    core::Player* player() const override final { return m_player; }

    gui::UserInputInSpace* inputs() const override final { return m_inputs; }

private:
    bool m_init = false;

    jeti::Camera* m_camera = nullptr;
    jeti::Render* m_render = nullptr;
    jeti::Screen* m_screen = nullptr;
    view::StarSystem* m_view = nullptr;
    core::Player* m_player = nullptr;

    gui::UserInputInSpace* m_inputs = nullptr;
};




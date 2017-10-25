
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

namespace jeti {
class Render;
class Camera;
class Screen;
} // namespace jeti

namespace client {

class Session : public core::Session {
public:
    Session();
    virtual ~Session()=default;

    void init() override final;

    jeti::Render* render() override final { return m_render; }
    jeti::Camera* camera() override final { return m_camera; }
    jeti::Screen* screen() override final { return m_screen; }

private:
    bool m_init = false;

    jeti::Render* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
    jeti::Screen* m_screen = nullptr;
};

} // namespace client



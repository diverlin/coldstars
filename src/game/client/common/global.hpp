
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

namespace jeti {
class Screen;
class Renderer;
class Camera;
} // namespace jeti

namespace client {

class global
{
public:
    static global& get();

    void init();

    jeti::Screen& screen() { return *m_screen; }
    jeti::Renderer& render() { return *m_render; }
    jeti::Camera& camera() { return *m_camera; }

private:
    global();
    global(const global&) = delete;
    ~global();
    global& operator=(const global&) = delete;

    jeti::Screen* m_screen = nullptr;
    jeti::Renderer* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
};

} // namespace client

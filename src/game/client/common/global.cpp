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

#include "global.hpp"

#include <client/resources/Data.hpp>
#include <client/gui/UserInputManagerInSpace.hpp>

#include <core/types/TextureTypes.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>

namespace client
{

global& global::get()
{
    static global instance;
    return instance;
}

global::global()
    :
      m_types(new type::Types)
    , m_screen(new jeti::Screen)
    , m_render(new jeti::Renderer)
    , m_camera(new jeti::Camera)
    , m_inputsManager(new UserInputInSpace)
{
}

global::~global()
{
    delete m_screen;
    delete m_render;
    delete m_camera;
    delete m_inputsManager;
}

void
global::init() {
    m_screen->init();
    m_render->init(m_camera, m_screen->width(), m_screen->height());

    Data data;
}

} // namespace client

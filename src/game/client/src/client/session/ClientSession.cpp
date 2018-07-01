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

#include "ClientSession.hpp"

#include <core/resource/Data.hpp>

#include <client/gui/UserInputManagerInSpace.hpp>
#include <client/view/StarSystem.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/pilot/Player.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>

#include <ceti/Logger.hpp>


ClientSession::ClientSession(int id, bool use_graphic)
    :
      core::BaseSession(id)
    , m_use_graphic(use_graphic)
{
    if (m_use_graphic) {
        m_camera = new jeti::Camera;
        m_render = new jeti::Render(m_camera);
        m_screen = new jeti::Screen;
        m_inputs = new gui::UserInputInSpace;
    }

    m_player = new client::Player(id);
}

ClientSession::~ClientSession()
{
    delete m_render;
    delete m_camera;
    delete m_screen;
    delete m_inputs;
    delete m_view;
    delete m_player;
}

void
ClientSession::init(bool save) {
    if (m_init) {
        return;
    }

    srand(time(0));

    if (m_use_graphic) {
        /// in a name of god don't change order below
        m_screen->init();
        m_render->init(m_screen->width(), m_screen->height());
    }

    core::Data data(save);

    if (m_use_graphic) {
        gui::MaterialCollector::get().load();

        m_view = new view::StarSystem(*m_render, *m_screen);
    }
    ///

    m_init = true;
}

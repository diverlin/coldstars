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
#include <client/pilot/Player.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>

#include <ceti/Logger.hpp>


ClientSession::ClientSession(int id, bool use_graphic)
    :
      core::BaseSession(id)
    , m_useGraphic(use_graphic)
{
}

ClientSession::~ClientSession()
{
    delete m_view;
    delete m_player;
}

void
ClientSession::init(bool save) {
    if (m_initialized) {
        return;
    }

    srand(time(0));

    core::Data data(save);

    m_player = new client::Player(id(), m_useGraphic);

    if (m_useGraphic) {
        m_view = new view::StarSystemViewer;
        m_player->initGraphic(); // run it after view
    }

    m_initialized = true;
}


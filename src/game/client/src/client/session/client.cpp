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

#include "client.hpp"

#include <core/communication/TelegramHandler.hpp>
#include <core/session/ServerSession.hpp>
#include <core/session/Sessions.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Planet.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Ship.hpp>
#include <core/common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/world/galaxy.hpp>
#include <core/world/Sector.hpp>
#include <core/world/starsystem.hpp>
#include <core/communication/TelegramHub.hpp>
#include <core/resource/Data.hpp>

#include <client/session/ClientSession.hpp>
#include <client/session/Shortcuts.hpp>
#include <client/gui/UserInputManagerInSpace.hpp>
#include <client/gui/UserInput.hpp>
#include <client/pilot/Player.hpp>
#include <client/view/StarSystem.hpp>
#include <client/gui/GuiManager.hpp>
#include <client/communication/TelegramHandler.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Render.hpp>

namespace client {

Client::Client(int id, bool graphic):
    m_id(id)
  , m_graphic(graphic)
{
    m_session = new ClientSession(id, m_graphic);

    core::Sessions::get().add(m_session);
    __activate();

    bool save = false;
    m_session->init(save);

    if (m_graphic) {
        m_camera = shortcuts::camera();
        m_inputs = shortcuts::inputs();
        m_render = shortcuts::render();
        m_screen = shortcuts::screen();
        m_view = shortcuts::view();
    }

    m_telegramHandler = std::shared_ptr<TelegramHandler>(new TelegramHandler());
    core::global::get().telegramHub().subscribe(m_telegramHandler);
}

Client::~Client()
{
    core::Sessions::get().remove(m_id);
//    global::get().telegramHub().unsubscribe(m_telegramHandler); // ??
    delete m_session;
}

Player* Client::player() const { return m_session->player(); }

bool Client::sessionIsRunning() const {
    if (m_graphic) {
        return m_screen->window().isOpen();
    } else {
        return true;
    }
}

bool Client::isRunning() const
{
    if (m_graphic) {
        return m_inputs->runSession() && m_screen->window().isOpen();
    } else {
        return true;
    }
}


void Client::update() {
    __activate();

    m_telegramHandler->update();

    if (!player()->npc()) {
        requestCreatePlayerNpc();
        return;
    }

    if (!player()->npc()->vehicle()) {
        requestCreatePlayerVehicle();
        return;
    }

    if (!player()->npc()->vehicle()->starsystem()) {
        return;
    }

    core::control::StarSystem* starsystem = player()->npc()->vehicle()->starsystem();

    // simulate model(repeate what server is doing)
    //std::cout<<core::shortcuts::session()->turnTimer().ticksLeft()<<std::endl;
    core::shortcuts::session()->turnTimer().update(/*threshold*/-100);
    starsystem->update_client(core::shortcuts::session()->turnTimer().ticksLeft());

    if (m_graphic) {

        if (!m_view->player()) {
            m_view->setPlayer(player());
        }
        m_inputs->update(player());
        player()->cursor().updateMouseInput(*m_render);

        m_view->update(m_inputs->scrollAccel());
        m_view->render(starsystem);

        gui::Manager::get().update(player());
        gui::Manager::get().render(*m_render, player());

        m_screen->draw();
    }
}

void Client::__activate() const {
    core::Sessions::get().activate(m_id);
}

void Client::requestCreatePlayerNpc() {
    player()->requestCreateNpc();
}

void Client::requestCreatePlayerVehicle()
{
    // assert(false);
}

} // namespace client

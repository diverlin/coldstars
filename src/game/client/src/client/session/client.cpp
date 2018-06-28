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
#include <core/session/Session.hpp>
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

#include <client/session/Session.hpp>
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
    if (m_graphic) {
        m_session = new Session(id);
    } else {
        m_session = new core::Session(id);
    }

    core::Sessions::get().add(m_session);
    __activate();

    bool save = false;
    core::shortcuts::session()->init(save);

    if (m_graphic) {
        m_camera = shortcuts::camera();
        m_inputs = shortcuts::inputs();
        m_render = shortcuts::render();
        m_screen = shortcuts::screen();
        m_view = shortcuts::view();
    }

    m_player = new Player(m_id);

    m_telegramHandler = std::shared_ptr<TelegramHandler>(new TelegramHandler());
    core::global::get().telegramHub().subscribe(m_telegramHandler);
}

Client::~Client()
{
    core::Sessions::get().remove(m_id);
//    global::get().telegramHub().unsubscribe(m_telegramHandler); // ??
    delete m_session;
}

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

    if (!m_player) {
        request_create_player();
        //assert(false);
        //__create_player();
        //m_view->setPlayer(m_player);
        //return;
    }

    //std::cout<<"111"<<std::endl;
    if (!m_player->npc()) {
        return;
    }
    //std::cout<<"222"<<std::endl;
    if (!m_player->npc()->vehicle()) {
        return;
    }
    //std::cout<<"333"<<std::endl;
    if (!m_player->npc()->vehicle()->starsystem()) {
        return;
    }
    std::cout<<"444"<<std::endl;

    core::control::StarSystem* starsystem = m_player->npc()->vehicle()->starsystem();

    // simulate model(repeate what server is doing)
    //std::cout<<core::shortcuts::session()->turnTimer().ticksLeft()<<std::endl;
    core::shortcuts::session()->turnTimer().update(/*threshold*/-100);
    starsystem->update_client(core::shortcuts::session()->turnTimer().ticksLeft());

    if (m_graphic) {
        m_inputs->update(m_player);
        m_player->cursor().updateMouseInput(*m_render);

        m_view->update(m_inputs->scrollAccel());
        m_view->render(starsystem);

        gui::Manager::get().update(m_player);
        gui::Manager::get().render(*m_render, m_player);

        m_screen->draw();
    }
}

void Client::__activate() const {
    core::Sessions::get().activate(m_id);
}

void Client::request_create_player() {
    m_player->requestCreateNpc();
}

void Client::reply_create_player(int_t npc_id)
{
    core::control::Npc* npc = core::shortcuts::entities()->npc(npc_id);
    assert(npc);
    m_player->setNpc(npc);
}

//void Client::__create_player() {
//    core::control::Galaxy* galaxy = core::shortcuts::entities()->galaxy();
//    if (!galaxy) {
//        //            if (meti::rand::gen_int(1000) == 1000)
//        //                std::cout<<"galaxy is null"<<std::endl;
//        return;
//    }

//    int_t id = core::shortcuts::entities()->nextId();
//    m_player = new Player(id);

//    core::control::StarSystem* starsystem = galaxy->randomSector()->randomStarSystem();
//    assert(starsystem->ships().size());
//    core::control::Npc* npc = starsystem->ships().front()->npc();
//    assert(npc);
//    m_player->setNpc(npc);
//}

} // namespace client

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

Client::Client(int id):
    m_id(id)
{
    core::Sessions::get().add(id, new client::Session(core::Session::Type::CLIENT));

    __activate();

    core::shortcuts::session()->init();

    m_camera = client::shortcuts::camera();
    m_inputs = client::shortcuts::inputs();
    m_render = client::shortcuts::render();
    m_screen = client::shortcuts::screen();
    m_view = client::shortcuts::view();

    m_telegramHandler = std::shared_ptr<client::comm::TelegramHandler>(new client::comm::TelegramHandler());
    core::global::get().telegramHub().subscribe(m_telegramHandler);
}

Client::~Client()
{
}

bool Client::sessionIsRunning() const {
    return m_screen->window().isOpen();
}

bool Client::isRunning() const { return m_inputs->runSession() && m_screen->window().isOpen(); }


void Client::update() {
    __activate();

    gui::Manager& gui = gui::Manager::get();

    m_telegramHandler->update();

    if (!m_player) {
        __create_player();
        m_view->setPlayer(m_player);
        return;
    }

    control::StarSystem* starsystem = m_player->npc()->vehicle()->starsystem();
    assert(starsystem);

    // simulate model(repeate what server is doing)
    //std::cout<<core::shortcuts::session()->turnTimer().ticksLeft()<<std::endl;
    core::shortcuts::session()->turnTimer().update(/*threshold*/-100);
    starsystem->update_client(core::shortcuts::session()->turnTimer().ticksLeft());

    m_inputs->update(m_player);
    m_player->cursor().updateMouseInput(*m_render);

    m_view->update(m_inputs->scrollAccel());
    m_view->render(starsystem);

    gui.update(m_player);
    gui.render(*m_render, m_player);

    m_screen->draw();
}


void Client::__activate() const {
    core::Sessions::get().activate(m_id);
}

void Client::__create_player() {
    control::Galaxy* galaxy = core::shortcuts::entities()->galaxy();
    if (!galaxy) {
        //            if (meti::rand::gen_int(1000) == 1000)
        //                std::cout<<"galaxy is null"<<std::endl;
        return;
    }

    int_t id = core::shortcuts::entities()->nextId();
    m_player = new client::Player(id);

    control::StarSystem* starsystem = galaxy->randomSector()->randomStarSystem();
    assert(starsystem->ships().size());
    control::Npc* npc = starsystem->ships().front()->npc();
    assert(npc);
    m_player->setNpc(npc);
}

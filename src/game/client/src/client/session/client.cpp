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
    IMachine(id)
  , m_graphic(graphic)
{
    m_session = new ClientSession(id, m_graphic);

    core::Sessions::get().add(m_session);
    _activate();

    bool save = false;
    m_session->init(save);

    m_telegramHandler = std::shared_ptr<TelegramHandler>(new TelegramHandler());
    core::global::get().telegramHub().subscribe(m_telegramHandler);
}

Client::~Client()
{
    core::Sessions::get().remove(id());
//    global::get().telegramHub().unsubscribe(m_telegramHandler); // ??
    delete m_session;
}

jeti::Camera* Client::_camera() const { return m_session->view()->camera(); }
jeti::Render* Client::_render() const { return m_session->view()->renderer(); }
jeti::Screen* Client::_screen() const { return m_session->view()->screen(); }
gui::UserInputInSpace* Client::_inputs() const { return m_session->view()->inputs(); }
view::StarSystemViewer* Client::_view() const { return m_session->view(); }
Player* Client::player() const { return m_session->player(); }

bool Client::sessionIsRunning() const {
    if (m_graphic) {
        return _screen()->window().isOpen();
    } else {
        return true;
    }
}

bool Client::isRunning() const
{
    if (m_graphic) {
        return _inputs()->runSession() && _screen()->window().isOpen();
    } else {
        return true;
    }
}


void Client::update() {
    _activate();

    m_telegramHandler->update();

    std::cout<<"111"<<std::endl;
    if (!m_isConnected) {
        return; // used for testing
    }

    std::cout<<"222"<<std::endl;
    if (!player()->npc()) {
        requestCreatePlayerNpc();
        return;
    }

    std::cout<<"333"<<std::endl;
    if (!player()->npc()->vehicle()) {
        requestCreatePlayerVehicle();
        return;
    }

    std::cout<<"444"<<std::endl;
//    // WORKAROUND
//    core::control::Galaxy* galaxy = m_session->entities()->galaxy();
//    core::control::StarSystem* starsystem = galaxy->starsystems()[0];
////    starsystem->add(static_cast<core::control::Ship*>(player()->npc()->vehicle()));
//    // END WORKAROUND

    if (!player()->npc()->vehicle()->starsystem()) {
        return;
    }

    std::cout<<"555"<<std::endl;
    core::control::StarSystem* starsystem = player()->npc()->vehicle()->starsystem();

    // simulate model(repeate what server is doing)
    //std::cout<<core::shortcuts::session()->turnTimer().ticksLeft()<<std::endl;
    core::shortcuts::session()->turnTimer().update(/*threshold*/-100);
    starsystem->update_client(core::shortcuts::session()->turnTimer().ticksLeft());

    if (m_graphic) {

        if (!_view()->player()) {
            _view()->setPlayer(player());
        }
        _inputs()->update(player());
        player()->cursor().updateMouseInput(*_render());

        _view()->update(_inputs()->scrollAccel());
        _view()->draw(starsystem);

        gui::Manager::get().update(player());
        gui::Manager::get().render(*_render(), player());

        _screen()->draw();
    }
}

int Client::telegramsNum() const {
    return m_telegramHandler->telegramsNum();
}

void Client::connect()
{
    if (m_isConnected) {
        return;
    }

    // TODO: put valid logic here
    m_isConnected = true;
}

void Client::disconnect()
{
    if (!m_isConnected) {
        return;
    }

    // TODO: put valid logic here
    m_isConnected = false;
}

void Client::requestCreatePlayerNpc() {
    if (m_wait_npc) {
        return;
    }

    player()->requestCreateNpc();
    m_wait_npc = true;
}

void Client::requestCreatePlayerVehicle() {
    if (m_wait_vehicle) {
        return;
    }
    player()->requestCreateVehicle();
    m_wait_vehicle = true;
}

} // namespace client

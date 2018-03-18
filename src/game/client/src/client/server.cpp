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

#include "server.hpp"

#include <iostream>

#include "builder/world/GalaxyBuilder.hpp"
#include <common/Config.hpp>

#include <core/communication/TelegramCreator.hpp>
#include <core/communication/TelegramHandler.hpp>
#include <core/session/Session.hpp>
#include <core/session/Sessions.hpp>
#include <core/session/Shortcuts.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>
#include <jeti/GlErrorHelper.hpp>

#include <meti/RandUtils.hpp>

#include <client/session/Session.hpp>
#include <client/session/Shortcuts.hpp>
#include <client/resources/Data.hpp>
#include <client/gui/UserInputManagerInSpace.hpp>
#include <client/gui/UserInput.hpp>

#include <client/gui/ButtonTrigger.hpp>
#include <client/gui/GuiActions.hpp>

#include "common/TurnTimer.hpp"

#include <core/pilot/Npc.hpp>
#include <client/pilot/Player.hpp>

#include <core/spaceobject/Planet.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Ship.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

//#include <world/galaxy.hpp>
//#include <world/Sector.hpp>
//#include <world/starsystem.hpp>
//#include <Game.hpp>
//#include <ai/God.hpp>
#include <core/world/World.hpp>
#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/communication/TelegramHub.hpp>
#include <client/communication/TelegramHandler.hpp>

Server::Server(int id)
    :
      m_id(id)
{
    core::Sessions::get().add(id, new core::Session(core::Session::Type::SERVER));
    __activate();

    m_telegramHandler = std::shared_ptr<core::comm::TelegramHandler>(new core::comm::TelegramHandler(core::TelegramCreator::get()));
    core::global::get().telegramHub().subscribe(m_telegramHandler);

    Data data(/*server*/true); // why we need it on server?
    m_world = new control::World;
}

Server::~Server()
{
}

void Server::__activate() const {
    core::Sessions::get().activate(m_id);
}

void Server::update()
{
    __activate();
    m_telegramHandler->update();

    //        if (!m_players.size()) {
    //            __create_player();
    //        }

    core::global::get().telegramHub().broadcast();
    m_world->update();
}

void Server::__create_player() {
    //        int_t id = core::shortcuts::entities()->nextId();
    //        core::Player* player = new core::Player(id);
    //        m_players.push_back(player);

    //        control::StarSystem* starsystem = m_world->galaxy()->randomSector()->randomStarSystem();
    //        assert(starsystem->ships().size());
    //        control::Npc* npc = starsystem->ships().front()->npc();
    //        assert(npc);
    //        player->setNpc(npc);

    //        int_t npc_id = composer().createNpc();
    //        int_t ship_id = composer().createShip();
    //        composer().putNpcToShip(npc_id, ship_id);
    //        int_t player_id = composer().createPlayer(npc_id);
    //        composer().putShipToSpace(ship_id, starsystem_id);
    //        composer().bindPlayerWithNpc(player_id, npc_id);
}



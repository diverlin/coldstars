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

#include <gtest/gtest.h>

#include <ceti/type/IdType.hpp>

#include <core/communication/TelegramCreator.hpp>
#include <core/session/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <client/session/Session.hpp>
#include <client/session/server.hpp>
#include <client/session/client.hpp>
#include <client/pilot/Player.hpp>

namespace {

core::control::Ship* getShip(core::Session* session, int_t id) {
    return session->entities()->ship(id);
}

int_t createStarSystem(core::Server& server) {
    return core::TelegramCreator::get().createPureStarsystem();
}

int_t createShip(core::Server& server) {
//    return core::TelegramCreator::get().createEquipedShipWithNpc();
    return core::TelegramCreator::get().createPureShip();
}

void addShipToStarSystem(int_t starsystem_id, int_t ship_id) {
    core::TelegramCreator::get().addShipToStarSystem(starsystem_id, ship_id);
}

} // namespace

TEST(world, player_creation)
{
    core::Server server(true);
    client::Client client(1);

    client.request_create_player();
    client.update();

    server.update();
    client.update();

    server.update();
    client.update();

    client::Player* player = client.player();

    EXPECT_TRUE(client.player());
    EXPECT_TRUE(client.player()->npc());
//    EXPECT_TRUE(client.player()->npc()->vehicle());
//    EXPECT_TRUE(client.player()->npc()->vehicle()->starsystem());
}

TEST(world, dummy)
{
    core::Server server(true);
    client::Client client(1);

    server.update();
    client.update();

//    server.update();

//   int_t starsystem_id = createStarSystem(server);
//    int_t ship_id = createShip(server);
//    addShipToStarSystem(starsystem_id, ship_id);

    server.update();
    client.update();

    //core::control::Ship* ship_from_server = getShip(server.session(), ship_id);
    //core::control::Ship* ship_from_client = getShip(client.session(), ship_id);

    // validate server and client identity
}


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
#include <ceti/Logger.hpp>

#include <core/communication/TelegramCreator.hpp>
#include <core/session/ServerSession.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <core/model/ALL>

#include <client/session/ClientSession.hpp>
#include <client/session/server.hpp>
#include <client/session/client.hpp>
#include <client/pilot/Player.hpp>

namespace {

core::control::Ship* getShip(core::BaseSession* session, int_t id) {
    return session->entities()->ship(id);
}

core::control::Npc* getNpc(core::BaseSession* session, int_t id) {
    return session->entities()->npc(id);
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

void updateMachines(const std::vector<core::IMachine*>& machines, int ticks) {
    for (int i=0; i<ticks; ++i) {
        LOG_TEST("---tick="+std::to_string(i))
        for (core::IMachine* machine: machines) {
            machine->update();
        }
    }
}

template<typename T>
bool check_matches(T* left, T* right)
{
    assert(left);
    assert(right);
    bool result = (left->model()->data() == right->model()->data());
    if (!result) {
        std::cout<<left->model()->data()<<std::endl;
        std::cout<<right->model()->data()<<std::endl;
        std::cout<<"DIFF: "<<left->model()->info().diff(right->model()->info())<<std::endl;
    }

    return result;
}


} // namespace

TEST(world, player_creation)
{
    core::Server server(true);
    client::Client client(1);

    std::vector<core::IMachine*> machines = {&server, &client};

    client.requestCreatePlayerNpc();
    client.requestCreatePlayerVehicle();

    updateMachines(machines, 3);

    core::control::Npc* client_npc = client.player()->npc();
    core::control::Npc* server_npc = getNpc(server.session(), client_npc->id());

    EXPECT_TRUE(client_npc);
    EXPECT_TRUE(client_npc->vehicle());

    EXPECT_TRUE(server_npc);
    EXPECT_TRUE(server_npc->vehicle());

    EXPECT_TRUE(check_matches(server_npc, client_npc));
    EXPECT_TRUE(check_matches(server_npc->vehicle(), client_npc->vehicle()));
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


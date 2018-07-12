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
#include <core/manager/DescriptorManager.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Ship.hpp>
#include <core/item/Item.hpp>

#include <core/world/ALL>
#include <core/model/ALL>
#include <core/descriptor/ALL>

#include <client/session/ClientSession.hpp>
#include <client/session/server.hpp>
#include <client/session/client.hpp>
#include <client/pilot/Player.hpp>

#include <ceti/macros.hpp>

namespace {

core::control::Item* getItem(core::BaseSession* session, int_t id) {
    return session->entities()->item(id);
}

core::control::Ship* getShip(core::BaseSession* session, int_t id) {
    return session->entities()->ship(id);
}

core::control::Npc* getNpc(core::BaseSession* session, int_t id) {
    return session->entities()->npc(id);
}

core::control::Galaxy* getGalaxy(core::BaseSession* session) {
    return session->entities()->galaxy();
}

core::control::StarSystem* getStarSystem(core::BaseSession* session, int_t id) {
    return session->entities()->starsystem(id);
}

//core::control::Star* getStar(core::BaseSession* session, int_t id) {
//    return session->entities()->star(id);
//}

//core::control::Planet* getPlanet(core::BaseSession* session, int_t id) {
//    return session->entities()->planet(id);
//}

//core::control::Asteroid* getAsteroid(core::BaseSession* session, int_t id) {
//    return session->entities()->asteroid(id);
//}


void update(const std::vector<core::IMachine*>& machines/*, int ticks*/) {
    bool running = true;
    int counter = 0;
    int sleep_counter = 0;
    while (running) {
        std::cout<<"---tick="<<std::to_string(counter)<<std::endl;
        int telegrams_num = 0;
        for (core::IMachine* machine: machines) {
            machine->update();
            telegrams_num += machine->telegramsNum();
        }
        if (telegrams_num == 0 || counter > 1000) {
            sleep_counter++;
        }
        if (sleep_counter > 6) {
            running = false;
        }
        counter++;
    }
}

template<class T>
static void test_data_match(T* ob1, T* ob2)
{
    EXPECT_TRUE(ob1);
    EXPECT_TRUE(ob2);

    bool result = (ob1->data() == ob2->data());
    std::string diff = ob1->info().diff(ob2->info());

    // std::cout<<"session1: "<<ob1->info().toString()<<std::endl;
    // std::cout<<"session2: "<<ob2->info().toString()<<std::endl;

    if (diff != "") {
        std::cout<<"DIFF: \n"<<diff<<std::endl;
    }
    EXPECT_TRUE(result);
    EXPECT_EQ("", diff);
}


void test_sessions_models_match(core::BaseSession* session1, core::BaseSession* session2)
{
    core::control::Galaxy* session1_galaxy = getGalaxy(session1);
    core::control::Galaxy* session2_galaxy = getGalaxy(session2);

    test_data_match(session1_galaxy->model(), session2_galaxy->model());

    for (int_t starsystem_id: session1_galaxy->model()->starsystems()) {
        core::control::StarSystem* session1_starsystem = getStarSystem(session1, starsystem_id);
        core::control::StarSystem* session2_starsystem = getStarSystem(session2, starsystem_id);

        test_data_match(session1_starsystem->model(), session2_starsystem->model());

        for (int_t ship_id: session1_starsystem->model()->ships()) {
            core::control::Ship* session1_ship = getShip(session1, ship_id);
            core::control::Ship* session2_ship = getShip(session2, ship_id);

            test_data_match(session1_ship->model(), session2_ship->model());
            test_data_match(session1_ship->npc()->model(), session2_ship->npc()->model());

            for (int_t item_id: session1_ship->model()->items()) {
                core::control::Item* session1_item = getItem(session1, item_id);
                core::control::Item* session2_item = getItem(session2, item_id);

                // std::cout<<session1_item->model()->info().toString()<<std::endl;
                test_data_match(session1_item->model(), session2_item->model());
            }
        }
    }
}

} // namespace

namespace core {
namespace manager {

class TEST_Descriptors {
public:
    static void test_matches(const core::manager::Descriptors& descriptors1,
                             const core::manager::Descriptors& descriptors2)
    {
        ceti::pack<int_t> ids = test_ids_matches(descriptors1, descriptors2);
        for (int_t id: ids) {
            test_data_match(descriptors1.get(id), descriptors2.get(id));
        }
    }

private:
    static ceti::pack<int_t> test_ids_matches(const core::manager::Descriptors& descriptors1,
                                              const core::manager::Descriptors& descriptors2)
    {
        ceti::pack<int_t> ids1 = descriptors1.__ids();
        ceti::pack<int_t> ids2 = descriptors2.__ids();
        EXPECT_TRUE(ids1 == ids2);

        return ids1;
    }

};
} // namespace manager
} // namespace core

void test_sessions_descriptors_matches(core::BaseSession* session1, core::BaseSession* session2) {
    const core::manager::Descriptors& desriptors1 = *session1->descriptors();
    const core::manager::Descriptors& desriptors2 = *session2->descriptors();

    core::manager::TEST_Descriptors::test_matches(desriptors1, desriptors2);
}

TEST(sessions, player_creation)
{
    core::Server server(WorldType::DUMMY);
    client::Client client(1);
    client.connect();

    std::vector<core::IMachine*> machines = {&server, &client};

    update(machines);

    core::control::Npc* client_npc = client.player()->npc();
    core::control::Npc* server_npc = getNpc(server.session(), client_npc->id());

    EXPECT_TRUE(client_npc);
    EXPECT_TRUE(client_npc->vehicle());

    EXPECT_TRUE(server_npc);
    EXPECT_TRUE(server_npc->vehicle());

    test_data_match(server_npc->model(), client_npc->model());
    test_data_match(server_npc->vehicle()->model(), client_npc->vehicle()->model());
}

TEST(sessions, minimal_world_creation)
{
    core::Server server(WorldType::MINIMAL);
    client::Client client(1);

    std::vector<core::IMachine*> machines = {&server, &client};

    update(machines);

    test_sessions_models_match(server.session(), client.session());
}

TEST(sessions, normal_world_creation)
{
    core::Server server;
    client::Client client(1);

    std::vector<core::IMachine*> machines = {&server, &client};

    update(machines);

    test_sessions_models_match(server.session(), client.session());
}

TEST(sessions, descriptors_are_equals)
{
    core::Server server(WorldType::DUMMY);
    client::Client client(1);
    client::Client client2(2);

    test_sessions_descriptors_matches(server.session(), client.session());
    test_sessions_descriptors_matches(server.session(), client2.session());
}

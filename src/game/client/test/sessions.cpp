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

#include <core/world/ALL>
#include <core/model/ALL>
#include <core/descriptor/ALL>

#include <client/session/ClientSession.hpp>
#include <client/session/server.hpp>
#include <client/session/client.hpp>
#include <client/pilot/Player.hpp>

#include <ceti/macros.hpp>

namespace {

core::control::Ship* getShip(core::BaseSession* session, int_t id) {
    return session->entities()->ship(id);
}

core::control::Npc* getNpc(core::BaseSession* session, int_t id) {
    return session->entities()->npc(id);
}

core::control::Galaxy* getGalaxy(core::BaseSession* session) {
    return session->entities()->galaxy();
}

core::control::Sector* getSector(core::BaseSession* session, int_t id) {
    return session->entities()->sector(id);
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

template<typename T>
bool check_matches(T* left, T* right)
{
    assert(left);
    assert(right);
    if (left->descriptor()->id() != right->descriptor()->id()) {
        std::cout<<"left descriptor id="<<left->descriptor()->id()<<" right descriptor id="<<right->descriptor()->id();
        assert(false);
    }

    bool result = (left->model()->data() == right->model()->data());
    if (!result) {
        std::cout<<"DIFF: \n"<<left->model()->info().diff(right->model()->info())<<std::endl;
    }

    return result;
}

void test_sessions_models_match(core::BaseSession* session1, core::BaseSession* session2) {
    core::control::Galaxy* session1_galaxy = getGalaxy(session1);
    core::control::Galaxy* session2_galaxy = getGalaxy(session2);
    EXPECT_TRUE(check_matches(session1_galaxy, session2_galaxy));

    for (int_t sector_id: session1_galaxy->descriptor()->sectors) {
        core::control::Sector* session1_sector = getSector(session1, sector_id);
        core::control::Sector* session2_sector = getSector(session2, sector_id);
        EXPECT_TRUE(check_matches(session1_sector, session2_sector));

        for (int_t starsystem_id: session1_sector->descriptor()->starsystems) {
            core::control::StarSystem* session1_starsystem = getStarSystem(session1, starsystem_id);
            core::control::StarSystem* session2_starsystem = getStarSystem(session2, starsystem_id);
            EXPECT_TRUE(check_matches(session1_starsystem, session2_starsystem));

            for (int_t ship_id: session1_starsystem->model()->ships()) {
                core::control::Ship* session1_ship = getShip(session1, ship_id);
                core::control::Ship* session2_ship = getShip(session2, ship_id);
                EXPECT_TRUE(check_matches(session1_ship, session2_ship));
                EXPECT_TRUE(check_matches(session1_ship->npc(), session2_ship->npc()));
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
            test_descriptor_pair_match(descriptors1.get(id), descriptors2.get(id));
        }
    }

private:
    template<class T>
    static void test_descriptor_pair_match(T* descriptor1, T* descriptor2)
    {
        EXPECT_TRUE(descriptor1);
        EXPECT_TRUE(descriptor2);

        std::string diff = descriptor1->info().diff(descriptor2->info());
//        std::cout<<"session1: "<<descriptor1->info().toString()<<std::endl;
//        std::cout<<"session2: "<<descriptor2->info().toString()<<std::endl;
        if (diff != "") {
            std::cout<<diff<<std::endl;
        }
        EXPECT_EQ("", diff);
    }

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
    core::Server server(true);
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

    EXPECT_TRUE(check_matches(server_npc, client_npc));
    EXPECT_TRUE(check_matches(server_npc->vehicle(), client_npc->vehicle()));
}

TEST(sessions, world_creation)
{
    core::Server server;
    client::Client client(1);

    std::vector<core::IMachine*> machines = {&server, &client};

    update(machines);

    test_sessions_models_match(server.session(), client.session());
}


TEST(sessions, descriptors_are_equals)
{
    core::Server server;
    client::Client client(1);
    client::Client client2(2);

    test_sessions_descriptors_matches(server.session(), client.session());
    test_sessions_descriptors_matches(server.session(), client2.session());
}

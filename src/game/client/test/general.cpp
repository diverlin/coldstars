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

#include <core/session/Session.hpp>
#include <core/manager/EntityManager.hpp>

#include <client/session/Session.hpp>
#include <client/session/server.hpp>
#include <client/session/client.hpp>

namespace {

core::control::Ship* getShip(core::Session* session, int_t id) {
    return session->entities()->ship(id);
}

int_t createShip(core::Server& server) {
    int_t id = server.session()->entities()->nextId();
    assert(false);
    return id;
}

} // namespace

TEST(world, dummy)
{
    core::Server server(0, true);
    client::Client client(1);

    int_t id = createShip(server);

    server.update();
    client.update();

    core::control::Ship* ship_from_server = getShip(server.session(), id);
    core::control::Ship* ship_from_client = getShip(client.session(), id);

    // validate server and client identity
}


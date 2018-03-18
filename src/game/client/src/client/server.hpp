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

#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>
#include <Game.hpp>
#include <ai/God.hpp>

#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/manager/DescriptorManager.hpp>
#include "dock/Land.hpp"

#include "run_scenario/NormalRunScenario.hpp"
#include "run_scenario/TestParticlesRunScenario.hpp"
#include "run_scenario/TestTextRunScenario.hpp"
#include "run_scenario/TestDrawManySimpleMeshesRunScenario.hpp"

#include <client/view/StarSystem.hpp>

#include <core/communication/TelegramHub.hpp>
#include <client/communication/TelegramHandler.hpp>

#include <client/gui/GuiManager.hpp>

#include <memory>


class Server {

public:
    Server(int id);
    ~Server();

    void update();

private:
    int m_id = -1;
    control::World* m_world = nullptr;
    std::vector<core::Player*> m_players;

    std::shared_ptr<core::comm::TelegramHandler> m_telegramHandler;

    void __activate() const;
    void __create_player();
};

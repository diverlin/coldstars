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

#include <pureTest/pureTest.cpp>
#include <pureTest/threadTest.cpp>
#include <pureTest/vectorPerfomanceTest.cpp>
#include <pureTest/matrixPerfomanceTest.cpp>

#include <client/view/StarSystem.hpp>

#include <core/communication/TelegramHub.hpp>
#include <client/communication/TelegramHandler.hpp>

#include <memory>

//enum class RUN_SCENARIO { NORMAL_RUN, TEST_PARTICLES, TEST_TEXT, TEST_MANY_VAO };

//void render(Starsystem* starsystem, glm::vec3& center) {

//}

//{
    //runThreadTest();
    //runSinglethread();
    //runVectorPerfomanceTest();
    //runMatrixPerfomanceTest();

//    BaseRunScenario* run_scenario = nullptr;
//    RUN_SCENARIO scenario_type = RUN_SCENARIO::NORMAL_RUN;
//    switch(scenario_type) {
//        case RUN_SCENARIO::NORMAL_RUN:         { run_scenario = new NormalRunScenario(); break; }
//        case RUN_SCENARIO::TEST_PARTICLES:     { run_scenario = new TestParticlesRunScenario(); break; }
//        case RUN_SCENARIO::TEST_TEXT:          { run_scenario = new TestTextRunScenario(); break; }
//        case RUN_SCENARIO::TEST_MANY_VAO:      { run_scenario = new TestDrawManySimpleMeshesRunScenario(); break; }
//        default:                               { std::cout<<"INVALID_RUNSCENARIO"<<std::endl; return EXIT_FAILURE; break; }
//    }
//    run_scenario->Init(player);
//}

namespace {
//class base {
//public:
//    base(int i):
//    i(i)
//    {
//        std::cout<<"create"<<i<<std::endl;
//    }
//    ~base() {
//        std::cout<<"destroy"<<i<<std::endl;
//    }
//private:
//    int i=0;
//};


//void bench() {
//    {
//    std::shared_ptr<base> z1(new base(1));
//    std::shared_ptr<base> z2(new base(2));
//    std::cout<<"z1 count="<<z1.use_count()<<std::endl;
//    std::cout<<"z2 count="<<z2.use_count()<<std::endl;
//    //z1.reset();
//    z2 = z1;
//    std::cout<<"z1 count="<<z1.use_count()<<std::endl;
//    std::cout<<"z2 count="<<z2.use_count()<<std::endl;
//    }
//    exit(1);
//}

core::TelegramCreator& composer() { return core::TelegramCreator::get(); }

enum Machine { server, client };


class Server {
private:
    control::World* m_world = nullptr;
    std::vector<core::Player*> m_players;

    std::shared_ptr<core::comm::TelegramHandler> m_telegramHandler;

public:
    Server()
    {
        core::Sessions::get().add(Machine::server, new core::Session);
        __activate();

        m_telegramHandler = std::shared_ptr<core::comm::TelegramHandler>(new core::comm::TelegramHandler(core::global::get().telegramHub()));
        core::global::get().telegramHub().subscribe(m_telegramHandler);

        Data data;
        m_world = new control::World;
    }

    ~Server()
    {
    }

    void update()
    {
        __activate();
        m_telegramHandler->update();

//        if (!m_players.size()) {
//            __create_player();
//        }

        core::global::get().telegramHub().broadcast();
        m_world->update();
    }

    void __create_player() {
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

private:
    void __activate() const {
        core::Sessions::get().activate(Machine::server);
    }
};

class Client {
private:
    client::Player* m_player = nullptr;
    jeti::Camera* m_camera = nullptr;
    jeti::Render* m_render= nullptr;
    view::StarSystem* m_view = nullptr;
    UserInputInSpace* m_inputs = nullptr;
    jeti::Screen* m_screen = nullptr;

    std::shared_ptr<client::comm::TelegramHandler> m_telegramHandler;

public:
    Client()
    {
        core::Sessions::get().add(Machine::client, new client::Session);

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

    ~Client()
    {
    }

    void update() {
        __activate();

        m_telegramHandler->update();

        if (!m_player) {
            __create_player();
            m_view->setPlayer(m_player);
            return;
        }

        m_inputs->update(m_player);
        m_view->update(m_inputs->scrollAccel());
        m_view->render(m_player->npc()->vehicle()->starsystem());
        m_screen->draw();
    }

    bool is_running() { return m_inputs->runSession() && m_screen->window().isOpen(); }

private:
    void __activate() const {
        core::Sessions::get().activate(Machine::client);
    }

    void __create_player() {
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
};


} // namespace

int main()
{
    Server server;
    Client client;

    while(true) {
        server.update();
        client.update();
    }
    return EXIT_SUCCESS;
}
















//    Galaxy* galaxy = player->GetNpc()->vehicle()->starsystem()->sector()->galaxy();
        
//    player->GetNpc()->vehicle()->setGodMode(true);
    //player->GetNpc()->vehicle()->TEST_DamageAndLockRandItems(); // test
    //player->GetNpc()->vehicle()->TEST_DropRandomItemToSpace();

    //Screen::Instance().Resize(core::global::get().config().SCREEN_WIDTH/1.5,core::global::get().config().SCREEN_HEIGHT);
    
    /** */
    //ButtonTrigger* button = new ButtonTrigger(/*group=*/1, /*info*/"info", /*pAction=*/GuiActions::Test, /*textureOb*/NULL);
    //button->OnPressEventMBL(player);
    //button->OnPressEventMBL(player);

    //ButtonTrigger* button2 = new ButtonTrigger(/*group=*/2, /*info*/"info", /*pAction=*/GuiActions::Test2, /*textureOb*/NULL);
    //button2->OnPressEventMBL(player);
    
    ////GuiActions::GalaxyMapGuiTransition(player);
    ////player->GetGuiManager().EnterGuiSpace();
    ////player->GetGuiManager().GetGuiSpace().EnterGalaxyMap();
    /** */
    
//    // GAME LOOP
//    while (client::shortcuts::screen()->GetWindow().isOpen())
//    {
//        //std::cout<<player->GetNpc()->vehicle()->center().x<<std::endl;
//        //std::cout<<player->GetNpc()->vehicle()->properties().radar<<std::endl;
                
//        /* server code start */
//        TurnTimer::Instance().Update();

//        God::Instance().Update(GameDate::Instance().GetDate());
//        galaxy->Update(TurnTimer::Instance().GetTurnTick());

//        if ((TurnTimer::Instance().GetTurnEnded() == true) and (UserInputManagerInSpace::Instance().GetNextTurnReady())) {
//            TurnTimer::Instance().NextTurn();
//        }
//        /* server code end */

//        /* client code start */
//        player->UpdatePostTransaction();
//        player->RunSession(TurnTimer::Instance());
//        player->UpdatePostTransactionEvent(TurnTimer::Instance());
//        /* client code end */
        
//        if (TurnTimer::Instance().GetTurnEnded() == true) {
//           core::global::get().entitiesManager().ClearGarbage();

//            bool save_event = core::global::get().entitiesManager().UpdateSaveRequest();
//            bool load_event = core::global::get().entitiesManager().UpdateLoadRequest();
//            if (load_event == true) {
//                player = core::global::get().entitiesManager().GetPlayer();
//                galaxy = player->GetNpc()->vehicle()->starsystem()->GetSector()->GetGalaxy();
//            }
//            if (save_event == true) {
//                //..
//            }
//        }

//        // hack
//        if (TurnTimer::Instance().GetTurnTick() > 1) {
//            run_scenario->Update_inDynamic(player);
//        } else  {
//            run_scenario->Update_inStatic(player);
//        }

//        jeti::checkOpenglErrors(__FILE__,__LINE__);
//    }



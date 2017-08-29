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
//#include <ceti/descriptor/Collector.hpp>

#include "builder/world/GalaxyBuilder.hpp"
#include "builder/pilots/PlayerBuilder.hpp"
#include <common/Config.hpp>


#include <core/manager/Session.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>
#include <jeti/GlErrorHelper.hpp>

#include <client/gui/UserInputManagerInSpace.hpp>
#include <client/gui/UserInput.hpp>

#include <client/gui/ButtonTrigger.hpp>
#include <client/gui/GuiActions.hpp>

#include "common/TurnTimer.hpp"
#include <client/common/global.hpp>


#include <core/pilot/Npc.hpp>
#include <client/pilots/Player.hpp>

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

#include <core/communication/TelegrammHub.hpp>
#include <client/communication/TelegrammManager.hpp>

#include <memory>

//enum class RUN_SCENARIO { NORMAL_RUN, TEST_PARTICLES, TEST_TEXT, TEST_MANY_VAO };

//void render(Starsystem* starsystem, glm::vec3& center) {

//}

Player* createPlayer() {
    return PlayerBuilder::Instance().createNewPlayer();
}

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
class base {
public:
    base(int i):
    i(i)
    {
        std::cout<<"create"<<i<<std::endl;
    }
    ~base() {
        std::cout<<"destroy"<<i<<std::endl;
    }
private:
    int i=0;
};


void bench() {
    {
    std::shared_ptr<base> z1(new base(1));
    std::shared_ptr<base> z2(new base(2));
    std::cout<<"z1 count="<<z1.use_count()<<std::endl;
    std::cout<<"z2 count="<<z2.use_count()<<std::endl;
    //z1.reset();
    z2 = z1;
    std::cout<<"z1 count="<<z1.use_count()<<std::endl;
    std::cout<<"z2 count="<<z2.use_count()<<std::endl;
    }
    exit(1);
}

} // namespace
int main()
{
    client::global::get().init();

    // client shortcuts
    UserInputInSpace& input = client::global::get().input();
    jeti::Render& render = client::global::get().render();
    jeti::Camera& camera = client::global::get().camera();
    jeti::Screen& screen = client::global::get().screen();
    //

    int server_id = 0;
    int client_id = 1;

    core::Sessions::get().add(server_id, new core::Session);
    core::Sessions::get().add(client_id, new core::Session);
    core::Sessions::get().activate(server_id);

    core::global::get().telegrammHub().add(new client::comm::TelegrammManager());
    Player* player = createPlayer();

    control::World world;
    view::StarSystem view(render);
    view.setPlayer(player);

    control::StarSystem* starsystem = world.galaxy()->randomSector()->randomStarSystem();

    assert(starsystem->ships().size());
    control::Npc* npc =starsystem->ships().front()->npc();
    assert(npc);
    player->setNpc(npc);

    client::global::get().setView(&view);

    while(input.runSession() && screen.window().isOpen()) {
        input.update(player);
        camera.addSpeed(input.scrollAccel());
        camera.update();

        world.update();
        view.render(starsystem);
        screen.draw();
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
//    while (client::global::get().screen().GetWindow().isOpen())
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

    return EXIT_SUCCESS;
}


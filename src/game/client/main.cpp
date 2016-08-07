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
#include "resources/Data.hpp"
#include <ceti/Collector.hpp>

#include "builder/world/GalaxyBuilder.hpp"
#include "builder/pilots/PlayerBuilder.hpp"
#include <common/Config.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Screen.hpp>
#include <jeti/GlErrorHelper.hpp>

#include "gui/UserInputManagerInSpace.hpp"
#include "gui/ButtonTrigger.hpp"
#include "gui/GuiActions.hpp"

#include "common/TurnTimer.hpp"

#include "pilots/Npc.hpp"
#include "pilots/Player.hpp"

#include "spaceobjects/Planet.hpp"
#include "spaceobjects/Vehicle.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>
#include <Game.hpp>
#include <ai/God.hpp>

#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/DescriptorManager.hpp>
#include "dock/Land.hpp"

#include "run_scenario/NormalRunScenario.hpp"
#include "run_scenario/TestParticlesRunScenario.hpp"
#include "run_scenario/TestTextRunScenario.hpp"
#include "run_scenario/TestDrawManySimpleMeshesRunScenario.hpp"

#include <pureTest/pureTest.cpp>
#include <pureTest/threadTest.cpp>
#include <pureTest/vectorPerfomanceTest.cpp>
#include <pureTest/matrixPerfomanceTest.cpp>

#include <render/RenderManager.hpp>

enum class RUN_SCENARIO { NORMAL_RUN, TEST_PARTICLES, TEST_TEXT, TEST_MANY_VAO };

void render(Starsystem* starsystem, glm::vec3& center) {
    view::Viewer viewer;


}

//double getGravityForce(double m1, double m2, double r) {
//    double G = 6.67*pow(10,-11);
//    return (G * (m1 * m2) / (r * r));
//}

int main()
{
//    {
//        double m1=0;
//        double m2=0;
//        double r=0;

//        double me = 5.97219 * pow(10,24);

//        std::cout<<"Earth-Moon"<<std::endl;
//        m1 = me;
//        m2 = me * 0.0123;
//        r = 384399.0 / 2.0 * 1000.0;
//        std::cout<<"m1="<<m1<<"kg, m2="<<m2<<"kg, r="<<r<<"m"<<std::endl;
//        std::cout<<"f="<<getGravityForce(m1, m2, r)<<std::endl;

//        std::cout<<"Earth-Sun"<<std::endl;
//        m1 = 1.98892*pow(10,30);
//        m2 = me;
//        r = 149598261.0 / 2.0 * 1000.0 ;
//        std::cout<<"m1="<<m1<<"kg, m2="<<m2<<"kg, r="<<r<<"m"<<std::endl;
//        std::cout<<"f="<<getGravityForce(m1, m2, r)<<std::endl;

//        exit(0);
//    }

    //runThreadTest();
    //runSinglethread();    
    //runVectorPerfomanceTest();
    
    jeti::Screen::get().init();
    Data data;
    jeti::Mesh* mesh = new jeti::Mesh(global::get().descriptors().mesh().getByType((int)type::mesh::PLANE_ID));
    jeti::Screen::get().renderer().setMeshQuad(mesh);
        
    //runMatrixPerfomanceTest();
        
    Player* player = PlayerBuilder::Instance().createNewPlayer();
    
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
    
    model::World world;
    while(true) {
        world.update();
        glm::vec3 pos(0,0,0);
        render(world.activeStarsystem(), pos);
    }

//    Galaxy* galaxy = player->GetNpc()->vehicle()->starsystem()->sector()->galaxy();
        
//    player->GetNpc()->vehicle()->setGodMode(true);
    //player->GetNpc()->vehicle()->TEST_DamageAndLockRandItems(); // test
    //player->GetNpc()->vehicle()->TEST_DropRandomItemToSpace();

    //Screen::Instance().Resize(global::get().config().SCREEN_WIDTH/1.5, global::get().config().SCREEN_HEIGHT);
    
    /** */
    //ButtonTrigger* button = new ButtonTrigger(/*subtype_id=*/1, /*info*/"info", /*pAction=*/GuiActions::Test, /*textureOb*/NULL);
    //button->OnPressEventMBL(player);
    //button->OnPressEventMBL(player);

    //ButtonTrigger* button2 = new ButtonTrigger(/*subtype_id=*/2, /*info*/"info", /*pAction=*/GuiActions::Test2, /*textureOb*/NULL);
    //button2->OnPressEventMBL(player);
    
    ////GuiActions::GalaxyMapGuiTransition(player);
    ////player->GetGuiManager().EnterGuiSpace();
    ////player->GetGuiManager().GetGuiSpace().EnterGalaxyMap();
    /** */
    
//    // GAME LOOP
//    while (jeti::Screen::get().GetWindow().isOpen())
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
//            global::get().entitiesManager().ClearGarbage();

//            bool save_event = global::get().entitiesManager().UpdateSaveRequest();
//            bool load_event = global::get().entitiesManager().UpdateLoadRequest();
//            if (load_event == true) {
//                player = global::get().entitiesManager().GetPlayer();
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


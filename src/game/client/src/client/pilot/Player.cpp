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


#include "Player.hpp"

#include <core/common/TurnTimer.hpp>
#include <core/common/Config.hpp>
#include <core/world/starsystem.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/ai/Task.hpp>
#include <core/ai/StateMachine.hpp>
#include <core/spaceobject/ALL>
#include <core/pilot/Npc.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/part/WeaponComplex.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/pilot/Npc.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <client/view/effect/Beam.hpp>
#include <client/text/VerticalFlowText.hpp>
#include <client/view/spaceobject/ALL>
#include <client/gui/GuiGalaxyMap.hpp>
#include <client/gui/GuiManager.hpp>
#include <client/gui/UserInput.hpp>
#include <client/gui/UserInputManagerInSpace.hpp>
#include <client/communication/TelegramCreator.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

#include <meti/RandUtils.hpp>
#include <core/math/rand.hpp>

#include <ceti/Logger.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace client {

Player::Player(int_t id, bool use_graphic)
    :
      core::Player(id)
    , m_useGraphic(use_graphic)
{ 
}
    
Player::~Player()
{}  

void Player::initGraphic()
{
    if (m_useGraphic) {
        gui::Manager::get().setPlayer(this);
        m_cursor = new gui::Cursor;
    }
}

bool Player::isAnyWeaponSelected() const
{
    return npc()->vehicle()->weapons().isAnyWeaponSelected();
}

void Player::unselectWeapon(int offset)
{
    gui::Manager::get().vehiclePanel()->unselect(gui::Type::WEAPON_SLOT_SELECTOR, offset);
}

void Player::toggleWeapon(int offset)
{
    gui::Manager::get().vehiclePanel()->toggle(gui::Type::WEAPON_SLOT_SELECTOR, offset);
}

bool Player::enterScan(core::control::Vehicle* vehicle)
{
    gui::Manager::get().enterScan(this);
    m_blockSpaceNavigation = true;
    return true;
}

void Player::exitScan()
{
    if (!npc()->scanTarget()) {
        return;
    }

    npc()->resetScanTarget();
    gui::Manager::get().exitScan(this);
    m_blockSpaceNavigation = false;
}

void Player::requestCreateNpc() const
{
    int_t npc_descriptor_id = core::shortcuts::descriptors()->randNpc()->id();
    TelegramCreator::get().playerRequestCreateNpc(id(), npc_descriptor_id);
}

void Player::requestCreateVehicle() const
{
    int_t vehicle_descriptor_id = core::shortcuts::descriptors()->randShip()->id();
    assert(npc());
    TelegramCreator::get().playerRequestCreateShip(npc()->id(), vehicle_descriptor_id);
}

void Player::endTurnEvent()
{
    TelegramCreator::get().playerRequestTurnEnd(id());
}

void Player::pressLeftMouseButtonEvent()
{
    m_cursor->mouseData().setEvent(MouseData::Event::LeftButtonPress);
}

void Player::pressRightMouseButtonEvent()
{
    m_cursor->mouseData().setEvent(MouseData::Event::RightButtonPress);
}


const meti::vec3&
Player::position() const {
    assert(npc());
    assert(npc()->vehicle());
    return npc()->vehicle()->position();
}


float
Player::radius() const {
    assert(npc());
    assert(npc()->vehicle());
    return npc()->vehicle()->properties().radar;
}

bool Player::isAbleToGetFullControlOnScanedVehicle(bool force_full_control) const
{
    if (force_full_control == false) {
        if (npc()->vehicle()->id() == npc()->scanTarget()->id()) {
            force_full_control = true;
            // modify full control for friend ships
        }
    }
    
    return force_full_control;
}
          
void Player::UpdatePostTransaction()
{
    assert(false);
//    switch (npc->vehicle()->place())
//    {
//        case type::place::KOSMOPORT:
//        {
//            if (GuiManager::Instance().GetGuiKosmoport().GetInitDone() == false)
//            {
//                GuiManager::Instance().EnterGuiKosmoport();
//            }
            
//            if (GuiManager::Instance().GetGuiSpace().GetInitDone() == true)
//            {
//                GuiManager::Instance().ExitGuiSpace();
//            }
            
//            break;
//        }

//        case type::place::LAND:
//        {
//            break;
//        }
        
//        case type::place::KOSMOS:
//        {
//            if (GuiManager::Instance().GetGuiKosmoport().GetInitDone() == true)
//            {
//                GuiManager::Instance().ExitGuiKosmoport();
//            }
            
//            if (GuiManager::Instance().GetGuiSpace().GetInitDone() == false)
//            {
//                GuiManager::Instance().EnterGuiSpace();
//            }
            
//            break;
//        }
//    }
}

void Player::UpdatePostTransactionEvent(TurnTimer& turn_timer)
{
    assert(false);
//    if (starsystem == nullptr) //hack
//    {
//        starsystem = npc->vehicle()->starsystem();
//    }
    
//    if (starsystem->id() != npc->vehicle()->starsystem()->id())
//    {
//        //shortcuts::screen()->InitiateScrollTo(npc->vehicle()->center());
//        //shortcuts::screen()->GetRect().setCenter(npc->vehicle()->center());
//        starsystem = npc->vehicle()->starsystem();
//    }
    
//    VEHICLE_SPECIAL_ACTION_TYPE action_id = npc->vehicle()->GetSpecialActionId();
//    switch(action_id)
//    {
        //case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN:
        //{
            //if (npc->vehicle()->placeTypeId() == ENTITY::SPACE)
            //{
                //if (turn_timer.GetTurnEnded() == true)
                //{
                    //shortcuts::screen()->InitiateScrollTo(npc->vehicle()->center());
                //}
            //}
            
            //break;
        //}
        
//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT:
//        {
//            if (npc->vehicle()->placeTypeId() == type::place::HYPER_SPACE)
//            {
//                if (turn_timer.GetTurnEnded() == true)
//                {
//                    turn_timer.NextTurn();
//                }
//            }
            
//            break;
//        }

//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING:
//        {
//            if (npc->vehicle()->placeTypeId() == type::place::SPACE)
//            {
//                if (turn_timer.GetTurnEnded() == true)
//                {
//                    shortcuts::screen()->InitiateScrollTo(meti::vec2(npc->vehicle()->center()));
//                    turn_timer.NextTurn();
//                }
//            }
            
//            break;
//        }
    
//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING:
//        {
//            if (turn_timer.GetTurnEnded() == true)
//            {
//                shortcuts::screen()->InitiateScrollTo(meti::vec2(npc->vehicle()->center()));
//                turn_timer.NextTurn();
//            }
            
//            break;
//        }
//    }
}
             
//void Player::RenderInSpace_NEW(jeti::Render& render, control::StarSystem* starsystem)
//{
//    bool draw_background    = true;
//    bool draw_volumetric    = true;
//    bool draw_something     = false;
//    bool draw_spaceObjects  = true;
//    bool draw_shockwave     = true;
//    bool draw_robustSpaceObjects = true;

//    float scale = global::get().render().scaleBase();
//    int w = shortcuts::screen()->width();
//    int h = shortcuts::screen()->height();
////    glm::vec2 world_coord(shortcuts::screen()->bottomLeft());
    
//    render.clearColorAndDepthBuffers();
    
//    //render.enable_CULLFACE();
//    {
//        if (draw_background)
//        {
//            // render background and star to FBO0
//            render.activateFbo(0, w, h);
//            {
//                render.setPerspectiveProjection();
//                //starsystem->DrawBackground(render, world_coord);
//                render.setOrthogonalProjection();

////                for(Star* star : visible_STAR_vec)
////                {
////                    //alpitodorender render.DrawMeshMultiTextured(star->mesh(), star->textureOb(), star->actualModelMatrix());
////                }
//            }
//            render.deactivateFbo(0);

//            // BLOOM background and star (uses many FBO)
//            //resizeGl(w, h);
//            // alpitodorender render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), npc->vehicle()->starsystem()->GetStar()->GetBrightThreshold());
//        }

//        // VOLUMETRIC LIGHT to FBO1
//        if (draw_volumetric)
//        {
//            //resizeGl(w, h);
//            render.activateFbo(1, w, h);
//            {
//                //render.DrawStarField(w/2, h/2, -world_coord.x/10000.0f, -world_coord.y/10000.0f);
//                //render.drawPostEffectVolumetricLight(world_coord, w, h);
//            }
//            render.deactivateFbo(1);
//        }

//        if (draw_something)
//        {
////            render.ActivateFbo(2, w, h);
////            {
////                render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w*2, h*2);
////            }
////            render.DeactivateFbo(2);
//        }

//        if (draw_spaceObjects)
//        {
//            // render space entites to FBO2
//            render.activateFbo(3, w, h);
//            {
//                render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);

//                // resizeGl(w*scale, h*scale);
//                {
//                    for(Planet* planet : visible_PLANET_vec)
//                    {
//                        //planet->Render_NEW(render);
//                    }

//                    for(SpaceStation* spacestation : visible_SPACESTATION_vec)
//                    {
//                        //spacestation->RenderInSpace(render, 1/scale);
//                    }

//                    //if (getRandInt(0, 30) == 0) std::cout<<"ship num rendered="<<visible_SHIP_vec.size()<<std::endl;
//                    for(Ship* ship : visible_SHIP_vec)
//                    {
//                        //ship->RenderInSpace(render, 1/scale);
//                    }

//                    for(Asteroid* asteroid : visible_ASTEROID_vec)
//                    {
//                        //asteroid->Render_NEW(render, world_coord);
//                    }

//                    assert(false);
////                    for(BlackHole* blackhole : visible_BLACKHOLE_vec)
////                    {
////                        //blackhole->Render_NEW(render);
////                    }
//                }

//                {
//                    for(Container* container : visible_CONTAINER_vec)
//                    {
//                        //container->Render(render);
//                    }

//                    for(Satellite* satellite : visible_SATELLITE_vec)
//                    {
//                        //satellite->RenderInSpace(render, 1/scale);
//                    }

//                    for(Bullet* rocket : visible_ROCKET_vec)
//                    {
//                        //rocket->RenderInSpace(render, 1/scale);
//                    }
//                }
////                if (m_show.collisionRadius()) {
////                    RenderAxis(render);
////                    RenderCollisionRadius(render);
////                }
//            }
//            render.deactivateFbo(3);
//        }

//        if (draw_shockwave)
//        {
//            // SHOCKWAVE post process to Fbo3
//            //resizeGl(w, h);
//            render.activateFbo(4, w, h);
//            {
//                float center_array[SHOCKWAVES_MAX_NUM][2];
//                float xyz_array[SHOCKWAVES_MAX_NUM][3];
//                float time_array[SHOCKWAVES_MAX_NUM];

//                unsigned int i=0;
////                for (i=0; ((i<visible_BLACKHOLE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); i++)
////                {
////                    ShockWaveEffect* shockwave = visible_BLACKHOLE_vec[i]->GetShockWaveEffect();

////                    center_array[i][0] = (shockwave->center().x - world_coord.x)/w;
////                    center_array[i][1] = (shockwave->center().y - world_coord.y)/h;
////                    xyz_array[i][0] = shockwave->parameters().x;
////                    xyz_array[i][1] = shockwave->parameters().y;
////                    xyz_array[i][2] = shockwave->parameters().z;
                    
////                    time_array[i] = shockwave->time();
////                }
////                for (unsigned int j=0; ((j<visible_effect_SHOCKWAVE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); j++, i++)
////                {
////                    center_array[i][0] = (visible_effect_SHOCKWAVE_vec[j]->center().x - world_coord.x)/(w*scale);
////                    center_array[i][1] = (visible_effect_SHOCKWAVE_vec[j]->center().y - world_coord.y)/(h*scale);
////                    xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[j]->parameters().x;
////                    xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[j]->parameters().y;
////                    xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[j]->parameters().z/scale;
                    
////                    time_array[i] = visible_effect_SHOCKWAVE_vec[j]->time();
////                }

//                render.drawPostEffectShockWaves(render.lastFbo().colorBuffer(), w, h, i, center_array, xyz_array, time_array);
//            }
//            render.deactivateFbo(4);
//        }

//        if (draw_robustSpaceObjects)
//        {
//            // render effects not distorted by SHOCKWAVE
//            render.activateFbo(5, w, h);
//            {
//                //resizeGl(w, h);
//                render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);

//                //resizeGl(w*scale, h*scale);
//                //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);

//                for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
//                {
//                    LazerTraceEffect& lazer_trace = *visible_effect_LAZERTRACE_vec[i];
//                    //render.DrawMesh(lazer_trace.mesh(), lazer_trace.textureOb(), lazer_trace.actualModelMatrix());
//                }

//                for(unsigned int i=0; i<visible_effect_PARTICLESYSTEM_vec.size(); i++)
//                {
//                    //BaseParticleSystem& ps = *visible_effect_PARTICLESYSTEM_vec[i];
//                    //render.DrawParticles(ps.mesh(), ps.textureOb(), ps.actualModelMatrix());
//                }
//            }
//            render.deactivateFbo(5);
//        }

//        render.clearColorAndDepthBuffers();
//        render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);
  
//        // FOGWAR and STARSPARK to final scene
//        //resizeGl(w, h);
            
      
//        //render.DrawPostEffectFogWar(render.GetLastFbo().GetTexture(), w, h, npc->vehicle()->center(), world_coord, 200 /*npc->vehicle()->properties().radius*/);
       
//        // render text
//        //resizeGl(w*scale, h*scale);
//        //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);
//        for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
//        {
//            //visible_text_DAMAGE_vec[i]->Render(world_coord, 1/scale);
//        }
                    
//        //starsystem->RestoreSceneColor();
//    }
//    //render.disable_CULLFACE();
    
//    //render.SetOrthogonalProjection(w, h);
//}
    
//void Player::RenderInSpace(control::StarSystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
//{
//    jeti::Render& renderer = global::get().render();
//    jeti::Camera& camera = global::get().camera();
//    camera.update();
    
//    renderer.composeViewMatrix(camera.viewMatrix());

//    //float scale = shortcuts::screen()->GetScale();

//    RenderInSpace_NEW(renderer, starsystem);


//    if (turn_ended) {
//        if (forceDraw_orbits) {
//            //starsystem->DrawOrbits(renderer);
//        }

//        if (forceDraw_path) {
//            //starsystem->DrawPath();
//        }

////        npc->vehicle()->GetComplexDrive().DrawPath(renderer);
////        npc->vehicle()->GetComplexWeapon().RenderWeaponsRange();
////        npc->vehicle()->GetComplexWeapon().RenderWeaponIcons();
        
////        if (m_show.GetRangeRadar()) {
////            //npc->vehicle()->RenderRadarRange();
////        }
        
////        if ( (npc->vehicle()->grappleSlot()->item()) && (npc->vehicle()->grappleSlot()->isSelected()) ) {
////            //npc->vehicle()->RenderGrappleRange();
////        }
//    }
    
//    //m_cursor->RenderFocusedObjectStuff();
//}

void Player::__manageMouseClickEventInSpace()
{
    if (m_cursor->mouseData().event() == MouseData::Event::None) {
        return;
    }

    if (view::Base* base = m_cursor->focusedView()) {
        switch (base->type()) {
        case entity::Type::BULLET: {
            __clickOn(static_cast<view::Bullet*>(base));
            break;
        }
        case entity::Type::CONTAINER: {
            __clickOn(static_cast<view::Container*>(base));
            break;
        }
        case entity::Type::SATELLITE: {
            __clickOn(static_cast<view::Satellite*>(base));
            break;
        }
        case entity::Type::ASTEROID: {
            __clickOn(static_cast<view::Asteroid*>(base));
            break;
        }
        case entity::Type::SHIP: {
            __clickOn(static_cast<view::Ship*>(base));
            break;
        }
//        case entity::Type::WORMHOLE: {
//            clickOn(static_cast<view::WormHole*>(base));
//            break;
//        }
        case entity::Type::SPACESTATION: {
            __clickOn(static_cast<view::SpaceStation*>(base));
            break;
        }
        case entity::Type::PLANET: {
            __clickOn(static_cast<view::Planet*>(base));
            break;
        }
        case entity::Type::STAR: {
            __clickOn(static_cast<view::Star*>(base));
            break;
        }
        default:
            assert(false);
        }
    } else {
        __navigate();
    }
}

void Player::__clickOn(view::Bullet* bullet)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
//        if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
//            npc->vehicle()->GetComplexWeapon().SetTarget(bullet);
//        }
        break;
    }
    case MouseData::Event::RightButtonPress: {
//        npc->vehicle()->GetComplexDrive().SetTarget(bullet, NAVIGATOR_ACTION::KEEP_MIDDLE);
//        npc->vehicle()->GetComplexDrive().UpdatePath();
        break;
    }
    }
}

void Player::__clickOn(view::Container* container)
{
//    if (data_mouse.left_click) {
//        //npc->vehicle()->GetComplexWeapon().SetTarget(visible_CONTAINER_vec[i]);
//    }

//    if (data_mouse.right_click) {
//        if (npc->vehicle()->properties().grab_radius > 0) {
//            if (npc->vehicle()->grappleSlot()->CheckTarget(container) == STATUS::TARGET_OK) {
//                if (!npc->vehicle()->grappleSlot()->GetGrappleEquipment()->CheckIfTargetAlreadyExistInQueue(container)) {
//                    npc->vehicle()->grappleSlot()->GetGrappleEquipment()->AddTarget(container);
//                } else {
//                    npc->vehicle()->grappleSlot()->GetGrappleEquipment()->RemoveTarget(container);
//                }
//            }
//        }
//    }

}

void Player::__clickOn(view::Satellite* satellite)
{
//            if (data_mouse.left_click) {
//                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
//                    npc->vehicle()->GetComplexWeapon().SetTarget(satellite);
//                } else {
//                    npc->vehicle()->GetComplexDrive().SetTarget(satellite, NAVIGATOR_ACTION::KEEP_MIDDLE);   // make it like a ai scenario (follow obj)
//                    npc->vehicle()->GetComplexDrive().UpdatePath();
//                }
//            }
            
//            if (data_mouse.right_click) {
//                if ( (npc->vehicle()->grappleSlot()->item()) && (npc->vehicle()->grappleSlot()->isSelected()) ) {
//                //if (npc->vehicle()->ableTo.GRAB) {
//                    //npc->vehicle()->grapple_slot.GetGrappleEquipment()->add(visible_SATELLITE_vec[i]);
//                    //npc->vehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();
//                //}
//                } else {
//                    if ( npc->CheckPossibilityToScan(satellite) ) {
//                        npc->SetScanTarget(satellite);
//                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
//                    }
//                }
//            }
}

void Player::__clickOn(view::Asteroid* asteroid)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        //        if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
        //            npc->vehicle()->GetComplexWeapon().SetTarget(asteroid);
        //        }
        break;
    }
    case MouseData::Event::RightButtonPress: {
        //            npc->vehicle()->GetComplexDrive().SetTarget(asteroid, NAVIGATOR_ACTION::KEEP_MIDDLE);
        //            npc->vehicle()->GetComplexDrive().UpdatePath();
        break;
    }
    }
}

void Player::__clickOn(view::Ship* ship)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        if (npc()->vehicle()->weapons().isAnyWeaponSelected()) {
            __requestServerSetSpaceObjectTarget(ship->control()->id());
            // telegram...
            //npc()->vehicle()->weapons().setTarget(ship->control());
        }
        break;
    }
    case MouseData::Event::RightButtonPress: {
        if (npc()->tryScan(ship->control(), false)) {
            enterScan(ship->control());
        }
        //            npc->vehicle()->GetComplexDrive().SetTarget(asteroid, NAVIGATOR_ACTION::KEEP_MIDDLE);
        //            npc->vehicle()->GetComplexDrive().UpdatePath();
        break;
    }
    }


//            if (npc->vehicle()->id() != ship->id()) {
////                if (data_mouse.left_click) {
////                    if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
////                        npc->vehicle()->GetComplexWeapon().SetTarget(ship);
////                    } else {
////                        npc->vehicle()->GetComplexDrive().SetTarget(ship, NAVIGATOR_ACTION::KEEP_MIDDLE);
////                        npc->vehicle()->GetComplexDrive().UpdatePath();
////                    }
////                }

//                if (data_mouse.right_click) {
//                    if ( (npc->vehicle()->grappleSlot()->item() ) && (npc->vehicle()->grappleSlot()->isSelected()) ) {
//                        //if (npc->vehicle()->ableTo.GRAB) {
//                               //if (npc->vehicle()->grappleSlot()->CheckTarget(visible_SHIP_vec[i])) {
//                                   //npc->vehicle()->grappleSlot()->GetGrappleEquipment()->AddTarget(ship);
//                               //}
//                           //}
//                    } else {
////                        if (npc->CheckPossibilityToScan(ship)) {
////                            npc->SetScanTarget(ship);
////                        }
////                    }
//                }
//            } else {
//                if (data_mouse.right_click) {
//                    npc->setScanTarget(ship);
//                    GuiManager::Instance().GetGuiSpace().EnterGuiScan();
//                }
//            }
}

void Player::__clickOn(view::WormHole* wormhole)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        // ..
        break;
    }
    case MouseData::Event::RightButtonPress: {
        // ..
        break;
    }
    }
}

void Player::__clickOn(view::SpaceStation* spacestation)
{
////            if (data_mouse.left_click) {
////                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected()) {
////                    npc->vehicle()->GetComplexWeapon().SetTarget(spacestation);
////                } else {
////                    Task microtask(TYPE::AISCENARIO::MICRO_DOCKING, spacestation->id());
////                    npc->GetStateMachine().SetCurrentMicroTask(microtask);
////                    npc->vehicle()->GetComplexDrive().UpdatePath();
////                }
////            }

//            if (data_mouse.right_click) {
//                if ( (npc->vehicle()->grappleSlot()->item() != nullptr) && (npc->vehicle()->grappleSlot()->isSelected()) )
//                {
//                    //if (npc->vehicle()->ableTo.GRAB) {
//                        //npc->vehicle()->grapple_slot.GetGrappleEquipment()->add(spacestation);
//                        //npc->vehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();
//                    //}
//                } else {
////                    if ( npc->CheckPossibilityToScan(spacestation) ) {
////                        npc->SetScanTarget(spacestation);
////                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
////                    }
////                }
//            }
}

void Player::__clickOn(view::Planet* planet)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        //        Task microtask(type::AISCENARIO::MICRO_DOCKING, planet->id());
        //        npc->GetStateMachine().SetCurrentMicroTask(microtask);
        //        npc->vehicle()->GetComplexDrive().UpdatePath();
        break;
    }
    case MouseData::Event::RightButtonPress: {
        // ..
        break;
    }
    }

}

void Player::__clickOn(view::Star* star)
{
    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        // ..
        break;
    }
    case MouseData::Event::RightButtonPress: {
        // ..
        break;
    }
    }
}

void Player::__requestServerMoveVehicle(const glm::vec3& target_pos) const
{
    // it's more proper to send player id instead, and on server got the id of vehicle which belongs to the certain player
//    TelegramCreator::get().playerRequestMove(id(), target_pos);
    TelegramCreator::get().playerRequestMove(npc()->vehicle()->id(), target_pos);
}

void Player::__requestServerSetSpaceObjectTarget(int_t target_id) const
{
    TelegramCreator::get().playerRequestSetSpaceObjectTarget(npc()->vehicle()->id(), target_id);
}

void Player::__navigate() const
{
    if (m_blockSpaceNavigation) {
        return;
    }

    switch(m_cursor->mouseData().event()) {
    case MouseData::Event::LeftButtonPress: {
        assert(npc());
        __requestServerMoveVehicle(m_cursor->mouseData().worldCoord());
        break;
    }
    case MouseData::Event::RightButtonPress: {
        // ..
        break;
    }
    }
}

//void Player::SessionInSpace(control::StarSystem* starsystem, const TurnTimer& turn_timer)
//{
////    starsystem->FindRenderVisibleEntities_c(this);
////    if (meti::getRandInt(1,5) == 1)
////    {
////        starsystem->FindRadarVisibleEntities_c(this);
////    }

//    UserInput::get().update();
//    //UserInputInSpace::get().update(this);
////    if (turn_timer.GetTurnEnded() == true)
////    {
////        GuiManager::Instance().GetGuiSpace().Update(this);
////        BaseGuiElement* gui_element = GuiManager::Instance().GetGuiSpace().UpdateMouseInteraction(m_cursor->GetMouseData().pos_screencoord);
////        if (gui_element == nullptr)
////        {
////            if ( (GuiManager::Instance().GetGuiVehicleScan()->vehicle() == nullptr) and (GuiManager::Instance().GetGuiGalaxyMap()->GetGalaxy() == nullptr) )
////            {
////                bool mouse_interaction = MouseInteractionWithSpaceObjectsInSpace(m_cursor->GetMouseData());
////                if (mouse_interaction == false)
////                {
////                    MouseNavigation(m_cursor->GetMouseData());
////                }
////            }
////        }
////        else
////        {
////            m_cursor->SetFocusedGuiElement(gui_element);
////        }
////    }

////    RenderInSpace(starsystem, turn_timer.GetTurnEnded(), show.GetAllOrbits(), show.GetAllPath());
    
//    GuiManager::Instance().UpdateSessionInSpace();
//    //GuiManager::Instance().GetGuiSpace().Render(this);
    
//    //m_cursor->RenderItem();
//}


//void Player::SessionInKosmoport()
//{
//    GuiManager::Instance().RunSessionInKosmoport(m_cursor->mouseData());
//}

//void Player::SessionInNatureLand()
//{
//    GuiManager::Instance().RunSessionInNatureLand(m_cursor->mouseData());
//}

void Player::update(const jeti::Render& render, view::Base* focusedView)
{
    m_cursor->setFocusedView(focusedView);
    m_cursor->update(this, render);
    __manageMouseClickEventInSpace();
}

void Player::RunSession(const TurnTimer& turn_timer)
{
    assert(false);
//    switch(npc->vehicle()->place())
//    {
//        case type::place::KOSMOS:         { SessionInSpace(npc->vehicle()->starsystem(), turn_timer); break; }
//        case type::place::HYPER:     { SessionInSpace((Starsystem*)npc->vehicle()->driveComplex().target(), turn_timer); break; }
//        case type::place::KOSMOPORT:      { SessionInKosmoport(); break; }
//        case type::place::LAND:      { SessionInNatureLand(); break; }
//    }

//    m_cursor->update(this);
    //m_cursor->RenderFocusedObjectInfo();
//    shortcuts::screen()->draw();
}

void Player::resetStateMachine() const
{
    //npc->GetStateMachine().ForceReset();
}    

} // namespace client

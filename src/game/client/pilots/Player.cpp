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
#include <common/Config.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include <world/starsystem.hpp>
#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>

#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>
#include <common/TurnTimer.hpp>
#include <ceti/Logger.hpp>

#include <ai/Task.hpp>
#include <ai/StateMachine.hpp>

#include <item/equipment/ScanerEquipment.hpp>
#include <item/equipment/GrappleEquipment.hpp>

#include <parts/WeaponComplex.hpp>

#include <effects/lazerTrace.hpp>
#include <text/VerticalFlowText.hpp>

#include <spaceobjects/RocketBullet.hpp>
#include <spaceobjects/Container.hpp>
#include <spaceobjects/Star.hpp>
#include <spaceobjects/Planet.hpp>
#include <spaceobjects/BlackHole.hpp>
#include <spaceobjects/Asteroid.hpp>
#include <spaceobjects/SpaceStation.hpp>
#include <spaceobjects/Satellite.hpp>
#include <spaceobjects/Ship.hpp>

#include <pilots/Npc.hpp>

#include <gui/GuiGalaxyMap.hpp>
#include <gui/GuiManager.hpp>

#include <slots/ItemSlot.hpp>

#include <gui/UserInput.hpp>
#include <gui/UserInputManagerInSpace.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>

#include <meti/RandUtils.hpp>

Player::Player(int id)
:
npc(nullptr),
starsystem(nullptr)     
{ 
//    setId(id);
//    setTypeId(type::entity::PLAYER_ID);
    
    GuiManager::Instance().SetPlayer(this);
}
    
Player::~Player()
{}  
            
                           
void Player::BindNpc(Npc* npc)
{
    this->npc = npc;
    npc->SetPlayer(this);
}

bool Player::IsAbleToGetFullControlOnScanedVehicle(bool force_full_control) const
{
    if (force_full_control == false)
    {
        if (npc->vehicle()->id() == npc->GetScanTarget()->id())
        {
            force_full_control = true;  
            // modify full control for friend ships         
        }
    }
    
    return force_full_control;
}
          
void Player::UpdatePostTransaction()
{
    switch (npc->vehicle()->placeTypeId())
    {
        case TYPE::PLACE::KOSMOPORT_ID:
        {
            if (GuiManager::Instance().GetGuiKosmoport().GetInitDone() == false)
            {
                GuiManager::Instance().EnterGuiKosmoport(); 
            }
            
            if (GuiManager::Instance().GetGuiSpace().GetInitDone() == true)
            {
                GuiManager::Instance().ExitGuiSpace();
            }
            
            break;
        }

        case TYPE::PLACE::NATURELAND_ID:
        {                       
            break;
        }
        
        case TYPE::PLACE::SPACE_ID:
        {
            if (GuiManager::Instance().GetGuiKosmoport().GetInitDone() == true)
            {
                GuiManager::Instance().ExitGuiKosmoport(); 
            }
            
            if (GuiManager::Instance().GetGuiSpace().GetInitDone() == false)
            {
                GuiManager::Instance().EnterGuiSpace();
            }
            
            break;
        }
    }        
}

void Player::UpdatePostTransactionEvent(TurnTimer& turn_timer)
{       
    if (starsystem == nullptr) //hack
    {
        starsystem = npc->vehicle()->starsystem();
    }
    
    if (starsystem->id() != npc->vehicle()->starsystem()->id())
    {
        //jeti::Screen::get().InitiateScrollTo(npc->vehicle()->center());
        //jeti::Screen::get().GetRect().setCenter(npc->vehicle()->center());
        starsystem = npc->vehicle()->starsystem();
    }
    
//    VEHICLE_SPECIAL_ACTION_TYPE action_id = npc->vehicle()->GetSpecialActionId();
//    switch(action_id)
//    {
        //case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:
        //{
            //if (npc->vehicle()->placeTypeId() == ENTITY::SPACE_ID)
            //{
                //if (turn_timer.GetTurnEnded() == true)
                //{
                    //jeti::Screen::get().InitiateScrollTo(npc->vehicle()->center());
                //}
            //}
            
            //break;
        //}
        
//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:
//        {
//            if (npc->vehicle()->placeTypeId() == TYPE::PLACE::HYPER_SPACE_ID)
//            {
//                if (turn_timer.GetTurnEnded() == true)
//                {
//                    turn_timer.NextTurn();
//                }
//            }
            
//            break;
//        }

//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:
//        {
//            if (npc->vehicle()->placeTypeId() == TYPE::PLACE::SPACE_ID)
//            {
//                if (turn_timer.GetTurnEnded() == true)
//                {
//                    jeti::Screen::get().InitiateScrollTo(meti::vec2(npc->vehicle()->center()));
//                    turn_timer.NextTurn();
//                }
//            }
            
//            break;
//        }
    
//        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:
//        {
//            if (turn_timer.GetTurnEnded() == true)
//            {
//                jeti::Screen::get().InitiateScrollTo(meti::vec2(npc->vehicle()->center()));
//                turn_timer.NextTurn();
//            }
            
//            break;
//        }
//    }
    
    jeti::Screen::get().UpdateInSpace();
}
             
void Player::RenderInSpace_NEW(jeti::Renderer& render, Starsystem* starsystem)
{   
    bool draw_background    = true;
    bool draw_volumetric    = true;
    bool draw_something     = false;
    bool draw_spaceObjects  = true;
    bool draw_shockwave     = true;
    bool draw_robustSpaceObjects = true;

    float scale = jeti::Screen::get().GetScale();
    int w = jeti::Screen::get().GetWidth();
    int h = jeti::Screen::get().GetHeight();
    glm::vec2 world_coord(jeti::Screen::get().GetBottomLeft());
    
    render.ClearColorAndDepthBuffers();
    
    //render.enable_CULLFACE();
    {
        if (draw_background)
        {
            // render background and star to FBO0
            render.ActivateFbo(0, w, h);
            {
                render.SetPerspectiveProjection(w, h);
                //starsystem->DrawBackground(render, world_coord);
                render.SetOrthogonalProjection(w*scale, h*scale);

                for(Star* star : visible_STAR_vec)
                {
                    //alpitodorender render.DrawMeshMultiTextured(star->mesh(), star->textureOb(), star->actualModelMatrix());
                }
            }
            render.DeactivateFbo(0);

            // BLOOM background and star (uses many FBO)
            //resizeGl(w, h);
            // alpitodorender render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), npc->vehicle()->starsystem()->GetStar()->GetBrightThreshold());
        }

        // VOLUMETRIC LIGHT to FBO1
        if (draw_volumetric)
        {
            //resizeGl(w, h);
            render.ActivateFbo(1, w, h);
            {
                //render.DrawStarField(w/2, h/2, -world_coord.x/10000.0f, -world_coord.y/10000.0f);
                render.DrawPostEffectVolumetricLight(world_coord, w, h);
            }
            render.DeactivateFbo(1);
        }

        if (draw_something)
        {
//            render.ActivateFbo(2, w, h);
//            {
//                render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w*2, h*2);
//            }
//            render.DeactivateFbo(2);
        }

        if (draw_spaceObjects)
        {
            // render space entites to FBO2
            render.ActivateFbo(3, w, h);
            {
                render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w, h);

                // resizeGl(w*scale, h*scale);
                {
                    for(Planet* planet : visible_PLANET_vec)
                    {
                        //planet->Render_NEW(render);
                    }

                    for(SpaceStation* spacestation : visible_SPACESTATION_vec)
                    {
                        //spacestation->RenderInSpace(render, 1/scale);
                    }

                    //if (getRandInt(0, 30) == 0) std::cout<<"ship num rendered="<<visible_SHIP_vec.size()<<std::endl;
                    for(Ship* ship : visible_SHIP_vec)
                    {
                        //ship->RenderInSpace(render, 1/scale);
                    }

                    for(Asteroid* asteroid : visible_ASTEROID_vec)
                    {
                        //asteroid->Render_NEW(render, world_coord);
                    }

                    for(BlackHole* blackhole : visible_BLACKHOLE_vec)
                    {
                        //blackhole->Render_NEW(render);
                    }
                }

                {
                    for(Container* container : visible_CONTAINER_vec)
                    {
                        //container->Render(render);
                    }

                    for(Satellite* satellite : visible_SATELLITE_vec)
                    {
                        //satellite->RenderInSpace(render, 1/scale);
                    }

                    for(RocketBullet* rocket : visible_ROCKET_vec)
                    {
                        //rocket->RenderInSpace(render, 1/scale);
                    }
                }
                if (show.collisionRadius() == true)
                {
                    RenderAxis(render);
                    RenderCollisionRadius(render);
                }
            }
            render.DeactivateFbo(3);
        }

        if (draw_shockwave)
        {
            // SHOCKWAVE post process to Fbo3
            //resizeGl(w, h);
            render.ActivateFbo(4, w, h);
            {
                float center_array[SHOCKWAVES_MAX_NUM][2];
                float xyz_array[SHOCKWAVES_MAX_NUM][3];
                float time_array[SHOCKWAVES_MAX_NUM];

                unsigned int i=0;
//                for (i=0; ((i<visible_BLACKHOLE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); i++)
//                {
//                    ShockWaveEffect* shockwave = visible_BLACKHOLE_vec[i]->GetShockWaveEffect();

//                    center_array[i][0] = (shockwave->center().x - world_coord.x)/w;
//                    center_array[i][1] = (shockwave->center().y - world_coord.y)/h;
//                    xyz_array[i][0] = shockwave->parameters().x;
//                    xyz_array[i][1] = shockwave->parameters().y;
//                    xyz_array[i][2] = shockwave->parameters().z;
                    
//                    time_array[i] = shockwave->time();
//                }
//                for (unsigned int j=0; ((j<visible_effect_SHOCKWAVE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); j++, i++)
//                {
//                    center_array[i][0] = (visible_effect_SHOCKWAVE_vec[j]->center().x - world_coord.x)/(w*scale);
//                    center_array[i][1] = (visible_effect_SHOCKWAVE_vec[j]->center().y - world_coord.y)/(h*scale);
//                    xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[j]->parameters().x;
//                    xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[j]->parameters().y;
//                    xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[j]->parameters().z/scale;
                    
//                    time_array[i] = visible_effect_SHOCKWAVE_vec[j]->time();
//                }

                render.DrawPostEffectShockWaves(render.GetLastFbo().GetTexture(), w, h, i, center_array, xyz_array, time_array);
            }
            render.DeactivateFbo(4);
        }

        if (draw_robustSpaceObjects)
        {
            // render effects not distorted by SHOCKWAVE
            render.ActivateFbo(5, w, h);
            {
                //resizeGl(w, h);
                render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w, h);

                //resizeGl(w*scale, h*scale);
                //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);

                for(unsigned int i = 0; i<visible_effect_LAZERTRACE_vec.size(); i++)
                {
                    LazerTraceEffect& lazer_trace = *visible_effect_LAZERTRACE_vec[i];
                    //render.DrawMesh(lazer_trace.mesh(), lazer_trace.textureOb(), lazer_trace.actualModelMatrix());
                }

                for(unsigned int i=0; i<visible_effect_PARTICLESYSTEM_vec.size(); i++)
                {
                    //BaseParticleSystem& ps = *visible_effect_PARTICLESYSTEM_vec[i];
                    //render.DrawParticles(ps.mesh(), ps.textureOb(), ps.actualModelMatrix());
                }
            }
            render.DeactivateFbo(5);
        }

        render.ClearColorAndDepthBuffers();       
        render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w, h);
  
        // FOGWAR and STARSPARK to final scene
        //resizeGl(w, h); 
            
      
        //render.DrawPostEffectFogWar(render.GetLastFbo().GetTexture(), w, h, npc->vehicle()->center(), world_coord, 200 /*npc->vehicle()->GetProperties().radius*/);
       
        // render text
        //resizeGl(w*scale, h*scale); 
        //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);
        for(unsigned int i = 0; i<visible_text_DAMAGE_vec.size(); i++)
        { 
            //visible_text_DAMAGE_vec[i]->Render(world_coord, 1/scale); 
        }   
                    
        //starsystem->RestoreSceneColor();
    }
    //render.disable_CULLFACE();
    
    //render.SetOrthogonalProjection(w, h); 
}
    
void Player::RenderInSpace(Starsystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{   
    jeti::Renderer& renderer = jeti::Screen::get().GetRender();
    jeti::Camera& camera = jeti::Screen::get().GetCamera();
    int w = jeti::Screen::get().GetWidth();
    int h = jeti::Screen::get().GetHeight();
    camera.Update(w, h);
    
    renderer.ComposeViewMatrix(camera.GetViewMatrix());

    //float scale = jeti::Screen::get().GetScale();

    RenderInSpace_NEW(renderer, starsystem);

    //resizeGl(w*scale, h*scale); 
    //enable_BLEND();   
    {           
        if (turn_ended == true)
        {
            if (forceDraw_orbits == true)
            {
                //starsystem->DrawOrbits(renderer);
            }
            
            if (forceDraw_path == true)
            {
                //starsystem->DrawPath();
            }
            
//            npc->vehicle()->GetComplexDrive().DrawPath(renderer);
//            npc->vehicle()->GetComplexWeapon().RenderWeaponsRange();
//            npc->vehicle()->GetComplexWeapon().RenderWeaponIcons();
        
            if (show.GetRangeRadar() == true)
            {
                //npc->vehicle()->RenderRadarRange();
            }
        
            if ( (npc->vehicle()->GetSlotGrapple()->item() != nullptr) and (npc->vehicle()->GetSlotGrapple()->GetSelected() == true) )
            {
                //npc->vehicle()->RenderGrappleRange();
            }
        }
    
        //cursor.RenderFocusedObjectStuff();
    }
    //disable_BLEND();
    //resizeGl(w, h); 
} 

bool Player::MouseInteractionWithSpaceObjectsInSpace(const MouseData& data_mouse) 
{
    /* NOTE: the intersection must be checked in order from small objects to huge */    
    if (MouseInteractionWithRockets(data_mouse)) { return true; }
    if (MouseInteractionWithContainers(data_mouse)) { return true; }
    if (MouseInteractionWithSatellites(data_mouse)) { return true; }
    if (MouseInteractionWithAsteroids(data_mouse)) { return true; }
    if (MouseInteractionWithShips(data_mouse)) { return true; }    
    if (MouseInteractionWithBlackHoles(data_mouse)) { return true; }    
    if (MouseInteractionWithSpaceStations(data_mouse)) { return true; }    
    if (MouseInteractionWithPlanets(data_mouse)) { return true; }    
    if (MouseInteractionWithStars(data_mouse)) { return true; }  
    
    return false;  
}

bool Player::MouseInteractionWithRockets(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_ROCKET_vec.size(); i++)
    { 
        const glm::vec3& rocket_pos = visible_ROCKET_vec[i]->center(); // shortcut
        float object_cursor_dist = meti::distance(rocket_pos, data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, rocket_pos.z);
        if (object_cursor_dist < visible_ROCKET_vec[i]->collisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_ROCKET_vec[i]);
       
//            if (data_mouse.left_click == true)
//            {
//                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                {
//                    npc->vehicle()->GetComplexWeapon().SetTarget(visible_ROCKET_vec[i]);
//                }
//                else
//                {
//                    npc->vehicle()->GetComplexDrive().SetTarget(visible_ROCKET_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);
//                    npc->vehicle()->GetComplexDrive().UpdatePath();
//                }
//            }
                
            return true; 
        }
    }
        
    return false;
}

bool Player::MouseInteractionWithContainers(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)
    { 
        const glm::vec3& container_pos = visible_CONTAINER_vec[i]->center(); // shortcut
        float object_cursor_dist = meti::distance(container_pos, data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, container_pos.z);
        if (object_cursor_dist < visible_CONTAINER_vec[i]->collisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_CONTAINER_vec[i]);
                            
            if (data_mouse.left_click == true)
            {                                  
                //npc->vehicle()->GetComplexWeapon().SetTarget(visible_CONTAINER_vec[i]);
            }
            
            if (data_mouse.right_click == true)
            {
//                if (npc->vehicle()->GetProperties().grab_radius > 0)
//                {
//                    if (npc->vehicle()->GetSlotGrapple()->CheckTarget(visible_CONTAINER_vec[i]) == STATUS::TARGET_OK)
//                    {
//                        if (npc->vehicle()->GetSlotGrapple()->GetGrappleEquipment()->CheckIfTargetAlreadyExistInQueue(visible_CONTAINER_vec[i]) == false)
//                        {
//                            npc->vehicle()->GetSlotGrapple()->GetGrappleEquipment()->AddTarget(visible_CONTAINER_vec[i]);
//                        }
//                        else
//                        {
//                            npc->vehicle()->GetSlotGrapple()->GetGrappleEquipment()->RemoveTarget(visible_CONTAINER_vec[i]);
//                        }
//                    }
//                }
            }
                
            return true; 
        }
            
    }
        
    return false;
}

bool Player::MouseInteractionWithSatellites(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(meti::vec2(visible_SATELLITE_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SATELLITE_vec[i]->collisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SATELLITE_vec[i]);
        
            if (data_mouse.left_click == true)
            {
//                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                {
//                    npc->vehicle()->GetComplexWeapon().SetTarget(visible_SATELLITE_vec[i]);
//                }
//                else
//                {
//                    npc->vehicle()->GetComplexDrive().SetTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
//                    npc->vehicle()->GetComplexDrive().UpdatePath();
//                }
            }
            
            if (data_mouse.right_click == true)
            {
                if ( (npc->vehicle()->GetSlotGrapple()->item() != nullptr) and (npc->vehicle()->GetSlotGrapple()->GetSelected() == true) )
                {
                //if (pPLAYER->vehicle()->ableTo.GRAB == true)
                //{
                    //pPLAYER->vehicle()->grapple_slot.GetGrappleEquipment()->add(visible_SATELLITE_vec[i]);
                    //pPLAYER->vehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();
                //}
                }
                else
                {
//                    if ( npc->CheckPossibilityToScan(visible_SATELLITE_vec[i]) == true )
//                    {
//                        npc->SetScanTarget(visible_SATELLITE_vec[i]);
//                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
//                    }

                }
            }
                        
            return true; 
        }
    }
        
    return false;
}

bool Player::MouseInteractionWithAsteroids(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(meti::vec2(visible_ASTEROID_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_ASTEROID_vec[i]->collisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_ASTEROID_vec[i]);        
        
//            if (data_mouse.left_click == true)
//            {
//                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                {
//                    npc->vehicle()->GetComplexWeapon().SetTarget(visible_ASTEROID_vec[i]);
//                }
//                else
//                {
//                    npc->vehicle()->GetComplexDrive().SetTarget(visible_ASTEROID_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);
//                    npc->vehicle()->GetComplexDrive().UpdatePath();
//                }
//            }
                        
            return true; 
        }            
    }
        
    return false;
}

bool Player::MouseInteractionWithShips(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_SHIP_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(meti::vec2(visible_SHIP_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SHIP_vec[i]->collisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SHIP_vec[i]);    
        
            if (npc->vehicle()->id() != visible_SHIP_vec[i]->id())
            {
//                if (data_mouse.left_click == true)
//                {
//                    if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                    {
//                        npc->vehicle()->GetComplexWeapon().SetTarget(visible_SHIP_vec[i]);
//                    }
//                    else
//                    {
//                        npc->vehicle()->GetComplexDrive().SetTarget(visible_SHIP_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);
//                        npc->vehicle()->GetComplexDrive().UpdatePath();
//                    }
//                }

                if (data_mouse.right_click == true)
                {
                    if ( (npc->vehicle()->GetSlotGrapple()->item() != nullptr) and (npc->vehicle()->GetSlotGrapple()->GetSelected() == true) )
                    {
                        //if (npc->vehicle()->ableTo.GRAB == true)
                           //{
                               //if (npc->vehicle()->GetSlotGrapple()->CheckTarget(visible_SHIP_vec[i]) == true)
                               //{
                                   //npc->vehicle()->GetSlotGrapple()->GetGrappleEquipment()->AddTarget(visible_SHIP_vec[i]);
                               //}                    
                           //}
                    }
//                    else
//                    {
//                        if (npc->CheckPossibilityToScan(visible_SHIP_vec[i]) == true)
//                        {
//                            npc->SetScanTarget(visible_SHIP_vec[i]);
//                        }
//                    }
                }
            }
            else
            {
                if (data_mouse.right_click == true)
                {
                    npc->SetScanTarget(visible_SHIP_vec[i]);
                    GuiManager::Instance().GetGuiSpace().EnterGuiScan();
                }
            }
                        
        return true; 
        }
    }
        
    return false;
}

bool Player::MouseInteractionWithBlackHoles(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)
    { 
        float cursor_dist = meti::distance(meti::vec2(visible_BLACKHOLE_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (cursor_dist < visible_BLACKHOLE_vec[i]->collisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_BLACKHOLE_vec[i]); 
            
            return true;
        }
    }
    
    return false;
}

bool Player::MouseInteractionWithSpaceStations(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(meti::vec2(visible_SPACESTATION_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SPACESTATION_vec[i]->collisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SPACESTATION_vec[i]); 
        
//            if (data_mouse.left_click == true)
//            {
//                if (npc->vehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
//                {
//                    npc->vehicle()->GetComplexWeapon().SetTarget(visible_SPACESTATION_vec[i]);
//                }
//                else
//                {
//                    Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, visible_SPACESTATION_vec[i]->id());
//                    npc->GetStateMachine().SetCurrentMicroTask(microtask);
//                    npc->vehicle()->GetComplexDrive().UpdatePath();
//                }
//            }

            if (data_mouse.right_click == true)
            {
                if ( (npc->vehicle()->GetSlotGrapple()->item() != nullptr) and (npc->vehicle()->GetSlotGrapple()->GetSelected() == true) )
                {
                    //if (pPLAYER->vehicle()->ableTo.GRAB == true)
                    //{
                        //pPLAYER->vehicle()->grapple_slot.GetGrappleEquipment()->add(visible_STARBASE_vec[i]);
                        //pPLAYER->vehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();
                    //}
                }
//                else
//                {
//                    if ( npc->CheckPossibilityToScan(visible_SPACESTATION_vec[i]) == true )
//                    {
//                        npc->SetScanTarget(visible_SPACESTATION_vec[i]);
//                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
//                    }
//                }
            }
    
            return true; 
        }
    }
        
    return false;
}

bool Player::MouseInteractionWithPlanets(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_PLANET_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(meti::vec2(visible_PLANET_vec[i]->center()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_PLANET_vec[i]->collisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_PLANET_vec[i]); 
  
            if (data_mouse.left_click == true)
            {
                Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, visible_PLANET_vec[i]->id());
//                npc->GetStateMachine().SetCurrentMicroTask(microtask);
//                npc->vehicle()->GetComplexDrive().UpdatePath();
            }   
        
            return true; 
        }
    }

    return false;
}

bool Player::MouseInteractionWithStars(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_STAR_vec.size(); i++)
    { 
        float object_cursor_dist = meti::distance(visible_STAR_vec[i]->center(), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_STAR_vec[i]->collisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_STAR_vec[i]); 
                
            return true; 
        }
    }
    
    return false;
}

void Player::MouseNavigation(const MouseData& data_mouse) const
{
    if (data_mouse.left_click == true)
    {
        ForceStateMachineReset();
        //npc->vehicle()->GetComplexDrive().SetStaticTargetCoords(glm::vec3(data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, npc->vehicle()->center().z));
    }
}

void Player::SessionInSpace(Starsystem* starsystem, const TurnTimer& turn_timer)
{    
//    starsystem->FindRenderVisibleEntities_c(this);
//    if (meti::getRandInt(1,5) == 1)
//    {
//        starsystem->FindRadarVisibleEntities_c(this);
//    }

    UserInput::Instance().Update();
    UserInputManagerInSpace::Instance().UpdateInSpace(this);
//    if (turn_timer.GetTurnEnded() == true)
//    {
//        GuiManager::Instance().GetGuiSpace().Update(this);
//        BaseGuiElement* gui_element = GuiManager::Instance().GetGuiSpace().UpdateMouseInteraction(cursor.GetMouseData().pos_screencoord);
//        if (gui_element == nullptr)
//        {
//            if ( (GuiManager::Instance().GetGuiVehicleScan()->vehicle() == nullptr) and (GuiManager::Instance().GetGuiGalaxyMap()->GetGalaxy() == nullptr) )
//            {
//                bool mouse_interaction = MouseInteractionWithSpaceObjectsInSpace(cursor.GetMouseData());
//                if (mouse_interaction == false)
//                {
//                    MouseNavigation(cursor.GetMouseData());
//                }
//            }
//        }
//        else
//        {
//            cursor.SetFocusedGuiElement(gui_element);
//        }
//    }

//    RenderInSpace(starsystem, turn_timer.GetTurnEnded(), show.GetAllOrbits(), show.GetAllPath());
    
    GuiManager::Instance().UpdateSessionInSpace();
    //GuiManager::Instance().GetGuiSpace().Render(this); 
    
    //cursor.RenderItem();
}


void Player::SessionInKosmoport()
{       
    GuiManager::Instance().RunSessionInKosmoport(cursor.GetMouseData());
}

void Player::SessionInNatureLand()
{       
    GuiManager::Instance().RunSessionInNatureLand(cursor.GetMouseData());        
}

void Player::RunSession(const TurnTimer& turn_timer)
{
    cursor.Reset();
    switch(npc->vehicle()->placeTypeId())
    {
        case TYPE::PLACE::SPACE_ID:         { SessionInSpace(npc->vehicle()->starsystem(), turn_timer); break; }
        case TYPE::PLACE::HYPER_SPACE_ID:     { SessionInSpace((Starsystem*)npc->vehicle()->GetComplexDrive().GetTarget(), turn_timer); break; }
        case TYPE::PLACE::KOSMOPORT_ID:      { SessionInKosmoport(); break; }
        case TYPE::PLACE::NATURELAND_ID:      { SessionInNatureLand(); break; }
    }       

    cursor.Update(this);
    //cursor.RenderFocusedObjectInfo();
    jeti::Screen::get().Draw();
}

void Player::ForceStateMachineReset() const
{
    //npc->GetStateMachine().ForceReset();
}    

void Player::RenderCollisionRadius(const jeti::Renderer& render) const
{
    //render.enable_BLEND(); 
    {   //a;pitodorender
        /*
        for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)   { visible_SPACESTATION_vec[i]->RenderCollisionRadius(render); }            
        for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)      { visible_SATELLITE_vec[i]->RenderCollisionRadius(render); } 
        for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)           { visible_SHIP_vec[i]->RenderCollisionRadius(render); } 
        
        for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)         { visible_ROCKET_vec[i]->RenderCollisionRadius(render); }
        for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)      { visible_CONTAINER_vec[i]->RenderCollisionRadius(render); } 
                        
        for(unsigned int i=0; i<visible_STAR_vec.size(); i++)           { visible_STAR_vec[i]->RenderCollisionRadius(render); }
        for(unsigned int i=0; i<visible_PLANET_vec.size(); i++)         { visible_PLANET_vec[i]->RenderCollisionRadius(render); }
        for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)       { visible_ASTEROID_vec[i]->RenderCollisionRadius(render); } 
        for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)      { visible_BLACKHOLE_vec[i]->RenderCollisionRadius(render); } 
        */
    }
    //render.disable_BLEND();
}

void Player::RenderAxis(const jeti::Renderer& render) const
{    
    //render.enable_DEPTH(); 
    //alpitodorender
    /*
        for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)   { visible_SPACESTATION_vec[i]->RenderAxis(render); }            
        for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)      { visible_SATELLITE_vec[i]->RenderAxis(render); } 
        for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)           { visible_SHIP_vec[i]->RenderAxis(render); } 
        
        for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)         { visible_ROCKET_vec[i]->RenderAxis(render); }
        for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)      { visible_CONTAINER_vec[i]->RenderAxis(render); } 
                        
        for(unsigned int i=0; i<visible_STAR_vec.size(); i++)           { visible_STAR_vec[i]->RenderAxis(render); }
        for(unsigned int i=0; i<visible_PLANET_vec.size(); i++)         { visible_PLANET_vec[i]->RenderAxis(render); }
        for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)       { visible_ASTEROID_vec[i]->RenderAxis(render); } 
        for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)      { visible_BLACKHOLE_vec[i]->RenderAxis(render); } 
*/
//render.disable_DEPTH();
}         

//void Player::Save(boost::property_tree::ptree& save_ptree) const
//{
//    std::string root = "player."+std::to_string(id())+".";
    
//    Base::SaveData(save_ptree, root);
//    Player::SaveData(save_ptree, root);
//}

//void Player::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//    Player::LoadData(load_ptree);
//}

//void Player::Resolve()
//{
//    Base::ResolveData();
//    Player::ResolveData();
//}
        
//void Player::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    save_ptree.put(root+"unresolved.npc_id", npc->id());
//    save_ptree.put(root+"unresolved.starsystem_id", starsystem->id());
//    save_ptree.put(root+"unresolved.screen_pos_x", jeti::Screen::get().GetBottomLeft().x);
//    save_ptree.put(root+"unresolved.screen_pos_y", jeti::Screen::get().GetBottomLeft().y);
//}

//void Player::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    data_unresolved_player.npc_id = load_ptree.get<int>("unresolved.npc_id");
//    data_unresolved_player.starsystem_id = load_ptree.get<int>("unresolved.starsystem_id");
//    data_unresolved_player.screen_pos.x = load_ptree.get<float>("unresolved.screen_pos_x");
//    data_unresolved_player.screen_pos.y = load_ptree.get<float>("unresolved.screen_pos_y");
//}

//void Player::ResolveData()
//{
//    BindNpc((Npc*)global::get().entitiesManager().GetEntityById(data_unresolved_player.npc_id));
//    starsystem = (Starsystem*)global::get().entitiesManager().GetEntityById(data_unresolved_player.starsystem_id);
//    //jeti::Screen::get().SetBottomLeft(data_unresolved_player.screen_pos);
//}



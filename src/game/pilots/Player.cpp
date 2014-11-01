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
#include "../config/config.hpp"

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include "../world/starsystem.hpp"
#include "../world/EntityManager.hpp"

#include <math/rand.hpp>
#include "../common/myStr.hpp"
#include "../common/TurnTimer.hpp"
#include "../common/Logger.hpp"

#include "../ai/Task.hpp"
#include "../ai/StateMachine.hpp"

#include "../items/equipment/ScanerEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"

#include "../parts/WeaponComplex.hpp"

#include "../effects/lazerTrace.hpp"
#include "../text/VerticalFlowText.hpp" 

#include "../spaceobjects/RocketBullet.hpp"
#include "../spaceobjects/Container.hpp"
#include "../spaceobjects/Star.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/BlackHole.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/Satellite.hpp"
#include "../spaceobjects/Ship.hpp"

#include "../pilots/Npc.hpp"

#include "../gui/GuiGalaxyMap.hpp"
#include "../gui/GuiManager.hpp"

#include "../slots/ItemSlot.hpp"

#include <gui/UserInput.hpp>
#include <gui/UserInputManagerInSpace.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>

Player::Player(int id)
:
npc(nullptr),
starsystem(nullptr)     
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::PLAYER_ID);
    
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
        if (npc->GetVehicle()->GetId() == npc->GetScanTarget()->GetId())
        {
            force_full_control = true;  
            // modify full control for friend ships         
        }
    }
    
    return force_full_control;
}
          
void Player::ClearVisibleEntities()
{
    visible_STAR_vec.clear();
    visible_PLANET_vec.clear();
    
    visible_ASTEROID_vec.clear();
    visible_CONTAINER_vec.clear();

    visible_SHIP_vec.clear();
    visible_SATELLITE_vec.clear();
    visible_SPACESTATION_vec.clear();
    visible_ROCKET_vec.clear();
    visible_BLACKHOLE_vec.clear();

    visible_effect_SHOCKWAVE_vec.clear();
    visible_effect_LAZERTRACE_vec.clear();
    visible_effect_PARTICLESYSTEM_vec.clear();          
    visible_text_DAMAGE_vec.clear();
}
            
void Player::AddIfVisible(Star* star)
{
    if (isObjectOnScreen(star->GetCenter(), star->GetSize()))
    {         
        visible_STAR_vec.push_back(star);
    }
}

void Player::AddIfVisible(Planet* planet)
{
    if (isObjectOnScreen(planet->GetCenter(), planet->GetSize()))
    {  
        visible_PLANET_vec.push_back(planet);
    }
}

void Player::AddIfVisible(Asteroid* asteroid)             
{
    if (isObjectOnScreen(asteroid->GetCenter(), asteroid->GetSize()))
    {       
        if (npc->GetVehicle()->IsObjectWithinRadarRange(asteroid))
        {
            visible_ASTEROID_vec.push_back(asteroid);
        }
    }
}

void Player::AddIfVisible(Container* container)         
{
    if (isObjectOnScreen(container->GetCenter(), container->GetSize()))
    {    
        if (npc->GetVehicle()->IsObjectWithinRadarRange(container))
        {
            visible_CONTAINER_vec.push_back(container);
        }
    }
}

void Player::AddIfVisible(RocketBullet* rocket)  
{
    if (isObjectOnScreen(rocket->GetCenter(), rocket->GetSize()))  
    {  
        if (npc->GetVehicle()->IsObjectWithinRadarRange(rocket))
        {
            visible_ROCKET_vec.push_back(rocket);
        }
    }
}

void Player::AddIfVisible(BlackHole* blackhole)  
{
    if (isObjectOnScreen(blackhole->GetCenter(), blackhole->GetSize()))  
    {  
        if (npc->GetVehicle()->IsObjectWithinRadarRange(blackhole))
        {
            visible_BLACKHOLE_vec.push_back(blackhole);
        }
    }
}


void Player::AddIfVisible(Vehicle* vehicle) 
{
    //if (isObjectOnScreen(vehicle->GetCenter(), vehicle->GetSize()))
    {      
        //if ( npc->GetVehicle()->IsObjectWithinRadarRange(vehicle) )
        {
            switch(vehicle->GetSubTypeId())
            {            
                case TYPE::ENTITY::SHIP_ID:             {     visible_SHIP_vec.push_back((Ship*)vehicle); break; }
                case TYPE::ENTITY::SATELLITE_ID:        {     visible_SATELLITE_vec.push_back((Satellite*)vehicle); break; }
                case TYPE::ENTITY::SPACESTATION_ID:     {     visible_SPACESTATION_vec.push_back((SpaceStation*)vehicle); break; }
            }
        }
    }
}             
        
void Player::AddIfVisible(ShockWaveEffect* effect)
{
    //if (isObjectOnScreen(effect->GetCenter(), 600))
    //{
        //if (isObjectWithinRadarRange(effect, npc->GetVehicle()))
        //{
            //visible_effect_SHOCKWAVE_vec.push_back(effect);
        //}
    //}
}

void Player::AddIfVisible(LazerTraceEffect* effect)
{
    if ( (isPointOnScreen(vec3ToVec2(effect->GetStartPos())) == true) or (isPointOnScreen(vec3ToVec2(effect->GetEndPos())) == true) )
    {
        if (isObjectWithinRadarRange(effect, npc->GetVehicle()))
        {
            visible_effect_LAZERTRACE_vec.push_back(effect);
        }
    }
}
 
void Player::AddIfVisible(jeti::BaseParticleSystem* effect)
{
    //if (isObjectOnScreen(effect->GetCenter(), 600))
    //{
        //if (isObjectWithinRadarRange(effect, npc->GetVehicle()))
        //{
            visible_effect_PARTICLESYSTEM_vec.push_back(effect);
        //}
    //}
}

void Player::AddIfVisible(VerticalFlowText* effect)
{
    if (isPointOnScreen(effect->GetCenter()))
    {
        if (isPointOnScreen(effect->GetCenter()))
        {
            visible_text_DAMAGE_vec.push_back(effect);
        }
    }
}             

void Player::UpdatePostTransaction()
{
    switch (npc->GetVehicle()->GetPlaceTypeId())
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
        starsystem = npc->GetVehicle()->GetStarSystem();
    }
    
    if (starsystem->GetId() != npc->GetVehicle()->GetStarSystem()->GetId())
    {
        //jeti::Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetCenter());
        //jeti::Screen::Instance().GetRect().SetCenter(npc->GetVehicle()->GetCenter());
        starsystem = npc->GetVehicle()->GetStarSystem();
    }
    
    VEHICLE_SPECIAL_ACTION_TYPE action_id = npc->GetVehicle()->GetSpecialActionId();
    switch(action_id)
    {
        //case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:
        //{
            //if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
            //{
                //if (turn_timer.GetTurnEnded() == true)
                //{
                    //jeti::Screen::Instance().InitiateScrollTo(npc->GetVehicle()->GetCenter());
                //}
            //}
            
            //break;
        //}
        
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:
        {
            if (npc->GetVehicle()->GetPlaceTypeId() == TYPE::PLACE::HYPER_SPACE_ID)
            {
                if (turn_timer.GetTurnEnded() == true)
                {
                    turn_timer.NextTurn();
                }
            }
            
            break;
        }

        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:
        {
            if (npc->GetVehicle()->GetPlaceTypeId() == TYPE::PLACE::SPACE_ID)
            {
                if (turn_timer.GetTurnEnded() == true)
                {
                    jeti::Screen::Instance().InitiateScrollTo(vec3ToVec2(npc->GetVehicle()->GetCenter()));
                    turn_timer.NextTurn();                
                }
            }
            
            break;
        }
    
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:
        {
            if (turn_timer.GetTurnEnded() == true)
            {
                jeti::Screen::Instance().InitiateScrollTo(vec3ToVec2(npc->GetVehicle()->GetCenter()));
                turn_timer.NextTurn();                
            }
            
            break;
        }        
    }
    
    jeti::Screen::Instance().UpdateInSpace();
}
             
void Player::RenderInSpace_NEW(jeti::Renderer& render, StarSystem* starsystem)
{   
    bool draw_background    = true;
    bool draw_volumetric    = true;
    bool draw_something     = false;
    bool draw_spaceObjects  = true;
    bool draw_shockwave     = true;
    bool draw_robustSpaceObjects = true;

    float scale = jeti::Screen::Instance().GetScale();
    int w = jeti::Screen::Instance().GetWidth();
    int h = jeti::Screen::Instance().GetHeight();
    glm::vec2 world_coord(jeti::Screen::Instance().GetBottomLeft());
    
    render.ClearColorAndDepthBuffers();
    
    //render.enable_CULLFACE();
    {
        if (draw_background)
        {
            // render background and star to FBO0
            render.ActivateFbo(0, w, h);
            {
                render.SetPerspectiveProjection(w, h);
                starsystem->DrawBackground(render, world_coord);
                render.SetOrthogonalProjection(w*scale, h*scale);

                for(Star* star : visible_STAR_vec)
                {
                    //alpitodorender render.DrawMeshMultiTextured(star->GetMesh(), star->GetTextureOb(), star->GetActualModelMatrix());
                }
            }
            render.DeactivateFbo(0);

            // BLOOM background and star (uses many FBO)
            //resizeGl(w, h);
            // alpitodorender render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), npc->GetVehicle()->GetStarSystem()->GetStar()->GetBrightThreshold());
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
                        container->Render(render);
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
                if (show.GetCollisionRadius() == true)
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
                for (i=0; ((i<visible_BLACKHOLE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); i++)
                {
                    ShockWaveEffect* shockwave = visible_BLACKHOLE_vec[i]->GetShockWaveEffect();

                    center_array[i][0] = (shockwave->center.x - world_coord.x)/w;
                    center_array[i][1] = (shockwave->center.y - world_coord.y)/h;
                    xyz_array[i][0] = shockwave->parameter.x;
                    xyz_array[i][1] = shockwave->parameter.y;
                    xyz_array[i][2] = shockwave->parameter.z;
                    
                    time_array[i] = shockwave->time;
                }
                for (unsigned int j=0; ((j<visible_effect_SHOCKWAVE_vec.size()) && (i<SHOCKWAVES_MAX_NUM)); j++, i++)
                {
                    center_array[i][0] = (visible_effect_SHOCKWAVE_vec[j]->center.x - world_coord.x)/(w*scale);
                    center_array[i][1] = (visible_effect_SHOCKWAVE_vec[j]->center.y - world_coord.y)/(h*scale);
                    xyz_array[i][0] = visible_effect_SHOCKWAVE_vec[j]->parameter.x;
                    xyz_array[i][1] = visible_effect_SHOCKWAVE_vec[j]->parameter.y;
                    xyz_array[i][2] = visible_effect_SHOCKWAVE_vec[j]->parameter.z/scale;
                    
                    time_array[i] = visible_effect_SHOCKWAVE_vec[j]->time;
                }

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
                    //render.DrawMesh(lazer_trace.GetMesh(), lazer_trace.GetTextureOb(), lazer_trace.GetActualModelMatrix());
                }

                for(unsigned int i=0; i<visible_effect_PARTICLESYSTEM_vec.size(); i++)
                {
                    //BaseParticleSystem& ps = *visible_effect_PARTICLESYSTEM_vec[i];
                    //render.DrawParticles(ps.GetMesh(), ps.GetTextureOb(), ps.GetActualModelMatrix());
                }
            }
            render.DeactivateFbo(5);
        }

        render.ClearColorAndDepthBuffers();       
        render.DrawScreenQuadTextured(render.GetLastFbo().GetTexture(), w, h);
  
        // FOGWAR and STARSPARK to final scene
        //resizeGl(w, h); 
            
      
        //render.DrawPostEffectFogWar(render.GetLastFbo().GetTexture(), w, h, npc->GetVehicle()->GetCenter(), world_coord, 200 /*npc->GetVehicle()->GetProperties().radius*/);         
       
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
    
void Player::RenderInSpace(StarSystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
{   
    jeti::Renderer& renderer = jeti::Screen::Instance().GetRender();
    jeti::Camera& camera = jeti::Screen::Instance().GetCamera();
    int w = jeti::Screen::Instance().GetWidth();
    int h = jeti::Screen::Instance().GetHeight();
    camera.Update(w, h);
    
    renderer.ComposeViewMatrix(camera.GetViewMatrix());

    //float scale = jeti::Screen::Instance().GetScale();

    RenderInSpace_NEW(renderer, starsystem);

    //resizeGl(w*scale, h*scale); 
    //enable_BLEND();   
    {           
        if (turn_ended == true)
        {
            if (forceDraw_orbits == true)
            {
                starsystem->DrawOrbits(renderer);
            }
            
            if (forceDraw_path == true)
            {
                starsystem->DrawPath();
            }
            
            npc->GetVehicle()->GetComplexDrive().DrawPath(renderer);
            npc->GetVehicle()->GetComplexWeapon().RenderWeaponsRange();
            npc->GetVehicle()->GetComplexWeapon().RenderWeaponIcons(); 
        
            if (show.GetRangeRadar() == true)
            {
                npc->GetVehicle()->RenderRadarRange();
            }
        
            if ( (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr) and (npc->GetVehicle()->GetSlotGrapple()->GetSelected() == true) )
            {
                npc->GetVehicle()->RenderGrappleRange();
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
        const glm::vec3& rocket_pos = visible_ROCKET_vec[i]->GetCenter(); // shortcut
        float object_cursor_dist = distanceBetween(rocket_pos, data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, rocket_pos.z);
        if (object_cursor_dist < visible_ROCKET_vec[i]->GetCollisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_ROCKET_vec[i]);
       
            if (data_mouse.left_click == true)
            {
                if (npc->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                {
                    npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_ROCKET_vec[i]);
                }
                else
                {
                    npc->GetVehicle()->GetComplexDrive().SetTarget(visible_ROCKET_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                    npc->GetVehicle()->GetComplexDrive().UpdatePath();
                }
            }
                
            return true; 
        }
    }
        
    return false;
}

bool Player::MouseInteractionWithContainers(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)
    { 
        const glm::vec3& container_pos = visible_CONTAINER_vec[i]->GetCenter(); // shortcut
        float object_cursor_dist = distanceBetween(container_pos, data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, container_pos.z);
        if (object_cursor_dist < visible_CONTAINER_vec[i]->GetCollisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_CONTAINER_vec[i]);
                            
            if (data_mouse.left_click == true)
            {                                  
                npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_CONTAINER_vec[i]);
            }
            
            if (data_mouse.right_click == true)
            {
                if (npc->GetVehicle()->GetProperties().grab_radius > 0)
                {
                    if (npc->GetVehicle()->GetSlotGrapple()->CheckTarget(visible_CONTAINER_vec[i]) == STATUS::TARGET_OK)
                    {
                        if (npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->CheckIfTargetAlreadyExistInQueue(visible_CONTAINER_vec[i]) == false)
                        {
                            npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->AddTarget(visible_CONTAINER_vec[i]);
                        }
                        else
                        {
                            npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->RemoveTarget(visible_CONTAINER_vec[i]);
                        }
                    }
                }
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
        float object_cursor_dist = distanceBetween(vec3ToVec2(visible_SATELLITE_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SATELLITE_vec[i]->GetCollisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SATELLITE_vec[i]);
        
            if (data_mouse.left_click == true)
            {
                if (npc->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                {
                    npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_SATELLITE_vec[i]);
                }
                else
                {
                    npc->GetVehicle()->GetComplexDrive().SetTarget(visible_SATELLITE_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);   // make it like a ai scenario (follow obj)
                    npc->GetVehicle()->GetComplexDrive().UpdatePath();
                }
            }
            
            if (data_mouse.right_click == true)
            {
                if ( (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr) and (npc->GetVehicle()->GetSlotGrapple()->GetSelected() == true) )
                {
                //if (pPLAYER->GetVehicle()->ableTo.GRAB == true)
                //{
                    //pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_SATELLITE_vec[i]);
                    //pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();                                   
                //}
                }
                else
                {
                    if ( npc->CheckPossibilityToScan(visible_SATELLITE_vec[i]) == true )
                    {
                        npc->SetScanTarget(visible_SATELLITE_vec[i]);
                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
                    }

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
        float object_cursor_dist = distanceBetween(vec3ToVec2(visible_ASTEROID_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_ASTEROID_vec[i]->GetCollisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_ASTEROID_vec[i]);        
        
            if (data_mouse.left_click == true)
            {
                if (npc->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                {
                    npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_ASTEROID_vec[i]);
                }
                else
                {
                    npc->GetVehicle()->GetComplexDrive().SetTarget(visible_ASTEROID_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                    npc->GetVehicle()->GetComplexDrive().UpdatePath();
                }
            }            
                        
            return true; 
        }            
    }
        
    return false;
}

bool Player::MouseInteractionWithShips(const MouseData& data_mouse)
{
    for (unsigned int i=0; i<visible_SHIP_vec.size(); i++)
    { 
        float object_cursor_dist = distanceBetween(vec3ToVec2(visible_SHIP_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SHIP_vec[i]->GetCollisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SHIP_vec[i]);    
        
            if (npc->GetVehicle()->GetId() != visible_SHIP_vec[i]->GetId())
            {
                if (data_mouse.left_click == true)
                {
                    if (npc->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                    {
                        npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_SHIP_vec[i]);
                    }
                    else
                    {
                        npc->GetVehicle()->GetComplexDrive().SetTarget(visible_SHIP_vec[i], NAVIGATOR_ACTION::KEEP_MIDDLE_ID);  
                        npc->GetVehicle()->GetComplexDrive().UpdatePath();
                    }
                }

                if (data_mouse.right_click == true)
                {
                    if ( (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr) and (npc->GetVehicle()->GetSlotGrapple()->GetSelected() == true) )
                    {
                        //if (npc->GetVehicle()->ableTo.GRAB == true)
                           //{
                               //if (npc->GetVehicle()->GetSlotGrapple()->CheckTarget(visible_SHIP_vec[i]) == true)
                               //{
                                   //npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->AddTarget(visible_SHIP_vec[i]);
                               //}                    
                           //}
                    }
                    else
                    {
                        if (npc->CheckPossibilityToScan(visible_SHIP_vec[i]) == true)
                        {
                            npc->SetScanTarget(visible_SHIP_vec[i]);
                        }
                       }
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
        float cursor_dist = distanceBetween(vec3ToVec2(visible_BLACKHOLE_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (cursor_dist < visible_BLACKHOLE_vec[i]->GetCollisionRadius())
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
        float object_cursor_dist = distanceBetween(vec3ToVec2(visible_SPACESTATION_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_SPACESTATION_vec[i]->GetCollisionRadius())
        { 
            cursor.SetFocusedSpaceObject(visible_SPACESTATION_vec[i]); 
        
            if (data_mouse.left_click == true)
            {
                if (npc->GetVehicle()->GetComplexWeapon().IsAnyWeaponSelected() == true)
                {
                    npc->GetVehicle()->GetComplexWeapon().SetTarget(visible_SPACESTATION_vec[i]);
                }
                else
                {
                    Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, visible_SPACESTATION_vec[i]->GetId());
                    npc->GetStateMachine().SetCurrentMicroTask(microtask);
                    npc->GetVehicle()->GetComplexDrive().UpdatePath();
                }
            }

            if (data_mouse.right_click == true)
            {
                if ( (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr) and (npc->GetVehicle()->GetSlotGrapple()->GetSelected() == true) )
                {
                    //if (pPLAYER->GetVehicle()->ableTo.GRAB == true)
                    //{
                        //pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->add(visible_STARBASE_vec[i]);
                        //pPLAYER->GetVehicle()->grapple_slot.GetGrappleEquipment()->validationTargets();                                   
                    //}
                }
                else
                {
                    if ( npc->CheckPossibilityToScan(visible_SPACESTATION_vec[i]) == true )
                    {
                        npc->SetScanTarget(visible_SPACESTATION_vec[i]);
                        GuiManager::Instance().GetGuiSpace().EnterGuiScan();
                    }
                }
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
        float object_cursor_dist = distanceBetween(vec3ToVec2(visible_PLANET_vec[i]->GetCenter()), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_PLANET_vec[i]->GetCollisionRadius())
        {   
            cursor.SetFocusedSpaceObject(visible_PLANET_vec[i]); 
  
            if (data_mouse.left_click == true)
            {
                Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, visible_PLANET_vec[i]->GetId());
                npc->GetStateMachine().SetCurrentMicroTask(microtask);
                npc->GetVehicle()->GetComplexDrive().UpdatePath();
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
        float object_cursor_dist = distanceBetween(visible_STAR_vec[i]->GetCenter(), data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y);
        if (object_cursor_dist < visible_STAR_vec[i]->GetCollisionRadius())
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
        npc->GetVehicle()->GetComplexDrive().SetStaticTargetCoords(glm::vec3(data_mouse.pos_worldcoord.x, data_mouse.pos_worldcoord.y, npc->GetVehicle()->GetCenter().z));  
    }
}

void Player::SessionInSpace(StarSystem* starsystem, const TurnTimer& turn_timer)
{    
    starsystem->FindRenderVisibleEntities_c(this);
    if (getRandInt(1,5) == 1)
    {
        starsystem->FindRadarVisibleEntities_c(this);
    }

    UserInput::Instance().Update();
    UserInputManagerInSpace::Instance().UpdateInSpace(this);
    if (turn_timer.GetTurnEnded() == true)  
    {    
        GuiManager::Instance().GetGuiSpace().Update(this);
        BaseGuiElement* gui_element = GuiManager::Instance().GetGuiSpace().UpdateMouseInteraction(cursor.GetMouseData().pos_screencoord);
        if (gui_element == nullptr)
        {  
            if ( (GuiManager::Instance().GetGuiVehicleScan()->GetVehicle() == nullptr) and (GuiManager::Instance().GetGuiGalaxyMap()->GetGalaxy() == nullptr) )
            {
                bool mouse_interaction = MouseInteractionWithSpaceObjectsInSpace(cursor.GetMouseData());  
                if (mouse_interaction == false)
                {    
                    MouseNavigation(cursor.GetMouseData());  
                }
            }
        }
        else
        {
            cursor.SetFocusedGuiElement(gui_element);
        }
    }

    RenderInSpace(starsystem, turn_timer.GetTurnEnded(), show.GetAllOrbits(), show.GetAllPath());
    
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
    switch(npc->GetVehicle()->GetPlaceTypeId())
    {
        case TYPE::PLACE::SPACE_ID:         { SessionInSpace(npc->GetVehicle()->GetStarSystem(), turn_timer); break; }
        case TYPE::PLACE::HYPER_SPACE_ID:     { SessionInSpace((StarSystem*)npc->GetVehicle()->GetComplexDrive().GetTarget(), turn_timer); break; }
        case TYPE::PLACE::KOSMOPORT_ID:      { SessionInKosmoport(); break; }
        case TYPE::PLACE::NATURELAND_ID:      { SessionInNatureLand(); break; }
    }       

    cursor.Update(this);
    //cursor.RenderFocusedObjectInfo();
    jeti::Screen::Instance().Draw();
}

void Player::ForceStateMachineReset() const
{
    npc->GetStateMachine().ForceReset();
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

void Player::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "player."+int2str(GetId())+".";
    
    Base::SaveData(save_ptree, root);
    Player::SaveData(save_ptree, root);    
}        

void Player::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Player::LoadData(load_ptree);       
}        

void Player::Resolve()
{
    Base::ResolveData();
    Player::ResolveData();    
}
        
void Player::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    save_ptree.put(root+"unresolved.npc_id", npc->GetId());
    save_ptree.put(root+"unresolved.starsystem_id", starsystem->GetId());
    save_ptree.put(root+"unresolved.screen_pos_x", jeti::Screen::Instance().GetBottomLeft().x);
    save_ptree.put(root+"unresolved.screen_pos_y", jeti::Screen::Instance().GetBottomLeft().y);
}

void Player::LoadData(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_player.npc_id = load_ptree.get<int>("unresolved.npc_id");
    data_unresolved_player.starsystem_id = load_ptree.get<int>("unresolved.starsystem_id");
    data_unresolved_player.screen_pos.x = load_ptree.get<float>("unresolved.screen_pos_x");
    data_unresolved_player.screen_pos.y = load_ptree.get<float>("unresolved.screen_pos_y");
}

void Player::ResolveData()
{
    BindNpc((Npc*)EntityManager::Instance().GetEntityById(data_unresolved_player.npc_id));
    starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_player.starsystem_id);
    //jeti::Screen::Instance().SetBottomLeft(data_unresolved_player.screen_pos);
}        




bool isObjectWithinRadarRange(jeti::BaseParticleSystem* effect, Vehicle* vehicle)
{
    float dist = distanceBetween(vehicle->GetCenter(), effect->GetCenter());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    return false;
}



bool isObjectOnScreen(const glm::vec3& center, const glm::vec3& size)
{      
    float scale = jeti::Screen::Instance().GetScale();
    if (center.x < (jeti::Screen::Instance().GetBottomLeftScreenWC().x - size.x*scale))
        return false;
    if (center.x > (jeti::Screen::Instance().GetTopRightScreenWC().x   + size.x*scale))
        return false;
    if (center.y < (jeti::Screen::Instance().GetBottomLeftScreenWC().y - size.y*scale))
        return false;
    if (center.y > (jeti::Screen::Instance().GetTopRightScreenWC().y   + size.y*scale))
        return false;
    
    return true;
}

bool isObjectOnScreen(const glm::vec3& ob_center, const float sizeInPixels)
{       
    float scale = jeti::Screen::Instance().GetScale();
    if (ob_center.x < (jeti::Screen::Instance().GetBottomLeftScreenWC().x - sizeInPixels*scale))
        return false;
    if (ob_center.x > (jeti::Screen::Instance().GetTopRightScreenWC().x + sizeInPixels*scale))
        return false;
    if (ob_center.y < (jeti::Screen::Instance().GetBottomLeftScreenWC().y - sizeInPixels*scale))
        return false;
    if (ob_center.y > (jeti::Screen::Instance().GetTopRightScreenWC().y + sizeInPixels*scale))
        return false;
    
    return true;
}

bool isPointOnScreen(const glm::vec2& p)
{       
    if (p.x < (jeti::Screen::Instance().GetBottomLeftScreenWC().x))
        return false;
    if (p.x > (jeti::Screen::Instance().GetTopRightScreenWC().x))
        return false;
    if (p.y < (jeti::Screen::Instance().GetBottomLeftScreenWC().y))
        return false;
    if (p.y > (jeti::Screen::Instance().GetTopRightScreenWC().y))
        return false;
    
    return true;
}

bool isObjectWithinRadarRange(ShockWaveEffect* effect, Vehicle* vehicle)
{
    float dist = distanceBetween(vehicle->GetCenter(), effect->GetCenter());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    return false;
}

bool isObjectWithinRadarRange(LazerTraceEffect* effect, Vehicle* vehicle)
{
    float dist = distanceBetween(vehicle->GetCenter(), effect->GetStartPos());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    dist = distanceBetween(vehicle->GetCenter(), effect->GetEndPos());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    return false;
}

//bool isObjectWithinRadarRange(VerticalFlowText* effect, Vehicle* vehicle)
//{
    //float dist = distanceBetween(vehicle->GetCenter(), effect->GetPos());
    //if (dist < vehicle->GetProperties().radar)
    //{
        //return true;
    //}
    
    //return false;
//}

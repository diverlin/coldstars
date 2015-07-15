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


#include "StarsystemRender.hpp"
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

#include <items/equipment/ScanerEquipment.hpp>
#include <items/equipment/GrappleEquipment.hpp>

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


StarsystemRender::StarsystemRender()
{}
    
StarsystemRender::~StarsystemRender()
{}  
          
void StarsystemRender::ClearVisibleEntities()
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
            
void StarsystemRender::AddIfVisible(Star* star)
{
    if (isObjectOnScreen(star->center(), star->size())) {
        visible_STAR_vec.push_back(star);
    }
}

void StarsystemRender::AddIfVisible(Planet* planet)
{
    if (isObjectOnScreen(planet->center(), planet->size())) {
        visible_PLANET_vec.push_back(planet);
    }
}

void StarsystemRender::AddIfVisible(Asteroid* asteroid)
{
    if (isObjectOnScreen(asteroid->center(), asteroid->size())) {
//        if (isObjectWithinRange(npc->GetVehicle()->center(), asteroid->center(), radius)) {
            visible_ASTEROID_vec.push_back(asteroid);
        }
//    }
}

void StarsystemRender::AddIfVisible(Container* container)
{
    if (isObjectOnScreen(container->center(), container->size())) {
//        if (isObjectWithinRange(npc->GetVehicle()->center(), container->center(), radius)) {
            visible_CONTAINER_vec.push_back(container);
        }
//    }
}

void StarsystemRender::AddIfVisible(RocketBullet* rocket)
{
    if (isObjectOnScreen(rocket->center(), rocket->size())) {
//        if (isObjectWithinRange(npc->GetVehicle()->center(), rocket->center(), radius)) {
            visible_ROCKET_vec.push_back(rocket);
        }
//    }
}

void StarsystemRender::AddIfVisible(BlackHole* blackhole)
{
    if (isObjectOnScreen(blackhole->center(), blackhole->size())) {
//        if (isObjectWithinRange(npc->GetVehicle()->center(), blackhole->center(), radius)) {
            visible_BLACKHOLE_vec.push_back(blackhole);
        }
//    }
}

void StarsystemRender::AddIfVisible(Vehicle* vehicle)
{
    //if (isObjectOnScreen(vehicle->center(), vehicle->size())) {
        //if (isObjectWithinRange(npc->GetVehicle()->center(), vehicle->center(), radius)) {
            switch(vehicle->subTypeId())
            {            
                case TYPE::ENTITY::SHIP_ID:             {     visible_SHIP_vec.push_back((Ship*)vehicle); break; }
                case TYPE::ENTITY::SATELLITE_ID:        {     visible_SATELLITE_vec.push_back((Satellite*)vehicle); break; }
                case TYPE::ENTITY::SPACESTATION_ID:     {     visible_SPACESTATION_vec.push_back((SpaceStation*)vehicle); break; }
            }
//        }
//    }
}             
        
void StarsystemRender::AddIfVisible(ShockWaveEffect* effect)
{
    //if (isObjectOnScreen(effect->center(), 600)) {
        //if (isObjectWithinRadarRange(effect, npc->GetVehicle())) {
            //visible_effect_SHOCKWAVE_vec.push_back(effect);
        //}
    //}
}

void StarsystemRender::AddIfVisible(LazerTraceEffect* effect)
{
    bool r1 = isPointOnScreen(meti::vec2(effect->GetStartPos()));
    bool r2 = isPointOnScreen(meti::vec2(effect->GetEndPos()));

    if (r1 || r2) {
//        if (isObjectWithinRadarRange(effect, npc->GetVehicle())) {
            visible_effect_LAZERTRACE_vec.push_back(effect);
        }
//    }
}
 
void StarsystemRender::AddIfVisible(jeti::BaseParticleSystem* effect)
{
    //if (isObjectOnScreen(effect->center(), 600)) {
        //if (isObjectWithinRadarRange(effect, npc->GetVehicle())) {
            visible_effect_PARTICLESYSTEM_vec.push_back(effect);
        //}
    //}
}

void StarsystemRender::AddIfVisible(VerticalFlowText* effect)
{
    if (isPointOnScreen(effect->center())) {
        if (isPointOnScreen(effect->center())) {
            visible_text_DAMAGE_vec.push_back(effect);
        }
    }
}             

void StarsystemRender::RenderInSpace_NEW(jeti::Renderer& render, StarSystem* starsystem)
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
                //starsystem->DrawBackground(render, world_coord);
                render.SetOrthogonalProjection(w*scale, h*scale);

                for(Star* star : visible_STAR_vec)
                {
                    //alpitodorender render.DrawMeshMultiTextured(star->GetMesh(), star->GetTextureOb(), star->GetActualModelMatrix());
                }
            }
            render.DeactivateFbo(0);

            // BLOOM background and star (uses many FBO)
            //resizeGl(w, h);
            // alpitodorender render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), npc->GetVehicle()->starsystem()->GetStar()->GetBrightThreshold());
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
                //if (show.collisionRadius() == true)
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
            
      
        //render.DrawPostEffectFogWar(render.GetLastFbo().GetTexture(), w, h, npc->GetVehicle()->center(), world_coord, 200 /*npc->GetVehicle()->GetProperties().radius*/);         
       
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
    
void StarsystemRender::RenderInSpace(StarSystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
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
                //starsystem->DrawOrbits(renderer);
            }
            
            if (forceDraw_path == true)
            {
                //starsystem->DrawPath();
            }
            
//            npc->GetVehicle()->GetComplexDrive().DrawPath(renderer);
//            npc->GetVehicle()->GetComplexWeapon().RenderWeaponsRange();
//            npc->GetVehicle()->GetComplexWeapon().RenderWeaponIcons();
        
            //if (show.GetRangeRadar() == true)
            {
                //npc->GetVehicle()->RenderRadarRange();
            }
        
            //if ( (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr) and (npc->GetVehicle()->GetSlotGrapple()->GetSelected() == true) )
            {
                //npc->GetVehicle()->RenderGrappleRange();
            }
        }
    
        //cursor.RenderFocusedObjectStuff();
    }
    //disable_BLEND();
    //resizeGl(w, h); 
} 

void StarsystemRender::RenderCollisionRadius(const jeti::Renderer& render) const
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

void StarsystemRender::RenderAxis(const jeti::Renderer& render) const
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




bool isObjectWithinRadarRange(jeti::BaseParticleSystem* effect, Vehicle* vehicle)
{
    float dist = meti::distance(vehicle->center(), effect->center());
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
//    float dist = meti::distance(vehicle->center(), effect->center());
//    if (dist < vehicle->GetProperties().radar)
//    {
//        return true;
//    }
    
    return false;
}

bool isObjectWithinRadarRange(LazerTraceEffect* effect, Vehicle* vehicle)
{
    float dist = meti::distance(vehicle->center(), effect->GetStartPos());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    dist = meti::distance(vehicle->center(), effect->GetEndPos());
    if (dist < vehicle->GetProperties().radar)
    {
        return true;
    }
    
    return false;
}

//bool isObjectWithinRadarRange(VerticalFlowText* effect, Vehicle* vehicle)
//{
    //float dist = meti::distance(vehicle->center(), effect->GetPos());
    //if (dist < vehicle->GetProperties().radar)
    //{
        //return true;
    //}
    
    //return false;
//}

bool isObjectWithinRange(const glm::vec3& c1, const glm::vec3& c2, float radius)
{
    return (meti::distance(c1, c2) < radius);
}

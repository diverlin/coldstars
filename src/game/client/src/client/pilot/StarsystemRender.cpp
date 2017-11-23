///*
//    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/


//#include "StarsystemRender.hpp"
////#include <common/Config.hpp>

//#include <jeti/Screen.hpp>
//#include <jeti/Render.hpp>
//#include <jeti/Camera.hpp>

//#include <world/starsystem.hpp>
////#include <common/Global.hpp>
////#include <managers/EntitiesManager.hpp>

////#include <math/rand.hpp>
////#include <ceti/StringUtils.hpp>
////#include <common/TurnTimer.hpp>
//#include <client/common/global.hpp>
//#include <ceti/Logger.hpp>

////#include <ai/Task.hpp>
////#include <ai/StateMachine.hpp>

////#include <item/equipment/ScanerEquipment.hpp>
////#include <item/equipment/GrappleEquipment.hpp>

////#include <parts/WeaponComplex.hpp>

//#include <client/effect/Beam.hpp>
//#include <client/text/VerticalFlowText.hpp>

//#include <core/spaceobject/ALL>

//#include <core/pilot/Npc.hpp>

////#include <client/gui/GuiGalaxyMap.hpp>
////#include <client/gui/GuiManager.hpp>

////#include <core/slot/ItemSlot.hpp>

////#include <client/gui/UserInput.hpp>
////#include <client/gui/UserInputManagerInSpace.hpp>

////#include <glm/gtc/matrix_transform.hpp>

//#include <jeti/particlesystem/BaseParticleSystem.hpp>

////#include <meti/RandUtils.hpp>


//StarsystemRender::StarsystemRender()
//{}
    
//StarsystemRender::~StarsystemRender()
//{}
          
//void StarsystemRender::clearVisibleEntities()
//{
//    m_objects.clear();

////    visible_STAR_vec.clear();
////    visible_PLANET_vec.clear();
    
////    visible_ASTEROID_vec.clear();
////    visible_CONTAINER_vec.clear();

////    visible_SHIP_vec.clear();
////    visible_SATELLITE_vec.clear();
////    visible_SPACESTATION_vec.clear();
////    visible_ROCKET_vec.clear();
////    visible_BLACKHOLE_vec.clear();

////    visible_effect_SHOCKWAVE_vec.clear();
////    visible_effect_LAZERTRACE_vec.clear();
////    visible_effect_PARTICLESYSTEM_vec.clear();
////    visible_text_DAMAGE_vec.clear();
//}

//void StarsystemRender::addIfVisible(jeti::view::Base* ob)
//{
//    assert(false);
//    //    if (ob->inRect(client::shortcuts::screen()->data().rect)) {
////        m_objects.push_back(ob);
////    }
//}

////void StarsystemRender::addIfVisible(Star* star)
////{
////    if (isObjectOnScreen(star->center(), star->size())) {
////        visible_STAR_vec.push_back(star);
////    }
////}

////void StarsystemRender::addIfVisible(Planet* planet)
////{
////    if (isObjectOnScreen(planet->center(), planet->size())) {
////        visible_PLANET_vec.push_back(planet);
////    }
////}

////void StarsystemRender::addIfVisible(Asteroid* asteroid)
////{
////    if (isObjectOnScreen(asteroid->center(), asteroid->size())) {
//////        if (isObjectWithinRange(npc->vehicle()->center(), asteroid->center(), radius)) {
////            visible_ASTEROID_vec.push_back(asteroid);
////        }
//////    }
////}

////void StarsystemRender::addIfVisible(Container* container)
////{
////    if (isObjectOnScreen(container->center(), container->size())) {
//////        if (isObjectWithinRange(npc->vehicle()->center(), container->center(), radius)) {
////            visible_CONTAINER_vec.push_back(container);
////        }
//////    }
////}

////void StarsystemRender::addIfVisible(Bullet* rocket)
////{
////    if (isObjectOnScreen(rocket->center(), rocket->size())) {
//////        if (isObjectWithinRange(npc->vehicle()->center(), rocket->center(), radius)) {
////            visible_ROCKET_vec.push_back(rocket);
////        }
//////    }
////}

////void StarsystemRender::addIfVisible(BlackHole* blackhole)
////{
////    if (isObjectOnScreen(blackhole->center(), blackhole->size())) {
//////        if (isObjectWithinRange(npc->vehicle()->center(), blackhole->center(), radius)) {
////            visible_BLACKHOLE_vec.push_back(blackhole);
////        }
//////    }
////}

////void StarsystemRender::addIfVisible(Vehicle* vehicle)
////{
////    //if (isObjectOnScreen(vehicle->center(), vehicle->size())) {
////        //if (isObjectWithinRange(npc->vehicle()->center(), vehicle->center(), radius)) {
////            switch(vehicle->subTypeId())
////            {
////                case entity::Type::SHIP:             {     visible_SHIP_vec.push_back((Ship*)vehicle); break; }
////                case entity::Type::SATELLITE:        {     visible_SATELLITE_vec.push_back((Satellite*)vehicle); break; }
////                case entity::Type::SPACESTATION:     {     visible_SPACESTATION_vec.push_back((SpaceStation*)vehicle); break; }
////            }
//////        }
//////    }
////}
        
////void StarsystemRender::addIfVisible(ShockWaveEffect* effect)
////{
////    //if (isObjectOnScreen(effect->center(), 600)) {
////        //if (isObjectWithinRadarRange(effect, npc->vehicle())) {
////            //visible_effect_SHOCKWAVE_vec.push_back(effect);
////        //}
////    //}
////}

////void StarsystemRender::addIfVisible(LazerTraceEffect* effect)
////{
////    bool r1 = isPointOnScreen(meti::vec2(effect->GetStartPos()));
////    bool r2 = isPointOnScreen(meti::vec2(effect->GetEndPos()));

////    if (r1 || r2) {
//////        if (isObjectWithinRadarRange(effect, npc->vehicle())) {
////            visible_effect_LAZERTRACE_vec.push_back(effect);
////        }
//////    }
////}
 
////void StarsystemRender::addIfVisible(jeti::BaseParticleSystem* effect)
////{
////    //if (isObjectOnScreen(effect->center(), 600)) {
////        //if (isObjectWithinRadarRange(effect, npc->vehicle())) {
////            visible_effect_PARTICLESYSTEM_vec.push_back(effect);
////        //}
////    //}
////}

////void StarsystemRender::addIfVisible(VerticalFlowText* effect)
////{
////    if (isPointOnScreen(effect->center())) {
////        if (isPointOnScreen(effect->center())) {
////            visible_text_DAMAGE_vec.push_back(effect);
////        }
////    }
////}

//void StarsystemRender::RenderInSpace_NEW(jeti::Render& render, Starsystem* starsystem)
//{
//    bool draw_background    = true;
//    bool draw_volumetric    = true;
//    bool draw_something     = false;
//    bool draw_spaceObjects  = true;
//    bool draw_shockwave     = true;
//    bool draw_robustSpaceObjects = true;

//    float scale = render.scaleBase();
//    int w = client::shortcuts::screen()->width();
//    int h = client::shortcuts::screen()->height();
////    glm::vec2 world_coord(client::shortcuts::screen()->bottomLeft());
    
//    render.clearColorAndDepthBuffers();
    
//    //render.enable_CULLFACE();
//    {
//        if (draw_background)
//        {
//            // render background and star to FBO0
//            render.activateFbo(0, w, h);
//            {
//                //render.setPerspectiveProjection(w, h);
//                //starsystem->DrawBackground(render, world_coord);
//                render.setOrthogonalProjection();

//                for(Star* star : visible_STAR_vec) {
//                    //alpitodorender render.DrawMeshMultiTextured(star->mesh(), star->textureOb(), star->actualModelMatrix());
//                }
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

//                    for(BlackHole* blackhole : visible_BLACKHOLE_vec)
//                    {
//                        //blackhole->Render_NEW(render);
//                    }
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
//                //if (show.collisionRadius() == true)
//                {
//                    RenderAxis(render);
//                    RenderCollisionRadius(render);
//                }
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
    
//void StarsystemRender::RenderInSpace(Starsystem* starsystem, bool turn_ended, bool forceDraw_orbits, bool forceDraw_path)
//{
//    jeti::Render& renderer = client::global::get().render();
//    jeti::Camera& camera = client::global::get().camera();
//    camera.update();

//    renderer.composeViewMatrix(camera.viewMatrix());

//    //float scale = client::shortcuts::screen()->GetScale();

//    RenderInSpace_NEW(renderer, starsystem);

//    //resizeGl(w*scale, h*scale);
//    //enable_BLEND();
//    {
//        if (turn_ended == true)
//        {
//            if (forceDraw_orbits == true)
//            {
//                //starsystem->DrawOrbits(renderer);
//            }
            
//            if (forceDraw_path == true)
//            {
//                //starsystem->DrawPath();
//            }
            
////            npc->vehicle()->GetComplexDrive().DrawPath(renderer);
////            npc->vehicle()->GetComplexWeapon().RenderWeaponsRange();
////            npc->vehicle()->GetComplexWeapon().RenderWeaponIcons();
        
//            //if (show.GetRangeRadar() == true)
//            {
//                //npc->vehicle()->RenderRadarRange();
//            }
        
//            //if ( (npc->vehicle()->grappleSlot()->item() != nullptr) and (npc->vehicle()->grappleSlot()->isSelected() == true) )
//            {
//                //npc->vehicle()->RenderGrappleRange();
//            }
//        }
    
//        //m_cursor.RenderFocusedObjectStuff();
//    }
//    //disable_BLEND();
//    //resizeGl(w, h);
//}

//void StarsystemRender::RenderCollisionRadius(const jeti::Render& render) const
//{
//    //render.enable_BLEND();
//    {   //a;pitodorender
//        /*
//        for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)   { visible_SPACESTATION_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)      { visible_SATELLITE_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)           { visible_SHIP_vec[i]->RenderCollisionRadius(render); }
        
//        for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)         { visible_ROCKET_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)      { visible_CONTAINER_vec[i]->RenderCollisionRadius(render); }
                        
//        for(unsigned int i=0; i<visible_STAR_vec.size(); i++)           { visible_STAR_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_PLANET_vec.size(); i++)         { visible_PLANET_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)       { visible_ASTEROID_vec[i]->RenderCollisionRadius(render); }
//        for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)      { visible_BLACKHOLE_vec[i]->RenderCollisionRadius(render); }
//        */
//    }
//    //render.disable_BLEND();
//}

//void StarsystemRender::RenderAxis(const jeti::Render& render) const
//{
//    //render.enable_DEPTH();
//    //alpitodorender
//    /*
//        for(unsigned int i=0; i<visible_SPACESTATION_vec.size(); i++)   { visible_SPACESTATION_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_SATELLITE_vec.size(); i++)      { visible_SATELLITE_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_SHIP_vec.size(); i++)           { visible_SHIP_vec[i]->RenderAxis(render); }
        
//        for(unsigned int i=0; i<visible_ROCKET_vec.size(); i++)         { visible_ROCKET_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_CONTAINER_vec.size(); i++)      { visible_CONTAINER_vec[i]->RenderAxis(render); }
                        
//        for(unsigned int i=0; i<visible_STAR_vec.size(); i++)           { visible_STAR_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_PLANET_vec.size(); i++)         { visible_PLANET_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_ASTEROID_vec.size(); i++)       { visible_ASTEROID_vec[i]->RenderAxis(render); }
//        for(unsigned int i=0; i<visible_BLACKHOLE_vec.size(); i++)      { visible_BLACKHOLE_vec[i]->RenderAxis(render); }
//*/
////render.disable_DEPTH();
//}




//bool isObjectWithinRadarRange(jeti::BaseParticleSystem* effect, Vehicle* vehicle)
//{
//    assert(false);
////    float dist = meti::distance(vehicle->position(), effect->center());
////    if (dist < vehicle->properties().radar)
////    {
////        return true;
////    }
    
//    return false;
//}

//bool isObjectOnScreen(const glm::vec3& center, const glm::vec3& size)
//{
////    float scale = client::shortcuts::screen()->scale();
////    if (center.x < (client::shortcuts::screen()->bottomLeftScreenWC().x - size.x*scale))
////        return false;
////    if (center.x > (client::shortcuts::screen()->topRightScreenWC().x   + size.x*scale))
////        return false;
////    if (center.y < (client::shortcuts::screen()->bottomLeftScreenWC().y - size.y*scale))
////        return false;
////    if (center.y > (client::shortcuts::screen()->topRightScreenWC().y   + size.y*scale))
////        return false;
    
//    return true;
//}

//bool isObjectOnScreen(const glm::vec3& ob_center, const float sizeInPixels)
//{
////    float scale = client::shortcuts::screen()->scale();
////    if (ob_center.x < (client::shortcuts::screen()->bottomLeftScreenWC().x - sizeInPixels*scale))
////        return false;
////    if (ob_center.x > (client::shortcuts::screen()->topRightScreenWC().x + sizeInPixels*scale))
////        return false;
////    if (ob_center.y < (client::shortcuts::screen()->bottomLeftScreenWC().y - sizeInPixels*scale))
////        return false;
////    if (ob_center.y > (client::shortcuts::screen()->topRightScreenWC().y + sizeInPixels*scale))
////        return false;
    
//    return true;
//}

//bool isPointOnScreen(const glm::vec2& p)
//{
////    if (p.x < (client::shortcuts::screen()->bottomLeftScreenWC().x))
////        return false;
////    if (p.x > (client::shortcuts::screen()->topRightScreenWC().x))
////        return false;
////    if (p.y < (client::shortcuts::screen()->bottomLeftScreenWC().y))
////        return false;
////    if (p.y > (client::shortcuts::screen()->topRightScreenWC().y))
////        return false;
    
//    return true;
//}

//bool isObjectWithinRadarRange(ShockWaveEffect* effect, Vehicle* vehicle)
//{
////    float dist = meti::distance(vehicle->center(), effect->center());
////    if (dist < vehicle->properties().radar)
////    {
////        return true;
////    }
    
//    return false;
//}

//bool isObjectWithinRadarRange(LazerTraceEffect* effect, Vehicle* vehicle)
//{
//    assert(false);
////    float dist = meti::distance(vehicle->position(), effect->GetStartPos());
////    if (dist < vehicle->properties().radar)
////    {
////        return true;
////    }
    
////    dist = meti::distance(vehicle->position(), effect->GetEndPos());
////    if (dist < vehicle->properties().radar)
////    {
////        return true;
////    }
    
//    return false;
//}

////bool isObjectWithinRadarRange(VerticalFlowText* effect, Vehicle* vehicle)
////{
//    //float dist = meti::distance(vehicle->center(), effect->GetPos());
//    //if (dist < vehicle->properties().radar)
//    //{
//        //return true;
//    //}
    
//    //return false;
////}

//bool isObjectWithinRange(const glm::vec3& c1, const glm::vec3& c2, float radius)
//{
//    return (meti::distance(c1, c2) < radius);
//}

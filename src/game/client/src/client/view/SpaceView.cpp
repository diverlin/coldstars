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

#include "SpaceView.hpp"
#include <jeti/constants.hpp>

#include <ceti/Collision.hpp>
#include <common/constants.hpp>
#include <client/common/global.hpp>

#include <world/starsystem.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>
#include <jeti/Camera.hpp>

#include <spaceobjects/Star.hpp>
#include <descriptors/Base.hpp>

/// entities
#include <spaceobjects/Star.hpp>
#include <spaceobjects/Planet.hpp>

#include <client/view/ShipDrawable.hpp>
#include <client/view/BulletDrawable.hpp>
#include <client/view/ContainerDrawable.hpp>
#include <client/view/Star.hpp>
#include <client/view/Planet.hpp>
#include <client/view/BlackHoleDrawable.hpp>
#include <client/view/Asteroid.hpp>
#include <client/view/SpaceStationDrawable.hpp>
#include <client/view/SatelliteDrawable.hpp>


/// effects
#include <client/effects/lazerTrace.hpp>
#include <client/effects/ShockWaveEffect.hpp>
#include <client/text/VerticalFlowText.hpp>

#include <client/resources/TextureCollector.hpp>
#include <ceti/descriptor/Collector.hpp>
#include <common/Global.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace {

bool isRectOnVisibleScreenArea(const glm::vec3& center, const glm::vec3& size, const glm::vec2& screen_wc, float scale)
{
    if (center.x < (screen_wc.x - size.x*scale)) {
        return false;
    }
    if (center.x > (screen_wc.x + size.x*scale)) {
        return false;
    }
    if (center.y < (screen_wc.y - size.y*scale)) {
        return false;
    }
    if (center.y > (screen_wc.y + size.y*scale)) {
        return false;
    }
    return true;
}

bool isRectOnVisibleScreenArea(const glm::vec2& center, const glm::vec2& size, const glm::vec2& screen_wc, float scale)
{
    if (center.x < (screen_wc.x - size.x*scale)) {
        return false;
    }
    if (center.x > (screen_wc.x + size.x*scale)) {
        return false;
    }
    if (center.y < (screen_wc.y - size.y*scale)) {
        return false;
    }
    if (center.y > (screen_wc.y + size.y*scale)) {
        return false;
    }
    return true;
}

bool isPointOnVisibleScreenArea(const glm::vec2& p, const glm::vec2& screen_wc)
{
    if (p.x < (screen_wc.x)) {
        return false;
    }
    if (p.x > (screen_wc.x)) {
        return false;
    }
    if (p.y < (screen_wc.y)) {
        return false;
    }
    if (p.y > (screen_wc.y)) {
        return false;
    }

    return true;
}

} // namespace


namespace view {

Space::Space()
{

}

Space::~Space()
{}                                    

void
Space::__updateVisible(Starsystem* starsystem,
                      const meti::vec3& lookFrom,
                      const meti::vec3& lookTo,
                      float lookFar)
{
    __clear();

    VisibilityData visibilityData;
    visibilityData.screen.worldcoord.x = lookTo.x;
    visibilityData.screen.worldcoord.y = lookTo.y;
    visibilityData.observer.center = lookFrom;
    visibilityData.observer.radius = lookFar;

    for(auto* star: starsystem->stars()) {
        addIfVisible(star->model(), visibilityData);
    }

    for(auto* planet: starsystem->planets()) {
        addIfVisible(planet->model(), visibilityData);
    }
}

void Space::__clear()
{
    // entities
    m_stars.clear();
    m_planets.clear();
    m_asteroids.clear();
//    m_containers.clear();
//    m_ships.clear();
//    m_satellites.clear();
//    m_spacestations.clear();
//    m_bullets.clear();
//    m_wormholes.clear();

    // effects
//    m_shockwaves.clear();
//    m_lazertraces.clear();
//    m_particlesystems.clear();
//    m_texts.clear();
}

jeti::view::BaseView*
Space::__isViewExists(model::SpaceObject* model)
{
    std::map<model::SpaceObject*, jeti::view::BaseView*>::const_iterator it = m_cache.find(model);
    if (it != m_cache.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Space::addIfVisible(model::Star* model, const VisibilityData& data)
{
    assert(model);
//    if (isRectOnVisibleScreenArea(star->position(), star->size(), data.screen.worldcoord, data.screen.scale)) {
        //const descriptor::Star& descriptor = core::global::get().descriptors().star().get(star->descriptorId());
        //jeti::control::TextureOb* texOb = TextureCollector::get().get(descriptor.texture());
        //jeti::Mesh* mesh = nullptr;
        //jeti::Mesh* mesh = MeshCollector::get().get(descriptor.mesh());
    jeti::view::BaseView* view = __isViewExists(model);
    if (!view) {
        view = new view::Star(model);
        __cache(model, view);
    }
    assert(view);

    __add(view);
    //    }
}

void Space::addIfVisible(model::Planet* model, const VisibilityData& data)
{
    assert(model);

//    if (isRectOnVisibleScreenArea(planet->center(), planet->size(), data.screen.worldcoord, data.screen.scale)) {
    jeti::view::BaseView* view = __isViewExists(model);
    if (!view) {
        view = new view::Planet(model);
        __cache(model, view);
    }
    assert(view);

    __add(view);
//    }
}

//void SpaceViewer::addIfVisible(AsteroidDrawable* asteroid, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(asteroid->center(), asteroid->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(asteroid->center(), data.observer.center, data.observer.radius)) {
//            __add(asteroid);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(view::Container* container, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(container->center(), container->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(container->center(), data.observer.center, data.observer.radius)) {
//            __add(container);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(BulletDrawable* bullet, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(bullet->center(), bullet->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(bullet->center(), data.observer.center, data.observer.radius)) {
//            __add(bullet);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(BlackHoleDrawable* wormhole, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(wormhole->center(), wormhole->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(wormhole->center(), data.observer.center, data.observer.radius)) {
//            __add(wormhole);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(ShipDrawable* ship, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(ship->center(), ship->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(ship->center(), data.observer.center, data.observer.radius)) {
//            __add(ship);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(SpaceStationDrawable* spacestation, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(spacestation->center(), spacestation->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(spacestation->center(), data.observer.center, data.observer.radius)) {
//            __add(spacestation);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(SatelliteDrawable* satellite, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(satellite->center(), satellite->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(satellite->center(), data.observer.center, data.observer.radius)) {
//            __add(satellite);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(ShockWaveEffect* effect, const VisibilityData& data)
//{
//    if (isRectOnVisibleScreenArea(effect->center(), glm::vec2(600.0), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(effect->center(), data.observer.center, data.observer.radius)) {
//            __add(effect);
//        }
//    }
//}

//void SpaceViewer::addIfVisible(LazerTraceEffect* effect, const VisibilityData& data)
//{
//    //    if ( (isLineOnVisibleScreenArea(effect->GetStartPos(), effect->GetEndPos()))) {
//    //        if (isObjectWithinRadarRange(effect, npc->vehicle()))
//    //        {
//    __add(effect);
//    //        }
//    //    }
//}

//void SpaceViewer::addIfVisible(jeti::BaseParticleSystem* effect, const VisibilityData& data)
//{
//    //    if (isRectOnVisibleScreenArea(effect->center(), 600, data.screen.worldcoord, data.screen.scale)) {
//    //        if (isObjectWithinRadarRange(effect, npc->vehicle())) {
//    __add(effect);
//    //        }
//    //    }
//}

//void SpaceViewer::addIfVisible(VerticalFlowText* effect, const VisibilityData& data)
//{
//    if (isPointOnVisibleScreenArea(effect->center(), data.screen.worldcoord)) {
//        m_texts.push_back(effect);
//    }
//}

/// visible entities
void Space::__add(jeti::view::BaseView* view)
{
    std::map<jeti::view::BaseView*, model::SpaceObject*>::const_iterator it = m_cache2.find(view);
    assert(it != m_cache2.end());
    model::SpaceObject* ob = it->second;

    switch(ob->type()) {
    case type::entity::STAR_ID: {
        view::Star* star = static_cast<view::Star*>(view);
        assert(star);
        m_stars.push_back(star);
        break;
    }
    case type::entity::PLANET_ID: {
        view::Planet* planet = static_cast<view::Planet*>(view);
        assert(planet);
        m_planets.push_back(planet);
        break;
    }
    }
}

void Space::__loadResourcesFor(model::SpaceObject* model, jeti::view::BaseView* view)
{
    {
    jeti::Mesh* mesh = nullptr;

    int_t descritprorId = model->mesh();
    auto it = m_meshCollector.find(descritprorId);
    if (it != m_meshCollector.end()) {
        mesh = it->second;
    } else {
        auto& collector = core::global::get().descriptors().mesh();
        ceti::descriptor::Mesh* descriptor = collector.get(descritprorId);
        if (descriptor) {
            mesh = new jeti::Mesh(descriptor);
        }
        assert(mesh);
        m_meshCollector.insert(std::make_pair(descritprorId, mesh));
    }
    view->setMesh(mesh);
    }


    {
    jeti::control::Material* material = nullptr;

    int_t descritprorId = model->material();
    auto it = m_materialCollector.find(descritprorId);
    if (it != m_materialCollector.end()) {
        material = it->second;
    } else {
        auto& collector = core::global::get().descriptors().material();
        ceti::descriptor::Material* descriptor = collector.get(descritprorId);
        if (descriptor) {
            jeti::model::Material* model = new jeti::model::Material(descriptor);
            material = new jeti::control::Material(model);
        }
        assert(material);
        m_materialCollector.insert(std::make_pair(descritprorId, material));
    }
    view->setMaterial(material);

    }
}

void Space::__cache(model::SpaceObject* ob, jeti::view::BaseView* view)
{
    __loadResourcesFor(ob, view);
    m_cache.insert(std::make_pair(ob, view));
    m_cache2.insert(std::make_pair(view, ob));
}

void Space::__add(Star* view)
{
    m_stars.push_back(view);
}

void Space::__add(Planet* view)
{
    m_planets.push_back(view);
}

void Space::__add(Asteroid* view)
{
    m_asteroids.push_back(view);
}

//void SpaceViewer::__add(Container* view)
//{
//    m_containers.push_back(view);
//}

//void SpaceViewer::__add(BulletDrawable* view)
//{
//    m_bullets.push_back(view);
//}

//void SpaceViewer::__add(BlackHoleDrawable* view)
//{
//    m_wormholes.push_back(view);
//}

//void SpaceViewer::__add(ShipDrawable* view)
//{
//    m_ships.push_back(view);
//}

//void SpaceViewer::__add(SpaceStationDrawable* view)
//{
//    //m_satellites.push_back(view);
//}

//void SpaceViewer::__add(SatelliteDrawable* view)
//{
//    //m_spacestations.push_back(view);
//}

///// visible effects
//void SpaceViewer::__add(ShockWaveEffect* view)
//{
//    m_shockwaves.push_back(view);
//}

//void SpaceViewer::__add(LazerTraceEffect* view)
//{
//    m_lazertraces.push_back(view);
//}

//void SpaceViewer::__add(jeti::BaseParticleSystem* view)
//{
//    m_particlesystems.push_back(view);
//}

//void SpaceViewer::__add(VerticalFlowText* view)
//{
//    m_texts.push_back(view);
//}



void Space::__render_NEW(jeti::Renderer& render)
{
//    bool draw_background    = true;
//    bool draw_volumetric    = true;
//    bool draw_something     = false;
//    bool draw_spaceObjects  = true;
//    bool draw_shockwave     = true;
//    bool draw_robustSpaceObjects = true;

    const auto& screen = client::global::get().screen();
    float scale = screen.scale();
    int w = screen.width();
    int h = screen.height();
    //glm::vec2 world_coord(client::global::get().screen().GetBottomLeft());

    render.clearColorAndDepthBuffers();

    //render.setPerspectiveProjection(w, h);
    //starsystem->DrawBackground(render, world_coord);
    render.setOrthogonalProjection(w*scale, h*scale);

    for(Star* star: m_stars) {
        star->draw(render);
    }

    for(Planet* planet: m_planets) {
        planet->draw(render);
    }
}

void Space::__render_NEW2(jeti::Renderer& render)
{   
    bool draw_background    = true;
    bool draw_volumetric    = true;
    bool draw_something     = false;
    bool draw_spaceObjects  = true;
    bool draw_shockwave     = true;
    bool draw_robustSpaceObjects = true;

    float scale = client::global::get().screen().scale();
    int w = client::global::get().screen().width();
    int h = client::global::get().screen().height();
    glm::vec2 world_coord(client::global::get().screen().bottomLeft());
    
    render.clearColorAndDepthBuffers();

    //render.enable_CULLFACE();
    {
        if (draw_background)
        {
            // render background and star to FBO0
            //render.activateFbo(0, w, h);
            {
                render.setPerspectiveProjection(w, h);
                //starsystem->DrawBackground(render, world_coord);
                render.setOrthogonalProjection(w*scale, h*scale);

                assert(m_stars.size());
                for(Star* star: m_stars) {
                    std::cout<<"-- render star "<<star->model()->typeInfo()<<std::endl;
                    star->draw(render);
                    //render.DrawMeshMultiTextured(star->mesh(), star->textureOb(), star->actualModelMatrix());
                }
            }
            //render.deactivateFbo(0);

            // BLOOM background and star (uses many FBO)
            //resizeGl(w, h);
            // alpitodorender render.GetBloom().Proceed(render, w, h, render.GetLastFbo().GetTexture(), npc->vehicle()->starsystem()->GetStar()->GetBrightThreshold());
        }

        // VOLUMETRIC LIGHT to FBO1
        if (draw_volumetric)
        {
            //resizeGl(w, h);
            render.activateFbo(1, w, h);
            {
                //render.DrawStarField(w/2, h/2, -world_coord.x/10000.0f, -world_coord.y/10000.0f);
                render.drawPostEffectVolumetricLight(world_coord, w, h);
            }
            render.deactivateFbo(1);
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
            render.activateFbo(3, w, h);
            {
                render.drawScreenQuadTextured(render.lastFbo().GetTexture(), w, h);

                // resizeGl(w*scale, h*scale);
                {
                    for(Planet* planet: m_planets) {
                        planet->draw(render);
                    }

//                    for(SpaceStationDrawable* spacestation: m_spacestations) {
//                        //spacestation->RenderInSpace(render, 1/scale);
//                    }

//                    //if (getRandInt(0, 30) == 0) std::cout<<"ship num rendered="<<visible_SHIP_vec.size()<<std::endl;
//                    for(ShipDrawable* ship: m_ships) {
//                        //ship->RenderInSpace(render, 1/scale);
//                    }

                    for(Asteroid* asteroid: m_asteroids) {
                        //asteroid->Render_NEW(render, world_coord);
                        asteroid->draw(render);
                    }

//                    for(BlackHoleDrawable* warmhole: m_wormholes) {
//                        //blackhole->Render_NEW(render);
//                    }
                }

//                {
//                    for(Container* container: m_containers) {
//                        container->render(render);
//                    }

//                    for(SatelliteDrawable* satellite: m_satellites) {
//                        //satellite->RenderInSpace(render, 1/scale);
//                    }

//                    for(BulletDrawable* bullet: m_bullets) {
//                        //rocket->RenderInSpace(render, 1/scale);
//                    }
//                }
//                //                if (show.collisionRadius() == true)
//                //                {
//                //                    RenderAxis(render);
//                //                    RenderCollisionRadius(render);
//                //                }
            }
            render.deactivateFbo(3);
        }

        if (draw_shockwave)
        {
            // SHOCKWAVE post process to Fbo3
            //resizeGl(w, h);
            render.activateFbo(4, w, h);
            {
                float center_array[SHOCKWAVES_MAX_NUM][2];
                float xyz_array[SHOCKWAVES_MAX_NUM][3];
                float time_array[SHOCKWAVES_MAX_NUM];

//                unsigned int i=0;
//                for (i=0; ((i<m_wormholes.size()) && (i<SHOCKWAVES_MAX_NUM)); i++)
//                {
//                    const ShockWaveEffect& shockwave = *m_wormholes[i]->GetShockWaveEffect();

//                    center_array[i][0] = (shockwave.center().x - world_coord.x)/w;
//                    center_array[i][1] = (shockwave.center().y - world_coord.y)/h;
//                    xyz_array[i][0] = shockwave.parameters().x;
//                    xyz_array[i][1] = shockwave.parameters().y;
//                    xyz_array[i][2] = shockwave.parameters().z;
                    
//                    time_array[i] = shockwave.time();
//                }
//                for (unsigned int j=0; ((j<m_shockwaves.size()) && (i<SHOCKWAVES_MAX_NUM)); j++, i++)
//                {
//                    center_array[i][0] = (m_shockwaves[j]->center().x - world_coord.x)/(w*scale);
//                    center_array[i][1] = (m_shockwaves[j]->center().y - world_coord.y)/(h*scale);
//                    xyz_array[i][0] = m_shockwaves[j]->parameters().x;
//                    xyz_array[i][1] = m_shockwaves[j]->parameters().y;
//                    xyz_array[i][2] = m_shockwaves[j]->parameters().z/scale;
                    
//                    time_array[i] = m_shockwaves[j]->time();
//                }

                //render.drawPostEffectShockWaves(render.lastFbo().GetTexture(), w, h, i, center_array, xyz_array, time_array);
            }
            render.deactivateFbo(4);
        }

        if (draw_robustSpaceObjects)
        {
            // render effects not distorted by SHOCKWAVE
            render.activateFbo(5, w, h);
            {
                //resizeGl(w, h);
                render.drawScreenQuadTextured(render.lastFbo().GetTexture(), w, h);

                //resizeGl(w*scale, h*scale);
                //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);

//                for(unsigned int i = 0; i<m_lazertraces.size(); i++)
//                {
//                    const LazerTraceEffect& lazer_trace = *m_lazertraces[i];
//                    //render.DrawMesh(lazer_trace.mesh(), lazer_trace.textureOb(), lazer_trace.actualModelMatrix());
//                }

//                for(unsigned int i=0; i<m_particlesystems.size(); i++)
//                {
//                    //BaseParticleSystem& ps = *visible_effect_PARTICLESYSTEM_vec[i];
//                    //render.DrawParticles(ps.mesh(), ps.textureOb(), ps.actualModelMatrix());
//                }
            }
            render.deactivateFbo(5);
        }

        render.clearColorAndDepthBuffers();
        render.drawScreenQuadTextured(render.lastFbo().GetTexture(), w, h);

        // FOGWAR and STARSPARK to final scene
        //resizeGl(w, h);


        //render.DrawPostEffectFogWar(render.GetLastFbo().GetTexture(), w, h, npc->vehicle()->center(), world_coord, 200 /*npc->vehicle()->properties().radius*/);

        // render text
        //resizeGl(w*scale, h*scale);
        //camera(world_coord.x, world_coord.y, CAMERA_POS_Z);
//        for(unsigned int i = 0; i<m_texts.size(); i++) {
//            //visible_text_DAMAGE_vec[i]->Render(world_coord, 1/scale);
//        }

        //starsystem->RestoreSceneColor();
    }
    //render.disable_CULLFACE();
    
    //render.SetOrthogonalProjection(w, h);
}

//void SpaceViewer::render(Starsystem* starsystem,
//                         const meti::vec3& lookFrom,
//                         const meti::vec3& lookTo,
//                         float lookFar,
//                         bool turn_ended,
//                         bool forceDraw_orbits,
//                         bool forceDraw_path)

void Space::render(Starsystem* starsystem, jeti::Camera& camera)
{   
    __updateVisible(starsystem, camera.lookFrom(), camera.lookTo(), camera.lookRadius());

    jeti::Renderer& renderer = client::global::get().render();

    int w = client::global::get().screen().width();
    int h = client::global::get().screen().height();

    camera.update(w, h);
    
    renderer.composeViewMatrix(camera.viewMatrix());
    __render_NEW(renderer);
    //resizeGl(w*scale, h*scale);
    //enable_BLEND();
    //    {
    //        if (turn_ended == true)
    //        {
    //            if (forceDraw_orbits == true)
    //            {
    //                starsystem->DrawOrbits(renderer);
    //            }

    //            if (forceDraw_path == true)
    //            {
    //                starsystem->DrawPath();
    //            }

    //            npc->vehicle()->GetComplexDrive().DrawPath(renderer);
    //            npc->vehicle()->GetComplexWeapon().RenderWeaponsRange();
    //            npc->vehicle()->GetComplexWeapon().RenderWeaponIcons();

    //            if (show.GetRangeRadar() == true)
    //            {
    //                npc->vehicle()->RenderRadarRange();
    //            }

    //            if ( (npc->vehicle()->grappleSlot()->item() != nullptr) and (npc->vehicle()->grappleSlot()->isSelected() == true) )
    //            {
    //                npc->vehicle()->RenderGrappleRange();
    //            }
    //        }
    
    //        //cursor.RenderFocusedObjectStuff();
    //    }
    //disable_BLEND();
    //resizeGl(w, h);
} 

void Space::__renderCollisionRadius(const jeti::Renderer& render) const
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

void Space::__renderAxis(const jeti::Renderer& render) const
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

} // namespace view

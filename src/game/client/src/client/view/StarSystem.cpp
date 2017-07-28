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

#include "StarSystem.hpp"

#include "Base.hpp"

#include <core/type/MeshType.hpp>
#include <core/common/constants.hpp>
#include <core/world/starsystem.hpp>
#include <core/descriptor/Base.hpp>

#include <core/spaceobject/ALL>

#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>

#include <core/descriptor/spaceobject/Star.hpp>
#include <core/descriptor/spaceobject/Planet.hpp>
#include <core/descriptor/spaceobject/Asteroid.hpp>

#include <core/model/spaceobject/ALL>

#include <client/view/spaceobject/ALL>

/// effects
#include <client/effects/lazerTrace.hpp>
#include <client/effects/ShockWaveEffect.hpp>
#include <client/text/VerticalFlowText.hpp>
#include <client/resources/TextureCollector.hpp>
#include <client/common/global.hpp>

#include <jeti/Render.hpp>
#include <jeti/constants.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>
#include <jeti/Camera.hpp>
#include <jeti/animation/ConstantRotation.hpp>

#include <ceti/Collision.hpp>

#include <client/gui/UserInput.hpp>
#include <client/gui/info/starsystem.hpp>
#include <client/gui/info/Camera.hpp>
#include <client/gui/info/Renderer.hpp>
#include <client/gui/GuiDemo.hpp>

namespace  {
std::string join(size_t int1, size_t int2) {
    return std::string(std::to_string(int1) + " / " + std::to_string(int2));
}
} // namespace

namespace view {

StarSystem::StarSystem(jeti::Renderer& render)
    :
      m_render(render)
    , m_camera(*render.camera())
    , m_guiDemo(new gui::Demo(&client::global::get().screen()))
{}

StarSystem::~StarSystem()
{}                                    

void
StarSystem::__updateVisible(control::StarSystem* starsystem)
{
    __clear();

    for(auto star: starsystem->stars()) {
        __addIfVisible(star);
    }
    for(auto planet: starsystem->planets()) {
        __addIfVisible(planet);
    }
//    for(auto wormHole: starsystem->wormHoles()) {
//        __addIfVisible(wormhole);
//    }
    for(auto asteroid: starsystem->asteroids()) {
        __addIfVisible(asteroid);
    }
    for(auto container: starsystem->containers()) {
        __addIfVisible(container);
    }

    for(auto spacestation: starsystem->spacestations()) {
        __addIfVisible(spacestation);
    }
    for(auto ship: starsystem->ships()) {
        __addIfVisible(ship);
    }
    for(auto satellite: starsystem->satellites()) {
        __addIfVisible(satellite);
    }
//    for(auto bullet: starsystem->bullets()) {
//        __addIfVisible(bullet);
//    }

//    std::cout<<"ship="<<ceti::to_string(starsystem->ships()[0]->position())<<std::endl;
//    std::cout<<"star="<<ceti::to_string(starsystem->stars()[0]->position())<<std::endl;

    // update ui
    {
    auto info = m_guiDemo->infoStarSystem();

    info->setStarsNum(starsystem->stars().size());
    info->setPlanetsNum(starsystem->planets().size());
    //info->setWormHolesNum(starsystem->wormHoles().size());
    info->setAsteroidsNum(starsystem->asteroids().size());
    info->setContainersNum(starsystem->containers().size());
    info->setSpaceStationsNum(starsystem->spacestations().size());
    info->setShipsNum(starsystem->ships().size());
    info->setSatellitesNum(starsystem->satellites().size());
    info->setBulletsNum(starsystem->bullets().size());

    info->setVisibleStarsNum(m_stars.size());
    info->setVisiblePlanetsNum(m_planets.size());
    info->setVisibleWormHolesNum(m_wormHoles.size());
    info->setVisibleAsteroidsNum(m_asteroids.size());
    info->setVisibleContainersNum(m_containers.size());
    info->setVisibleSpaceStationsNum(m_spacestations.size());
    info->setVisibleShipsNum(m_ships.size());
    info->setVisibleSatellitesNum(m_satellites.size());
    info->setVisibleBulletsNum(m_bullets.size());
    }

    {
        // update ui
        auto info = m_guiDemo->infoCamera();
        info->setLookFrom(ceti::to_string(m_render.camera()->position()));
        info->setLookAt(ceti::to_string(m_render.camera()->target()));
        info->setUp(ceti::to_string(m_render.camera()->up()));
    }

    {
        const jeti::Renderer& render = client::global::get().render();
        // update ui
        auto info = m_guiDemo->infoRender();
        info->setZNear(std::to_string(jeti::ZNEAR));
        info->setZFar(std::to_string(jeti::ZFAR));
        info->setScreenQuadZ(std::to_string(jeti::SCREEN_QUAD_ZPOS));

        info->setScale(std::to_string(render.scale()));
        info->setWidth(ceti::to_string(render.width()));
        info->setHeight(ceti::to_string(render.height()));
    }

    {
        m_guiDemo->updateFps(client::global::get().render().fps());
        m_guiDemo->updateMousePos(100, 100);
    }
}

void StarSystem::__clear()
{
    // entities
    m_stars.clear();
    m_planets.clear();
    m_wormHoles.clear();
    m_asteroids.clear();
    m_containers.clear();
    m_spacestations.clear();
    m_ships.clear();
    m_satellites.clear();
    m_bullets.clear();

    // effects
//    m_shockwaves.clear();
//    m_lazertraces.clear();
//    m_particlesystems.clear();
//    m_texts.clear();
}

bool
StarSystem::__addIfVisible(control::Star* star)
{
    assert(star);
    if (!__isObjectOnScreen(star->position(), star->size())) {
        return false;
    }

    Base* view = m_cache.get(star->id());
    if (!view) {
        view = new Star(star);
        applyConstantRotationAnimation(meti::OY, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool
StarSystem::__addIfVisible(control::Planet* planet)
{
    assert(planet);
    if (!__isObjectOnScreen(planet->position(), planet->size())) {
        return false;
    }

    Base* view = m_cache.get(planet->id());
    if (!view) {
        view = new Planet(planet);
        applyConstantRotationAnimation(meti::OY, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool
StarSystem::__addIfVisible(control::Asteroid* asteroid)
{
    assert(asteroid);
    if (!__isObjectOnScreen(asteroid->position(), asteroid->size())) {
        return false;
    }
    if (!ceti::isPointInObserverRadius(asteroid->position(), m_camera.position(), m_camera.radius())) {
        return false;
    }

    Base* view = m_cache.get(asteroid->id());
    if (!view) {
        view = new Asteroid(asteroid);
        applyConstantRotationAnimation(meti::OY, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}


bool
StarSystem::__addIfVisible(control::Ship* ship)
{
    assert(ship);
    if (!__isObjectOnScreen(ship->position(), ship->size())) {
        return false;
    }
    if (!ceti::isPointInObserverRadius(ship->position(), m_camera.position(), m_camera.radius())) {
        return false;
    }

    Base* view = m_cache.get(ship->id());
    if (!view) {
        view = new Ship(ship);
        applyConstantRotationAnimation(meti::OZ, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool
StarSystem::__addIfVisible(control::SpaceStation* spacestation)
{
    assert(spacestation);
    if (!__isObjectOnScreen(spacestation->position(), spacestation->size())) {
        return false;
    }
    if (!ceti::isPointInObserverRadius(spacestation->position(), m_camera.position(), m_camera.radius())) {
        return false;
    }

    Base* view = m_cache.get(spacestation->id());
    if (!view) {
        view = new SpaceStation(spacestation);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool
StarSystem::__addIfVisible(control::Satellite* satellite)
{
    assert(satellite);
    if (!__isObjectOnScreen(satellite->position(), satellite->size())) {
        return false;
    }
    if (!ceti::isPointInObserverRadius(satellite->position(), m_camera.position(), m_camera.radius())) {
        return false;
    }

    Base* view = m_cache.get(satellite->id());
    if (!view) {
        view = new Satellite(satellite);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

void StarSystem::applyConstantRotationAnimation(const glm::vec3& axis, Base* view)
{
    jeti::animation::ConstantRotation* animation = new jeti::animation::ConstantRotation(axis, meti::getRandFloat(0.001, 0.01));
    view->setAnimationRotation(animation);
}

void StarSystem::__addIfVisible(control::Container* container)
{
    assert(false);
//    if (isRectOnVisibleScreenArea(container->center(), container->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(container->center(), data.observer.center, data.observer.radius)) {
//            __add(container);
//        }
//    }
}

void StarSystem::__addIfVisible(control::Bullet* bullet)
{
    assert(false);
//    if (isRectOnVisibleScreenArea(bullet->center(), bullet->size(), data.screen.worldcoord, data.screen.scale)) {
//        if (ceti::isPointInObserverRadius(bullet->center(), data.observer.center, data.observer.radius)) {
//            __add(bullet);
//        }
//    }
}

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
void StarSystem::__add(Base* view)
{
    switch(view->type()) {
    case entity::Type::STAR: {
        Star* star = static_cast<Star*>(view);
        assert(star);
        m_stars.push_back(star);
        return;
    }
    case entity::Type::PLANET: {
        Planet* planet = static_cast<Planet*>(view);
        assert(planet);
        m_planets.push_back(planet);
        return;
    }
    case entity::Type::ASTEROID: {
        Asteroid* asteroid = static_cast<Asteroid*>(view);
        assert(asteroid);
        m_asteroids.push_back(asteroid);
        return;
    }
    case entity::Type::VEHICLE: {
        switch(view->subType()) {
        case entity::Type::SPACESTATION: {
            SpaceStation* spacestation = static_cast<SpaceStation*>(view);
            assert(spacestation);
            m_spacestations.push_back(spacestation);
            return;
        }
        case entity::Type::SHIP: {
            Ship* ship = static_cast<Ship*>(view);
            assert(ship);
            m_ships.push_back(ship);
            return;
        }
        case entity::Type::SATELLITE: {
            Satellite* satellite = static_cast<Satellite*>(view);
            assert(satellite);
            m_satellites.push_back(satellite);
            return;
        }
        }
    }
    }
    assert(false);
}

void StarSystem::__add(Star* view)
{
    m_stars.push_back(view);
}

void StarSystem::__add(Planet* view)
{
    m_planets.push_back(view);
}

void StarSystem::__add(Asteroid* view)
{
    m_asteroids.push_back(view);
}

void StarSystem::__add(Container* view)
{
    m_containers.push_back(view);
}

void StarSystem::__add(Bullet* view)
{
    m_bullets.push_back(view);
}

void StarSystem::__add(WormHole* view)
{
    m_wormHoles.push_back(view);
}

void StarSystem::__add(Ship* view)
{
    m_ships.push_back(view);
}

void StarSystem::__add(SpaceStation* view)
{
    m_spacestations.push_back(view);
}

void StarSystem::__add(Satellite* view)
{
    m_satellites.push_back(view);
}

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



void StarSystem::__render_NEW(jeti::Renderer& render)
{
//    bool draw_background    = true;
//    bool draw_volumetric    = true;
//    bool draw_something     = false;
//    bool draw_spaceObjects  = true;
//    bool draw_shockwave     = true;
//    bool draw_robustSpaceObjects = true;

    const auto& screen = client::global::get().screen();

    render.clearColorAndDepthBuffers();

    //render.setPerspectiveProjection(w, h);
    //starsystem->DrawBackground(render, world_coord);
    render.setOrthogonalProjection();

    render.enable_CULLFACE();

    for(Star* star: m_stars) {
        star->update();
        star->draw(render);
    }

    for(Planet* planet: m_planets) {
        planet->update();
        planet->draw(render);
    }

    for(Asteroid* asteroid: m_asteroids) {
        asteroid->update();
        asteroid->draw(render);
    }

    for(Ship* ship: m_ships) {
        ship->update();
        ship->draw(render);
    }


    render.disable_CULLFACE();

    UserInput::get().setDesktop(m_guiDemo->desktop()); // hack

    if (m_guiDemo) {
        m_guiDemo->draw();
    }
}

void StarSystem::__render_NEW2(jeti::Renderer& render)
{   
    bool draw_background    = true;
    bool draw_volumetric    = true;
    bool draw_something     = false;
    bool draw_spaceObjects  = true;
    bool draw_shockwave     = true;
    bool draw_robustSpaceObjects = true;

    float scale = client::global::get().render().scale();
    int w = client::global::get().screen().width();
    int h = client::global::get().screen().height();
//    glm::vec2 world_coord(client::global::get().screen().bottomLeft());
    
    render.clearColorAndDepthBuffers();

    //render.enable_CULLFACE();
    {
        if (draw_background)
        {
            // render background and star to FBO0
            //render.activateFbo(0, w, h);
            {
                //render.setPerspectiveProjection(w, h);
                //starsystem->DrawBackground(render, world_coord);
                render.setOrthogonalProjection();

                assert(m_stars.size());
                for(Star* star: m_stars) {
                    //std::cout<<"-- render star "<<star->star()->model()->typeInfo()<<std::endl;
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
                //render.drawPostEffectVolumetricLight(world_coord, w, h);
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

void StarSystem::render(control::StarSystem* starsystem)
{   
    assert(starsystem);
    jeti::Renderer& renderer = client::global::get().render();

    renderer.update();
    m_camera.update();
    
    __updateVisible(starsystem);

    renderer.composeViewMatrix(m_camera.viewMatrix());
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
    
    //        //m_cursor.RenderFocusedObjectStuff();
    //    }
    //disable_BLEND();
    //resizeGl(w, h);
} 

void StarSystem::__renderCollisionRadius(const jeti::Renderer& render) const
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

void StarSystem::__renderAxis(const jeti::Renderer& render) const
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

bool
StarSystem::__isObjectOnScreen(const glm::vec3& pos, const glm::vec3& size)
{
    glm::vec3 position_screen_coord = m_render.toScreenCoord(pos);
    return isObjectOnScreen(position_screen_coord, size, m_render.size(), m_render.scale());
}

bool
StarSystem::__isObjectOnScreen2(const glm::vec3& pos, const glm::vec3& size)
{
    glm::vec3 position_screen_coord = m_render.toScreenCoord(pos);
    bool result = isObjectOnScreen(position_screen_coord, size, m_render.size(), m_render.scale());
    std::cout<<"screen coord"<<ceti::to_string(position_screen_coord)<<" visible="<<result<<std::endl;
    return result;
}

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
    const glm::vec3 center3(center.x, center.y, 0);
    const glm::vec3 size3(size.x, size.y, 0);
    return isRectOnVisibleScreenArea(center3, size3, screen_wc, scale);
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

bool isPointInRect(const glm::vec3& p, const ceti::Rect& rect)
{
    if (p.x < 0) {
        return false;
    }
    if (p.x > rect.width()) {
        return false;
    }
    if (p.y < 0) {
        return false;
    }
    if (p.y > rect.height()) {
        return false;
    }

    return true;
}

bool isPointInRect(const glm::vec2& p, const ceti::Rect& rect)
{
    if (p.x < 0) {
        return false;
    }
    if (p.x > rect.width()) {
        return false;
    }
    if (p.y < 0) {
        return false;
    }
    if (p.y > rect.height()) {
        return false;
    }

    return true;
}

bool isObjectOnScreen(const glm::vec3& screen_coord, const glm::vec3& object_size, const glm::ivec2& screen_size, float scale)
{
    float max_part = std::max(object_size.x*scale, object_size.y*scale);

    if (screen_coord.x < -max_part) {
        return false;
    }
    if (screen_coord.x > (screen_size.x + max_part)) {
        return false;
    }
    if (screen_coord.y < -max_part) {
        return false;
    }
    if (screen_coord.y > (screen_size.y + max_part)) {
        return false;
    }

    return true;
}

} // namespace view

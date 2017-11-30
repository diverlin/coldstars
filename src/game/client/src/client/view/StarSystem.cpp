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
#include <client/effect/Beam.hpp>
#include <client/effect/ShockWaveEffect.hpp>
#include <client/text/VerticalFlowText.hpp>
#include <client/resources/TextureCollector.hpp>
#include <client/effect/DistantStarsEffect.hpp>
#include <client/effect/DistantNebulaEffect.hpp>
#include <client/effect/Beam.hpp>
#include <client/gui/info/GenericTable.hpp>

#include <jeti/Render.hpp>
#include <jeti/constants.hpp>
#include <jeti/Screen.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>
#include <jeti/Camera.hpp>
#include <jeti/animation/ConstantRotation.hpp>
#include <jeti/particlesystem/Jet.hpp>
#include <jeti/particlesystem/Explosion.hpp>
#include <jeti/particlesystem/Damage.hpp>

#include <ceti/Collision.hpp>

#include <client/gui/UserInput.hpp>
#include <client/gui/info/starsystem.hpp>
#include <client/gui/info/Camera.hpp>
#include <client/gui/info/Renderer.hpp>
#include <client/gui/GuiDemo.hpp>
#include <client/gui/GuiManager.hpp>
#include <client/resources/Utils.hpp>
#include <client/pilot/Player.hpp>
#include <client/session/Shortcuts.hpp>


namespace jeti {
class Render;
class Screen;
} // namespace jeti

namespace view {

StarSystem::StarSystem(jeti::Render& render, jeti::Screen& screen)
    :
      m_render(render)
    , m_camera(*render.camera())
    , m_guiDemo(new gui::Demo(&screen))
    , m_distantStars(::effect::genDistantStars())
    , m_distantNebulas(::effect::genDistantNebulas())
//    , m_lastTime(std::chrono::steady_clock::now())
{
}

StarSystem::~StarSystem()
{}                                    

void
StarSystem::add(std::shared_ptr<jeti::particlesystem::Base> ps, const glm::vec3& center)
{
    ps->setCenter(center);
    m_particlesystems.push_back(ps);
}

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
    for(auto wormhole: starsystem->wormholes()) {
        __addIfVisible(wormhole);
    }
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
    for(auto bullet: starsystem->bullets()) {
        __addIfVisible(bullet);
    }
    for(auto jet: m_beams) {
        __addIfVisible(jet);
    }
    for(auto ps: m_particlesystems) {
        __addIfVisible(ps);
    }
    for(auto text: m_texts) {
        __addIfVisible(text);
    }

    //__createText();
    //__createExplosion();
    //__createBeam();

    // update ui
    {
    auto info = m_guiDemo->infoStarSystem();

    info->setStarsNum(starsystem->stars().size());
    info->setPlanetsNum(starsystem->planets().size());
    info->setWormHolesNum(starsystem->wormholes().size());
    info->setAsteroidsNum(starsystem->asteroids().size());
    info->setContainersNum(starsystem->containers().size());
    info->setSpaceStationsNum(starsystem->spacestations().size());
    info->setShipsNum(starsystem->ships().size());
    info->setSatellitesNum(starsystem->satellites().size());
    info->setBulletsNum(starsystem->bullets().size());

    info->setVisibleStarsNum(m_stars.size());
    info->setVisiblePlanetsNum(m_planets.size());
    info->setVisibleWormHolesNum(m_wormholes.size());
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
        info->setSpeed(ceti::to_string(m_render.camera()->speed()));
    }

    {
        // update ui
        auto info = m_guiDemo->infoRender();
        info->setZNear(std::to_string(jeti::ZNEAR));
        info->setZFar(std::to_string(jeti::ZFAR));
        info->setScreenQuadZ(std::to_string(jeti::SCREEN_QUAD_ZPOS));

        info->setScale(std::to_string(m_render.scaleBase()));
        info->setWidth(ceti::to_string(m_render.width()));
        info->setHeight(ceti::to_string(m_render.height()));
    }

    {
        // update ui
        m_guiDemo->updateFps(m_render.fps());

        const glm::vec3 screen_coord = glm::vec3(m_player->cursor().mouseData().screenCoord(), 0.0f);
        const glm::vec3 world_coord = m_player->cursor().mouseData().worldCoord();

        m_guiDemo->setMousePosScreenCoord(screen_coord.x, screen_coord.y);
        m_guiDemo->setMousePosWorldCoord(world_coord.x, world_coord.y);

        Base* view = mouseInterraction(screen_coord);
        m_player->update(m_render, view);

        if (view) {
            m_guiDemo->windowObjectProperties()->Show(true);
            m_guiDemo->modelTable()->update(view->control()->model()->info());
            m_guiDemo->descriptorTable()->update(view->control()->descriptor()->info());
        } else {
            m_guiDemo->modelTable()->reset();
            m_guiDemo->descriptorTable()->reset();
            m_guiDemo->windowObjectProperties()->Show(false);
        }
    }
}

void StarSystem::__clear()
{
    // entities
    m_stars.clear();
    m_planets.clear();
    m_wormholes.clear();
    m_asteroids.clear();
    m_containers.clear();
    m_spacestations.clear();
    m_ships.clear();
    m_satellites.clear();
    m_bullets.clear();

    // effects
//    m_shockwaves.clear();

    // clear jets
    for(std::vector<::effect::Beam*>::iterator it=m_beams.begin(); it < m_beams.end(); ++it) {
        ::effect::Beam* beam = *it;
        if (!beam->isAlive()) {
            it = m_beams.erase(it);
            delete beam;
        }
    }
    m_visible_beams.clear();
    //

    // clear texts
    for(std::vector<::effect::Text*>::iterator it=m_texts.begin(); it < m_texts.end(); ++it) {
        ::effect::Text* text = *it;
        if (!text->isAlive()) {
            it = m_texts.erase(it);
            delete text;
        }
    }
    m_visible_texts.clear();
    //

    // clear effects
    for(std::vector<std::shared_ptr<jeti::particlesystem::Base>>::iterator it=m_particlesystems.begin(); it < m_particlesystems.end(); ++it) {
        if (!(*it)->isAlive()) {
            it = m_particlesystems.erase(it);
        }
    }
    m_visible_particlesystems.clear();
    //
}

void StarSystem::__applyConstantRotationAnimation(const glm::vec3& axis, Base* view)
{
    jeti::animation::ConstantRotation* animation = new jeti::animation::ConstantRotation(axis, meti::rand::gen_float(0.001, 0.01));
    view->setAnimationRotation(animation);
}

bool
StarSystem::__addIfVisible(control::Star* star)
{
    assert(star);
    if (!__isObjectOnScreen(star)) {
        return false;
    }

    Base* view = m_cache.get(star->id());
    if (!view) {
        view = new Star(star);
        __applyConstantRotationAnimation(meti::OY, view);
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
    if (!__isObjectOnScreen(planet)) {
        return false;
    }

    Base* view = m_cache.get(planet->id());
    if (!view) {
        view = new Planet(planet);
        __applyConstantRotationAnimation(meti::OY, view);
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
    if (!__isObjectOnScreen(asteroid)) {
        return false;
    }
    if (!ceti::isPointInCircle(asteroid->position(), m_player->position(), m_player->radius())) {
        return false;
    }

    Base* view = m_cache.get(asteroid->id());
    if (!view) {
        view = new Asteroid(asteroid);
        __applyConstantRotationAnimation(meti::OY, view);
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
    if (!__isObjectOnScreen(ship)) {
        return false;
    }
    if (!ceti::isPointInCircle(ship->position(), m_player->position(), m_player->radius())) {
        return false;
    }

    Base* view = m_cache.get(ship->id());
    if (!view) {
        view = new Ship(ship);
        //applyConstantRotationAnimation(meti::OZ, view);
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
    if (!__isObjectOnScreen(spacestation)) {
        return false;
    }
    if (!ceti::isPointInCircle(spacestation->position(), m_player->position(), m_player->radius())) {
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
    if (!__isObjectOnScreen(satellite)) {
        return false;
    }
    if (!ceti::isPointInCircle(satellite->position(), m_player->position(), m_player->radius())) {
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

bool StarSystem::__addIfVisible(control::Container* container)
{
    assert(container);
    if (!__isObjectOnScreen(container)) {
        return false;
    }
    if (!ceti::isPointInCircle(container->position(), m_player->position(), m_player->radius())) {
        return false;
    }

    Base* view = m_cache.get(container->id());
    if (!view) {
        view = new Container(container);
        //applyConstantRotationAnimation(meti::OZ, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool StarSystem::__addIfVisible(control::Bullet* bullet)
{
    assert(bullet);
    if (!__isObjectOnScreen(bullet)) {
        return false;
    }
    if (!ceti::isPointInCircle(bullet->position(), m_player->position(), m_player->radius())) {
        return false;
    }

    Base* view = m_cache.get(bullet->id());
    if (!view) {
        view = new Bullet(bullet);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

bool StarSystem::__addIfVisible(control::WormHole* wormhole)
{
    assert(wormhole);
    if (!__isObjectOnScreen(wormhole)) {
        return false;
    }
    if (!ceti::isPointInCircle(wormhole->position(), m_player->position(), m_player->radius())) {
        return false;
    }

    Base* view = m_cache.get(wormhole->id());
    if (!view) {
        view = new WormHole(wormhole);
        //applyConstantRotationAnimation(meti::OZ, view);
        m_cache.add(view);
    }
    assert(view);

    __add(view);

    return true;
}

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


void
StarSystem::__createBeam()
{
    if (m_beams.size()>=1) {
        return;
    }

    glm::vec3 from(100.0f, 100.0f, 0.0f);
    glm::vec3 to(200.0f, 200.0f, 0.0f);
    //glm::vec3 from(meti::getRandFloat(-500.0f,500.0f), meti::getRandFloat(-500.0f,500.0f), 0.0f);
//    glm::vec3 to(meti::getRandFloat(-200.0f,200.0f), meti::getRandFloat(-200.0f,200.0f), 0.0f);

    ::effect::Beam* beam = new ::effect::Beam(utils::createMaterialByDescriptorType(texture::Type::LAZER_EFFECT));

    beam->setFrom(from);
    beam->setTo(to);

    float size = 3.0f;
    jeti::particlesystem::Base* ps = jeti::particlesystem::genDamage(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), size);
    beam->setParticleSystem(ps);

    m_beams.push_back(beam);
}

void
StarSystem::__createText()
{
    if (m_texts.size()>=10) {
        return;
    }

    std::string str = std::to_string(meti::rand::gen_int(1,200));
    float size = meti::rand::gen_float(18.0f, 32.0f);
    glm::vec2 center(meti::rand::gen_float(-10.0f,10.0f), meti::rand::gen_float(-10.0f,10.0f));
    glm::vec4 color;
    color.r = meti::rand::gen_float(0.7f, 1.0f);
    color.g = meti::rand::gen_float(0.7f, 1.0f);
    color.b = meti::rand::gen_float(0.7f, 1.0f);

    sf::Font& font = client::shortcuts::screen()->font();
    ::effect::Text* text = new ::effect::Text(font, str, size, center, color);

    m_texts.push_back(text);
}

void
StarSystem::__createExplosion()
{
    if (m_particlesystems.size()>=0) {
        return;
    }

    float size = meti::rand::gen_float(1.0f, 10.0f);
    glm::vec3 center(meti::rand::gen_float(-400.0f,400.0f), meti::rand::gen_float(-400.0f,400.0f), 0.0f);

    std::shared_ptr<jeti::particlesystem::Explosion> ps(jeti::particlesystem::genExplosion(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), size));

    ps->setCenter(center);
    m_particlesystems.push_back(ps);
}

bool
StarSystem::__addIfVisible(std::shared_ptr<jeti::particlesystem::Base> ps)
{
    m_render.toScreenCoord(ps->center(), m_tmpScreenCoord);
    if (!isObjectOnScreen(m_tmpScreenCoord, ps->size(), m_render.size(), m_render.scaleBase())) {
        return false;
    }
    if (!ceti::isPointInCircle(ps->center(), m_player->position(), m_player->radius())) {
        return false;
    }

    m_visible_particlesystems.push_back(ps);
    return true;
}

bool
StarSystem::__addIfVisible(::effect::Beam* effect)
{
//    m_render.toScreenCoord(ps->center(), m_tmpScreenCoord);
//    if (!isObjectOnScreen(m_tmpScreenCoord, ps->size(), m_render.size(), m_render.scaleBase())) {
//        return false;
//    }
//    if (!ceti::isPointInObserverRadius(ps->center(), m_player->position(), m_player->radius())) {
//        return false;
//    }

    m_visible_beams.push_back(effect);
    return true;
}

bool
StarSystem::__addIfVisible(::effect::Text* text)
{
//    if (isPointOnVisibleScreenArea(effect->center(), data.screen.worldcoord)) {
//        m_texts.push_back(effect);
//    }
    m_visible_texts.push_back(text);
    return true;
}

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
    case entity::Type::CONTAINER: {
        Container* container = static_cast<Container*>(view);
        assert(container);
        m_containers.push_back(container);
        return;
    }
    case entity::Type::BULLET: {
        Bullet* bullet = static_cast<Bullet*>(view);
        assert(bullet);
        m_bullets.push_back(bullet);
        return;
    }
    default:
        assert(false);
    }
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
    m_wormholes.push_back(view);
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

void StarSystem::__renderBackground(jeti::Render& render) const {
    if (!m_player->show().background()) {
        return;
    }

    if (m_player->show().backgroundFbo()) {
        render.fboBackGround().activate(render.size().x, render.size().y);
    }

    if (m_player->show().nebulas()) {
        // projection
        render.applyOrthogonalProjection();

        glEnable(GL_DEPTH_TEST);
        m_distantNebulas->update();
        m_distantNebulas->draw(render);
        glDisable(GL_DEPTH_TEST);
    }
    if (m_player->show().stars()) {
        // projection
        render.applyPerspectiveProjection();

        m_distantStars->draw(render);
    }
    if (m_player->show().backgroundFbo()) {
        render.fboBackGround().deactivate();
    }
}

void StarSystem::__renderStarPostEffect(jeti::Render& render) const {
    if (!m_player->show().star()) {
        return;
    }

    // projection
    render.applyOrthogonalProjection();

    render.drawStar(render.fboBackGround().colorBuffer());
}

void StarSystem::__renderSpaceObjects(jeti::Render& render) const {
    if (!m_player->show().spaceobjects()) {
        return;
    }

    // projections
    render.applyOrthogonalProjection();

    for(Star* star: m_stars) {
        star->update();
        //star->draw(render); // post effect is used instead
    }

    for(Planet* planet: m_planets) {
        planet->update();
        planet->draw(render);
    }

    for(WormHole* wormhole: m_wormholes) {
        wormhole->update();
        wormhole->draw(render);
    }

    for(Asteroid* asteroid: m_asteroids) {
        asteroid->update();
        asteroid->draw(render);
    }

    for(Ship* ship: m_ships) {
        ship->update();
        ship->draw(render);
    }

    for(Bullet* bullet: m_bullets) {
        bullet->update();
        bullet->draw(render);
    }

    for(Container* container: m_containers) {
        container->update();
        container->draw(render);
    }

    // beams
    for(::effect::Beam* beam: m_beams) {
        beam->update();
    }
    for(::effect::Beam* beam: m_visible_beams) {
        beam->draw(render);
    }
    //

    // particles systems
    for(std::shared_ptr<jeti::particlesystem::Base> ps: m_particlesystems) {
        ps->update();
    }
    for(std::shared_ptr<jeti::particlesystem::Base> ps: m_visible_particlesystems) {
        ps->draw(render);
    }
    //

    m_player->cursor().renderFocusedObjectStuff(render);
}


void StarSystem::__renderSpaceObjectsMeta(jeti::Render& render) const {
    if (!m_player->show().spaceobjects_meta()) {
        return;
    }

    // projection
    render.applyOrthogonalProjection();

    if (m_player->show().collisionRadius()) {
        __drawCollisionRadius(render);
    }
    if (m_player->show().axis()) {
        __drawAxis(render);
    }
}

void StarSystem::__renderHUD(jeti::Render& render) const {
    if (!m_player->show().hud()) {
        return;
    }

    gui::UserInput::get().setDesktop(m_guiDemo->desktop()); // hack
    if (m_guiDemo) {
        m_guiDemo->draw();
    }
}

void StarSystem::__renderTexts(jeti::Render& render) const {
    // texts
    for(::effect::Text* text: m_texts) {
        text->update();
    }
    sf::RenderWindow& window = client::shortcuts::screen()->window();

    window.pushGLStates();
    for(::effect::Text* text: m_visible_texts) {
        text->draw(window, m_camera.position());
    }
    window.popGLStates();
    //
}

void StarSystem::__renderExperiment(jeti::Render& render) const {
    if (!m_player->show().experimental()) {
        return;
    }

    // projection
    render.applyOrthogonalProjection();
}

void StarSystem::__render(jeti::Render& render)
{
    render.clearColorAndDepthBuffers();

    __renderBackground(render);
    __renderStarPostEffect(render);
    __renderSpaceObjects(render);
    __renderSpaceObjectsMeta(render);
    __renderTexts(render);
    __renderExperiment(render);
    __renderHUD(render);
}

Base*
StarSystem::mouseInterraction(const glm::vec3& mouse_pos) const
{
    if (!m_allowInterraction) {
        return nullptr;
    }

    for(SpaceStation* spacestation: m_spacestations) {
        if(__isPointInsideObject(mouse_pos, spacestation->control())) {
            return spacestation;
        }
    }
    for(Satellite* satellite: m_satellites) {
        if(__isPointInsideObject(mouse_pos, satellite->control())) {
            return satellite;
        }
    }
    for(Ship* ship: m_ships) {
        if(__isPointInsideObject(mouse_pos, ship->control())) {
            return ship;
        }
    }
    for(Bullet* bullet: m_bullets) {
        if(__isPointInsideObject(mouse_pos, bullet->control())) {
            return bullet;
        }
    }
    for(Container* container: m_containers) {
        if(__isPointInsideObject(mouse_pos, container->control())) {
            return container;
        }
    }
    for(Star* star: m_stars) {
        if(__isPointInsideObject(mouse_pos, star->star())) {
            return star;
        }
    }
    for(Planet* planet: m_planets) {
        if(__isPointInsideObject(mouse_pos, planet->control())) {
            return planet;
        }
    }
    for(Asteroid* asteroid: m_asteroids) {
        if(__isPointInsideObject(mouse_pos, asteroid->control())) {
            return asteroid;
        }
    }
    for(WormHole* wormhole: m_wormholes) {
        if(__isPointInsideObject(mouse_pos, wormhole->control())) {
            return wormhole;
        }
    }

    return nullptr;
}

void StarSystem::update(const glm::vec3& camera_accel)
{
    m_allowInterraction = !gui::Manager::get().vehicle()->isActive();
    m_camera.addSpeed(camera_accel);
    m_camera.update();
}

void StarSystem::render(control::StarSystem* starsystem)
{   
//    const auto now_time = std::chrono::steady_clock::now();
//    float msec_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now_time-m_lastTime).count();
//    if (msec_diff < 30) {
//        return;
//    }


//    m_lastTime = now_time;

    assert(starsystem);

    m_render.update();
    __updateVisible(starsystem);

    __render(m_render);

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

void StarSystem::__drawCollisionRadius(const jeti::Render& render) const
{
    if (!m_player->show().collisionRadius()) {
        return;
    }

    for(const SpaceStation* spacestation: m_spacestations)  { spacestation->drawCollisionRadius(render); }
    for(const Satellite* satellite: m_satellites)           { satellite->drawCollisionRadius(render); }
    for(const Ship* ship: m_ships)                          { ship->drawCollisionRadius(render); }

    for(const Bullet* bullet: m_bullets)            { bullet->drawCollisionRadius(render); }
    for(const Container* container: m_containers)   { container->drawCollisionRadius(render); }

    for(const Star* star: m_stars)                  { star->drawCollisionRadius(render); }
    for(const Planet* planet: m_planets)            { planet->drawCollisionRadius(render); }
    for(const Asteroid* asteroid: m_asteroids)      { asteroid->drawCollisionRadius(render); }
    for(const WormHole* wormHole: m_wormholes)      { wormHole->drawCollisionRadius(render); }
}

void StarSystem::__drawAxis(const jeti::Render& render) const
{
    if (!m_player->show().axis()) {
        return;
    }

    for(const SpaceStation* spacestation: m_spacestations)  { spacestation->drawAxis(render); }
    for(const Satellite* satellite: m_satellites)           { satellite->drawAxis(render); }
    for(const Ship* ship: m_ships)                          { ship->drawAxis(render); }

    for(const Bullet* bullet: m_bullets) { bullet->drawAxis(render); }
    for(const Container* container: m_containers) { container->drawAxis(render); }

    for(const Star* star: m_stars)                  { star->drawAxis(render); }
    for(const Planet* planet: m_planets)            { planet->drawAxis(render); }
    for(const Asteroid* asteroid: m_asteroids)      { asteroid->drawAxis(render); }
    for(const WormHole* wormHole: m_wormholes)    { wormHole->drawAxis(render); }
}










void StarSystem::__render_DEPRECATED(jeti::Render& render)
{
    bool draw_background    = true;
    bool draw_volumetric    = true;
    bool draw_something     = false;
    bool draw_spaceObjects  = true;
    bool draw_shockwave     = true;
    bool draw_robustSpaceObjects = true;

    float scale = render.scaleBase();
    int w = client::shortcuts::screen()->width();
    int h = client::shortcuts::screen()->height();
//    glm::vec2 world_coord(client::shortcuts::screen()->bottomLeft());

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
                render.applyOrthogonalProjection();

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
                render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);

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
                render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);

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
        render.drawScreenQuadTextured(render.lastFbo().colorBuffer(), w, h);

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

bool
StarSystem::__isObjectOnScreen(ceti::control::Orientation* orientation) const
{
    m_render.toScreenCoord(orientation->position(), m_tmpScreenCoord);
    return isObjectOnScreen(m_tmpScreenCoord, orientation->size(), m_render.size(), m_render.scaleBase());
}

bool StarSystem::__isPointInsideObject(const glm::vec3& p, ceti::control::Orientation* orientation) const {
    m_render.toScreenCoord(orientation->position(), m_tmpScreenCoord);
    glm::vec3 diff(m_tmpScreenCoord-p);
    if (glm::length(diff) < orientation->collisionRadius()/m_render.scaleBase()) {
        return true;
    }
    return false;
}



//void StarSystem::add(ShockWaveEffect* shockwave, const glm::vec2& center)
//{
//    //    shockwave->setCenter(center);
//    //    effect_SHOCKWAVE_vec.push_back(shockwave);
//}

//void StarSystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center)
//{
//    //    float radius_damage = explosion->GetRadius();
//    //    float damage = 0;
//    //    Add(explosion, center, damage, radius_damage);
//}

//void StarSystem::add(jeti::ExplosionEffect* explosion, const glm::vec3& center, float damage, float radius_damage)
//{
//    //    explosion->setCenter(center);
//    //    effect_PARTICLESYSTEM_vec.push_back(explosion);

//    //    float radius_effect = explosion->GetRadius();
//    //    if ((radius_effect > 75) && (GetShockWaveEffectNum() < SHOCKWAVES_MAX_NUM))
//    //    {
//    //        ShockWaveEffect* shockwave = getNewShockWave(radius_effect);
//    //        Add(shockwave, meti::vec2(center));
//    //    }

//    //    if (radius_effect > 25)
//    //    {
//    //        DamageEventInsideCircle(center, radius_damage, damage, true);
//    //    }
//    //explosion.play()
//}

//void StarSystem::Add(LazerTraceEffect* lazerTraceEffect)     { effect_LAZERTRACE_vec.push_back(lazerTraceEffect); }
//void StarSystem::Add(jeti::BaseParticleSystem* ps)                 { effect_PARTICLESYSTEM_vec.push_back(ps); }
//void StarSystem::Add(VerticalFlowText* text)                 { text_DAMAGE_vec.push_back(text); }
//void StarSystem::Add(DistantNebulaEffect* dn)                { distantNebulaEffect_vec.push_back(dn); }
//void StarSystem::Add(DistantStarEffect* ds)                  { distantStarEffect_vec.push_back(ds); }



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

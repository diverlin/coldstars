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

#pragma once

#include <client/view/Cache.hpp>
#include <client/pilot/Show.hpp>

#include <ceti/type/IdType.hpp>
#include <ceti/rect.hpp>
#include <ceti/Pack.hpp>

#include <jeti/Screen.hpp>
#include <jeti/Material.hpp>

#include <vector>
#include <map>
#include <chrono>
#include <memory>

namespace client {
class Player;
} // namespace client

namespace ceti {
namespace control {
class Orientation;
} // namespace control
} // namespace ceti

namespace gui {
class Demo;
class UserInputInSpace;
} // namespace gui

namespace jeti {
class Render;
class Camera;
class Mesh;
namespace particlesystem {
class Base;
} // namespace particlesystem

namespace control {
class Material;
} // namespace controlobject

} // namespace jeti

namespace core {
namespace control {
class Base;
class StarSystem;
class Star;
class Planet;
class Asteroid;
class WormHole;
class Container;
class SpaceStation;
class Ship;
class Satellite;
class Bullet;
} // namespace control
} // namespace core

namespace effect {
class DistantStars;
class DistantNebulas;
class Beam;
class Text;
} // namespace

namespace view {
class Base;
class Star;
class Planet;
class Asteroid;
class WormHole;
class Container;
class SpaceStation;
class Ship;
class Satellite;
class Bullet;
} // namespace view

/// effects
class ShockWaveEffect;
class VerticalFlowText;

namespace view {

class StarSystemViewer
{
public:
    StarSystemViewer();
    ~StarSystemViewer();

    bool isOpened() const { return m_screen->window().isOpen(); }

    client::Player* player() const { return m_player; }

    void setPlayer(client::Player* player) { m_player = player; }
    Base* mouseInterraction(const glm::vec3&) const;

    void update(const glm::vec3& = glm::vec3(0.0f));
    void draw();
    void drawDeffered();
    void draw(core::control::StarSystem*);

    void add(std::shared_ptr<jeti::particlesystem::Base>, const glm::vec3&);

    Show& show() { return m_show; }

    jeti::Screen* screen() const { return m_screen; }
    jeti::Render* renderer() const { return m_render; }
    jeti::Camera* camera() const { return m_camera; }
    gui::UserInputInSpace* inputs() const { return m_inputs; }

    // effects
//    void add(jeti::BaseParticleSystem*);
//    void add(ShockWaveEffect*, const glm::vec2&);
//    void add(jeti::ExplosionEffect*, const glm::vec3&, float, float);
//    void add(jeti::particlesystem::Explosion*, const glm::vec3&);
//    void add(LazerTraceEffect*);

//    void add(DistantNebulaEffect*);
//    void add(DistantStarEffect*);

    //void Add(VerticalFlowText*);
    //

private:
    bool m_allowInterraction = true;
    Show m_show;

//    std::unique_ptr<jeti::Screen> m_screen = nullptr;
//    std::unique_ptr<jeti::Render> m_render = nullptr;
//    std::unique_ptr<jeti::Camera> m_camera = nullptr;
//    std::unique_ptr<gui::UserInputInSpace> m_inputs = nullptr;

    jeti::Screen* m_screen = nullptr;
    jeti::Camera* m_camera = nullptr;
    jeti::Render* m_render = nullptr;
    gui::UserInputInSpace* m_inputs = nullptr;

    gui::Demo* m_guiDemo = nullptr;
    ::effect::DistantStars* m_distantStars = nullptr;
    ::effect::DistantNebulas* m_distantNebulas = nullptr;

//    std::chrono::steady_clock::time_point m_lastTime;

    /// visible entities
    std::vector<Star*> m_stars;
    std::vector<Planet*> m_planets;
    std::vector<WormHole*> m_wormholes;
    std::vector<Asteroid*> m_asteroids;
    std::vector<Container*> m_containers;
    std::vector<SpaceStation*> m_spacestations;
    std::vector<Ship*> m_ships;
    std::vector<Satellite*> m_satellites;
    std::vector<Bullet*> m_bullets;

    mutable glm::vec3 m_tmpScreenCoord;
    client::Player* m_player = nullptr;

    Cache m_cache;

    /// visible effects
//    std::vector<ShockWaveEffect*> m_shockwaves;
    std::vector<std::shared_ptr<jeti::particlesystem::Base>> m_particlesystems;
    std::vector<std::shared_ptr<jeti::particlesystem::Base>> m_visible_particlesystems;

    std::vector<::effect::Beam*> m_beams;
    std::vector<::effect::Beam*> m_visible_beams;
    std::vector<::effect::Text*> m_texts;
    std::vector<::effect::Text*> m_visible_texts;

    ceti::pack<jeti::control::Material*> m_demoMaterials;

    void __applyConstantRotationAnimation(const glm::vec3&, Base*);

    void __updateVisible(core::control::StarSystem* starsystem);

    void __render();
    void __drawCollisionRadius(const jeti::Render&) const;
    void __drawAxis(const jeti::Render&) const;

    /// visible entities
    bool __addIfVisible(core::control::Star*);
    bool __addIfVisible(core::control::Planet*);
    bool __addIfVisible(core::control::Asteroid* data);
    bool __addIfVisible(core::control::Container* data);
    bool __addIfVisible(core::control::Bullet* data);
    bool __addIfVisible(core::control::WormHole* data);
    bool __addIfVisible(core::control::Ship*);
    bool __addIfVisible(core::control::SpaceStation*);
    bool __addIfVisible(core::control::Satellite*);

    /// visible effects
//    void addIfVisible(ShockWaveEffect*, const VisibilityData&);
    bool __addIfVisible(::effect::Beam*);
    bool __addIfVisible(std::shared_ptr<jeti::particlesystem::Base>);
    bool __addIfVisible(::effect::Text*);

    // debug
    void __createText();
    void __createExplosion();
    void __createBeam();
    //

    /// visible entities
    void __add(Base*);
    void __add(Star*);
    void __add(Planet*);
    void __add(Asteroid*);
    void __add(Container*);
    void __add(Bullet*);
    void __add(WormHole*);
    void __add(Ship*);
    void __add(SpaceStation*);
    void __add(Satellite*);

    /// visible effects
    void __add(ShockWaveEffect*);
    void __add(::effect::Beam*);
    void __add(jeti::particlesystem::Base*);
    void __add(VerticalFlowText*);

    void __clear();

    bool __isObjectOnScreen(ceti::control::Orientation*) const;
    bool __isPointInsideObject(const glm::vec3&, ceti::control::Orientation*) const;

    void __renderBackground() const;
    void __renderStarPostEffect() const;
    void __renderSpaceObjects() const;
    void __renderTexts() const;
    void __renderSpaceObjectsMeta() const;
    void __renderHUD() const;
    void __renderExperiment() const;


    void __render_DEPRECATED(jeti::Render&);
    void __initDemoResources();
};

bool isRectOnVisibleScreenArea(const glm::vec3& center, const glm::vec3& size, const glm::vec2& screen_wc, float scale);
bool isRectOnVisibleScreenArea(const glm::vec2& center, const glm::vec2& size, const glm::vec2& screen_wc, float scale);
bool isPointOnVisibleScreenArea(const glm::vec2& p, const glm::vec2& screen_wc);

bool isPointInRect(const glm::vec2& p, const ceti::Rect& rect);
bool isPointInRect(const glm::vec3& p, const ceti::Rect& rect);
bool isObjectOnScreen(const glm::vec3&, const glm::vec3&, const glm::ivec2&, float);

} // namespace view


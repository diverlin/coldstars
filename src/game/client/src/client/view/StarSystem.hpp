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

#include <ceti/type/IdType.hpp>

#include <jeti/Screen.hpp>

#include <vector>
#include <map>

class StarSystemDrawable;

namespace gui {
class Demo;
} // naemspace gui

namespace jeti {
class Renderer;
class Camera;
class Mesh;

namespace control {
class Material;
} // namespace control

} // namespace jeti

namespace control {
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
class LazerTraceEffect;
class ShockWaveEffect;
namespace jeti {
class BaseParticleSystem;
}
class VerticalFlowText;

namespace view {

class StarSystem
{
public:
    StarSystem(jeti::Camera& camera);
    ~StarSystem();

    void render(control::StarSystem*);

private:
    gui::Demo* m_guiDemo = nullptr;

    /// visible entities
    std::vector<Star*> m_stars;
    std::vector<Planet*> m_planets;
    std::vector<WormHole*> m_wormHoles;
    std::vector<Asteroid*> m_asteroids;
    std::vector<Container*> m_containers;
    std::vector<SpaceStation*> m_spacestations;
    std::vector<Ship*> m_ships;
    std::vector<Satellite*> m_satellites;
    std::vector<Bullet*> m_bullets;

    /// visible effects
//    std::vector<ShockWaveEffect*> m_shockwaves;
//    std::vector<LazerTraceEffect*> m_lazertraces;
//    std::vector<jeti::BaseParticleSystem*> m_particlesystems;
//    std::vector<VerticalFlowText*> m_texts;
    
    void applyConstantRotationAnimation(Base*);

    void __updateVisible(control::StarSystem* starsystem);

    void __render_NEW(jeti::Renderer&);
    void __render_NEW2(jeti::Renderer&);
    void __renderCollisionRadius(const jeti::Renderer&) const;
    void __renderAxis(const jeti::Renderer&) const;

    /// visible entities
    bool __addIfVisible(control::Star*, const jeti::Screen::Data&);
    bool __addIfVisible(control::Planet*, const jeti::Screen::Data&);
    bool __addIfVisible(control::Asteroid*, const jeti::Screen::Data& data);
    void __addIfVisible(control::Container*, const jeti::Screen::Data& data);
    void __addIfVisible(control::Bullet*, const jeti::Screen::Data& data);
    void __addIfVisible(control::WormHole*, const jeti::Screen::Data& data);
    bool __addIfVisible(control::Ship*, const jeti::Screen::Data&);
    bool __addIfVisible(control::SpaceStation*, const jeti::Screen::Data&);
    bool __addIfVisible(control::Satellite*, const jeti::Screen::Data&);

    /// visible effects
//    void addIfVisible(ShockWaveEffect*, const VisibilityData&);
//    void addIfVisible(LazerTraceEffect*, const VisibilityData&);
//    void addIfVisible(jeti::BaseParticleSystem*, const VisibilityData&);
//    void addIfVisible(VerticalFlowText*, const VisibilityData&);

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
    void __add(LazerTraceEffect*);
    void __add(jeti::BaseParticleSystem*);
    void __add(VerticalFlowText*);

    void __loadResourcesFor(Base*);
    void __cache(Base*);

    void __clear();

    Base* __tryGetViewCached(int_t);

    std::map<int_t, Base*> m_cache;

    std::map<int_t, jeti::Mesh*> m_meshCollector;
    std::map<int_t, jeti::control::Material*> m_materialCollector;

    bool __isObjectOnScreen(const glm::vec3& center, const jeti::Screen::Data& screen);
    jeti::Camera& m_camera;

    bool m_debug = true;
};

bool isRectOnVisibleScreenArea(const glm::vec3& center, const glm::vec3& size, const glm::vec2& screen_wc, float scale);
bool isRectOnVisibleScreenArea(const glm::vec2& center, const glm::vec2& size, const glm::vec2& screen_wc, float scale);
bool isPointOnVisibleScreenArea(const glm::vec2& p, const glm::vec2& screen_wc);

bool isPointInRect(const glm::vec2& p, const ceti::Rect& rect);
bool isPointInRect(const glm::vec3& p, const ceti::Rect& rect);
bool isObjectOnScreen(const glm::vec3& pos_sc, const jeti::Screen::Data&);

glm::vec3 screenCoord(const glm::vec3& pos_wc, const jeti::Camera& camera, const jeti::Screen::Data& screen);

} // namespace view


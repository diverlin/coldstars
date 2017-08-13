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

#include <ceti/type/IdType.hpp>

#include <jeti/Screen.hpp>

#include <vector>
#include <map>

class Player;

namespace ceti {
namespace control {
class Orientation;
} // namespace control
} // namespace ceti

namespace gui {
class Demo;
} // naemspace gui

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

namespace effect {
class DistantStars;
class DistantNebulas;
class Beam;
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

class StarSystem
{
public:
    StarSystem(jeti::Render&);
    ~StarSystem();

    void setPlayer(Player* player) { m_player = player; }
    Base* mouseInterraction(const glm::vec3&) const;
    void render(control::StarSystem*);

private:
    jeti::Render& m_render;
    jeti::Camera& m_camera;

    gui::Demo* m_guiDemo = nullptr;
    ::effect::DistantStars* m_distantStars = nullptr;
    ::effect::DistantNebulas* m_distantNebulas = nullptr;

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
    Player* m_player = nullptr;

    Cache m_cache;

    /// visible effects
//    std::vector<ShockWaveEffect*> m_shockwaves;
    std::vector<jeti::particlesystem::Base*> m_particlesystems;
    std::vector<jeti::particlesystem::Base*> m_visible_particlesystems;

    std::vector<::effect::Beam*> m_jets;
    std::vector<::effect::Beam*> m_visible_jets;
    //    std::vector<VerticalFlowText*> m_texts;
    
    void __applyConstantRotationAnimation(const glm::vec3&, Base*);

    void __updateVisible(control::StarSystem* starsystem);

    void __render(jeti::Render&);
    void __drawCollisionRadius(const jeti::Render&) const;
    void __drawAxis(const jeti::Render&) const;

    /// visible entities
    bool __addIfVisible(control::Star*);
    bool __addIfVisible(control::Planet*);
    bool __addIfVisible(control::Asteroid* data);
    bool __addIfVisible(control::Container* data);
    bool __addIfVisible(control::Bullet* data);
    bool __addIfVisible(control::WormHole* data);
    bool __addIfVisible(control::Ship*);
    bool __addIfVisible(control::SpaceStation*);
    bool __addIfVisible(control::Satellite*);

    /// visible effects
//    void addIfVisible(ShockWaveEffect*, const VisibilityData&);
    bool __addIfVisible(::effect::Beam*);
    bool __addIfVisible(jeti::particlesystem::Base*);
//    void addIfVisible(VerticalFlowText*, const VisibilityData&);

    void __createDamage();
    void __createExplosion();
    void __createJet();

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

    void __renderBackground(jeti::Render& render) const;
    void __renderStarPostEffect(jeti::Render& render) const;
    void __renderSpaceObjects(jeti::Render& render) const;
    void __renderSpaceObjectsMeta(jeti::Render& render) const;
    void __renderHUD(jeti::Render& render) const;
    void __renderExperiment(jeti::Render& render) const;


    void __render_DEPRECATED(jeti::Render&);
};

bool isRectOnVisibleScreenArea(const glm::vec3& center, const glm::vec3& size, const glm::vec2& screen_wc, float scale);
bool isRectOnVisibleScreenArea(const glm::vec2& center, const glm::vec2& size, const glm::vec2& screen_wc, float scale);
bool isPointOnVisibleScreenArea(const glm::vec2& p, const glm::vec2& screen_wc);

bool isPointInRect(const glm::vec2& p, const ceti::Rect& rect);
bool isPointInRect(const glm::vec3& p, const ceti::Rect& rect);
bool isObjectOnScreen(const glm::vec3&, const glm::vec3&, const glm::ivec2&, float);

} // namespace view


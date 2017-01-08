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

#include <vector>
#include <jeti/Render.hpp>
#include <ceti/descriptor/Collector.hpp>

#include <world/starsystem.hpp>

#include <map>

class StarSystemDrawable;

namespace model {
class Star;
class Asteroid;
class Planet;
//class Container;
} // namespace view

namespace core {
namespace model {
class Base;
} // namespace model
} // namespace core

namespace jeti {
class Camera;
namespace view {
class BaseView;
} // namespace view
} // namespace jeti

namespace view {
class Star;
class Asteroid;
class Planet;
//class Container;
} // namespace view


//class BlackHoleDrawable;
//class ShipDrawable;
//class SpaceStationDrawable;
//class SatelliteDrawable;
//class BulletDrawable;

/// effects
class LazerTraceEffect;
class ShockWaveEffect;
namespace jeti {
class BaseParticleSystem;
}
class VerticalFlowText;


namespace view {

struct VisibilityData
{
    struct VisibilityScreenData {
        glm::vec2 worldcoord;
        float scale = 1.0f;
    };
    struct VisibilityObserverData {
        glm::vec3 center;
        float radius = 0.0f;
    };
    VisibilityScreenData screen;
    VisibilityObserverData observer;
};

class Space
{
public:
    Space();
    ~Space();

    /// visible entities
    void addIfVisible(model::Star*, const VisibilityData&);
    void addIfVisible(model::Planet*, const VisibilityData&);
    void addIfVisible(model::Asteroid*, const VisibilityData&);
//    void addIfVisible(view::Container*, const VisibilityData&);
//    void addIfVisible(BulletDrawable*, const VisibilityData&);
//    void addIfVisible(BlackHoleDrawable*, const VisibilityData&);
//    void addIfVisible(ShipDrawable*, const VisibilityData&);
//    void addIfVisible(SpaceStationDrawable*, const VisibilityData&);
//    void addIfVisible(SatelliteDrawable*, const VisibilityData&);

    /// visible effects
//    void addIfVisible(ShockWaveEffect*, const VisibilityData&);
//    void addIfVisible(LazerTraceEffect*, const VisibilityData&);
//    void addIfVisible(jeti::BaseParticleSystem*, const VisibilityData&);
//    void addIfVisible(VerticalFlowText*, const VisibilityData&);

    void render(Starsystem*, jeti::Camera&);

private:
    /// visible entities
    std::vector<Star*> m_stars;
    std::vector<Planet*> m_planets;
    std::vector<Asteroid*> m_asteroids;
//    std::vector<view::Container*> m_containers;
//    std::vector<BulletDrawable*> m_bullets;
//    std::vector<BlackHoleDrawable*> m_wormholes;
//    std::vector<ShipDrawable*> m_ships;
//    std::vector<SatelliteDrawable*> m_satellites;
//    std::vector<SpaceStationDrawable*> m_spacestations;

    /// visible effects
//    std::vector<ShockWaveEffect*> m_shockwaves;
//    std::vector<LazerTraceEffect*> m_lazertraces;
//    std::vector<jeti::BaseParticleSystem*> m_particlesystems;
//    std::vector<VerticalFlowText*> m_texts;
    
    void __updateVisible(Starsystem* starsystem,
                  const meti::vec3& lookFrom,
                  const meti::vec3& lookTo,
                  float lookFar);

    void __render_NEW(jeti::Renderer&);
    void __render_NEW2(jeti::Renderer&);
    void __renderCollisionRadius(const jeti::Renderer&) const;
    void __renderAxis(const jeti::Renderer&) const;

    /// visible entities
    void __add(jeti::view::BaseView*);
    void __add(Star*);
    void __add(Planet*);
    void __add(Asteroid*);
    void __add(Container*);
//    void __add(BulletDrawable*);
//    void __add(BlackHoleDrawable*);
//    void __add(ShipDrawable*);
//    void __add(SpaceStationDrawable*);
//    void __add(SatelliteDrawable*);

    /// visible effects
    void __add(ShockWaveEffect*);
    void __add(LazerTraceEffect*);
    void __add(jeti::BaseParticleSystem*);
    void __add(VerticalFlowText*);

    void __loadResourcesFor(model::SpaceObject* model, jeti::view::BaseView* view);
    void __cache(model::SpaceObject*, jeti::view::BaseView*);

    void __clear();

    jeti::view::BaseView* __tryGetView(model::SpaceObject*);

    std::map<model::SpaceObject*, jeti::view::BaseView*> m_cache;
    [[warning("ugly, think how to make it better")]]
    std::map<jeti::view::BaseView*, model::SpaceObject*> m_cache2;

//    ceti::Collector<jeti::Mesh> m_meshCollector;
//    ceti::Collector<jeti::control::TextureOb> m_materialCollector;
    std::map<int_t, jeti::Mesh*> m_meshCollector;
    std::map<int_t, jeti::control::Material*> m_materialCollector;

//    ceti::Collector<jeti::control::TextureOb> m_materialCollector;
};

} // namespace view


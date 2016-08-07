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

#include <world/starsystem.hpp>
class StarSystemDrawable;

/// entities
class Star;

class StarDrawable;
class PlanetDrawable;
class AsteroidDrawable;
class BlackHoleDrawable;
class ShipDrawable;
class SpaceStationDrawable;
class SatelliteDrawable;
class ContainerDrawable;
class BulletDrawable;

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
        float scale;
    };
    struct VisibilityObserverData {
        glm::vec3 center;
        float radius;
    };
    VisibilityScreenData screen;
    VisibilityObserverData observer;
};

class Viewer
{
public:
    Viewer();
    ~Viewer();

    /// visible entities
    void addIfVisible(Star*, const VisibilityData&);
    void addIfVisible(PlanetDrawable*, const VisibilityData&);
    void addIfVisible(AsteroidDrawable*, const VisibilityData&);
    void addIfVisible(ContainerDrawable*, const VisibilityData&);
    void addIfVisible(BulletDrawable*, const VisibilityData&);
    void addIfVisible(BlackHoleDrawable*, const VisibilityData&);
    void addIfVisible(ShipDrawable*, const VisibilityData&);
    void addIfVisible(SpaceStationDrawable*, const VisibilityData&);
    void addIfVisible(SatelliteDrawable*, const VisibilityData&);

    /// visible effects
    void addIfVisible(ShockWaveEffect*, const VisibilityData&);
    void addIfVisible(LazerTraceEffect*, const VisibilityData&);
    void addIfVisible(jeti::BaseParticleSystem*, const VisibilityData&);
    void addIfVisible(VerticalFlowText*, const VisibilityData&);

    void renderSceneInSpace(Starsystem*, bool, bool, bool);

private:
    /// visible entities
    std::vector<StarDrawable*>         m_stars;
    std::vector<PlanetDrawable*>       m_planets;
    std::vector<AsteroidDrawable*>     m_asteroids;
    std::vector<ContainerDrawable*>    m_containers;
    std::vector<BulletDrawable*>       m_bullets;
    std::vector<BlackHoleDrawable*>    m_wormholes;
    std::vector<ShipDrawable*>         m_ships;
    std::vector<SatelliteDrawable*>    m_satellites;
    std::vector<SpaceStationDrawable*> m_spacestations;

    /// visible effects
    std::vector<ShockWaveEffect*>    m_shockwaves;
    std::vector<LazerTraceEffect*>   m_lazertraces;
    std::vector<jeti::BaseParticleSystem*> m_particlesystems;
    std::vector<VerticalFlowText*>   m_texts;
    
    void __renderInSpace_NEW(jeti::Renderer&, Starsystem*);
    void __renderCollisionRadius(const jeti::Renderer&) const;
    void __renderAxis(const jeti::Renderer&) const;

    /// visible entities
    void __add(StarDrawable*);
    void __add(PlanetDrawable*);
    void __add(AsteroidDrawable*);
    void __add(ContainerDrawable*);
    void __add(BulletDrawable*);
    void __add(BlackHoleDrawable*);
    void __add(ShipDrawable*);
    void __add(SpaceStationDrawable*);
    void __add(SatelliteDrawable*);

    /// visible effects
    void __add(ShockWaveEffect*);
    void __add(LazerTraceEffect*);
    void __add(jeti::BaseParticleSystem*);
    void __add(VerticalFlowText*);

    void __clear();
};

} // namespace view


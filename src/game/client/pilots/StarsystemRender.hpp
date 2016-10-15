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

#include <common/Base.hpp>
//#include <gui/Cursor.hpp>
//#include <pilots/Show.hpp>
//#include <jeti/Render.hpp>
#include <jeti/BaseView.hpp>

//class TurnTimer;

class Starsystem;
class Star;
class Planet;
class BlackHole;
class Asteroid;
class Vehicle;
class Npc;
class SpaceStation;
class Satellite;
class Ship;
class Container; 
class RocketBullet; 


// effects
class LazerTraceEffect;
class ShockWaveEffect;
namespace jeti {
class BaseParticleSystem;
}
class VerticalFlowText;

class SpaceObject;

//class RenderSpaceObject {
//    public:
//        RenderSpaceObject(SpaceObject* ob)
//            : m_ob(ob)
//        {

//        }

//        ~RenderSpaceObject() {}
//        bool inRect(const ceti::Rect& rect) {
//            return true;
//        }

//    private:
//        SpaceObject* m_ob;
//};


class StarsystemRender
{
    public:
        StarsystemRender();
        ~StarsystemRender();

    private:
        std::vector<jeti::view::Base*> m_objects;

        // VISIBLE ENTITY LIST
        std::vector<Star*>         visible_STAR_vec;
        std::vector<Planet*>       visible_PLANET_vec;
        std::vector<Asteroid*>     visible_ASTEROID_vec;
        std::vector<Container*>    visible_CONTAINER_vec;
        std::vector<RocketBullet*> visible_ROCKET_vec;
        std::vector<BlackHole*>    visible_BLACKHOLE_vec;
        std::vector<Ship*>         visible_SHIP_vec;
        std::vector<Satellite*>    visible_SATELLITE_vec;
        std::vector<SpaceStation*> visible_SPACESTATION_vec;

        //effects
        std::vector<ShockWaveEffect*>    visible_effect_SHOCKWAVE_vec;
        std::vector<LazerTraceEffect*>   visible_effect_LAZERTRACE_vec;
        std::vector<jeti::BaseParticleSystem*> visible_effect_PARTICLESYSTEM_vec;
        std::vector<VerticalFlowText*>   visible_text_DAMAGE_vec;
        //

        void RenderInSpace(Starsystem*, bool, bool, bool);
        void RenderInSpace_NEW(jeti::Renderer&, Starsystem*);
        void RenderCollisionRadius(const jeti::Renderer&) const;
        void RenderAxis(const jeti::Renderer&) const;

        void clearVisibleEntities();
        void addIfVisible(jeti::view::Base*);

//        void addIfVisible(Star*);
//        void addIfVisible(Planet*);
//        void addIfVisible(Asteroid*);
//        void addIfVisible(Container*);
//        void addIfVisible(RocketBullet*);
//        void addIfVisible(BlackHole*);
//        void addIfVisible(Vehicle*);

//        void addIfVisible(ShockWaveEffect*);
//        void addIfVisible(LazerTraceEffect*);
//        void addIfVisible(jeti::BaseParticleSystem*);
//        void addIfVisible(VerticalFlowText*);
};

bool isObjectOnScreen(const glm::vec3&, const glm::vec3&);
bool isObjectOnScreen(const glm::vec3&, float);
bool isPointOnScreen(const glm::vec2&);

bool isObjectWithinRadarRange(jeti::BaseParticleSystem*, Vehicle*);
bool isObjectWithinRadarRange(ShockWaveEffect*, Vehicle*);
bool isObjectWithinRadarRange(LazerTraceEffect*, Vehicle*);

bool isObjectWithinRange(const glm::vec3& c1, const glm::vec3& c2, float radius);




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

#include <core/common/Base.hpp>
#include <core/pilot/Show.hpp>

#include <client/gui/Cursor.hpp>

#include <jeti/Render.hpp>

#include <vector>

class TurnTimer;

namespace control {
class StarSystem;
} // namespace control


namespace view {
class Star;
class Planet;
class Asteroid;
class WormHole;
class SpaceStation;
class Satellite;
class Ship;
class Container;
class Bullet;
} // namespace view

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
class Bullet;

class LazerTraceEffect;
class ShockWaveEffect;

namespace jeti {
class BaseParticleSystem;
} // namespce jeti

class VerticalFlowText;


//struct UnresolvedDataPlayer
//{
//    int npc_id;
//    int starsystem_id;
//    glm::vec2 screen_pos;
//};


class Player
{
public:
    Player();
    ~Player();

    virtual void putChildrenToGarbage() const {}

    void setStarSystem(control::StarSystem* starsystem) { m_starsystem = starsystem; }
    control::StarSystem* starSystem() { return m_starsystem; }

    Show& show() { return m_show; }

    Npc* GetNpc() const { return m_npc; }
    gui::Cursor& cursor() { return m_cursor; }

    void BindNpc(Npc*);

    bool IsAbleToGetFullControlOnScanedVehicle(bool force_full_control = false) const;

    void RunSession(const TurnTimer&);

    void ForceStateMachineReset() const;

    void UpdatePostTransaction();
    void UpdatePostTransactionEvent(TurnTimer&);

private:
    Npc* m_npc = nullptr;

    gui::Cursor m_cursor;

    Show m_show;
    control::StarSystem* m_starsystem = nullptr;

    // VISIBLE ENTITY LIST
    std::vector<Star*>         visible_STAR_vec;
    std::vector<Planet*>       visible_PLANET_vec;
    std::vector<Asteroid*>     visible_ASTEROID_vec;
    std::vector<Container*>    visible_CONTAINER_vec;
    std::vector<Bullet*> visible_ROCKET_vec;
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
    
    void RenderInSpace(control::StarSystem*, bool, bool, bool);
    void RenderInSpace_NEW(jeti::Render&, control::StarSystem*);
    void RenderCollisionRadius(const jeti::Render&) const;
    void RenderAxis(const jeti::Render&) const;

    void SessionInSpace(control::StarSystem*, const TurnTimer&);
    void SessionInKosmoport();
    void SessionInNatureLand();

    void __manageClickEvent();
    void __clickOn(view::Bullet*);
    void __clickOn(view::Container*);
    void __clickOn(view::Satellite*);
    void __clickOn(view::Asteroid*);
    void __clickOn(view::Ship*);
    void __clickOn(view::WormHole*);
    void __clickOn(view::SpaceStation*);
    void __clickOn(view::Planet*);
    void __clickOn(view::Star*);
    void __navigate() const;

    friend class UserInput;
};







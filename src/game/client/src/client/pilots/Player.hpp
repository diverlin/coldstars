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

#include <core/Base.hpp>
#include <core/pilot/Show.hpp>

#include <client/gui/Cursor.hpp>

#include <jeti/Render.hpp>

#include <meti/VectorUtils.hpp>

#include <vector>

namespace control {
class Npc;
} // namespace control

class TurnTimer;

namespace view {
class Base;
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

class Player
{
public:
    Player();
    ~Player();

    Show& show() { return m_show; }

    const meti::vec3& position() const;
    float radius() const;

    control::Npc* npc() const { return m_npc; }
    gui::Cursor& cursor() { return m_cursor; }

    void setNpc(control::Npc* npc) { m_npc = npc; }

    bool IsAbleToGetFullControlOnScanedVehicle(bool force_full_control = false) const;

    void update(const jeti::Render&, view::Base* focusedView = nullptr);
    void RunSession(const TurnTimer&);

    void resetStateMachine() const;

    void UpdatePostTransaction();
    void UpdatePostTransactionEvent(TurnTimer&);

private:
    control::Npc* m_npc = nullptr;
    gui::Cursor m_cursor;
    Show m_show;

//    void RenderInSpace(control::StarSystem*, bool, bool, bool);
//    void RenderInSpace_NEW(jeti::Render&, control::StarSystem*);
//    void RenderCollisionRadius(const jeti::Render&) const;
//    void RenderAxis(const jeti::Render&) const;

//    void SessionInSpace(control::StarSystem*, const TurnTimer&);
//    void SessionInKosmoport();
//    void SessionInNatureLand();

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







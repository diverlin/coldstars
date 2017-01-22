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

#include <ai/Task.hpp>
#include <ai/MacroTaskManager.hpp>
#include <ai/MicroTaskManager.hpp>

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    void setNpc(Npc* npc) { m_npc = npc; }

    void setCurrentMacroTask(const Task&);
    void setCurrentMicroTask(const Task&);

    const MacroTaskManager& macroTaskManager() const { return m_macrotaskManager; }
    const MicroTaskManager& microTaskManager() const { return m_microtaskManager; }

    void updateInStaticInSpace();
    void updateInStaticInDock();
    void updateInDynamicInSpace();
    void updateInDynamicInDock();

    void reset(); // was private

private:
    Npc* m_npc = nullptr;

    MacroTaskManager m_macrotaskManager;
    MicroTaskManager m_microtaskManager;

    //friend void Player::ForceStateMachineReset() const;
}; 


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

        void SetNpcOwner(Npc* npc_owner) { this->npc_owner = npc_owner; }
        
        void SetCurrentMacroTask(const Task&);
        void SetCurrentMicroTask(const Task&);
        
        const MacroTaskManager& GetMacroTaskManager() const { return macrotask_manager; }
        const MicroTaskManager& GetMicroTaskManager() const { return microtask_manager; }
                
        void UpdateInStaticInSpace();    
        void UpdateInStaticInDock();    
        void UpdateInDynamicInSpace();            
        void UpdateInDynamicInDock();    
        
        void ForceReset(); // was private
        
    private:
        Npc* npc_owner = nullptr;
        
        MacroTaskManager macrotask_manager;
        MicroTaskManager microtask_manager;
                    
    //friend void Player::ForceStateMachineReset() const;
}; 


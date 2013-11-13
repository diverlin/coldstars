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

#include "StateMachine.hpp"

StateMachine::StateMachine() 
{
    npc_owner = nullptr;
}
        
StateMachine::~StateMachine() 
{}
        
void StateMachine::UpdateInStaticInSpace()
{
    if (macrotask_manager.GetScenario() != nullptr) 
    { 
        macrotask_manager.GetScenario()->UpdateInStaticInSpace(npc_owner); 
    }
    if (microtask_manager.GetScenario() != nullptr) 
    {
        if (microtask_manager.GetScenario()->Validate(npc_owner) == true)
        {
            microtask_manager.GetScenario()->UpdateInStaticInSpace(npc_owner); 
        }
        else
        {
            microtask_manager.GetScenario()->Exit(npc_owner);
            microtask_manager.Reset();
        }
    }
}

void StateMachine::UpdateInStaticInDock()
{
    if (macrotask_manager.GetScenario() != nullptr) 
    { 
        macrotask_manager.GetScenario()->UpdateInStaticInDock(npc_owner); 
    }
    if (microtask_manager.GetScenario() != nullptr) 
    {
        if (microtask_manager.GetScenario()->Validate(npc_owner) == true)
        {
            microtask_manager.GetScenario()->UpdateInStaticInDock(npc_owner); 
        }
        else
        {
            microtask_manager.GetScenario()->Exit(npc_owner);
            microtask_manager.Reset();
        }
    }
}

void StateMachine::UpdateInDynamicInSpace()
{
    if (microtask_manager.GetScenario() != nullptr)
    {
         microtask_manager.GetScenario()->UpdateInDynamicInSpace(npc_owner);
    }
}

void StateMachine::UpdateInDynamicInDock()
{
    if (microtask_manager.GetScenario() != nullptr)
    {
         microtask_manager.GetScenario()->UpdateInDynamicInDock(npc_owner);
    }
}
    
        
void StateMachine::SetCurrentMacroTask(const Task& macrotask)
{
    if (macrotask_manager.GetScenario() != nullptr)
    {
        macrotask_manager.GetScenario()->Exit(npc_owner);
        macrotask_manager.Reset();
    }
    
    macrotask_manager.SetTask(macrotask);
    macrotask_manager.GetScenario()->Enter(npc_owner);
}

                
void StateMachine::SetCurrentMicroTask(const Task& microtask)
{
    if (microtask_manager.GetScenario() != nullptr)
    {
        microtask_manager.GetScenario()->Exit(npc_owner);
        microtask_manager.Reset();
    }
    
    microtask_manager.SetTask(microtask);
    microtask_manager.GetScenario()->Enter(npc_owner);
}

void StateMachine::ForceReset()
{
    if (microtask_manager.GetScenario() != nullptr)
    {
        microtask_manager.GetScenario()->Exit(npc_owner);
        microtask_manager.Reset();
    }

    if (macrotask_manager.GetScenario() != nullptr)
    {    
        macrotask_manager.GetScenario()->Exit(npc_owner);
        macrotask_manager.Reset();
    }
}





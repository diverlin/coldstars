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

#include "MacroScenarioSelfSafety.hpp"
#include "../../../world/starsystem.hpp"
#include "../../../spaceobjects/Planet.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../ai/Task.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

MacroScenarioSelfSafety::MacroScenarioSelfSafety() 
{
    setTypeId(type::AISCENARIO::MACRO_SELFSAFETY_ID);
}

MacroScenarioSelfSafety::~MacroScenarioSelfSafety() 
{}

void MacroScenarioSelfSafety::UpdateInStaticInSpace(Npc* npc) const
{
    if (npc->starsystem()->conditionId() == ENTITY::STARSYSTEM::CONDITION::SAFE_ID)
    {
        if (npc->stateMachine().macroTaskManager().target()->type() != type::entity::PLANET_ID)
        { 
//            Task microtask(type::AISCENARIO::MICRO_DOCKING_ID, npc->planetForDocking()->id());
//            npc->stateMachine().setCurrentMicroTask(microtask);
        }
    }
    else
    {
        //if (npc->GetStateMachine().GetMacroTaskManager().GetTarget()->typeId() != type::entity::STARSYSTEM_ID)
        //{
            //if (npc->vehicle()->GetFailBackStarSystem() != nullptr)
            //{
                //Task microtask(type::AISCENARIO::MICRO_JUMP_ID, npc->vehicle()->GetFailBackStarSystem()->id());
                //npc->GetStateMachine().SetCurrentMicroTask(microtask);
            //}
        //}
    }        
}


std::string MacroScenarioSelfSafety::GetDescription(Npc* npc) const
{
    return "MacroScenarioSelfSafety";
}

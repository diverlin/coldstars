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
    type_id = TYPE::AISCENARIO::MACRO_SELFSAFETY_ID;
}

MacroScenarioSelfSafety::~MacroScenarioSelfSafety() 
{}

void MacroScenarioSelfSafety::UpdateInStaticInSpace(Npc* npc) const
{
    if (npc->starsystem()->GetConditionId() == ENTITY::STARSYSTEM::CONDITION::SAFE_ID)
    {
        if (npc->GetStateMachine().GetMacroTaskManager().GetTarget()->typeId() != TYPE::ENTITY::PLANET_ID)
        { 
            Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, npc->GetPlanetForDocking()->id());
            npc->GetStateMachine().SetCurrentMicroTask(microtask);
        }
    }
    else
    {
        //if (npc->GetStateMachine().GetMacroTaskManager().GetTarget()->typeId() != TYPE::ENTITY::STARSYSTEM_ID)
        //{
            //if (npc->GetVehicle()->GetFailBackStarSystem() != nullptr)
            //{
                //Task microtask(TYPE::AISCENARIO::MICRO_JUMP_ID, npc->GetVehicle()->GetFailBackStarSystem()->id());
                //npc->GetStateMachine().SetCurrentMicroTask(microtask);
            //}
        //}
    }        
}


std::string MacroScenarioSelfSafety::GetDescription(Npc* npc) const
{
    return "MacroScenarioSelfSafety";
}

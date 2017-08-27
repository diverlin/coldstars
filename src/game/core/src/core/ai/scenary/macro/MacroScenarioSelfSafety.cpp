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
#include "../../../ai/StateMachine.hpp"
#include "../../../ai/Task.hpp"

#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Planet.hpp>

MacroScenarioSelfSafety::MacroScenarioSelfSafety() 
{
    setTypeId(ai::type::MACRO_SELFSAFETY);
}

MacroScenarioSelfSafety::~MacroScenarioSelfSafety() 
{}

void MacroScenarioSelfSafety::UpdateInStaticInSpace(control::Npc* npc) const
{
    assert(false);
//    if (npc->starsystem()->conditionId() == ENTITY::STARSYSTEM::CONDITION::SAFE)
//    {
//        if (npc->stateMachine().macroTaskManager().target()->type() != entity::Type::PLANET)
//        {
////            Task microtask(type::AISCENARIO::MICRO_DOCKING, npc->planetForDocking()->id());
////            npc->stateMachine().setCurrentMicroTask(microtask);
//        }
//    }
//    else
//    {
//        //if (npc->GetStateMachine().GetMacroTaskManager().GetTarget()->typeId() != entity::Type::STARSYSTEM)
//        //{
//            //if (npc->vehicle()->GetFailBackStarSystem() != nullptr)
//            //{
//                //Task microtask(type::AISCENARIO::MICRO_JUMP, npc->vehicle()->GetFailBackStarSystem()->id());
//                //npc->GetStateMachine().SetCurrentMicroTask(microtask);
//            //}
//        //}
//    }
}


std::string MacroScenarioSelfSafety::GetDescription(control::Npc* npc) const
{
    return "MacroScenarioSelfSafety";
}

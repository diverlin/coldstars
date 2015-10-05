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

#include "MacroScenarioStarSystemDefence.hpp"
#include "../../../pilots/Npc.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>

#include "../../Task.hpp"
#include "../../../world/starsystem.hpp"
#include "../../../ai/StateMachine.hpp"

#include <common/RaceDescriptors.hpp>
#include <common/Global.hpp>


MacroScenarioStarSystemDefence::MacroScenarioStarSystemDefence() 
{
    type_id = TYPE::AISCENARIO::MACRO_STARSYSTEMDEFENCE_ID;
}

/*virtual*/
MacroScenarioStarSystemDefence::~MacroScenarioStarSystemDefence() 
{}

/*virtual*/
void MacroScenarioStarSystemDefence::Enter(Npc* npc) const
{    
    Logger::Instance().Log("npc_id=" + std::to_string(npc->id()) + " ENTER MacroScenarioStarSystemDefence");
}

/*virtual*/
void MacroScenarioStarSystemDefence::UpdateInStaticInSpace(Npc* npc) const
{
    StarSystem* target_starsystem = npc->GetStateMachine().GetMacroTaskManager().GetTarget()->starsystem();
    if (npc->starsystem()->id() != target_starsystem->id())
    {
        if (npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() != TYPE::AISCENARIO::MICRO_JUMP_ID)
        {
            Task microtask(TYPE::AISCENARIO::MICRO_JUMP_ID, target_starsystem->id());
            npc->GetStateMachine().SetCurrentMicroTask(microtask);
            
            return;
        }
    }
    else
    {
        if (target_starsystem->conditionId() != ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID)
        {
            if (npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() != TYPE::AISCENARIO::MICRO_DESTROY_ID)
            {           
                Vehicle* target_vehicle = npc->GetObservation().GetRandVisibleVehicle(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
                if (target_vehicle != nullptr) {
                    Task microtask(TYPE::AISCENARIO::MICRO_DESTROY_ID, target_vehicle->id());
                    npc->GetStateMachine().SetCurrentMicroTask(microtask);
                    
                    return;
                }
                else
                {
                    Task microtask(TYPE::AISCENARIO::MICRO_EXPLORATION_ID, NONE_ID);
                    npc->GetStateMachine().SetCurrentMicroTask(microtask);
                    
                    return;
                }
            }
        }
    }
}

/*virtual*/
void MacroScenarioStarSystemDefence::Exit(Npc* npc) const
{
    Logger::Instance().Log("npc_id=" + std::to_string(npc->id()) + " EXIT MacroScenarioStarSystemDefence");
}


/*virtual*/
std::string MacroScenarioStarSystemDefence::GetDescription(Npc* npc) const
{
    return "MacroScenarioStarSystemDefence: ss_id = " + std::to_string(npc->GetStateMachine().GetMacroTaskManager().GetTarget()->id());
}

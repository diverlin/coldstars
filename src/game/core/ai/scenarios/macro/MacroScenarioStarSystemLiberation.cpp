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


#include "MacroScenarioStarSystemLiberation.hpp"

#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>

#include "../../../world/starsystem.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../ai/Task.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

#include <descriptors/RaceDescriptors.hpp>
#include <common/Global.hpp>


MacroScenarioStarSystemLiberation::MacroScenarioStarSystemLiberation() 
{
    setTypeId(type::AISCENARIO::MACRO_STARSYSTEMLIBERATION_ID);
}

/*virtual*/
MacroScenarioStarSystemLiberation::~MacroScenarioStarSystemLiberation() 
{}

/*virtual*/
void MacroScenarioStarSystemLiberation::enter(Npc* npc) const
{    
    LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MacroScenarioStarSystemLiberation");
}

/*virtual*/
void MacroScenarioStarSystemLiberation::UpdateInStaticInSpace(Npc* npc) const
{
    Starsystem* target_starsystem = npc->stateMachine().macroTaskManager().target()->starsystem();
    if (npc->starsystem()->id() != target_starsystem->id())
    {
        if (npc->stateMachine().microTaskManager().task().GetScenarioTypeId() != type::AISCENARIO::MICRO_JUMP_ID)
        {
            Task microtask(type::AISCENARIO::MICRO_JUMP_ID, target_starsystem->id());
            npc->stateMachine().setCurrentMicroTask(microtask);
            
            return;
        }
    }
    else
    {
        if (target_starsystem->conditionId() != ENTITY::STARSYSTEM::CONDITION::SAFE_ID)
        {
            if (npc->stateMachine().microTaskManager().task().GetScenarioTypeId() != type::AISCENARIO::MICRO_DESTROY_ID)
            {
                Vehicle* target_vehicle = npc->observation().GetRandVisibleVehicle(core::global::get().raceDescriptors().getRaces(type::KIND::EVIL));
                if (target_vehicle != nullptr) {
                    Task microtask(type::AISCENARIO::MICRO_DESTROY_ID, target_vehicle->id());
                    npc->stateMachine().setCurrentMicroTask(microtask);
                    
                    return;
                }
                else
                {
                    Task microtask(type::AISCENARIO::MICRO_EXPLORATION_ID);
                    npc->stateMachine().setCurrentMicroTask(microtask);
                    
                    return;
                }
            }
        }
        //else
        //{
            //npc->GetStateMachine().GetTaskManager().GetTask().SetResult(SUCCESS_ID);
            //return;
        //}
    }        
}

/*virtual*/
void MacroScenarioStarSystemLiberation::exit(Npc* npc) const
{
    LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MacroScenarioStarSystemLiberation");
}

/*virtual*/
std::string MacroScenarioStarSystemLiberation::GetDescription(Npc* npc) const
{
    return "MacroScenarioStarSystemLiberation: ss_id = " + std::to_string(npc->stateMachine().macroTaskManager().target()->id());
}

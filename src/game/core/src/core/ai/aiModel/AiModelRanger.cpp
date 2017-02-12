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

#include "AiModelRanger.hpp"
#include "../Task.hpp"
#include "../../common/constants.hpp"
#include "../../world/starsystem.hpp"
#include "../../ai/StateMachine.hpp"

AiModelRanger::AiModelRanger() 
{
    type_id = AIMODEL::RANGER;
}

AiModelRanger::~AiModelRanger() 
{}

void AiModelRanger::UpdateInStatic(Npc* npc) const
{
    assert(false);
//    if (npc->stateMachine().macroTaskManager().scenario() == nullptr)
//    {
//        Starsystem* target_starsystem = nullptr;
//        target_starsystem = npc->closestStarSystem(ENTITY::STARSYSTEM::CONDITION::WAR);
//        if (target_starsystem == nullptr)
//        {
//            target_starsystem = npc->closestStarSystem(ENTITY::STARSYSTEM::CONDITION::CAPTURED);
//        }

//        if (target_starsystem != nullptr)
//        {
//            Task macrotask(type::AISCENARIO::MACRO_STARSYSTEMLIBERATION, target_starsystem->id());
//            npc->stateMachine().setCurrentMacroTask(macrotask);
//        }
//    }
}

std::string AiModelRanger::GetDescription(Npc* npc) const
{
    return "AiModelRanger";
}

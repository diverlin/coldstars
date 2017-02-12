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

#include "AiModelConqueror.hpp"
#include "../Task.hpp"
#include "../../common/constants.hpp"
#include "../../world/starsystem.hpp"
#include "../../ai/StateMachine.hpp"

AiModelConqueror::AiModelConqueror() 
{
    type_id = AIMODEL::CONQUEROR;
}

AiModelConqueror::~AiModelConqueror() 
{}

void AiModelConqueror::UpdateInStatic(Npc* npc) const
{
    assert(false);
//    if (npc->stateMachine().macroTaskManager().scenario() != nullptr)
//    {
//        if (npc->stateMachine().macroTaskManager().scenario()->typeId() == type::AISCENARIO::MACRO_WARRIORRECRUTE)
//        {
//            // recrute warriors able to jump into target starsystem
//            // apply macroscenario invasion for each in group
            
//            return;
//        }
//    }
//    else
//    {
//        Task macrotask(type::AISCENARIO::MACRO_STARSYSTEMDEFENCE, npc->starsystem()->id());
//            npc->stateMachine().setCurrentMacroTask(macrotask);
            
//            return;
//    }
}

std::string AiModelConqueror::GetDescription(Npc* npc) const
{
    return "AiModelConqueror";
}

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

#include "AiModelTrader.hpp"
#include "../Task.hpp"
#include "../StateMachine.hpp"

AiModelTrader::AiModelTrader() 
{
    type_id = AIMODEL::TRADER_ID;
}

AiModelTrader::~AiModelTrader() 
{}

void AiModelTrader::UpdateInStatic(Npc* npc) const
{
    if (npc->GetStateMachine().GetMacroTaskManager().GetScenario() == nullptr)
        {
            Task macrotask(TYPE::AISCENARIO::MACRO_GOODSTRADING_ID);
            npc->GetStateMachine().SetCurrentMacroTask(macrotask);
        }            
}

std::string AiModelTrader::GetDescription(Npc* npc) const
{
    return "AiModelTrader";
}

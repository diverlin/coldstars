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

#include "MicroScenarioJump.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include "../../../spaceobjects/Vehicle.hpp"

#include "../../../world/starsystem.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../pilots/Npc.hpp"

MicroScenarioJump::MicroScenarioJump()
{
    setTypeId(ai::type::MICRO_JUMP_ID);
}

/* virtual */
MicroScenarioJump::~MicroScenarioJump()
{}
        
/* virtual */
void MicroScenarioJump::enter(Npc* npc) const
{
    assert(false);
//    LOG("vehicle_id/npc_id="+std::to_string(npc->vehicle()->id())+"/"+std::to_string(npc->id())+"  ENTER MicroScenarioJump");
    
//    npc->vehicle()->driveComplex().SetTarget(npc->stateMachine().microTaskManager().target()->starsystem(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);
}

/* virtual */
bool MicroScenarioJump::Validation(Npc* npc) const
{
    assert(false);
//    if (npc->vehicle()->starsystem()->id() != npc->stateMachine().microTaskManager().target()->starsystem()->id())
//    {
//        return true;
//    }
    
    return false;
}

/* virtual */
void MicroScenarioJump::UpdateInStaticInSpace(Npc* npc) const
{
    // check if still able to jump
}

/* virtual */
void MicroScenarioJump::UpdateInDynamicInSpace(Npc* npc) const
{
        assert(false);
//         if (npc->vehicle()->driveComplex().CheckTargetEchievement() == true)
//         {
//             VEHICLE_SPECIAL_ACTION_TYPE action_id = npc->vehicle()->GetSpecialActionId();
//             if ( (action_id != VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID) and (action_id != VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID) )
//             {
//                 npc->vehicle()->SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID);
//             }
//         }
}

/* virtual */
void MicroScenarioJump::exit(Npc* npc) const
{
//    LOG("vehicle_id/npc_id="+std::to_string(npc->vehicle()->id())+"/"+std::to_string(npc->id())+" EXIT MicroScenarioJump");
}

/* virtual */
std::string MicroScenarioJump::GetDescription(Npc* npc) const
{
    assert(false);
    //return "JUMP to ss_id = " + std::to_string( npc->stateMachine().microTaskManager().target()->id());
}

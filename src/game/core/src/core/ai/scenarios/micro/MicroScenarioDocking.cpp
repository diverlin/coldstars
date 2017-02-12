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

#include "MicroScenarioDocking.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../pilots/Npc.hpp"

MicroScenarioDocking::MicroScenarioDocking()
{
    setTypeId(ai::type::MICRO_DOCKING);
}

/* virtual */
MicroScenarioDocking::~MicroScenarioDocking()
{}

/* virtual */
void MicroScenarioDocking::enter(Npc* npc) const
{    
    assert(false);
//    npc->vehicle()->driveComplex().SetTarget(npc->stateMachine().microTaskManager().target(), NAVIGATOR_ACTION::DOCKING);

//    LOG( "npc_id="+std::to_string(npc->id())+" ENTER MicroScenarioDocking");
}

/* virtual */
bool MicroScenarioDocking::Validate(Npc* npc) const
{
    assert(false);
    //    if (npc->vehicle()->place() == type::place::KOSMOS)
//    {
//        return true;
//    }

    return false;
}

/* virtual */
void MicroScenarioDocking::UpdateInStaticInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioDocking::UpdateInDynamicInSpace(Npc* npc) const
{
        assert(false);

//    if (npc->vehicle()->driveComplex().CheckTargetEchievement() == true)
//    {
//        if (npc->vehicle()->driveComplex().GetDockingPermission() == true)
//        {
//            if (npc->vehicle()->GetSpecialActionId() != VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING)
//            {
//                npc->vehicle()->SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING);
//            }
//        }
//        else
//        {
//            // wait or reset
//        }
//    }
}

/* virtual */
void MicroScenarioDocking::exit(Npc* npc) const 
{
    assert(false);
    //LOG("npc_id="+std::to_string( npc->id())+" EXIT MicroScenarioDocking");
}

/* virtual */
std::string MicroScenarioDocking::GetDescription(Npc* npc) const
{
    assert(false);
    //return "MicroScenarioDocking to ob_id = " + std::to_string( npc->stateMachine().microTaskManager().target()->id());
}

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
#include "../../../common/Logger.hpp"
//#include <ceti/StringUtils.hpp>
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../pilots/Npc.hpp"

MicroScenarioDocking::MicroScenarioDocking()
{
    type_id = TYPE::AISCENARIO::MICRO_DOCKING_ID;
}

/* virtual */
MicroScenarioDocking::~MicroScenarioDocking()
{}

/* virtual */
void MicroScenarioDocking::Enter(Npc* npc) const
{    
    npc->GetVehicle()->GetComplexDrive().SetTarget(npc->GetStateMachine().GetMicroTaskManager().GetTarget(), NAVIGATOR_ACTION::DOCKING_ID);

    #if AISCENARIO_LOG_ENABLED == 1 
    Logger::Instance().Log( "npc_id="+std::to_string(npc->id())+" ENTER MicroScenarioDocking", 1);
    #endif
}

/* virtual */
bool MicroScenarioDocking::Validate(Npc* npc) const
{
    if (npc->GetVehicle()->placeTypeId() == TYPE::PLACE::SPACE_ID)
    {
        return true;
    }

    return false;
}

/* virtual */
void MicroScenarioDocking::UpdateInStaticInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioDocking::UpdateInDynamicInSpace(Npc* npc) const
{
         if (npc->GetVehicle()->GetComplexDrive().CheckTargetEchievement() == true)
         {
             if (npc->GetVehicle()->GetComplexDrive().GetDockingPermission() == true)
             {
                 if (npc->GetVehicle()->GetSpecialActionId() != VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID)
                 {
                     npc->GetVehicle()->SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID);
                 }
             }
             else
             {
                 // wait or reset
             }
         }
}

/* virtual */
void MicroScenarioDocking::Exit(Npc* npc) const 
{
    #if AISCENARIO_LOG_ENABLED == 1 
    Logger::Instance().Log("npc_id="+std::to_string( npc->id())+" EXIT MicroScenarioDocking", 1);
    #endif
}

/* virtual */
std::string MicroScenarioDocking::GetDescription(Npc* npc) const
{
    return "MicroScenarioDocking to ob_id = " + std::to_string( npc->GetStateMachine().GetMicroTaskManager().GetTarget()->id());
}

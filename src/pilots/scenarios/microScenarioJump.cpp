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


MicroScenarioJump :: MicroScenarioJump()
{}


MicroScenarioJump :: ~MicroScenarioJump()
{}
		
void MicroScenarioJump :: enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex()->setTarget(npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetStarSystem(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);
	printf("npc_id = %i, is GOING to MicroScenarioJump from ss_id = %i to ss_id = %i\n", npc->GetId(), npc->GetStarSystem()->GetId(), npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}

void MicroScenarioJump :: update_inStatic(Npc* _npc) const
{
	// check if still able to jump
}

void MicroScenarioJump :: update_inDynamic(Npc* npc) const
{
     	if (npc->GetVehicle()->GetDriveComplex()->checkEchievement() == true)
     	{
                npc->GetVehicle()->HyperJumpEvent();
     	        printf("npc id = %i, jumpEvent()\n", npc->GetId());
     	}
}

void MicroScenarioJump :: exit(Npc* npc) const
{
	printf("npc_id = %i, FINISH MicroScenarioJump from ss_id = %i to ss_id = %i\n", npc->GetId(), npc->GetStarSystem()->GetId(), npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}


std::string MicroScenarioJump :: getDescription(Npc* npc) const
{
	return "JUMP to ss_id = " + int2str( npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}

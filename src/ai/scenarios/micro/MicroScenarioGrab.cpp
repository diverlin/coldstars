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


MicroScenarioGrab::MicroScenarioGrab()
{}


MicroScenarioGrab::~MicroScenarioGrab()
{}
		
void MicroScenarioGrab::Enter(Npc* npc) const
{	
	printf("npc_id = %i, STARTS MicroScenarioGrab item id = %i\n", npc->GetId(), npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetId());
}

void MicroScenarioGrab::UpdateInStatic(Npc* npc) const
{
              
        //for (unsigned int i = 0; i < npc->GetObservation()->visible_MINERAL_vec.size(); i++)
        //{                	
		//if ( npc->GetObservation()->visible_MINERAL_vec[i].dist < npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->GetRadius() )
                //{                                       
                	//npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(npc->GetObservation()->visible_MINERAL_vec[i].mineral);
                //}
                //else
                //{
                	//break;
                //}
        //}
        
        //npc->GetVehicle()->GetDriveComplex()->setTarget(npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);

}

void MicroScenarioGrab::UpdateInDynamic(Npc* npc) const
{
        /*
	GrappleEquipment* grapple_equipment = npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment();
        grapple_equipment->ValidateTargets();  
                
        for (unsigned int i = 0; i < grapple_equipment->target_vec.size(); i++)
        {	
               	grapple_equipment->target_vec[i]->MovingByExternalForce(npc->GetVehicle()->GetPoints().GetCEnter(), grapple_equipment->GetStrength());        	
       	
       		float dist = distBetweenPoints(npc->GetVehicle()->GetPoints().GetCEnter(), grapple_equipment->target_vec[i]->GetPoints().GetCEnter()); 
       		if (dist < npc->GetVehicle()->GetCollisionRadius()/10)
       		{
       			//if (grapple_equipment->target_vec[i]->GetTypeId() == ENTITY::MINERAL_ID)
       			//{
       				//GoodsPack* goodsPack = GetNewGoodsPack(ENTITY::MINERAL_ID);
       				//goodsPack->Increase(grapple_equipment->target_vec[i]->GetMass());
       				//ItemSlot* slot = npc->GetVehicle()->GetEmptyOtsecSlot();
       				//if (slot != NULL)
       				//{
       					//slot->InsertItem(goodsPack);
       					//grapple_equipment->AddToRemoveQueue(grapple_equipment->target_vec[i]);

       					//npc->GetStarSystem()->AddToRemoveFromOuterSpaceQueue((Mineral*)grapple_equipment->target_vec[i]);  
       				//}			
       			//}
        			
       			//if (grapple_equipment->target_vec[i]->GetTypeId() == ENTITY::CONTAINER_ID)
       			//{
       				//ItemSlot* slot = npc->GetVehicle()->GetEmptyOtsecSlot();
       				//if (slot != NULL)
       				//{
       					//slot->ExtractItemFromContainer((Container*)grapple_equipment->target_vec[i]);
       					//grapple_equipment->AddToRemoveQueue(grapple_equipment->target_vec[i]);

       					//npc->GetStarSystem()->AddToRemoveFromOuterSpaceQueue((Container*)grapple_equipment->target_vec[i]);  
       				//}	
       			//}
        	}
        }
        */
}

void MicroScenarioGrab::Exit(Npc* npc) const
{
	printf("npc_id = %i, ends MicroScenarioGrab\n", npc->GetId());
}


std::string MicroScenarioGrab::GetDescription(Npc* npc) const 
{
	return "GRAB to ob id = %i\n" + int2str(npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetId());
}

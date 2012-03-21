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


MicroScenarioGrab :: MicroScenarioGrab()
{}


MicroScenarioGrab :: ~MicroScenarioGrab()
{}
		
void MicroScenarioGrab :: Enter(Npc* npc) const
{	
	printf("npc_id = %i, STARTS MicroScenarioGrab item id = %i\n", npc->getId(), npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getId());
}

void MicroScenarioGrab :: update_inStatic(Npc* npc) const
{
              
        for (unsigned int i = 0; i < npc->getObservation()->visible_MINERAL_vec.size(); i++)
        {                	
		if ( npc->getObservation()->visible_MINERAL_vec[i].dist < npc->getVehicle()->getGrappleSlot()->getGrappleEquipment()->getRadius() )
                {                                       
                	npc->getVehicle()->getGrappleSlot()->getGrappleEquipment()->addTarget(npc->getObservation()->visible_MINERAL_vec[i].mineral);
                }
                else
                {
                	break;
                }
        }
        
        npc->getVehicle()->getDriveComplex()->setTarget(npc->getStateMachine()->getCurrentMicroTask()->getTarget(), FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID);
}

void MicroScenarioGrab :: update_inDynamic(Npc* npc) const
{
	GrappleEquipment* grapple_equipment = npc->getVehicle()->getGrappleSlot()->getGrappleEquipment();
        grapple_equipment->validateTargets();  
                
        for (unsigned int i = 0; i < grapple_equipment->target_vec.size(); i++)
        {	
               	grapple_equipment->target_vec[i]->movingByExternalForce(npc->getVehicle()->getPoints()->getCenter(), grapple_equipment->getStrength());        	
       	
       		float dist = distBetweenPoints(npc->getVehicle()->getPoints()->getCenter(), grapple_equipment->target_vec[i]->getPoints()->getCenter()); 
       		if (dist < npc->getVehicle()->getCollisionRadius()/10)
       		{
       			if (grapple_equipment->target_vec[i]->getTypeId() == MINERAL_ID)
       			{
       				GoodsPack* goodsPack = getNewGoodsPack(MINERAL_ID);
       				goodsPack->increase(grapple_equipment->target_vec[i]->getMass());
       				ItemSlot* slot = npc->getVehicle()->getEmptyOtsecSlot();
       				if (slot != NULL)
       				{
       					slot->insertItem(goodsPack);
       					grapple_equipment->addToRemoveQueue(grapple_equipment->target_vec[i]);

       					npc->getStarSystem()->addToRemoveFromOuterSpaceQueue((Mineral*)grapple_equipment->target_vec[i]);  
       				}			
       			}
        			
       			if (grapple_equipment->target_vec[i]->getTypeId() == CONTAINER_ID)
       			{
       				ItemSlot* slot = npc->getVehicle()->getEmptyOtsecSlot();
       				if (slot != NULL)
       				{
       					slot->extractContainer((Container*)grapple_equipment->target_vec[i]);
       					grapple_equipment->addToRemoveQueue(grapple_equipment->target_vec[i]);

       					npc->getStarSystem()->addToRemoveFromOuterSpaceQueue((Container*)grapple_equipment->target_vec[i]);  
       				}	
       			}
        	}
        }
}

void MicroScenarioGrab :: Exit(Npc* npc) const
{
	printf("npc_id = %i, ends MicroScenarioGrab\n", npc->getId());
}


std::string MicroScenarioGrab :: getDescription(Npc* npc) const 
{
	return "GRAB to ob id = %i\n" + int2str(npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getId());
}

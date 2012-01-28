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
		
void MicroScenarioGrab :: Enter(Npc* _npc) const
{	
	printf("npc_id = %i, STARTS MicroScenarioGrab item id = %i\n", _npc->getId(), _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getObId());
}

void MicroScenarioGrab :: update_inStatic(Npc* _npc) const
{
              
        for (unsigned int i = 0; i < _npc->observation->visible_MINERAL_vec.size(); i++)
        {                	
		if ( _npc->observation->visible_MINERAL_vec[i].dist < _npc->getShip()->grapple_slot.getGrappleEquipment()->getRadius() )
                {                                       
                	_npc->getShip()->grapple_slot.getGrappleEquipment()->add(_npc->observation->visible_MINERAL_vec[i].mineral);
                }
                else
                {
                	break;
                }
        }
        
        _npc->getShip()->getNavigator()->setTarget(_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getNpc()->getShip(), FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID );
}

void MicroScenarioGrab :: update_inDynamic(Npc* _npc) const
{
        //_npc->getShip()->grapple_slot.getGrappleEquipment()->validationTargets();  
                
        //for (unsigned int i = 0; i < _npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec.size(); i++)
        //{	//printf("blablabla\n");
                //if (_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getValid() == true)
                //{
                	////printf("blablabla\n");
                       	//_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->moveExternalyToPosition(_npc->getShip()->getPoints()->getCenter());        	
       	
        		//float dist = distBetweenPoints(_npc->getShip()->getPoints()->getCenter(), *_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getpCenter() ); 
        		//if (dist < _npc->getShip()->getCollisionRadius()/10)
        		//{
        			//if (_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getObTypeId() == MINERAL_ID)
        			//{
        				//GoodsPack* _goodsPack = createGoodsPack(MINERAL_ID, vec2f (0, 0));
        				//_goodsPack->increase(_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->getMass());
        				//ItemSlot* _slot = _npc->getShip()->getEmptyOtsecSlot();
        				//if (_slot != NULL)
        				//{
        					//_slot->insertGoods(_goodsPack);
        					//_npc->getStarSystem()->killMineralById(_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getObId());   
        					//_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        				//}			
        			//}
        			
        			//if (_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getObTypeId() == CONTAINER_ID)
        			//{
        				//_npc->getStarSystem()->removeContainer(_npc->getShip()->grapple_slot.getGrappleEquipment()->target_vec[i]->getObId());
        			//}
        		//}
        	//}
        //}
}

void MicroScenarioGrab :: Exit(Npc* _npc) const
{
	printf("npc_id = %i, ends MicroScenarioGrab\n", _npc->getId());
}


std::string MicroScenarioGrab :: getDescription(Npc* _npc) const 
{
	return "GRAB to ob id = %i\n" + int2str( _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getObId());
}

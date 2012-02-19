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


DockingStation :: DockingStation(int race_id)
{
	this->race_id = race_id;
	
	land      = NULL;
	kosmoport = NULL;
}

DockingStation :: ~DockingStation()
{}
    
void DockingStation :: createInternals()
{
      	if (race_id != NONE_ID) 
      	{ 
      		createKosmoport(); 
      	}
        else
        { 
        	createLand(); 
        }
}

		
Kosmoport* DockingStation :: getKosmoport() { return kosmoport; }
Land* DockingStation :: getLand()           { return land; }
                

void DockingStation :: update_inSpace_inDynamic()
{}
  


void DockingStation :: update_inSpace_inStatic()
{      
     	if (race_id != NONE_ID) 
     	{ 
     		kosmoport->ai(); 
     	}
        else 
        { 
        	land->ai(); 
        }    	
}
         

void DockingStation :: updateInfo()
{
	//info.clear();

    	//info.addTitleStr("PLANET");
    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->getId()));
    	//info.addNameStr("population:");  info.addValueStr(int2str(population));
}


void DockingStation :: renderInfo()
{  
     	//drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y);
}

        
void DockingStation :: createKosmoport() { kosmoport = new Kosmoport(RACE_0_ID); }
void DockingStation :: createLand()      { land      = new Land(); }


//// ******* TRANSITION ******* 
void DockingStation :: launchingProcedure()
{
         for (unsigned int i = 0; i<NPC_launching_vec.size(); i++)
         {
         	NPC_launching_vec[i]->getVehicle()->launchingEvent();
         }
              
         NPC_launching_vec.clear();  
}

void DockingStation :: addToLaunchingQueue(Npc* _npc)
{
         NPC_launching_vec.push_back(_npc);
}
		
                
bool DockingStation :: add(Ship* _ship)
{
     	if (race_id != NONE_ID)
        {
                return kosmoport->addShip(_ship);
        }
     	else
        {
                return land->addShip(_ship);
        }
}

bool DockingStation :: add(Npc* _npc)
{
     	if (race_id != NONE_ID)
        {       
                return kosmoport->addNpc(_npc);
        }
     	else
        {
                return land->addNpc(_npc);
        }
}

bool DockingStation :: removeShipById(int _id)
{
     	if (race_id != NONE_ID)
     	{
         	return kosmoport->removeShip(_id);
        }
        else
     	{
         	return land->removeShip(_id);
        }
}

bool DockingStation :: removeNpcById(int _id)
{
     	if (race_id != NONE_ID)
     	{
         	return kosmoport->removeNpc(_id);
        }
        else
     	{
         	return land->removeNpc(_id);
        }
}
//// ******* TRANSITION ******* 



bool DockingStation :: getPermissionToLand() const
{
     	if (race_id != NONE_ID)
     	{
        	if (kosmoport->getAngar()->getNumFreelandingArea() > 0) 
        	{ 
        		return true; 
        	}
        	else 
        	{ 
        		return false; 
        	}       
     	}
     	else 
     	{
        	return true;
        }
}

        


DockingStation* getNewDockingStation(int race_id)
{
        DockingStation* docking_station = new DockingStation(race_id);
    			     
        return docking_station;        
}

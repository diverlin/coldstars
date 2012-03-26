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


GarbageEntities :: GarbageEntities()
{}

GarbageEntities :: ~GarbageEntities()
{}
         
         
void GarbageEntities :: add(BaseGameEntity* entitiy) 
{
	entities_vec.push_back(entitiy);
}

	
void GarbageEntities :: clear()
{  
    	for(unsigned int i = 0; i < entities_vec.size(); i++)
    	{ 
		delete entities_vec[i];
		entities_vec[i] = NULL; 
    	}
    	entities_vec.clear();
}

//void GarbageEntities :: clear()
//{  
    	//for(unsigned int i = 0; i < entities_vec.size(); i++)
    	//{ 
    		//switch(entities_vec[i]->getTypeId())
    		//{
    			//case SHIP_ID:      { delete (Ship*)entities_vec[i]; break; }
    			//case NPC_ID:       { delete (Npc*)entities_vec[i]; break; }
    			//case ROCKET_BULLET_ID:    { delete (RocketBullet*)entities_vec[i]; break; }
    			//case ASTEROID_ID:  { delete (Asteroid*)entities_vec[i]; break; }
    			//case MINERAL_ID:   { delete (Mineral*)entities_vec[i]; break; }
    			//case CONTAINER_ID: { delete (Container*)entities_vec[i]; break; }
    		//}
       		
    	//}
    	//entities_vec.clear();
//}

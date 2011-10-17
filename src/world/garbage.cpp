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


Garbage :: Garbage()
{}

Garbage :: ~Garbage()
{}
         
         
void Garbage :: add(Ship* _ship) 
{
	SHIP_vec.push_back(_ship);
}

void Garbage :: add(Npc* _npc)
{
	NPC_vec.push_back(_npc);
}

void Garbage :: add(Asteroid* _asteroid)
{
	ASTEROID_vec.push_back(_asteroid);
}

void Garbage :: add(Mineral* _mineral)
{
	MINERAL_vec.push_back(_mineral);
}

void Garbage :: add(Container* _container)
{
	CONTAINER_vec.push_back(_container);
}

void Garbage :: add(RocketBullet* _rocket)
{
	ROCKET_vec.push_back(_rocket);
}		
		
		
void Garbage :: clear()
{  
    	for(unsigned int ki = 0; ki < SHIP_vec.size(); ki++)
    	{ 
       		delete SHIP_vec[ki];
       		SHIP_vec.erase(SHIP_vec.begin() + ki);
    	}

    	for(unsigned int ni = 0; ni < NPC_vec.size(); ni++)
    	{ 
       		delete NPC_vec[ni];
       		NPC_vec.erase(NPC_vec.begin() + ni);
    	}


    	for(unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
    	{ 
       		delete ROCKET_vec[ri];
       		ROCKET_vec.erase(ROCKET_vec.begin() + ri);
    	}


    	for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
    	{
       		delete ASTEROID_vec[ai];
       		ASTEROID_vec.erase(ASTEROID_vec.begin() + ai);
    	}

    	for(unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
   	{
	        delete MINERAL_vec[mi];
       		MINERAL_vec.erase(MINERAL_vec.begin() + mi);
    	}

    	for(unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
    	{
       		delete CONTAINER_vec[ci];
       		CONTAINER_vec.erase(CONTAINER_vec.begin() + ci);
    	}
}

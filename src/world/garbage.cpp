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

void Garbage :: add(Bomb* bomb)
{
	BOMB_vec.push_back(bomb);
}

void Garbage :: add(Container* _container)
{
	CONTAINER_vec.push_back(_container);
}

void Garbage :: add(RocketBullet* _rocket)
{
	ROCKET_vec.push_back(_rocket);
}		
		
	
// effects	
void Garbage :: add(LazerTraceEffect* _effect)
{
	effect_LAZERTRACE_vec.push_back(_effect);
}

void Garbage :: add(ExplosionEffect* _effect)
{
	effect_EXPLOSION_vec.push_back(_effect);
}
		
void Garbage :: add(DamageEffect* _effect)
{
	effect_DAMAGE_vec.push_back(_effect);
}
		
void Garbage :: add(ShockWaveEffect* _effect)
{
	effect_SHOCKWAVE_vec.push_back(_effect);
}		

void Garbage :: add(VerticalFlowText* _text)
{
	text_DAMAGE_vec.push_back(_text);
}
// effects
	
		
void Garbage :: clear()
{  
    	for(unsigned int ki = 0; ki < SHIP_vec.size(); ki++)
    	{ 
       		delete SHIP_vec[ki];
    	}
    	SHIP_vec.clear();

    	for(unsigned int ni = 0; ni < NPC_vec.size(); ni++)
    	{ 
       		delete NPC_vec[ni];
    	}
    	NPC_vec.clear();


    	for(unsigned int ri = 0; ri < ROCKET_vec.size(); ri++)
    	{ 
       		delete ROCKET_vec[ri];
    	}
       	ROCKET_vec.clear();

    	for(unsigned int ai = 0; ai < ASTEROID_vec.size(); ai++)
    	{
       		delete ASTEROID_vec[ai];
    	}
       	ASTEROID_vec.clear();
       		
    	for(unsigned int mi = 0; mi < MINERAL_vec.size(); mi++)
   	{
	        delete MINERAL_vec[mi];
    	}
       	MINERAL_vec.clear();
       	
       	for(unsigned int i = 0; i < BOMB_vec.size(); i++)
   	{
	        delete BOMB_vec[i];
    	}
       	BOMB_vec.clear();
       		
    	for(unsigned int ci = 0; ci < CONTAINER_vec.size(); ci++)
    	{
       		delete CONTAINER_vec[ci];
    	}
       	CONTAINER_vec.clear();
       		    	
    	// effects
    	for(unsigned int ei = 0; ei < effect_LAZERTRACE_vec.size(); ei++)
    	{
       		delete effect_LAZERTRACE_vec[ei];
    	}
       	effect_LAZERTRACE_vec.clear();
       		    	
    	for(unsigned int ei = 0; ei < effect_EXPLOSION_vec.size(); ei++)
    	{
       		delete effect_EXPLOSION_vec[ei];
    	}
       	effect_EXPLOSION_vec.clear();
       		    	
    	for(unsigned int ei = 0; ei < effect_DAMAGE_vec.size(); ei++)
    	{
       		delete effect_DAMAGE_vec[ei];
    	}
       	effect_DAMAGE_vec.clear();
       		    	
    	for(unsigned int ei = 0; ei < effect_SHOCKWAVE_vec.size(); ei++)
    	{
       		delete effect_SHOCKWAVE_vec[ei];
    	}
       	effect_SHOCKWAVE_vec.clear();
       	
       	
       	for(unsigned int ti = 0; ti < text_DAMAGE_vec.size(); ti++)
    	{
       		delete text_DAMAGE_vec[ti];
    	}
       	text_DAMAGE_vec.clear();
    	// effects
}

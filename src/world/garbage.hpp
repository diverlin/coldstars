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


#ifndef GARBAGE_H
#define GARBAGE_H


class Garbage
{
	public:
		Garbage();
		~Garbage();
		
		void add(Ship*);
		void add(Npc*);
		void add(Asteroid*);
		void add(Mineral*);
		void add(Container*);
		void add(RocketBullet*);
		
		//effect
		void add(LazerTraceEffect*);
		void add(ExplosionEffect*);
		void add(DamageEffect*);
		void add(ShockWaveEffect*);
		
		void add(VerticalFlowText*);
		//effect
		
		void clear();
	
	private:
	    	std::vector<Ship*>  SHIP_vec;
    		std::vector<Npc*>   NPC_vec;

    		std::vector<Asteroid*>     ASTEROID_vec;
    		std::vector<Mineral*>      MINERAL_vec;
    		std::vector<Container*>    CONTAINER_vec;
    		std::vector<RocketBullet*> ROCKET_vec;
    		
    		// effects
    		std::vector<LazerTraceEffect*> effect_LAZERTRACE_vec;
    		std::vector<ExplosionEffect*>  effect_EXPLOSION_vec;
    		std::vector<DamageEffect*>     effect_DAMAGE_vec;
    		std::vector<ShockWaveEffect*>  effect_SHOCKWAVE_vec;
    		
    		std::vector<VerticalFlowText*> text_DAMAGE_vec;  		
    		// effects
};
     		
#endif 

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


#ifndef EXPLOSION_H
#define EXPLOSION_H


struct ParticleSystemData 
{
	unsigned int particles_num;

	float particleSize_start;
	float particleSize_end;

	float velocity_start;
	float velocity_end;

	float alpha_start;
	float alpha_end;

	float d_particleSize;
	float d_velocity;
	float d_alpha;
};



class ParticleForExplosionEffect
{ 
    	public:
        	bool is_alive;
        	float size;        	       
        
      		ParticleForExplosionEffect(vec2f, ParticleSystemData, int);      				 
      		~ParticleForExplosionEffect();

      		void update();
      		void render();
      		
      	private:
      		int curnum;  
      		      
        	vec2f center;
   
        	float alpha_start;
        	float alpha_end;
        	float d_alpha;
        	float alpha;
   
        	float size_start;
        	float d_size;
 
        	float velocity_start;
        	float d_velocity; 

        	vec2f velocity;
        	
        	void fastCalcVelocityVector();
      		void accurateCalcVelocityVector();
      	
};


class ExplosionEffect
{ 
    	public:
    	       	bool is_alive;    	       	        
    	       	        
       		ExplosionEffect(TextureOb*, vec2f, ParticleSystemData);       		       
       		~ExplosionEffect();

		void setStarSystem(StarSystem* _starsystem);
       		void update();
       		void render();
       		
       	private:
          	bool alreadyInRemoveQueue;
   
          	std::vector<ParticleForExplosionEffect*> particles_pList;  
          	
       	        TextureOb* texOb;
          	
          	int num_particles;
          	         	          	
       	        vec2f center;
          	
          	float pSize_start;       	
};


void createExplosion(StarSystem* _starsystem, vec2f _center_pos, int obSize);


#endif 

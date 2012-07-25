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


#ifndef BASEPARTICLESYSTEM_H
#define BASEPARTICLESYSTEM_H

#include <vector>

#include "particle.hpp"

class BaseParticleSystem 
{
    	public:
    		BaseParticleSystem();
    		virtual ~BaseParticleSystem();

      		void setDying();
                void setTextureOb(TextureOb*);
                void setParent(BaseGameEntity*);
                void setPosition(vec2f);
                void setParticlesNum(int);
                void setParticleData(ParticleData);
                
		bool GetAlive() const;
		
       		virtual void update() = 0;
       		virtual void Render() = 0;
       		
       	protected:
       		int subtype_id;
       		int num_particles;
       		
       		TextureOb* texOb;
       		ParticleData data_particle;
       		vec2f center;
                BaseGameEntity* parent;
                
       	    	bool is_alive, is_dying;
   
          	std::vector<Particle*> particles_vec;  
                
                vec2f getRandomVelocity();            
		vec2f getRandomAccurateVelocity();
                vec2f getRandomDirtyVelocity();
		//void calcAccurateRandomVelocity2(vec2f);
};


#endif 

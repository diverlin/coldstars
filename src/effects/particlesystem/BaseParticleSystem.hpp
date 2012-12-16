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

#include "Particle.hpp"
#include "../../resources/textureOb.hpp"
#include "../../spaceobjects/BaseSpaceEntity.hpp"

class BaseParticleSystem 
{
    	public:
    		BaseParticleSystem();
    		virtual ~BaseParticleSystem();

      		void SetDying() { is_dying = true; };
		void SetTextureOb(TextureOb* textureOb) { this->textureOb = textureOb; };
                void SetParent(BaseSpaceEntity* parent) { this->parent = parent; };
                void SetCenter(const vec2f& center) { this->center = center; };
                void SetParticlesNum(int num_particles)  { this->num_particles = num_particles; };
                void SetParticleData(const ParticleData& data_particle) { this->data_particle = data_particle; };
                
		bool GetAlive() const { return is_alive; };
		const vec2f& GetCenter() const { return center; };
		
       		virtual void Update() = 0;
       		virtual void Render() = 0;
       		
       	protected:
       		int subtype_id;
       		int num_particles;
       		
       		TextureOb* textureOb;
       		ParticleData data_particle;
       		vec2f center;
                BaseSpaceEntity* parent;
                
       	    	bool is_alive, is_dying;
   
          	std::vector<Particle*> particles_vec;  
                
                vec2f GetRandomVelocity();            
		vec2f GetRandomAccurateVelocity();
                vec2f GetRandomDirtyVelocity();
		//void calcAccurateRandomVelocity2(vec2f);
};


#endif 

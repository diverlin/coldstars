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


#ifndef TRAIL_H
#define TRAIL_H


class TrailEffect
{
   	public:
       		TrailEffect(TextureOb* _texOb, 
		    	    vec2f* _pTo_start_pos, 
			    vec2f* _pTo_target_pos, 
			    ParticleData _data_particle,
			    unsigned int _num_particles);

       		~TrailEffect();
       
       		void update();
       		void render();
       		
       	private:
       	       	TextureOb* texOb;

       		float* pTo_start_pos_x;       //ob.points.midLeft
       		float* pTo_start_pos_y;

       		float* pTo_target_pos_x;     //ob.points.midFarLeft
       		float* pTo_target_pos_y;  


       		ParticleData data_particle;
       		vec2f velocity;

       		float particle_offset;

       		std::vector<Particle*> particles_vec;
       		
       		void updateVelocity();
       		void putParticlesToInitPos();
       	
       	
};  

TrailEffect* createTrailEffect(int size_id, vec2f* pTo_pos, vec2f* pTo_target_pos);

#endif

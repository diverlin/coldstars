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


#ifndef DAMAGE_H
#define DAMAGE_H



class DamageEffect
{
   	public: 
       		DamageEffect(TextureOb* _texOb, 
       		    	     vec2f* _pTo_center, 
       		    	     ParticleData _data_particle,
       		    	     int _num_particles);
       		    	     
       		DamageEffect(TextureOb* _texOb, 
       		    	     float* _pTo_center_x, 
       		    	     float* _pTo_center_y, 
       		    	     ParticleData _data_particle,
       		    	     int _num_particles);
       		    
       		~DamageEffect();

      		bool getAlive() const;
      		bool setDying();
      		      		
       		void update();
       		void render();
       		
       	private:       	
       	       	bool is_alive;
       		bool is_dying;

       		float* pTo_center_x;
       		float* pTo_center_y;

		TextureOb* texOb;
		ParticleData data_particle;

       		std::vector<Particle*> particles_vec;       		       	
};

DamageEffect* createDamageEffect(TextureOb* _texOb, float* pTo_pos_x, float* pTo_pos_y);

#endif 

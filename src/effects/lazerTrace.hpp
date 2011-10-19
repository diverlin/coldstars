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

#ifndef LAZERTRACE_H
#define LAZERTRACE_H 

class LazerTraceEffect
{ 
    	public:
       		LazerTraceEffect(TextureOb* _texOb, TextureOb* texOb_particle, float _particle_size, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_end_pos_x, float* _pTo_end_pos_y);
       		~LazerTraceEffect();

		void setDamageEffect(DamageEffect*);
		bool getAlive() const;
		
       		void update();
       		void render();
            		
 	private:
 	       	bool is_alive;
       		bool is_alreadyInRemoveQueue; 
       		
 	       	TextureOb* texOb;
       		TextureOb* texOb_particle;

       		float particle_size;

       		float len; 
       		float angle_inR;
       		float d_angle_inR;
       		float additional_angle_inR;
       		float angle_inD; 
       		
       		int existance_time;
       		       		
       		float* pTo_start_pos_x;
       		float* pTo_start_pos_y;
       		float* pTo_end_pos_x;
       		float* pTo_end_pos_y;
       		       		
       		DamageEffect* damage_effect;
 	       		
           	void updateAngleAndLen();
           	
           	void (LazerTraceEffect::*pToFunc_render)();
		void _renderFrame();
		void _renderFrames();
};


#endif

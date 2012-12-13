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

#include "../effects/particlesystem/DamageEffect.hpp"

class LazerTraceEffect
{ 
    	public:
       		LazerTraceEffect(TextureOb* _texOb, 
       				 vec2f* _pTo_start_pos, 
       				 vec2f* _pTo_end_pos);
       		~LazerTraceEffect();

		void setDamageEffect(DamageEffect* _damage_effect) { damage_effect = _damage_effect; };
		bool GetAlive() const { return is_alive; };
		
		const vec2f& GetStartPos() const { return *pTo_start_pos; };
		const vec2f& GetEndPos() const { return *pTo_end_pos; };
				
       		void update();
       		void Render();
            		
 	private:
 	       	bool is_alive;
       		bool is_alreadyInRemoveQueue; 
       		
 	       	TextureOb* texOb;

       		float len; 
       		float angle_inR;
       		float d_angle_inR;
       		float additional_angle_inR;
       		float angle_inD; 
       		
       		int existance_time;
       		       		
       		vec2f* pTo_start_pos;
       		vec2f* pTo_end_pos;
       		       		
       		DamageEffect* damage_effect;
 	       		
           	void updateAngleAndLen();
};


#endif

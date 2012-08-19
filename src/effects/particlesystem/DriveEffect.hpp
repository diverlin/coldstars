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

#include "baseParticleSystem.hpp"

class TrailEffect : public BaseParticleSystem
{
   	public:
       		TrailEffect(vec2f*, vec2f*);
       		virtual ~TrailEffect();
       
       		virtual void update();
       		virtual void Render();
       		
                void createParticles();
                void updateVelocity();
       		void putParticlesToInitPos();
                                
       	private:
       		vec2f* pTo_start_pos;      //ob.points.midLeft
       		vec2f* pTo_target_pos;     //ob.points.midFarLeft

       		vec2f velocity;


       	
       	
};  

TrailEffect* createTrailEffect(int, vec2f*, vec2f*);

#endif

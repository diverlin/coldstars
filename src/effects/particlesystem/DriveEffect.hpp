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


#ifndef DRIVEEFFECT_H
#define DRIVEEFFECT_H

#include "baseParticleSystem.hpp"

class DriveEffect : public BaseParticleSystem
{
   	public:
       		DriveEffect(vec2f*, vec2f*);
       		virtual ~DriveEffect();
       
       		virtual void Update();
       		virtual void Render();
       		
                void CreateParticles();
                void UpdateVelocity();
       		void PutParticlesToInitPos();
                                
       	private:
       		vec2f* pTo_start_pos;      //ob.points.midLeft
       		vec2f* pTo_target_pos;     //ob.points.midFarLeft

       		vec2f velocity;


       	
       	
};  

DriveEffect* GetNewDriveEffect(int, vec2f*, vec2f*);

#endif

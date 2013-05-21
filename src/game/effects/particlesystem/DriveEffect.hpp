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

#include "BaseParticleSystem.hpp"

class DriveEffect : public BaseParticleSystem
{
   	public:
       		DriveEffect(Vec3<float>*, Vec3<float>*);
       		virtual ~DriveEffect();
       
       		virtual void Update();
       		virtual void Render() {};
       		void Render(float parent_d_alpha = 0.0);
       		
                void CreateParticles();
                void UpdateVelocity();
       		void PutParticlesToInitPos();
                                
       	private:
       		Vec3<float>* pTo_start_pos;      //ob.points.midLeft
       		Vec3<float>* pTo_target_pos;     //ob.points.midFarLeft

       		Vec3<float> velocity;


       	
       	
};  

DriveEffect* GetNewDriveEffect(int, Vec3<float>*, Vec3<float>*);

#endif

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
        DriveEffect(glm::vec3*, glm::vec3*);
        virtual ~DriveEffect() override final;
        
        virtual void Update() override final;
        void Render(float scale, float parent_d_alpha);
        
        void CreateParticles();
        void UpdateVelocity();
        void PutParticlesToInitPos();
                                
    private:
        glm::vec3* pTo_start_pos;      //ob.points.midLeft
        glm::vec3* pTo_target_pos;     //ob.points.midFarLeft
        
        glm::vec3 velocity;


           
           
};  

DriveEffect* GetNewDriveEffect(int, glm::vec3*, glm::vec3*);

#endif

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


#ifndef SHOCKWAVEEFFECT_H
#define SHOCKWAVEEFFECT_H
 
#include "../math/myVector.hpp"

class ShockWaveEffect
{
    public:
        bool is_alive;
              bool is_alreadyInRemoveQueue;

              glm::vec2 center;
                            
              glm::vec3 parameter;
              glm::vec3 d_parameter;
              float time, d_time;
              
              void SetCenter(const glm::vec2& center) { this->center = center; };
              const glm::vec2& GetCenter() const { return center; };

              ShockWaveEffect(float _x, float _y, float _z, float _time, float _d_x, float _d_y, float _d_z, float d_time);
              ~ShockWaveEffect();
              
              void Update();
              
          private:

          
};

ShockWaveEffect* getNewShockWave(float, bool dynamic = true);          
    
#endif

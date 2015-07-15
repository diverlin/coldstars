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

#include "ShockWaveEffect.hpp"
#include <common/constants.hpp>

ShockWaveEffect::ShockWaveEffect(float x, float y, float z, float time, 
                                 float d_x, float d_y, float d_z, float d_time)
    :
      m_isAlive(true),
      m_isAlreadyInRemoveQueue(false),
      m_parameters(glm::vec3(x, y, z)),
      m_time(time),
      m_dParameters(glm::vec3(d_x, d_y, d_z)),
      m_dTime(d_time)
{}

ShockWaveEffect::~ShockWaveEffect()
{}

void ShockWaveEffect::Update()
{
    m_parameters.x -= m_dParameters.x;

    if (m_parameters.y > 0) {
        m_parameters.y -= m_dParameters.y;
    } else {
        m_isAlive = false;
    }

    m_parameters.z -= m_dParameters.z;
    m_time -= m_dTime;
    
    if (m_isAlive == false) {
        if (m_isAlreadyInRemoveQueue == false) {
            //pTo_starsystem.effect_SHOCKWAVE_remove_queue.append();
            m_isAlreadyInRemoveQueue = true;
        }
    }
}


ShockWaveEffect* getNewShockWave(float radius, bool dynamic)
{       
    int size_id = CONVERTER::SIZE2SIZEID.GetEquivalent(radius);
    float x = 10;
    float y = 1.8;
    float z = 0.13;
    float time = 0.0;
    float dx = 0;
    float dy = 0.02;
    float dz = 0.0005;
    float dtime = -(0.001 + size_id * 0.0005);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004
    //float dtime = -(0.0001*obSize + obSize * 0.0003);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004

    if (dynamic == false)
    {
        x = 100;
        y = 1.8;
        z = 0.02;
        time = 0.1;
        dx = 0.0;
        dy = 0.0;
        dz = 0.0;
        dtime = 0.0;
    }
    
    ShockWaveEffect* shockwave = new ShockWaveEffect(x, y, z, time, dx, dy, dz, dtime);
    return shockwave;
}

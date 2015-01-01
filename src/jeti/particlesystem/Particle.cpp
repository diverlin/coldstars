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

#include "Particle.hpp"
#include <meti/RandUtils.hpp>

namespace jeti {

Particle::Particle(const ParticleData& data_particle)
:
m_IsAlive(true),
m_Color(data_particle.color_start),
m_Size(data_particle.size_start),
m_DataParticle(data_particle)
{} 
      
Particle::~Particle()
{}

void Particle::RandomizeLifeTime(float low, float high)
{
    float speed_rate              = meti::getRandFloat(low, high);   // 0.5, 0.8
    m_DataParticle.d_size         *= speed_rate;
    m_DataParticle.velocity_start *= speed_rate;
}

void Particle::Randomize_d_alpha(float val1_f, float val2_f)
{
    float val1_i = val1_f*10000;
    float val2_i = val2_f*10000;
        
    m_DataParticle.color_delta.a = meti::getRandInt(val1_i, val2_i)/1000.0;
}                
              
                
void Particle::CalcRandomVelocity()
{
    if (meti::getRandBool() == true) {
        CalcRandomDirtyVelocity();
    } else {
        CalcRandomAccurateVelocity();
    }
}

void Particle::CalcRandomDirtyVelocity()
{
    float dx_n = meti::getRandFloat(0.1, 1.0) * meti::getRandSign();
    float dy_n = meti::getRandFloat(0.1, 1.0) * meti::getRandSign();
    
    m_Velocity.x = dx_n * m_DataParticle.velocity_start;
    m_Velocity.y = dy_n * m_DataParticle.velocity_start;
    m_Velocity.z = 0;
}


void Particle::CalcRandomAccurateVelocity()
{
    float _len   = meti::getRandInt(50, 100);
    float _angle = glm::radians((float)meti::getRandInt(0, 360));
    
    float target_x = cos(_angle) * _len;
    float target_y = sin(_angle) * _len;
    
    float dx_n = target_x/_len;
    float dy_n = target_y/_len;
    
    m_Velocity.x = dx_n * m_DataParticle.velocity_start;
    m_Velocity.y = dy_n * m_DataParticle.velocity_start;
    m_Velocity.z = 0;
}  


//void Particle::calcAccurateRandomVelocity2(glm::vec2 center)
//{
    //float _len   = getRandInt(50, 100);
    //float _angle = getRandInt(0, 360)/RADIAN_TO_DEGREE_RATE;
    
    //glm::vec2 target;
    //target = center;
    
    //pos.x = center.x + sin(_angle) * _len;
    //pos.y = center.y + cos(_angle) * _len;
    
    //float xl = (target.x - pos.x);
    //float yl = (target.y - pos.y);
    
    //float dx_n = xl/_len;
    //float dy_n = yl/_len;
    
    //m_Velocity.x = dx_n * m_DataParticle.velocity_start;
    //m_Velocity.y = dy_n * m_DataParticle.velocity_start;
    //m_Velocity.z = 0;
//}  

void Particle::Reborn()
{   
    m_Position = glm::vec3(0.0f);  
    m_IsAlive = true;
                   
    m_Color = m_DataParticle.color_start;
    m_Size  = m_DataParticle.size_start;
}
              

void Particle::Update()
{
    if (m_IsAlive)  
    {
        m_Position += m_Velocity;    
        m_Color.a  -= m_DataParticle.color_delta.a;
        m_Size     -= m_DataParticle.d_size;     

        if (m_Color.a < m_DataParticle.color_end.a)
        {
            m_Color.a = m_DataParticle.color_end.a;
            m_IsAlive = false;
        }
    
        if (m_Size < m_DataParticle.size_end)
        {
            m_Size = m_DataParticle.size_end;
            m_IsAlive = false;
        }
    }
}

}

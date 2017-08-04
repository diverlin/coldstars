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
namespace particlesystem {

Particle::Particle(const ParticleData& data_particle)
    :
      m_color(data_particle.color_start),
      m_size(data_particle.size_start),
      m_dataParticle(data_particle)
{} 

Particle::~Particle()
{}

void Particle::randomizeLifeTime(float low, float high)
{
    float speed_rate              = meti::getRandFloat(low, high);   // 0.5, 0.8
    m_dataParticle.d_size         *= speed_rate;
    m_dataParticle.velocity_start *= speed_rate;
}

void Particle::randomizeDeltaAlpha(float val1_f, float val2_f)
{
    float val1_i = val1_f*10000;
    float val2_i = val2_f*10000;

    m_dataParticle.color_delta.a = meti::getRandInt(val1_i, val2_i)/1000.0;
}                


void Particle::randomVelocity()
{
    if (meti::getRandBool() == true) {
        randDirtyVelocity();
    } else {
        randAccurateVelocity();
    }
}

void Particle::randDirtyVelocity()
{
    float dx_n = meti::getRandFloat(0.1, 1.0) * meti::getRandSign();
    float dy_n = meti::getRandFloat(0.1, 1.0) * meti::getRandSign();
    
    m_velocity.x = dx_n * m_dataParticle.velocity_start;
    m_velocity.y = dy_n * m_dataParticle.velocity_start;
    m_velocity.z = 0;
}


void Particle::randAccurateVelocity()
{
    float _len   = meti::getRandInt(50, 100);
    float _angle = glm::radians((float)meti::getRandInt(360));
    
    float target_x = cos(_angle) * _len;
    float target_y = sin(_angle) * _len;
    
    float dx_n = target_x/_len;
    float dy_n = target_y/_len;
    
    m_velocity.x = dx_n * m_dataParticle.velocity_start;
    m_velocity.y = dy_n * m_dataParticle.velocity_start;
    m_velocity.z = 0;
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

void Particle::reborn()
{   
    m_position = glm::vec3(0.0f);
    m_isAlive = true;

    m_color = m_dataParticle.color_start;
    m_size  = m_dataParticle.size_start;
}


void Particle::update()
{
    if (!m_isAlive) {
        return;
    }

    m_position += m_velocity;
    m_color.a  -= m_dataParticle.color_delta.a;
    m_size     -= m_dataParticle.d_size;

    if (m_color.a < m_dataParticle.color_end.a) {
        m_color.a = m_dataParticle.color_end.a;
        m_isAlive = false;
    }

    if (m_size < m_dataParticle.size_end) {
        m_size = m_dataParticle.size_end;
        m_isAlive = false;
    }
}

} // namespace particlesystem
} // namespace jeti

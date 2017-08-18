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

#include <ceti/StringUtils.hpp>
#include <iostream>

namespace jeti {
namespace particlesystem {

Particle::Particle(const ParticleConfig& config)
    :
      m_color(config.color_start),
      m_size(config.size_start),
      m_velocity(config.velocity_start),
      m_config(config)
{}

Particle::~Particle()
{}

void Particle::randomizeDirection()
{
    meti::rand::fill_vec3xy_unit(m_direction);
}

void Particle::restart(const glm::vec3& direction)
{   
    restart();
    m_direction = direction;
}

void Particle::restart()
{
    m_position = glm::vec3(0.0f);
    m_isAlive = true;

    m_color = m_config.color_start;
    m_size  = m_config.size_start;
    m_velocity = m_config.velocity_start;
}

void Particle::update()
{
    if (!m_isAlive) {
        return;
    }

    m_position += m_velocity*m_direction;
    m_color    -= m_config.color_delta;
    m_size     -= m_config.size_delta;

    if (m_color.a < m_config.color_end) {
        m_color.a = m_config.color_end;
        m_isAlive = false;
    }

    if (m_size < m_config.size_end) {
        m_size = m_config.size_end;
        m_isAlive = false;
    }
}

} // namespace particlesystem
} // namespace jeti

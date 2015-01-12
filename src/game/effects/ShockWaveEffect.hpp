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


#pragma once

#include <meti/VectorUtils.hpp>

class ShockWaveEffect
{
    public:
        ShockWaveEffect(float x, float y, float z, float time, float d_x, float d_y, float d_z, float d_time);
        ~ShockWaveEffect();

        void setCenter(const glm::vec2& center) { m_center = center; }

        bool isAlive() const { return m_isAlive; }
        bool isAlreadyInRemoveQueue() const { return m_isAlreadyInRemoveQueue; }
        const glm::vec2& center() const { return m_center; }
        float time() const { return m_time; }
        const glm::vec3& parameters() const { return m_parameters; }

        void Update();

    private:
        bool m_isAlive;
        bool m_isAlreadyInRemoveQueue;

        glm::vec2 m_center;

        glm::vec3 m_parameters;
        glm::vec3 m_dParameters;
        float m_time, m_dTime;
};

ShockWaveEffect* getNewShockWave(float, bool dynamic = true);          



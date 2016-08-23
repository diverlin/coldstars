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

#include "lazerTrace.hpp"

#include <glm/gtx/transform.hpp>
#include <meti/QuaternionUtils.hpp>

#include <jeti/particlesystem/BaseParticleSystem.hpp>


#include <ceti/descriptor/Collector.hpp> // remove


LazerTraceEffect::LazerTraceEffect(jeti::TextureOb* textureOb, const glm::vec3* const start_pos, const glm::vec3* const end_pos)
:
m_IsAlive(true),
m_TextureOb(textureOb),
m_pStartPos(start_pos),
m_pEndPos(end_pos)
{
    //MeshCollector::get().get(type::mesh::PLANE_ID);
    m_LiveTime = 40;
}

LazerTraceEffect::~LazerTraceEffect()
{}

void LazerTraceEffect::Update()
{
    if (m_IsAlive)
    {
        if (m_LiveTime < 0)
        {
            m_IsAlive = false;
            if (m_ParticleSystem != nullptr)
            {
                //m_ParticleSystem->StartDying();
            }
        }

        m_LiveTime -= 1;
    }
}

const glm::mat4& LazerTraceEffect::actualModelMatrix()
{
    m_MatrixTranslate = glm::translate(*m_pStartPos);

    const glm::vec3& origin_dir = glm::vec3(1.0f, 0.0f, 0.0f);
    meti::RotationBetweenVectors(m_QuatPosition, origin_dir, glm::normalize(*m_pEndPos));

    m_MatrixRotate = glm::toMat4(m_QuatPosition);

    float length = glm::length(*m_pEndPos - *m_pStartPos);
    m_MatrixScale = glm::scale(glm::vec3(length, 6.0, 0.0f));

    m_MatrixModel = m_MatrixTranslate * m_MatrixRotate * m_MatrixScale;

    return m_MatrixModel;
}


//void LazerTraceEffect::Render()
//{
    //if (m_IsAlive == true)
    //{         
        //glUseProgram(ShaderCollector::Instance().flash);
        
        //glUniform1i(glGetUniformLocation(ShaderCollector::Instance().flash, "iTexture_0"), 0);
        //glUniform1f(glGetUniformLocation(ShaderCollector::Instance().flash, "iTime"), Screen::Instance().GetElapsedTimeInSeconds()*10.0);
        
        //glActiveTexture(GL_TEXTURE0);        
        
        ////drawLine(*texOb, *pTo_start_pos, len, angle_inD, texOb->GetFrameHeight()/4);            
        
        //glUseProgram(0);
        //glActiveTexture(GL_TEXTURE0);
    //}
//}



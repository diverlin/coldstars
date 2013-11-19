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

#ifndef LAZERTRACE_HPP
#define LAZERTRACE_HPP 

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class TextureOb;
class BaseParticleSystem;

class LazerTraceEffect
{ 
    public:
        LazerTraceEffect(TextureOb*, const glm::vec3* const, const glm::vec3* const);
        ~LazerTraceEffect();

        bool GetIsAlive() const { return m_IsAlive; };

        void BindParticleSystem(BaseParticleSystem* particle_system) { m_ParticleSystem = particle_system; }
        
        const glm::vec3& GetStartPos() const { return *m_pStartPos; };
        const glm::vec3& GetEndPos() const { return *m_pEndPos; };
                
        void Update();
        const glm::mat4& GetActualModelMatrix();
                    
     private:
        bool m_IsAlive;
        int m_LiveTime;
        
        TextureOb* m_TextureOb;
        BaseParticleSystem* m_ParticleSystem;

        const glm::vec3* m_pStartPos;
        const glm::vec3* m_pEndPos;

        glm::mat4 m_MatrixModel;
        glm::mat4 m_MatrixTranslate;
        glm::mat4 m_MatrixRotate;
        glm::mat4 m_MatrixScale;

        glm::quat m_QuatPosition;
};


#endif

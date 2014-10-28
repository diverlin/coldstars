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

namespace jeti {
class Mesh;
class TextureOb;
class BaseParticleSystem;
}

class LazerTraceEffect
{ 
    public:
        LazerTraceEffect(jeti::TextureOb*, const glm::vec3* const, const glm::vec3* const);
        ~LazerTraceEffect();

        bool GetIsAlive() const { return m_IsAlive; }

        void BindParticleSystem(jeti::BaseParticleSystem* particle_system) { m_ParticleSystem = particle_system; }
        
        const glm::vec3& GetStartPos() const { return *m_pStartPos; }
        const glm::vec3& GetEndPos() const { return *m_pEndPos; }

        const glm::mat4& GetActualModelMatrix();
        const jeti::Mesh& GetMesh() const { return *m_Mesh; }
        const jeti::TextureOb& GetTextureOb() const { return *m_TextureOb; }

        void Update();
                    
     private:
        bool m_IsAlive;
        int m_LiveTime;
        
        jeti::Mesh* m_Mesh;
        jeti::TextureOb* m_TextureOb;
        jeti::BaseParticleSystem* m_ParticleSystem;

        const glm::vec3* m_pStartPos;
        const glm::vec3* m_pEndPos;

        glm::mat4 m_MatrixModel;
        glm::mat4 m_MatrixTranslate;
        glm::mat4 m_MatrixRotate;
        glm::mat4 m_MatrixScale;

        glm::quat m_QuatPosition;
};


#endif

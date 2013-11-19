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


#ifndef RENDER_HPP
#define RENDER_HPP

#include <common/NonCopyable.hpp>
#include <render/MyGl.hpp>
#include "../resources/textureOb.hpp" // to be removed
#include <common/Box2D.hpp>           // to be removed

class Mesh;

enum class PROJECTION_TYPE { PERSPECTIVE, ORTHOGONAL};

class Renderer : public NonCopyable
{
    public:
        Renderer();
        ~Renderer();

        void Init();
        void MakeShortCuts();

        void SetPerspectiveProjection(float, float);
        void SetOrthogonalProjection(float, float);

        void ClearScreen() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
        
        void enable_CULLFACE() const    { /*glEnable(GL_CULL_FACE);*/ }
        void disable_CULLFACE() const   { /*glDisable(GL_CULL_FACE);*/ }
        
        void enable_BLEND() const   { glEnable(GL_BLEND);  }
        void disable_BLEND() const  { glDisable(GL_BLEND); }
        
        void enable_DEPTH() const   { glEnable(GL_DEPTH_TEST); }
        void disable_DEPTH() const  { glDisable(GL_DEPTH_TEST); }
        
        void enable_POINTSPRITE() const     { glEnable(GL_POINT_SPRITE); glEnable(GL_PROGRAM_POINT_SIZE); }    
        void disable_POINTSPRITE() const    { glDisable(GL_POINT_SPRITE); glDisable(GL_PROGRAM_POINT_SIZE); }   
                
        void ComposeViewMatrix(const glm::mat4&);

        void RenderMeshGeometry           (const Mesh&, const glm::mat4&) const;
        void RenderMeshGeometry           (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void RenderTransparentMeshGeometry(const Mesh&, const TextureOb&, const glm::mat4&) const;
        void RenderMeshLight              (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void RenderMeshLightNormalMap     (const Mesh&, const TextureOb&, const glm::mat4&, const glm::vec2&, const glm::vec4&) const;
        void RenderTransparentMeshLight   (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void RenderMeshMultiTextured      (const Mesh&, const TextureOb&, const glm::mat4&, float) const;

        void DrawQuad(const TextureOb&, const glm::mat4&) const;
        void DrawQuad(const TextureOb&, const Box2D&) const;

        void DrawQuad(int, int) const;        
        void DrawQuadTextured(GLuint, int, int) const; 
        void DrawQuadTexturedFullScreen(GLuint) const;
        void DrawQuadTexturedBlurred(GLuint, int, int) const;
                        
        void DrawParticleTextured(const TextureOb&, const glm::vec3&, float) const;
        void DrawParticles(const Mesh&, const TextureOb&, const glm::mat4&) const;
        
        void DrawAxis(const glm::mat4&, float) const;
        void DrawVector(const glm::vec3&, const glm::vec3&, float, float) const;                                             
        void DrawVector(const glm::vec3&, const glm::mat4&, float) const;  
                                                                 
    private:
        glm::mat4 m_Pm;
        glm::mat4 m_Vm;
        glm::mat4 m_PVm;
        
        glm::vec4 m_Color;
       
        void ComposeModelMatrix(const glm::mat4&) const;
        void UpdateProjectionViewMatrix();
        
        GLuint m_ProgramLight;          
        GLint m_ProgramLightLocation_uProjectionViewMatrix;
        GLint m_ProgramLightLocation_uModelMatrix;
        GLint m_ProgramLightLocation_uNormalMatrix;
        GLint m_ProgramLightLocation_uLightPos;
        GLint m_ProgramLightLocation_uEyePos;
        GLint m_ProgramLightLocation_uDiffColor;
        GLint m_ProgramLightLocation_uAmbientColor; 
        GLint m_ProgramLightLocation_uTexture; 
    
        GLuint m_ProgramBlur;        
};

// TEXT
void drawColoredTextWithBackground(const std::string&, 
               int,
               const glm::vec2&, 
               const glm::ivec4&);
               
void drawColoredText(const std::string&, int, const glm::vec2&, const glm::ivec4&);
               
void drawInfoIn2Column(
                const std::vector<std::string>& pnfo_title_list, 
                const std::vector<std::string>& info_value_list, 
                const glm::vec2& pos);

#endif 



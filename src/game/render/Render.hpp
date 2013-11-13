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
#include "../resources/textureOb.hpp"
#include "../common/rect.hpp"
#include <common/Box2D.hpp>
class Mesh;

enum class PROJECTION_TYPE { PERSPECTIVE, ORTHOGONAL};

class Renderer : public NonCopyable
{
    public:
        Renderer();
        ~Renderer();

        void Init();
        void MakeShortCuts();

        void ClearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); } const
        
        void SetPerspectiveProjection(float, float);
        void SetOrthogonalProjection(float, float);
                
        void ComposeViewMatrix(const glm::mat4&);
        
        void DrawQuad(TextureOb*, const glm::mat4&) const;
        void RenderMeshGeometry(const Mesh*, const glm::mat4&) const;
        void RenderMeshGeometry(const Mesh*, const TextureOb*, const glm::mat4&) const;
        void RenderTransparentMeshGeometry(const Mesh*, const TextureOb*, const glm::mat4&) const;
        void RenderMeshLight(const Mesh*, const TextureOb*, const glm::mat4&) const;
        void RenderMeshLightNormalMap(const Mesh*, const TextureOb*, const glm::mat4&, const glm::vec2&, const glm::vec4&) const;
        void RenderTransparentMeshLight(const Mesh*, const TextureOb*, const glm::mat4&) const;
        void RenderMeshMultiTextured(const Mesh*, const TextureOb*, const glm::mat4&, float) const;

        void DrawQuad(int, int) const;        
        void DrawQuadTextured(GLuint, int, int) const; 
        void DrawQuadTexturedFullScreen(GLuint) const;
        void DrawQuadTexturedBlurred(GLuint, int, int) const;
                        
        void DrawParticleTextured(TextureOb*, const glm::vec3&, float) const;
        
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


void enable_CULLFACE();
void disable_CULLFACE();

void enable_BLEND();
void disable_BLEND();

void enable_DEPTH();
void disable_DEPTH();

void enable_POINTSPRITE();
void disable_POINTSPRITE();

void drawQuad(TextureOb* texOb, 
         const glm::vec3& center,
         const glm::vec3& size, 
         float angle=0);
         
void drawQuad(TextureOb* texOb,
         const glm::vec2& center, 
         const glm::vec2& size,
         float angle);
              
void drawQuad(TextureOb*, const Box2D&);
void drawQuadMasked(TextureOb*, const Box2D&, TextureOb*, float);
                           
void drawTexturedRect(TextureOb* texOb, const Rect& rect, float z_pos);   

void drawLine(TextureOb* texOb, 
              const glm::vec3& start_pos, 
              float len, 
              float angle_inD, 
              int half_h);

void drawColoredTextWithBackground(const std::string&, 
               int,
               const glm::vec2&, 
               const glm::ivec4&);
               
void drawColoredText(const std::string&, int, const glm::vec2&, const glm::ivec4&);
               
void drawInfoIn2Column(
                const std::vector<std::string>& pnfo_title_list, 
                const std::vector<std::string>& info_value_list, 
                const glm::vec2& pos);

void drawParticleTextured(GLuint texture, const glm::vec2& _center, float size, float pos_z);
void drawParticle(const glm::vec2&, float, float r, float g, float b, float a);
void drawParticle(const glm::vec2&, float, const glm::vec4&);
void drawParticle(const glm::vec2&, float);

#endif 



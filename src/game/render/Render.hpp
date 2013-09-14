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

#include <GL/glew.h>
#include "../resources/textureOb.hpp"
#include "../common/rect.hpp"
#include <common/Box2D.hpp>
class Mesh;

class Render
{
    public:
        Render() {}
        ~Render() {}

        void ApplyViewMatrix(const glm::mat4& Vm)  { m_Vm = Vm; UpdateProjectionViewMatrix(); }
        void ApplyMatrixToOpengl(const glm::mat4& Mm) 
        { 
            m_PVMm = m_PVm * Mm;
            glLoadMatrixf(&m_PVMm[0][0]);     
        }
                                 
    private:
        glm::mat4 m_Pm;
        glm::mat4 m_Vm;
        glm::mat4 m_PVm;
        
        glm::mat4 m_PVMm;
       
        void UpdateProjectionViewMatrix() { m_PVm = m_Pm * m_Vm; }               

};

class Camera
{
    public:
        Camera() {}
        ~Camera() {}

        const glm::mat4& GetViewMatrix() { return m_Vm; }  
            
    private:
        glm::mat4 m_Vm;
  
};

void initGl(int, int);
void resizeGl(int, int);

void clearScreen();
void resetRenderTransformation();

void camera(float x, float y, float z);
void setColor4f(const glm::vec4&);    
void setColor4f(float, float, float, float);

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

void drawFullScreenQuad(int w, int h, float pos_z);


void drawFullScreenTexturedQuad(GLuint texture, int w, int h, float pos_z);


void drawFullScreenTexturedQuadBlurred(GLuint texture, int w, int h, float pos_z, GLuint program_blur);

void renderMesh(const Mesh* const mesh, const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle, bool ZYX);
void rotateZYX(const glm::vec3&);
void rotateXYZ(const glm::vec3&);

void drawParticleTextured(GLuint texture, const glm::vec2& _center, float size, float pos_z);
void drawParticle(const glm::vec2&, float, float r, float g, float b, float a);
void drawParticle(const glm::vec2&, float, const glm::vec4&);
void drawParticle(const glm::vec2&, float);

#endif 



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


#include "Render.hpp"
#include "Screen.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <resources/GuiTextureObCollector.hpp>
#include <resources/ShaderCollector.hpp>

#include "Mesh.hpp"
#include "../common/constants.hpp"

// for ugly
#include <glm/glm.hpp> // glm::vec
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <math/QuaternionUtils.hpp>
// for ugly

Renderer::Renderer()
:
m_Color(1.0f),
m_ProgramLight(0),
m_ProgramLightLocation_uProjectionViewMatrix(-1),
m_ProgramLightLocation_uModelMatrix(-1),
m_ProgramLightLocation_uNormalMatrix(-1),
m_ProgramLightLocation_uLightPos(-1),
m_ProgramLightLocation_uEyePos(-1),
m_ProgramLightLocation_uDiffColor(-1),
m_ProgramLightLocation_uAmbientColor(-1), 
m_ProgramLightLocation_uTexture(-1), 
m_ProgramBlur(0) 
{}

Renderer::~Renderer() 
{}

void Renderer::Init()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    
    // Enable Z-buffer read and write
    //glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    
    glShadeModel(GL_SMOOTH);
}

void Renderer::MakeShortCuts()
{
    {
    m_ProgramLight = ShaderCollector::Instance().light;
    m_ProgramLightLocation_uProjectionViewMatrix = glGetUniformLocation(m_ProgramLight, "u_ProjectionViewMatrix");
    m_ProgramLightLocation_uModelMatrix          = glGetUniformLocation(m_ProgramLight, "u_ModelMatrix");
    m_ProgramLightLocation_uNormalMatrix         = glGetUniformLocation(m_ProgramLight, "u_NormalModelMatrix");
            
    m_ProgramLightLocation_uLightPos = glGetUniformLocation(m_ProgramLight, "u_LightPos");
    m_ProgramLightLocation_uEyePos   = glGetUniformLocation(m_ProgramLight, "u_EyePos");
    
    m_ProgramLightLocation_uDiffColor     = glGetUniformLocation(m_ProgramLight, "u_DiffColor");
    m_ProgramLightLocation_uAmbientColor  = glGetUniformLocation(m_ProgramLight, "u_AmbientColor");                    
        
    m_ProgramLightLocation_uTexture  = glGetUniformLocation(m_ProgramLight, "u_Texture0"); 
    }    
    
    
    m_ProgramBlur  = ShaderCollector::Instance().blur;
}
        
void Renderer::SetPerspectiveProjection(float w, float h) 
{        
    m_Pm = glm::perspective(90.0f, w/h, 0.1f, 1000.0f);
 
    UpdateProjectionViewMatrix();
}

void Renderer::SetOrthogonalProjection(float w, float h) 
{        
    m_Pm = glm::ortho(0.0f, w, 0.0f, h, 0.1f, 1000.0f);

    UpdateProjectionViewMatrix();
}

void Renderer::ComposeViewMatrix(const glm::mat4& Vm)  
{ 
    m_Vm = Vm; 
    UpdateProjectionViewMatrix(); 
}

void Renderer::ComposeModelMatrix(const glm::mat4& Mm) const
{ 
    glm::mat4 PVMm = m_PVm * Mm; // needs to be done inside vertex shader
    glLoadMatrixf(&PVMm[0][0]);     
}
                                 
void Renderer::UpdateProjectionViewMatrix() 
{ 
    m_PVm = m_Pm * m_Vm; 
}



void Renderer::DrawQuad(const TextureOb& texOb, const glm::mat4& Mm) const
{
    glBindTexture(GL_TEXTURE_2D, texOb.texture);
    int frame = 0; //texOb.updateAnimationFrame();
   
    ComposeModelMatrix(Mm);
    
    glBegin(GL_QUADS);
    {   
        glTexCoord3f(texOb.texCoord_bottomLeft_vec[frame].x,  texOb.texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
        glTexCoord3f(texOb.texCoord_bottomRight_vec[frame].x, texOb.texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
        glTexCoord3f(texOb.texCoord_topRight_vec[frame].x,    texOb.texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
        glTexCoord3f(texOb.texCoord_topLeft_vec[frame].x,     texOb.texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
    }
    glEnd();
}

void Renderer::DrawQuad(const TextureOb& texOb, const Box2D& box) const
{
    // ugly start
    glm::vec2 pos = box.GetCenter();
    glm::mat4 Tm = glm::translate(glm::vec3(pos.x, pos.y, -2.0f));
     
    glm::quat Qx, Qy, Qz;
    
    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);   
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z); 
       
    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);
    
    glm::vec2 size = box.GetSize()*box.GetScale();
    glm::mat4 Sm = glm::scale(glm::vec3(size.x, size.y, 1.0f));
      
    glm::mat4 Mm = Tm * Rm * Sm;
    // ugly end

    DrawQuad(texOb, Mm);
}

void Renderer::RenderMeshGeometry(const Mesh& mesh, const glm::mat4& Mm) const
{
    ComposeModelMatrix(Mm);                     
    mesh.Draw();
}

void Renderer::RenderMeshGeometry(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm) const
{
    glBindTexture(GL_TEXTURE_2D, textureOb.texture);
    
ComposeModelMatrix(Mm);                     
    mesh.Draw();
}

void Renderer::RenderTransparentMeshGeometry(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm) const
{
    enable_BLEND();
        glBindTexture(GL_TEXTURE_2D, textureOb.texture);

        ComposeModelMatrix(Mm);                     
        mesh.Draw();

    disable_BLEND();
}

void Renderer::RenderMeshLight(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm) const
{
    float ambient_factor = 0.25;       
        
    glm::vec3 eye_pos = Screen::Instance().GetCamera().GetPos();
 
    glUseProgram(m_ProgramLight);
    {
        glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(Mm)));
    
        glUniformMatrix4fv(m_ProgramLightLocation_uProjectionViewMatrix, 1, GL_FALSE, &m_PVm[0][0]);
        glUniformMatrix4fv(m_ProgramLightLocation_uModelMatrix         , 1, GL_FALSE, &Mm[0][0]);
        glUniformMatrix3fv(m_ProgramLightLocation_uNormalMatrix        , 1, GL_FALSE, &NormalModelMatrix[0][0]);
                
        glUniform3f(m_ProgramLightLocation_uLightPos, 0.0f, 0.0f, 200.0);
        glUniform3f(m_ProgramLightLocation_uEyePos  , eye_pos.x, eye_pos.y, eye_pos.z);
        
        glUniform4f(m_ProgramLightLocation_uDiffColor,    m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        glUniform4f(m_ProgramLightLocation_uAmbientColor, ambient_factor*m_Color.r, ambient_factor*m_Color.g, ambient_factor*m_Color.b, ambient_factor*m_Color.a);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.texture); 
        glUniform1i(m_ProgramLightLocation_uTexture, 0);
                            
        mesh.Draw();
    }
    glUseProgram(0);
}

void Renderer::RenderMeshLightNormalMap(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm, const glm::vec2& scroll_coords, const glm::vec4& color) const
{
    float ambient_factor = 0.25;
    
    glUseProgram(ShaderCollector::Instance().light_normalmap);
    {
        glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_lightPos"), -scroll_coords.x, -scroll_coords.y, 0.0);
        glUniform3f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_eyePos"), -scroll_coords.x, -scroll_coords.y, 0.0);
        glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_diffColor"), color.r, color.g, color.b, color.a);
        glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_ambientColor"), ambient_factor*color.r, ambient_factor*color.g, ambient_factor*color.b, ambient_factor*color.a);
                
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.texture);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_texture"), 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureOb.normalmap);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light_normalmap, "u_normalmap"), 1);
                
        ComposeModelMatrix(Mm);                     
        mesh.Draw();
    }
    glUseProgram(0);
}

void Renderer::RenderTransparentMeshLight(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm) const
{
    enable_BLEND();
        RenderMeshLight(mesh, textureOb, Mm);
    disable_BLEND();
}

void Renderer::RenderMeshMultiTextured(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm, float offset) const
{
    glUseProgram(ShaderCollector::Instance().multitexturing);
    {    
        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, textureOb.texture);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "Texture_0"), 0);
        
        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, textureOb.texture);
        glUniform1i(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "Texture_1"), 1);
        
        glUniform2f(glGetUniformLocation(ShaderCollector::Instance().multitexturing, "displ"), offset, -offset);
        
        ComposeModelMatrix(Mm);                     
        mesh.Draw();
    }
    glUseProgram(0);
}        

void Renderer::DrawQuad(int w, int h) const
{
    float pos_z = -499.0f;
    
    glLoadMatrixf(&m_Pm[0][0]); 
    
    glBegin(GL_QUADS);
    {
        glTexCoord3f(0, 0, 0); glVertex3f(0, 0, pos_z);
        glTexCoord3f(1, 0, 0); glVertex3f(w, 0, pos_z);
        glTexCoord3f(1, 1, 0); glVertex3f(w, h, pos_z);
        glTexCoord3f(0, 1, 0); glVertex3f(0, h, pos_z); 
    }   
    glEnd();
}
    
void Renderer::DrawQuadTextured(GLuint texture, int w, int h) const
{   
    glBindTexture(GL_TEXTURE_2D, texture);
    DrawQuad(w, h);
}

void Renderer::DrawQuadTexturedFullScreen(GLuint texture) const
{
    int w = Screen::Instance().GetWidth(); 
    int h = Screen::Instance().GetHeight(); 
    
    DrawQuadTextured(texture, w, h);
}

void Renderer::DrawQuadTexturedBlurred(GLuint texture, int w, int h) const
{    
    glUseProgram(m_ProgramBlur);
    
    glActiveTexture(GL_TEXTURE0);                              
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glUniform1i(glGetUniformLocation(m_ProgramBlur, "sceneTex"), 0);
    
    glUniform1f(glGetUniformLocation(m_ProgramBlur, "rt_w"), 3*w); 
    glUniform1f(glGetUniformLocation(m_ProgramBlur, "rt_h"), 3*h);
    glUniform1f(glGetUniformLocation(m_ProgramBlur, "vx_offset"), 1.0);
    
    DrawQuad(w, h);
    
    glUseProgram(0);
}
 
void Renderer::DrawParticleTextured(const TextureOb& texOb, const glm::vec3& center, float size) const
{
    glBindTexture(GL_TEXTURE_2D, texOb.texture);
    
    glPointSize(size);
        
    glLoadMatrixf(&m_PVm[0][0]);  // point sprites doesn't use Model Matrix
    
    glBegin(GL_POINTS);
        glVertex3f(center.x, center.y, center.z);
    glEnd();
} 

void Renderer::DrawParticles(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& Mm) const
{
    enable_BLEND();
    enable_POINTSPRITE();
    {
        glPointSize(12.0f);
    
        glUseProgram(ShaderCollector::Instance().particle);
        {    
            glActiveTexture(GL_TEXTURE0);                                
            glBindTexture(GL_TEXTURE_2D, textureOb.texture);
            glUniform1i(glGetUniformLocation(ShaderCollector::Instance().particle, "uTexture_0"), 0);

            glUniformMatrix4fv(glGetUniformLocation(ShaderCollector::Instance().particle, "u_ModelMatrix"), 1, GL_FALSE, &Mm[0][0]);      
            glUniformMatrix4fv(glGetUniformLocation(ShaderCollector::Instance().particle, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_PVm[0][0]);       
      
            mesh.Draw();
        }
        glUseProgram(0);
    }
    disable_POINTSPRITE();
    disable_BLEND();
}
   



void Renderer::DrawAxis(const glm::mat4& Mm, float width) const
{
    float r = 1.5f;
    
    glDisable(GL_TEXTURE_2D);
    
    ComposeModelMatrix(Mm); 
    
    glLineWidth(width);

    // draw axis X
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(r, 0.0f, 0.0f);
    glEnd();
                
    // draw axis Y    
    glColor3f(0.0f, 1.0f, 0.0f);    
    glBegin(GL_LINES);        
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, r, 0.0f);
    glEnd();

    // draw axis Z    
    glColor3f(0.0f, 0.0f, 1.0f);    
    glBegin(GL_LINES);        
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, r);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);
}
      
      
void Renderer::DrawVector(const glm::vec3& v, const glm::vec3& pos, float length, float width) const
{
    glDisable(GL_TEXTURE_2D);
    
    ComposeModelMatrix(glm::mat4(1.0f)); 
    
    glLineWidth(width); 
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINES);  
        glVertex3f(pos.x, pos.y, pos.z);
        glVertex3f(pos.x+length*v.x, pos.y+length*v.y, pos.z+length*v.z);
    glEnd();
    
    glEnable(GL_TEXTURE_2D);
}

void Renderer::DrawVector(const glm::vec3& v, const glm::mat4& Mm, float width) const
{
    glDisable(GL_TEXTURE_2D);
    
    ComposeModelMatrix(Mm); 
    
    glLineWidth(width); 
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINES);        
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(v.x, v.y, v.z);
    glEnd();
    
    glEnable(GL_TEXTURE_2D);
}
  
//void drawQuad(const TextureOb& texOb,
         //const glm::vec3& center, 
         //const glm::vec3& size,
         //float angle)
//{
    //glBindTexture(GL_TEXTURE_2D, texOb->texture);
    //int frame = texOb->updateAnimationFrame();
    
    //glPushMatrix();
    //{
        //glTranslatef(center.x, center.y, center.z);
        //glRotatef(angle, 0.0, 0.0, 1.0);
        //glScalef(size.x, size.y, size.z);
                                    
        //glBegin(GL_QUADS);
        //{   
            //glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
        //}
        //glEnd();
    //}
    //glPopMatrix();
//}

//void drawQuad(const TextureOb& texOb,
         //const glm::vec2& center, 
         //const glm::vec2& size,
         //float angle)
//{
    //glBindTexture(GL_TEXTURE_2D, texOb->texture);
    //int frame = texOb->updateAnimationFrame();
    
    //glPushMatrix();
    //{
        //glTranslatef(center.x, center.y, GUI::POS_Z);
        //glRotatef(angle, 0.0, 0.0, 1.0);
        //glScalef(size.x, size.y, 1.0);
                                    
        //glBegin(GL_QUADS);
        //{   
            //glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
            //glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
        //}
        //glEnd();
    //}
    //glPopMatrix();
//}


//void drawQuad(const TextureOb& texOb,
         //const glm::vec2& center, 
         //const glm::vec2& size,
         //float angle,
         //const TextureOb& texOb_mask,
         //float threshold)
//{
    //glUseProgram(ShaderCollector::Instance().mask);
    //{    
        //int frame = 0;
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texOb_mask->texture);
        //glUniform1i(glGetUniformLocation(ShaderCollector::Instance().mask, "u_TextureMask"), 0);
        
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texOb->texture);        
        //glUniform1i(glGetUniformLocation(ShaderCollector::Instance().mask, "u_TextureTarget"), 1);

        //glUniform1f(glGetUniformLocation(ShaderCollector::Instance().mask, "u_Threshold"), threshold);
                        
        //glPushMatrix();
        //{
            //glTranslatef(center.x, center.y, GUI::POS_Z);
            //glRotatef(angle, 0.0, 0.0, 1.0);
            //glScalef(size.x, size.y, 1.0);
                                        
            //glBegin(GL_QUADS);
            //{   
                //glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(-0.5, -0.5, 0.0);
                //glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f( 0.5, -0.5, 0.0);
                //glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f( 0.5,  0.5, 0.0);
                //glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(-0.5,  0.5, 0.0);      
            //}
            //glEnd();
        //}
        //glPopMatrix();
    //}
    //glUseProgram(0);
    //glActiveTexture(GL_TEXTURE0);
//}

//void drawQuad(const TextureOb& texOb, const Box2D& box)
//{
    //drawQuad(texOb, box.GetCenter(), box.GetSize()*box.GetScale(), box.GetAngle());
//}

//void drawQuadMasked(const TextureOb& texOb, const Box2D& box, const TextureOb& texOb_mask, float threshold)
//{
    //drawQuad(texOb, box.GetCenter(), box.GetSize()*box.GetScale(), box.GetAngle(), texOb_mask, threshold);
//}

//void drawTexturedRect(const TextureOb& texOb, const Rect& rect, float z_pos)
//{
    //glBindTexture(GL_TEXTURE_2D, texOb->texture);
    //int frame = texOb->updateAnimationFrame();
    
    //glBegin(GL_QUADS);
        //glTexCoord3f(texOb->texCoord_bottomLeft_vec[frame].x,  texOb->texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(rect.GetBottomLeft().x,                        rect.GetBottomLeft().y + rect.GetHeight(),     z_pos);
        //glTexCoord3f(texOb->texCoord_bottomRight_vec[frame].x, texOb->texCoord_bottomRight_vec[frame].y, 0); glVertex3f(rect.GetBottomLeft().x + rect.GetWidth(),     rect.GetBottomLeft().y + rect.GetHeight(),     z_pos);
        //glTexCoord3f(texOb->texCoord_topRight_vec[frame].x,    texOb->texCoord_topRight_vec[frame].y,    0); glVertex3f(rect.GetBottomLeft().x + rect.GetWidth(),     rect.GetBottomLeft().y,                       z_pos);
        //glTexCoord3f(texOb->texCoord_topLeft_vec[frame].x,     texOb->texCoord_topLeft_vec[frame].y,     0); glVertex3f(rect.GetBottomLeft().x,                         rect.GetBottomLeft().y,                      z_pos);
    //glEnd();
//}


void drawLine(const TextureOb& texOb, 
              const glm::vec3& start_pos, 
              float len, 
              float angle_inD, 
              int half_h)
{
    glBindTexture(GL_TEXTURE_2D, texOb.texture);
    int frame = 0;//texOb.updateAnimationFrame();
        
    glPushMatrix();
        glTranslatef(start_pos.x, start_pos.y, start_pos.z);
        glRotatef(angle_inD, 0.0, 0.0, 1.0);
    
        glBegin(GL_QUADS);
            glTexCoord3f(texOb.texCoord_bottomLeft_vec[frame].x,  texOb.texCoord_bottomLeft_vec[frame].y,  0); glVertex3f(0,   -half_h, 0.0);
            glTexCoord3f(texOb.texCoord_bottomRight_vec[frame].x, texOb.texCoord_bottomRight_vec[frame].y, 0); glVertex3f(len, -half_h, 0.0);
            glTexCoord3f(texOb.texCoord_topRight_vec[frame].x,    texOb.texCoord_topRight_vec[frame].y,    0); glVertex3f(len,  half_h, 0.0);
            glTexCoord3f(texOb.texCoord_topLeft_vec[frame].x,     texOb.texCoord_topLeft_vec[frame].y,     0); glVertex3f(0,    half_h, 0.0);
        glEnd();
    glPopMatrix();
}

void drawColoredTextWithBackground(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color)
{
    //float char_w = font_size;
    //float char_h = font_size;
            
    //float string_w = char_w * str.size();

    //const TextureOb& texOb_textBg = GuiTextureObCollector::Instance().text_background;
    //Rect rect(pos.x - char_w, pos.y - char_h, string_w, 2*char_h);
        
    //enable_BLEND();
    //{
        //drawTexturedRect(texOb_textBg, rect, GUI::POS_Z);
    //}
    //disable_BLEND();
    
    //Screen::Instance().DrawText(str, font_size, pos, color);
}

void drawColoredText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color)
{
    glPushMatrix();
    {
        glLoadIdentity();
        Screen::Instance().DrawText(str, font_size, pos, color);
    }
    glPopMatrix();
}

void drawInfoIn2Column(
                    const std::vector<std::string>& info_title_list, 
                    const std::vector<std::string>& info_value_list, 
                    const glm::vec2& pos)
{        
    int font_size = 13;
    float char_w = font_size;
    float char_h = 2*font_size;
    
    float max_info_total_str_size = 0;
    float max_info_title_str_size = 0;
    
    for (unsigned int i=1; i<info_title_list.size(); i++)
    {
        int total_length = info_title_list[i].length() + info_value_list[i-1].length();
        int title_length = info_title_list[i].length(); 
    
        if (total_length > max_info_total_str_size)
            max_info_total_str_size = total_length;
    
        if (title_length > max_info_title_str_size)
            max_info_title_str_size = title_length;
    }    

    float info_total_string_w = char_w * max_info_total_str_size;
    float info_total_string_h = char_h * info_title_list.size();
        
    //Rect rect(-char_w, -info_total_string_h, info_total_string_w, info_total_string_h + char_h/2);
    
    glm::ivec4 color_title(250, 250, 250, 255);
    glm::ivec4 color_info(250, 250, 0, 255);

    const TextureOb& texOb_textBg = *GuiTextureObCollector::Instance().text_background;
                                    
    //glPushMatrix();
    {
        //glTranslatef(pos.x, pos.y, 0.0);
    
        //drawTexturedRect(texOb_textBg, rect, -2);
    
        glm::vec2 curpos(info_total_string_w/3, 0.0); 
        Screen::Instance().DrawText(info_title_list[0], font_size+1, curpos);

        for (unsigned int i=1; i<info_title_list.size(); i++)
        {
            glm::vec2 curpos(0.0, -char_h*i); 
            Screen::Instance().DrawText(info_title_list[i], font_size, curpos, color_title);
        
        }        
        for (unsigned int i=0; i<info_value_list.size(); i++)
        {
            glm::vec2 curpos(max_info_title_str_size * (char_w - 1.2), -(char_h*(i + 1))); 
            Screen::Instance().DrawText(info_value_list[i], font_size, curpos, color_info);
        }
    }  
    //glPopMatrix();
}

    
//void renderMesh(const Mesh* const mesh, const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle, bool ZYX)
//{
    //glPushMatrix();
    //{
        //glTranslatef(center.x, center.y, center.z);        
        //glScalef(size.x, size.y, size.z); 
        //if (ZYX)     {    rotateZYX(angle); } // animation rotation along axis X
        //else        {    rotateXYZ(angle); } // animation rotation along axis z
                        
        //mesh->Draw();
    //}
    //glPopMatrix();

//}

//void rotateZYX(const glm::vec3& angle)
//{
    //glRotatef(angle.z, 0.0, 0.0, 1.0); 
    //glRotatef(angle.y, 0.0, 1.0, 0.0); 
    //glRotatef(angle.x, 1.0, 0.0, 0.0); 
//}

//void rotateXYZ(const glm::vec3& angle)
//{
    //glRotatef(angle.x, 1.0, 0.0, 0.0); 
    //glRotatef(angle.y, 0.0, 1.0, 0.0); 
    //glRotatef(angle.z, 0.0, 0.0, 1.0); 
//}

void drawParticleTextured(GLuint texture, const glm::vec2& center, float size, float pos_z)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glPointSize(size);
        
    glBegin(GL_POINTS);
        glVertex3f(center.x, center.y, pos_z);
    glEnd();
}

void drawParticle(const glm::vec2& center, float size, float r, float g, float b, float a)
{        
    glPointSize(size);
            
    glBegin(GL_POINTS);  
    {                 
        glColor4f(r, g, b, a);
        glVertex3f(center.x, center.y, -2);
    }
    glEnd();
}

void drawParticle(const glm::vec2& center, float size, const glm::vec4& color)
{    
    glPointSize(size);
            
    glBegin(GL_POINTS);   
    {            
        glColor4f(color.r, color.g, color.b, color.a);
        glVertex3f(center.x, center.y, -2);
    }
    glEnd();
}

void drawParticle(const glm::vec2& center, float size)
{
    glPointSize(size);
            
    glBegin(GL_POINTS); 
    {                  
        glVertex3f(center.x, center.y, -2);
    }
    glEnd();
}

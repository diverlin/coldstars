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

#include "../resources/textureOb.hpp" // to be removed
#include <resources/GuiTextureObCollector.hpp>
#include <render/Shaders.hpp>

#include "Mesh.hpp"
#include "../common/constants.hpp"

#include "../config/config.hpp"

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
m_ProgramBlur(0),
m_ActiveProgram(0),
m_FboNum(5),
m_IndexFboLastActivated(-1),
m_IndexFboLastDeactivated(-1) 
{}

Renderer::~Renderer() 
{}

void Renderer::ActivateFbo(int index, int w, int h)
{
    if ( (index < 0) or (index >= m_FboNum) )
    {
        std::cout<<"wrong fbo index"; 
        exit(1); 
    }

    m_Fbos[index].Activate(w, h);
    m_IndexFboLastActivated = index;
}

void Renderer::DeactivateFbo(int index)
{
    if ((index < 0) or (index >= m_FboNum))
    {
        std::cout<<"wrong fbo index"; 
        exit(1); 
    }

    if (m_IndexFboLastActivated != index)
    {
        std::cout<<"you are trying to deactivate not active fbo"; 
        exit(1); 
    }
    
    m_Fbos[index].Deactivate();
    m_IndexFboLastDeactivated = index;
}

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


void Renderer::InitPostEffects()
{
    for (int i=0; i<m_FboNum; i++)
    {
        m_Fbos[i].Create();
    }
        
    m_Bloom.Create(m_Shaders.blur, m_Shaders.extractbright, m_Shaders.combine);
    
    int width      = Config::Instance().SCREEN_WIDTH; 
    int height     = Config::Instance().SCREEN_HEIGHT;
    ResizePostEffects(width, height);
}
 
  
void Renderer::ResizePostEffects(int width, int height)
{
    for (int i=0; i<m_FboNum; i++)
    {
        m_Fbos[i].Resize(width, height);
    }
        
    m_Bloom.Resize(width, height);
} 

void Renderer::MakeShortCuts()
{
    {
    m_ProgramLight = m_Shaders.light;
    m_ProgramLightLocation_uProjectionViewMatrix = glGetUniformLocation(m_ProgramLight, "u_ProjectionViewMatrix");
    m_ProgramLightLocation_uModelMatrix          = glGetUniformLocation(m_ProgramLight, "u_ModelMatrix");
    m_ProgramLightLocation_uNormalMatrix         = glGetUniformLocation(m_ProgramLight, "u_NormalModelMatrix");
            
    m_ProgramLightLocation_uLightPos = glGetUniformLocation(m_ProgramLight, "u_LightPos");
    m_ProgramLightLocation_uEyePos   = glGetUniformLocation(m_ProgramLight, "u_EyePos");
    
    m_ProgramLightLocation_uDiffColor     = glGetUniformLocation(m_ProgramLight, "u_DiffColor");
    m_ProgramLightLocation_uAmbientColor  = glGetUniformLocation(m_ProgramLight, "u_AmbientColor");                    
        
    m_ProgramLightLocation_uTexture  = glGetUniformLocation(m_ProgramLight, "u_Texture"); 
    }            
    
    m_ProgramBlur  = m_Shaders.blur;
}
        
void Renderer::SetPerspectiveProjection(float w, float h) 
{        
    m_ProjectionMatrix = glm::perspective(90.0f, w/h, 0.1f, 1000.0f); 
    UpdateProjectionViewMatrix();
}

void Renderer::SetOrthogonalProjection(float w, float h) 
{        
    m_ProjectionMatrix = glm::ortho(0.0f, w, 0.0f, h, 0.1f, 1000.0f);
    UpdateProjectionViewMatrix();
}

void Renderer::ComposeViewMatrix(const glm::mat4& Vm)  
{ 
    m_ViewMatrix = Vm; 
    UpdateProjectionViewMatrix(); 
} 
                                
void Renderer::UpdateProjectionViewMatrix() 
{ 
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix; 
}


void Renderer::DrawQuadTransparent(const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    DrawMeshTransparent(*m_MeshQuad, textureOb, ModelMatrix);
}

void Renderer::DrawQuad(const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    DrawMesh(*m_MeshQuad, textureOb, ModelMatrix);
}

void Renderer::DrawQuad(const TextureOb& texOb, const Box2D& box) const
{
    // ugly start
    glm::vec2 pos = box.GetCenter();
    glm::mat4 TranslationMatrix = glm::translate(glm::vec3(pos.x, pos.y, -2.0f));
     
    glm::quat Qx, Qy, Qz;
    
    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);   
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z); 
       
    glm::mat4 RotationMatrix = glm::toMat4(Qx*Qy*Qz);
    
    glm::vec2 size = box.GetSize()*box.GetScale();
    glm::mat4 ScaleMatrix = glm::scale(glm::vec3(size.x, size.y, 1.0f));
      
    glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
    // ugly end

    DrawMesh(*m_MeshQuad, texOb, ModelMatrix);
}

void Renderer::DrawMesh(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    UseProgram(m_Shaders.base);
	{
	    glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_ProjectionViewMatrix[0][0]);
	    glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);
	
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture); 
	    glUniform1i(glGetUniformLocation(m_Shaders.base, "u_Texture"), 0);
	                        
	    mesh.Draw();
	}
}

void Renderer::DrawMeshTransparent(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    enable_BLEND();
    {
        DrawMesh(mesh, textureOb, ModelMatrix);
    }
    disable_BLEND();
}

void Renderer::DrawMeshLight(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    float ambient_factor = 0.25;       
    const glm::vec3& eye_pos = Screen::Instance().GetCamera().GetPos();
 
    UseProgram(m_ProgramLight);
    {
	    glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(ModelMatrix)));
	
	    glUniformMatrix4fv(m_ProgramLightLocation_uProjectionViewMatrix, 1, GL_FALSE, &m_ProjectionViewMatrix[0][0]);
	    glUniformMatrix4fv(m_ProgramLightLocation_uModelMatrix         , 1, GL_FALSE, &ModelMatrix[0][0]);
	    glUniformMatrix3fv(m_ProgramLightLocation_uNormalMatrix        , 1, GL_FALSE, &NormalModelMatrix[0][0]);
	            
	    glUniform3f(m_ProgramLightLocation_uLightPos, 0.0f, 0.0f, 200.0);
	    glUniform3f(m_ProgramLightLocation_uEyePos  , eye_pos.x, eye_pos.y, eye_pos.z);
	    
	    glUniform4f(m_ProgramLightLocation_uDiffColor,    m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	    glUniform4f(m_ProgramLightLocation_uAmbientColor, ambient_factor*m_Color.r, ambient_factor*m_Color.g, ambient_factor*m_Color.b, ambient_factor*m_Color.a);
	    
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture); 
	    glUniform1i(m_ProgramLightLocation_uTexture, 0);
	                        
	    mesh.Draw();
	}
}
/*
void Renderer::DrawMeshLightNormalMap(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    float ambient_factor = 0.25; 
    const glm::vec3& eye_pos = Screen::Instance().GetCamera().GetPos();
   
    UseProgram(m_Shaders.light_normalmap);

	glUniform3f(glGetUniformLocation(m_Shaders.light_normalmap, "u_lightPos"), 0.0f, 0.0f, 200.0);
	glUniform3f(glGetUniformLocation(m_Shaders.light_normalmap, "u_eyePos"), eye_pos.x, eye_pos.y, eye_pos.z);
	glUniform4f(glGetUniformLocation(m_Shaders.light_normalmap, "u_diffColor"), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glUniform4f(glGetUniformLocation(m_Shaders.light_normalmap, "u_ambientColor"), ambient_factor*m_Color.r, ambient_factor*m_Color.g, ambient_factor*m_Color.b, ambient_factor*m_Color.a);
			
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture);
	glUniform1i(glGetUniformLocation(m_Shaders.light_normalmap, "u_texture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureOb.GetData().normalmap);
	glUniform1i(glGetUniformLocation(m_Shaders.light_normalmap, "u_normalmap"), 1);
			
	ComposeModelMatrix(ModelMatrix);                     
	mesh.Draw();
} */

void Renderer::DrawMeshTransparentLight(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    enable_BLEND();
        DrawMeshLight(mesh, textureOb, ModelMatrix);
    disable_BLEND();
}

void Renderer::DrawMeshMultiTextured(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    UseProgram(m_Shaders.multitexturing);
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.multitexturing, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_ProjectionViewMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.multitexturing, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture);
		glUniform1i(glGetUniformLocation(m_Shaders.multitexturing, "Texture_0"), 0);
		
		glActiveTexture(GL_TEXTURE1);                                
		glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture);
		glUniform1i(glGetUniformLocation(m_Shaders.multitexturing, "Texture_1"), 1);
		
		glUniform2f(glGetUniformLocation(m_Shaders.multitexturing, "displ"), textureOb.GetData().texture_offset.x, textureOb.GetData().texture_offset.y);        
				  
		mesh.Draw();
	}
}  

void Renderer::DrawPostEffectCombined(const std::vector<GLuint>& textures, int w, int h) const 
{
    // ugly 
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly 

    UseProgram(m_Shaders.combine);
    {
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.combine, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.combine, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
		
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_TextureScene"), 0);
	
		
		glActiveTexture(GL_TEXTURE1);                                
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass0_tex1"), 1);
		
		glActiveTexture(GL_TEXTURE2);        
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass0_tex2"), 2);
		
		glActiveTexture(GL_TEXTURE3);                                
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass0_tex3"), 3);
		
		glActiveTexture(GL_TEXTURE4);                                
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass0_tex4"), 4);
		
		
		glActiveTexture(GL_TEXTURE5);                                
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass1_tex1"), 5);
		
		glActiveTexture(GL_TEXTURE6);                                
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass1_tex2"), 6);
		
		glActiveTexture(GL_TEXTURE7);                                
		glBindTexture(GL_TEXTURE_2D, textures[7]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass1_tex3"), 7);
		
		glActiveTexture(GL_TEXTURE8);                                
		glBindTexture(GL_TEXTURE_2D, textures[8]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass1_tex4"), 8);
		
		
		glActiveTexture(GL_TEXTURE9);                                
		glBindTexture(GL_TEXTURE_2D, textures[9]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass2_tex1"), 9);
		
		glActiveTexture(GL_TEXTURE10);                                
		glBindTexture(GL_TEXTURE_2D, textures[10]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass2_tex2"), 10);
		
		glActiveTexture(GL_TEXTURE11);                                
		glBindTexture(GL_TEXTURE_2D, textures[11]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass2_tex3"), 11);
		
		glActiveTexture(GL_TEXTURE12);                                
		glBindTexture(GL_TEXTURE_2D, textures[12]);
		glUniform1i(glGetUniformLocation(m_Shaders.combine, "u_Pass2_tex4"), 12);
	
		m_MeshQuad->Draw();
	}
}

void Renderer::DrawPostEffectFogWar(GLuint texture, int w, int h, const glm::vec3& center, const glm::vec2& world_coord, float radius) const
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    UseProgram(m_Shaders.fogwarspark);
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.fogwarspark, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.fogwarspark, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i (glGetUniformLocation(m_Shaders.fogwarspark, "sceneTex"), 0);
	
		glUniform2f(glGetUniformLocation(m_Shaders.fogwarspark, "resolution"), w, h);
		glUniform2f(glGetUniformLocation(m_Shaders.fogwarspark, "center"), center.x/(w*scale), center.y/(h*scale));
		glUniform1f(glGetUniformLocation(m_Shaders.fogwarspark, "radius"), radius/(h*scale));
		glUniform2f(glGetUniformLocation(m_Shaders.fogwarspark, "world_coord"), world_coord.x/(w*scale), world_coord.y/(h*scale));
	
		glUniform1f(glGetUniformLocation(m_Shaders.fogwarspark, "dcolor"), 0.5f/*npc->GetVehicle()->GetStarSystem()->GetStar()->GetDeltaColor()*/);
	
		m_MeshQuad->Draw();
	}
}


void Renderer::DrawPostEffectShockWaves(GLuint scene_texture, int w, int h, int i, float center_array[10][2], float xyz_array[10][3], float time_array[10]) const
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
   
    UseProgram(m_Shaders.shockwave);
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.shockwave, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.shockwave, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, scene_texture);
		glUniform1i (glGetUniformLocation(m_Shaders.shockwave, "u_Texture"), 0);
	
		glUniform1i (glGetUniformLocation(m_Shaders.shockwave, "distortion_num"), i);
		glUniform2fv(glGetUniformLocation(m_Shaders.shockwave, "center"),      i, *center_array);
		glUniform3fv(glGetUniformLocation(m_Shaders.shockwave, "shockParams"), i, *xyz_array);
		glUniform1fv(glGetUniformLocation(m_Shaders.shockwave, "time"),        i, time_array);
	
		m_MeshQuad->Draw();
	}
}



void Renderer::DrawPostEffectExtractBright(GLuint scene_texture, int w, int h, float brightThreshold) const
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
                             
    UseProgram(m_Shaders.extractbright);
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.extractbright, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_Shaders.extractbright, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, scene_texture);
		glUniform1i(glGetUniformLocation(m_Shaders.extractbright, "source"), 0);
	
		glUniform1f(glGetUniformLocation(m_Shaders.extractbright, "threshold"), brightThreshold);
		
		m_MeshQuad->Draw();
	}
}

void Renderer::DrawPostEffectCombinedDebug(const std::vector<GLuint>& textures, int w, int h) const 
{
    float ratio = (float)h/w;
    unsigned int quad_num = textures.size();
    unsigned int quad_num_w = quad_num / 3;
    unsigned int quad_num_h = quad_num / 4;

    int size_w = w/quad_num_w;  
    int size_h = h/quad_num_w;  

    for (unsigned int i=0; i<quad_num_w; ++i)
    {
        for (unsigned int j=0; j<quad_num_h; ++j)
        {
            // ugly 
            glm::mat4 TranslateMatrix = glm::translate(glm::vec3(size_w+i*size_w, size_h+j*size_h, -499.0f));
            glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(size_w, size_h, 1.0f));
            glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
            // ugly 
    
            UseProgram(m_Shaders.base);
			{
				glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_ProjectionViewMatrix[0][0]);
				glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);
				
				glActiveTexture(GL_TEXTURE0);                                
				glBindTexture(GL_TEXTURE_2D, textures[i+j]);
				glUniform1i(glGetUniformLocation(m_Shaders.base, "u_TextureScene"), 0);
		
				m_MeshQuad->Draw();
			}
        }
    }
}

void Renderer::DrawPostEffectVolumetricLight(const glm::vec2& world_coord, int w, int h)
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
    
    UseProgram(m_Shaders.volumetriclight);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_Shaders.volumetriclight, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_Shaders.volumetriclight, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, m_Bloom.GetFboFinal().GetTexture());
        glUniform1i(glGetUniformLocation(m_Shaders.volumetriclight, "FullSampler"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, m_Bloom.GetTextureBlured());
        glUniform1i(glGetUniformLocation(m_Shaders.volumetriclight, "BlurSampler"), 1);

        glUniform4f(glGetUniformLocation(m_Shaders.volumetriclight, "sun_pos"), -world_coord.x/(w*scale), -world_coord.y/(h*scale), -100.0, 1.0);

        m_MeshQuad->Draw(); 
    }
}

void Renderer::DrawPostEffectBlur(GLuint texture, int w, int h) const
{  
    // ugly  
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    UseProgram(m_ProgramBlur);
    {    
        glActiveTexture(GL_TEXTURE0);                              
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(m_ProgramBlur, "sceneTex"), 0);
        
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramBlur, "u_ProjectionMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramBlur, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform1f(glGetUniformLocation(m_ProgramBlur, "rt_w"), 3*w); 
        glUniform1f(glGetUniformLocation(m_ProgramBlur, "rt_h"), 3*h);
        glUniform1f(glGetUniformLocation(m_ProgramBlur, "vx_offset"), 1.0);
        
        m_MeshQuad->Draw();
    }
}

void Renderer::DrawScreenQuadTextured(GLuint texture, int w, int h) const
{
    // ugly 
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, -499.0f));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    UseProgram(m_Shaders.base);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_Shaders.base, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); 
        glUniform1i(glGetUniformLocation(m_Shaders.base, "u_Texture"), 0);
                    
        m_MeshQuad->Draw();
    }
}
 
void Renderer::DrawParticles(const Mesh& mesh, const TextureOb& textureOb, const glm::mat4& ModelMatrix) const
{
    enable_BLEND();
    enable_POINTSPRITE();
    {   
        UseProgram(m_Shaders.particle);
        {    
            glActiveTexture(GL_TEXTURE0);                                
            glBindTexture(GL_TEXTURE_2D, textureOb.GetData().texture);
            glUniform1i(glGetUniformLocation(m_Shaders.particle, "uTexture_0"), 0);

            glUniformMatrix4fv(glGetUniformLocation(m_Shaders.particle, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_ProjectionViewMatrix[0][0]);  
            glUniformMatrix4fv(glGetUniformLocation(m_Shaders.particle, "u_ModelMatrix"),          1, GL_FALSE, &ModelMatrix[0][0]);      
      
            mesh.Draw(GL_POINTS);
        }
    }
    disable_POINTSPRITE();
    disable_BLEND();
}

void Renderer::UseProgram(GLuint program) const
{
	if (m_ActiveProgram != program)
    {
        glUseProgram(program);
        m_ActiveProgram = program; 
    }
}
        
void Renderer::DrawAxis(const glm::mat4& ModelMatrix, float width) const
{
    //float r = 1.5f;
    
    //glDisable(GL_TEXTURE_2D);
    
    //ComposeModelMatrix(Mm); 
    
    //glLineWidth(width);

    //// draw axis X
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glBegin(GL_LINES);
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //glVertex3f(r, 0.0f, 0.0f);
    //glEnd();
                
    //// draw axis Y    
    //glColor3f(0.0f, 1.0f, 0.0f);    
    //glBegin(GL_LINES);        
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //glVertex3f(0.0f, r, 0.0f);
    //glEnd();

    //// draw axis Z    
    //glColor3f(0.0f, 0.0f, 1.0f);    
    //glBegin(GL_LINES);        
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //glVertex3f(0.0f, 0.0f, r);
    //glEnd();

    //glColor3f(1.0f, 1.0f, 1.0f);
    
    //glEnable(GL_TEXTURE_2D);
}
      
      
void Renderer::DrawVector(const glm::vec3& v, const glm::vec3& pos, float length, float width) const
{
    //glDisable(GL_TEXTURE_2D);
    
    //ComposeModelMatrix(glm::mat4(1.0f)); 
    
    //glLineWidth(width); 
    //glColor3f(1.0f, 1.0f, 1.0f);
    
    //glBegin(GL_LINES);  
        //glVertex3f(pos.x, pos.y, pos.z);
        //glVertex3f(pos.x+length*v.x, pos.y+length*v.y, pos.z+length*v.z);
    //glEnd();
    
    //glEnable(GL_TEXTURE_2D);
}

void Renderer::DrawVector(const glm::vec3& v, const glm::mat4& ModelMatrix, float width) const
{
    //glDisable(GL_TEXTURE_2D);
    
    //ComposeModelMatrix(Mm); 
    
    //glLineWidth(width); 
    //glColor3f(1.0f, 1.0f, 1.0f);
    
    //glBegin(GL_LINES);        
        //glVertex3f(0.0f, 0.0f, 0.0f);
        //glVertex3f(v.x, v.y, v.z);
    //glEnd();
    
    //glEnable(GL_TEXTURE_2D);
}






// TODO BELOW

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
    //glPushMatrix();
    //{
        //glLoadIdentity();
        //Screen::Instance().DrawText(str, font_size, pos, color);
    //}
    //glPopMatrix();
}

void drawInfoIn2Column(
                    const std::vector<std::string>& info_title_list, 
                    const std::vector<std::string>& info_value_list, 
                    const glm::vec2& pos)
{ /*       
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

*/
}

  

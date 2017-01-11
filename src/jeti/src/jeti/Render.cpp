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
#include <Screen.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Material.hpp> // to be removed
#include <Shaders.hpp>
#include <ShaderLoader.hpp>

#include <Mesh.hpp>
#include <Camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// for ugly
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <meti/QuaternionUtils.hpp>
// for ugly

namespace jeti {

Renderer::Renderer()
{
    m_light.position    = glm::vec3(0.0f, 0.0f, 200.0f);
    m_light.ambient     = glm::vec4(0.2f);
    m_light.diffuse     = glm::vec4(1.0f);
//    m_light.specular    = glm::vec4(1.5f); // visual artefact
    m_light.specular    = glm::vec4(0.0f);
    m_light.attenuation = glm::vec3(0.1f);
}

Renderer::~Renderer() 
{
    delete m_meshQuad;
    delete m_meshAxis;
}


void Renderer::init(Camera* camera, int w, int h)
{
    if (m_initialized)
        return;

    m_camera = camera;

    glewInit();

    m_meshQuad = new Mesh;

    //
    m_meshAxis = new Mesh;

    std::vector<glm::vec3> vertices;
    float r = 1.5;
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(r, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, r, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, r));

    std::vector<glm::vec4> colors;
    colors.push_back(glm::vec4(1.0, 0.0, 0.0, 1.0));
    colors.push_back(glm::vec4(1.0, 0.0, 0.0, 1.0));
    colors.push_back(glm::vec4(0.0, 1.0, 0.0, 1.0));
    colors.push_back(glm::vec4(0.0, 1.0, 0.0, 1.0));
    colors.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
    colors.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));

    m_meshAxis->fillVertices(vertices, colors);
    //

    m_w = w;
    m_h = h;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

    glShadeModel(GL_SMOOTH);

    setOrthogonalProjection(w, h);

    m_shaders.basetexture     = compile_program(SHADERS_PATH+"basetexture.vert",       SHADERS_PATH+"basetexture.frag");
    m_shaders.basecolor       = compile_program(SHADERS_PATH+"basecolor.vert",         SHADERS_PATH+"basecolor.frag");
    m_shaders.black2alpha     = compile_program(SHADERS_PATH+"black2alpha.vert",       SHADERS_PATH+"black2alpha.frag");
    m_shaders.shockwave       = compile_program(SHADERS_PATH+"shockwave.vert",         SHADERS_PATH+"shockwave.frag");
    m_shaders.volumetriclight = compile_program(SHADERS_PATH+"volumetricLight.vert",   SHADERS_PATH+"volumetricLight.frag");
    m_shaders.light           = compile_program(SHADERS_PATH+"light.vert",             SHADERS_PATH+"light.frag");
    m_shaders.light_normalmap = compile_program(SHADERS_PATH+"light_normalmap.vert",   SHADERS_PATH+"light_normalmap.frag");
    m_shaders.blur            = compile_program(SHADERS_PATH+"blur.vert",              SHADERS_PATH+"blur.frag");
    m_shaders.extractbright   = compile_program(SHADERS_PATH+"extractBright.vert",     SHADERS_PATH+"extractBright.frag");
    m_shaders.combine         = compile_program(SHADERS_PATH+"combine.vert",           SHADERS_PATH+"combine.frag");
    m_shaders.multitexturing  = compile_program(SHADERS_PATH+"multitex.vert",          SHADERS_PATH+"multitex.frag");
    m_shaders.blank           = compile_program(SHADERS_PATH+"blank.vert",             SHADERS_PATH+"blank.frag");
    m_shaders.fogwarspark     = compile_program(SHADERS_PATH+"fogwarspark.vert",       SHADERS_PATH+"fogwarspark.frag");
    m_shaders.flash           = compile_program(SHADERS_PATH+"flash.vert",             SHADERS_PATH+"flash.frag");
    m_shaders.mask            = compile_program(SHADERS_PATH+"mask.vert",              SHADERS_PATH+"mask.frag");
    m_shaders.particle        = compile_program(SHADERS_PATH+"particle.vert",          SHADERS_PATH+"particle.frag");
    m_shaders.starfield       = compile_program(SHADERS_PATH+"starfield.vert",         SHADERS_PATH+"starfield.frag");

    __initPostEffects();
    __makeShortCuts();

    m_initialized = true;
}

void Renderer::activateFbo(int index, int w, int h)
{
    if ( (index < 0) or (index >= m_fboNum) ) {
        throw std::runtime_error("wrong fbo index");
    }

    m_fbos[index].Activate(w, h);
    m_indexFboLastActivated = index;
}

void Renderer::deactivateFbo(int index)
{
    if ((index < 0) or (index >= m_fboNum)) {
        throw std::runtime_error("wrong fbo index");
    }

    if (m_indexFboLastActivated != index) {
        throw std::runtime_error("you are trying to deactivate not active fbo");
    }
    
    m_fbos[index].Deactivate();
    m_indexFboLastDeactivated = index;
}

void Renderer::__initPostEffects()
{
    for (int i=0; i<m_fboNum; i++) {
        m_fbos[i].Create();
    }
        
    m_bloom.Create(m_shaders.blur, m_shaders.extractbright, m_shaders.combine);
    __resizePostEffects(m_w, m_h);
}
 
  
void Renderer::__resizePostEffects(int width, int height)
{
    for (int i=0; i<m_fboNum; i++) {
        m_fbos[i].Resize(width, height);
    }
        
    m_bloom.Resize(width, height);
} 

void Renderer::__makeShortCuts()
{
    {
    m_programLight = m_shaders.light;
    m_programLightLocation_uProjectionViewMatrix = glGetUniformLocation(m_programLight, "u_Matrices.projectionView");
    m_programLightLocation_uModelMatrix          = glGetUniformLocation(m_programLight, "u_Matrices.model");
    m_programLightLocation_uNormalMatrix         = glGetUniformLocation(m_programLight, "u_Matrices.normal");
            
    m_programLightLocation_uEyePos   = glGetUniformLocation(m_programLight, "u_EyePos");
        
    m_programLightLocation_uTexture  = glGetUniformLocation(m_programLight, "u_Texture");
    }            
    
    m_programBlur  = m_shaders.blur;
}
        
void Renderer::setPerspectiveProjection(float w, float h)
{        
    m_projectionMatrix = glm::perspective(90.0f, w/h, ZNEAR, ZFAR);
    __updateProjectionViewMatrix();
}

void Renderer::setOrthogonalProjection(float w, float h)
{        
    m_projectionMatrix = glm::ortho(-w/2 * m_scale, w/2 * m_scale, -h/2 * m_scale, h/2 * m_scale, ZNEAR, ZFAR);
    __updateProjectionViewMatrix();
}

void Renderer::composeViewMatrix(const glm::mat4& Vm)
{ 
    m_viewMatrix = Vm;
    __updateProjectionViewMatrix();
} 
                                
void Renderer::__updateProjectionViewMatrix()
{ 
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}


void Renderer::drawQuad(const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    drawMesh(*m_meshQuad, textureOb, ModelMatrix);
}

void Renderer::drawQuad(const control::Material& texOb, const ceti::Box2D& box) const
{
    // ugly start
    glm::vec2 pos = box.center();
    glm::mat4 TranslationMatrix = glm::translate(glm::vec3(pos.x, pos.y, -2.0f));
     
    glm::quat Qx, Qy, Qz;
    
    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);   
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z); 
       
    glm::mat4 RotationMatrix = glm::toMat4(Qx*Qy*Qz);
    
    glm::vec2 size = box.size()*box.GetScale();
    glm::mat4 ScaleMatrix = glm::scale(glm::vec3(size.x, size.y, 1.0f));
      
    glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
    // ugly end

    drawMesh(*m_meshQuad, texOb, ModelMatrix);
}

void Renderer::drawMesh(const Mesh& mesh, const glm::mat4& modelMatrix) const
{
    __useProgram(m_shaders.basecolor);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ModelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        mesh.draw();
    }
}

void Renderer::drawMesh(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& modelMatrix) const
{
    __useTransparentMode(textureOb.model()->use_alpha);
 	
    __useProgram(m_shaders.basetexture);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ModelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);
	
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
        glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_Texture"), 0);
	                        
        mesh.draw();
    }
}

void Renderer::drawMeshLight(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    if (mesh.isFlat()) {
        drawMesh(mesh, textureOb, ModelMatrix);
        return;
    }

    float ambient_factor = 0.25;
    const glm::vec3& eye_pos = m_camera->lookFrom();

    const model::Material& material = *textureOb.model();

    __useTransparentMode(material.use_alpha);
 	 	
    __useProgram(m_programLight);
    {
	    glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(ModelMatrix)));
	
        glUniformMatrix4fv(m_programLightLocation_uProjectionViewMatrix, 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(m_programLightLocation_uModelMatrix         , 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix3fv(m_programLightLocation_uNormalMatrix        , 1, GL_FALSE, &NormalModelMatrix[0][0]);
	            
        glUniform3fv(m_programLightLocation_uEyePos, 1, glm::value_ptr(eye_pos));

        glUniform3fv(glGetUniformLocation(m_programLight, "u_Light.position"), 1, glm::value_ptr(m_light.position));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.ambient"),  1, glm::value_ptr(m_light.ambient));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.diffuse"),  1, glm::value_ptr(m_light.diffuse));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.specular"), 1, glm::value_ptr(m_light.specular));
        glUniform3fv(glGetUniformLocation(m_programLight, "u_Light.attenuation"), 1, glm::value_ptr(m_light.attenuation));

        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.ambient"),  1, glm::value_ptr(material.ambient));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.diffuse"),  1, glm::value_ptr(material.diffuse));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.specular"), 1, glm::value_ptr(material.specular));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.emission"), 1, glm::value_ptr(material.emission));
        glUniform1f(glGetUniformLocation(m_programLight,  "u_Material.shininess"), material.shininess);

	    glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
        glUniform1i(m_programLightLocation_uTexture, 0);
	                        
	    mesh.draw();
	}
}

void Renderer::drawMeshLightNormalMap(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    if (mesh.isFlat()) {
        drawMesh(mesh, textureOb, ModelMatrix);
        return;
    }

    float ambient_factor = 0.25; 
    const glm::vec3& eye_pos = m_camera->lookTo();
   
    __useTransparentMode(textureOb.model()->use_alpha);
    	
    __useProgram(m_shaders.light_normalmap);
	{
	    glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(ModelMatrix)));          

        glUniformMatrix4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.projectionView"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.model")         , 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.normal")        , 1, GL_FALSE, &NormalModelMatrix[0][0]);
      
        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_EyePos"), 1, glm::value_ptr(eye_pos));

        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.position"), 1, glm::value_ptr(m_light.position));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.ambient"),  1, glm::value_ptr(m_light.ambient));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.diffuse"),  1, glm::value_ptr(m_light.diffuse));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.specular"), 1, glm::value_ptr(m_light.specular));
        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.attenuation"), 1, glm::value_ptr(m_light.attenuation));

        const model::Material& material = *textureOb.model();
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.ambient"),  1, glm::value_ptr(material.ambient));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.diffuse"),  1, glm::value_ptr(material.diffuse));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.specular"), 1, glm::value_ptr(material.specular));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.emission"), 1, glm::value_ptr(material.emission));
        glUniform1f(glGetUniformLocation(m_shaders.light_normalmap,  "u_Material.shininess"), material.shininess);

		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
        glUniform1i(glGetUniformLocation(m_shaders.light_normalmap, "u_Texture"), 0);
		
		glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->normalmap);
        glUniform1i(glGetUniformLocation(m_shaders.light_normalmap, "u_Normalmap"), 1);
                  
		mesh.draw();
	}
} 

void Renderer::drawMeshMultiTextured(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    __useTransparentMode(textureOb.model()->use_alpha);
 	
    __useProgram(m_shaders.multitexturing);
	{
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.multitexturing, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.multitexturing, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
        glUniform1i(glGetUniformLocation(m_shaders.multitexturing, "Texture_0"), 0);
		
		glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
        glUniform1i(glGetUniformLocation(m_shaders.multitexturing, "Texture_1"), 1);
		
        glUniform2f(glGetUniformLocation(m_shaders.multitexturing, "displ"), textureOb.model()->texture_offset.x, textureOb.model()->texture_offset.y);
				  
		mesh.draw();
	}
}  

void Renderer::drawPostEffectCombined(const std::vector<GLuint>& textures, int w, int h) const
{
    // ugly 
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly 

    __usePostEffectMode(true);
 	
    __useProgram(m_shaders.combine);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.combine, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.combine, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
		
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, textures[0]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_TextureScene"), 0);
	
		
		glActiveTexture(GL_TEXTURE1);                                
		glBindTexture(GL_TEXTURE_2D, textures[1]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass0_tex1"), 1);
		
		glActiveTexture(GL_TEXTURE2);        
		glBindTexture(GL_TEXTURE_2D, textures[2]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass0_tex2"), 2);
		
		glActiveTexture(GL_TEXTURE3);                                
		glBindTexture(GL_TEXTURE_2D, textures[3]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass0_tex3"), 3);
		
		glActiveTexture(GL_TEXTURE4);                                
		glBindTexture(GL_TEXTURE_2D, textures[4]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass0_tex4"), 4);
		
		
		glActiveTexture(GL_TEXTURE5);                                
		glBindTexture(GL_TEXTURE_2D, textures[5]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass1_tex1"), 5);
		
		glActiveTexture(GL_TEXTURE6);                                
		glBindTexture(GL_TEXTURE_2D, textures[6]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass1_tex2"), 6);
		
		glActiveTexture(GL_TEXTURE7);                                
		glBindTexture(GL_TEXTURE_2D, textures[7]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass1_tex3"), 7);
		
		glActiveTexture(GL_TEXTURE8);                                
		glBindTexture(GL_TEXTURE_2D, textures[8]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass1_tex4"), 8);
		
		
		glActiveTexture(GL_TEXTURE9);                                
		glBindTexture(GL_TEXTURE_2D, textures[9]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass2_tex1"), 9);
		
		glActiveTexture(GL_TEXTURE10);                                
		glBindTexture(GL_TEXTURE_2D, textures[10]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass2_tex2"), 10);
		
		glActiveTexture(GL_TEXTURE11);                                
		glBindTexture(GL_TEXTURE_2D, textures[11]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass2_tex3"), 11);
		
		glActiveTexture(GL_TEXTURE12);                                
		glBindTexture(GL_TEXTURE_2D, textures[12]);
        glUniform1i(glGetUniformLocation(m_shaders.combine, "u_Pass2_tex4"), 12);
	
        m_meshQuad->draw();
	}
}

void Renderer::drawPostEffectFogWar(GLuint texture, int w, int h, const glm::vec3& center, const glm::vec2& world_coord, float radius) const
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __usePostEffectMode(true);
 	
    __useProgram(m_shaders.fogwarspark);
	{
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.fogwarspark, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.fogwarspark, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i (glGetUniformLocation(m_shaders.fogwarspark, "sceneTex"), 0);
	
        glUniform2f(glGetUniformLocation(m_shaders.fogwarspark, "resolution"), w, h);
        glUniform2f(glGetUniformLocation(m_shaders.fogwarspark, "center"), center.x/(w*scale), center.y/(h*scale));
        glUniform1f(glGetUniformLocation(m_shaders.fogwarspark, "radius"), radius/(h*scale));
        glUniform2f(glGetUniformLocation(m_shaders.fogwarspark, "world_coord"), world_coord.x/(w*scale), world_coord.y/(h*scale));
	
        glUniform1f(glGetUniformLocation(m_shaders.fogwarspark, "dcolor"), 0.5f/*npc->vehicle()->starsystem()->GetStar()->GetDeltaColor()*/);
	
        m_meshQuad->draw();
	}
}


void Renderer::drawPostEffectShockWaves(GLuint scene_texture, int w, int h, int count, float center_array[10][2], float xyz_array[10][3], float time_array[10]) const
{
    // ugly 
    //float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
   
    __usePostEffectMode(true);
    	
    __useProgram(m_shaders.shockwave);
	{
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.shockwave, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.shockwave, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, scene_texture);
        glUniform1i (glGetUniformLocation(m_shaders.shockwave, "u_Texture"), 0);
	
        glUniform1i (glGetUniformLocation(m_shaders.shockwave, "distortion_num"), count);
        glUniform2fv(glGetUniformLocation(m_shaders.shockwave, "center"),      count, *center_array);
        glUniform3fv(glGetUniformLocation(m_shaders.shockwave, "shockParams"), count, *xyz_array);
        glUniform1fv(glGetUniformLocation(m_shaders.shockwave, "time"),        count, time_array);
	
        m_meshQuad->draw();
	}
}



void Renderer::drawPostEffectExtractBright(GLuint scene_texture, int w, int h, float brightThreshold) const
{
    // ugly 
    //float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
      
    __usePostEffectMode(true);
       	                       
    __useProgram(m_shaders.extractbright);
	{
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.extractbright, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.extractbright, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);
	
		glActiveTexture(GL_TEXTURE0);                                
		glBindTexture(GL_TEXTURE_2D, scene_texture);
        glUniform1i(glGetUniformLocation(m_shaders.extractbright, "source"), 0);
	
        glUniform1f(glGetUniformLocation(m_shaders.extractbright, "threshold"), brightThreshold);
		
        m_meshQuad->draw();
	}
}

void Renderer::drawPostEffectCombinedDebug(const std::vector<GLuint>& textures, int w, int h) const
{
    //float ratio = (float)h/w;
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
            glm::mat4 TranslateMatrix = glm::translate(glm::vec3(size_w+i*size_w, size_h+j*size_h, SCREEM_QUAD_ZPOS));
            glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(size_w, size_h, 1.0f));
            glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
            // ugly 
    
            __usePostEffectMode(true);
     	
            __useProgram(m_shaders.basetexture);
			{
                glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);
				
				glActiveTexture(GL_TEXTURE0);                                
				glBindTexture(GL_TEXTURE_2D, textures[i+j]);
                glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_TextureScene"), 0);
		
                m_meshQuad->draw();
			}
        }
    }
}

void Renderer::drawPostEffectVolumetricLight(const glm::vec2& world_coord, int w, int h)
{
    // ugly 
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly
    
    __usePostEffectMode(true);
     	
    __useProgram(m_shaders.volumetriclight);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.volumetriclight, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.volumetriclight, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, m_bloom.GetFboFinal().GetTexture());
        glUniform1i(glGetUniformLocation(m_shaders.volumetriclight, "FullSampler"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, m_bloom.GetTextureBlured());
        glUniform1i(glGetUniformLocation(m_shaders.volumetriclight, "BlurSampler"), 1);

        glUniform4f(glGetUniformLocation(m_shaders.volumetriclight, "sun_pos"), -world_coord.x/(w*scale), -world_coord.y/(h*scale), -100.0, 1.0);

        m_meshQuad->draw();
    }
}

void Renderer::drawPostEffectBlur(GLuint texture, int w, int h) const
{  
    // ugly  
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __usePostEffectMode(true);
 	
    __useProgram(m_programBlur);
    {    
        glActiveTexture(GL_TEXTURE0);                              
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(m_programBlur, "sceneTex"), 0);
        
        glUniformMatrix4fv(glGetUniformLocation(m_programBlur, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_programBlur, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform1f(glGetUniformLocation(m_programBlur, "rt_w"), 3*w);
        glUniform1f(glGetUniformLocation(m_programBlur, "rt_h"), 3*h);
        glUniform1f(glGetUniformLocation(m_programBlur, "vx_offset"), 1.0);
        
        m_meshQuad->draw();
    }
}

void Renderer::drawScreenQuadTextured(GLuint texture, int w, int h) const
{
    // ugly 
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __usePostEffectMode(true);
 	
    __useProgram(m_shaders.basetexture);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); 
        glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_Texture"), 0);
                    
        m_meshQuad->draw();
    }
}
 
void Renderer::drawParticles(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    __enable_POINTSPRITE();
    {   
        __useTransparentMode(true);
     	
        __useProgram(m_shaders.particle);
        {    
            glActiveTexture(GL_TEXTURE0);                                
            glBindTexture(GL_TEXTURE_2D, textureOb.model()->texture);
            glUniform1i(glGetUniformLocation(m_shaders.particle, "uTexture_0"), 0);

            glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ModelMatrix"),          1, GL_FALSE, &ModelMatrix[0][0]);
      
            mesh.draw(GL_POINTS);
        }
    }
    __disable_POINTSPRITE();
}

void Renderer::drawStarField(int w, int h, float pos_x, float pos_y) const
{
    // ugly 
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEM_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __usePostEffectMode(true);
 	
    __useProgram(m_shaders.starfield);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.starfield, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.starfield, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform2f(glGetUniformLocation(m_shaders.starfield, "resolution"), w, h);
        glUniform2f(glGetUniformLocation(m_shaders.starfield, "mouse"), pos_x, pos_y);
        glUniform1f(glGetUniformLocation(m_shaders.starfield, "time"), 1.0f);
                    
        m_meshQuad->draw();
    }
}

void Renderer::__useProgram(GLuint program) const
{
    if (m_activeProgram != program) {
        glUseProgram(program);
        m_activeProgram = program;
    }
}
 
void Renderer::enable_CULLFACE()
{
    glEnable(GL_CULL_FACE);
}

void Renderer::disable_CULLFACE()
{
    glDisable(GL_CULL_FACE);
}

void Renderer::__useTransparentMode(bool transparent_mode_on) const
{
    if (m_transparentModeOn != transparent_mode_on) {
        if (transparent_mode_on) {
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE); // turn off depth buffer writing
			//glDisable(GL_CULL_FACE);					
        } else {
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE); // turn on depth buffer writing
			//glEnable(GL_CULL_FACE);		
		}
        m_transparentModeOn = transparent_mode_on;
	}
	
    m_postEffectModeOn = -1;
}

void Renderer::__usePostEffectMode(bool posteffect_mode_on) const
{
    if (m_postEffectModeOn != posteffect_mode_on) {
        if (posteffect_mode_on) {
			glDisable(GL_BLEND);
			glDepthMask(GL_FALSE);
		}
        m_postEffectModeOn = posteffect_mode_on;
	}
	
    m_transparentModeOn = -1;
}
       
void Renderer::drawAxis(const glm::mat4& modelMatrix) const
{
    int width = 2;
    glLineWidth(width);
    drawMesh(*m_meshAxis, modelMatrix);
}
      
      
void Renderer::drawVector(const glm::vec3& v, const glm::vec3& pos, float length, float width) const
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

void Renderer::drawVector(const glm::vec3& v, const glm::mat4& ModelMatrix, float width) const
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

} // namespace jeti

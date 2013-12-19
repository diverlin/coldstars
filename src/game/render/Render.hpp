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

#include <common/Box2D.hpp>           // to be removed
#include <render/Fbo.hpp>
#include <render/Bloom.hpp>
#include <render/Shaders.hpp>

class Mesh;
class TextureOb;

enum class PROJECTION_TYPE { PERSPECTIVE, ORTHOGONAL};

class Renderer : public NonCopyable
{
    public:
        Renderer();
        ~Renderer();
                        
        void ActivateFbo(int, int, int);
        void DeactivateFbo(int);
        
        void Init();
        void InitPostEffects();
        void MakeShortCuts();
        void SetMeshQuad(Mesh* mesh) { m_MeshQuad = mesh; }

        void SetPerspectiveProjection(float, float);
        void SetOrthogonalProjection(float, float);
        void SetShaders(const Shaders& shaders) { m_Shaders = shaders; }
        
        BloomEffect& GetBloom() { return m_Bloom; };
        const Fbo& GetLastFbo() const { return m_Fbos[m_IndexFboLastDeactivated]; };
        const Shaders& GetShaders() const { return m_Shaders; }
        
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

        void DrawMesh                   (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void DrawMeshTransparent        (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void DrawMeshLight              (const Mesh&, const TextureOb&, const glm::mat4&) const;
        //void DrawMeshLightNormalMap   (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void DrawMeshTransparentLight   (const Mesh&, const TextureOb&, const glm::mat4&) const;
        void DrawMeshMultiTextured      (const Mesh&, const TextureOb&, const glm::mat4&) const;

        void DrawQuadTransparent(const TextureOb&, const glm::mat4&) const;
        void DrawQuad(const TextureOb&, const glm::mat4&) const;
        void DrawQuad(const TextureOb&, const Box2D&) const;

        void DrawPostEffectExtractBright(GLuint, int, int, float) const;
        void DrawPostEffectCombined(const std::vector<GLuint>&, int, int) const; 
        void DrawPostEffectCombinedDebug(const std::vector<GLuint>&, int, int) const; 
        void DrawPostEffectVolumetricLight(const glm::vec2&, int, int);
        void DrawPostEffectBlur(GLuint, int, int) const;
        void DrawScreenQuadTextured(GLuint, int, int) const;
                        
        void DrawParticles(const Mesh&, const TextureOb&, const glm::mat4&) const;
        
        void DrawAxis(const glm::mat4&, float) const;
        void DrawVector(const glm::vec3&, const glm::vec3&, float, float) const;                                             
        void DrawVector(const glm::vec3&, const glm::mat4&, float) const;  
                                                                 
    private:
        Mesh* m_MeshQuad;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionViewMatrix;
        
        glm::vec4 m_Color;
        
        Shaders m_Shaders;
        
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

        int m_FboNum;
        Fbo m_Fbos[5];
 
        int m_IndexFboLastActivated;
        int m_IndexFboLastDeactivated;

        BloomEffect m_Bloom;

        //void ComposeModelMatrix(const glm::mat4&) const;
        void UpdateProjectionViewMatrix();

        void ResizePostEffects(int, int);
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



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


#pragma once

#include <jeti/MyGl.hpp>
#include <jeti/Fbo.hpp>
#include <jeti/Bloom.hpp>
#include <jeti/Shaders.hpp>
#include <jeti/Light.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>

#include <ceti/NonCopyable.hpp>
#include <ceti/Box2D.hpp>           // depr

#include <string>
#include <chrono>

namespace  jeti {

class Mesh;
class Camera;

namespace control {
class Material;
} // namespace control

const int FBO_NUM = 6;
const float SCREEN_QUAD_ZPOS = -999.0f;
const float ZNEAR = -1000.0f;
const float ZFAR = 1000.0f;

class Render : public NonCopyable
{
    const float SCALE_INIT = 2.5;
    const float SCALE_MIN = 0.2;
    const float SCALE_MAX = 50.0;
    const float SCALE_STEP = 0.05;

    const std::string SHADERS_PATH = "shaders/";

    enum class projection { NONE, PERSPECTIVE, ORTHOGONAL, ORTHOGONAL_PARALLAX };

public:
    Render();
    ~Render();

    int fps() const { return m_fps; }

    float scaleBase() const { return m_scaleBase; }
    const glm::ivec2& size() const { return m_size; }
    int width() const { return m_size.x; }
    int height() const { return m_size.y; }
    float time() const { return m_time; }

    void increaseScale();
    void decreaseScale();

    void setScaleBase(float scaleBase) { m_scaleBase = scaleBase;}

    void increaseLightPos();
    void decreaseLightPos();
//    void setLightPos(int, int);

    void activateFbo(int, int, int);
    void deactivateFbo(int);

    void init(Camera*, int, int);

    void setPerspectiveProjection();
    void applyOrthogonalProjection();
    void applyOrthogonalProjection(float);
    void applyOrthogonalProjectionForHUD();

    BloomEffect& bloom() { return m_bloom; }
    const Fbo& lastFbo() const { return m_fbos[m_indexFboLastDeactivated]; }
    Fbo& fboBackGround() { return m_fboBackGround; }
    const Shaders& shaders() const { return m_shaders; }

    void clearColorAndDepthBuffers() const
    { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void composeViewMatrix(const glm::mat4&);

    void draw(const Mesh&, const control::Material&, const glm::mat4&) const;

    void drawMesh(const Mesh&, const glm::mat4&) const;
    void drawMesh(const Mesh&, const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawMesh_HUD(const Mesh&, const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawMeshLight(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawMeshLightNormalMap(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawMeshMultiTextured(const Mesh&, const control::Material&, const glm::mat4&) const;

    void drawQuad(const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawQuadAdditive(const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawQuad_HUD(const ceti::Box2D&, const control::Material&) const;

    void drawStar(GLuint texture=0) const;
    void drawPostEffectFogWar(GLuint, int, int, const glm::vec3&, const glm::vec2&, float) const;
    void drawPostEffectShockWaves(GLuint, int, int, int, float[10][2], float[10][3], float[10]) const;
    void drawPostEffectExtractBright(GLuint, int, int, float) const;
    void drawPostEffectCombined(const std::vector<GLuint>&, int, int) const;
    void drawPostEffectCombinedDebug(const std::vector<GLuint>&, int, int) const;
    void drawPostEffectVolumetricLight(const glm::vec2&, int, int);
    void drawPostEffectBlur(GLuint, int, int) const;
    void drawScreenQuadTextured(GLuint, int, int) const;

    void drawParticles(const Mesh& mesh, const control::Material& material) const;
    void drawParticles(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawParticlesForHUD(const Mesh& mesh, const control::Material& material) const;
    void drawParticlesForHUD(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawBlinkingParticles(const Mesh&, const control::Material&, const glm::mat4&) const;

    void drawLines(const Mesh& mesh) const;
    void drawAxis(const glm::mat4&) const;
    void drawCollisionRadius(const glm::mat4&) const;
    void drawVector(const glm::vec3&, const glm::vec3&, float, float) const;
    void drawVector(const glm::vec3&, const glm::mat4&, float) const;

    void drawStarField(int, int, float, float) const;

    void update();

    glm::vec3 toWorldCoord(const glm::vec3&) const;
    void toScreenCoord(const glm::vec3&, glm::vec3&) const;
    Camera* camera() const { return m_camera; }

private:
    projection m_activeProjection = projection::NONE;
    mutable Mesh::States m_activeStates = Mesh::States::NONE;

    float m_time = 0.0f;

    int m_fps = 0;
    int m_framesCounter = 0;
    std::chrono::steady_clock::time_point m_lastTime;

    bool m_initialized = false;

    float m_scale = 0.0f;
    float m_scaleBase = SCALE_INIT;
    float m_deltaScale = SCALE_STEP;

    glm::ivec2 m_size;

    Mesh* m_meshQuad = nullptr;
    Mesh* m_meshQuadAdditive = nullptr;
    Mesh* m_meshAxis = nullptr;
    control::Material* m_materialCollisionRadius = nullptr;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;
    glm::mat4 m_screenModelMatrix;
    glm::mat4 m_identityMatrix;

    Light m_light;

    Shaders m_shaders;

    GLuint m_programLight = 0;
    GLint m_programLightLocation_uProjectionViewMatrix = -1;
    GLint m_programLightLocation_uModelMatrix = -1;
    GLint m_programLightLocation_uNormalMatrix = -1;
    GLint m_programLightLocation_uLightPos = -1;
    GLint m_programLightLocation_uEyePos = -1;
    GLint m_programLightLocation_uDiffColor = -1;
    GLint m_programLightLocation_uAmbientColor = -1;
    GLint m_programLightLocation_uTexture = -1;
    
    GLuint m_programBlur = 0;

    int m_fboNum = FBO_NUM;
    Fbo m_fbos[FBO_NUM];
    Fbo m_fboBackGround;

    int m_indexFboLastActivated = -1;
    int m_indexFboLastDeactivated = -1;

    BloomEffect m_bloom;
    Camera* m_camera = nullptr;

    void __initAxisMesh();
    void __initPostEffects();
    void __makeShortCuts();

    void __updateProjectionViewMatrix();

    void __resizePostEffects(int, int);

    void __useProgram(GLuint) const;

    void __updateFps();
    void __drawMesh(const Mesh&) const;

    void __setOrthogonalProjection();

    // states
    void __enable_POINTSPRITE() const;
    void __disable_POINTSPRITE() const;

    void __enable_DEPTH_TEST() const;
    void __disable_DEPTH_TEST() const;

    void __enable_ADDITIVE_BLEND() const;
    void __enable_BLEND() const;
    void __disable_BLEND() const;

    void __enable_CULLFACE() const;
    void __disable_CULLFACE() const;
    //
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

}



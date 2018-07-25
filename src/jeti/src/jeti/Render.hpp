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

#include <ceti/Pack.hpp>
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
const float SCREEN_QUAD_ZPOS = 0.0f; // remove, make it 0
const float ZDEFAULT = 0.0f;
const float ZNEAR = 1.0f;
const float ZFAR = 3000.0f;

const glm::vec4 COLOR_YELLOW = glm::vec4(1.0f, 1.0f, 0.6f, 1.0f);
const glm::vec4 COLOR_RED = glm::vec4(1.0f, 0.6f, 0.6f, 1.0f);
const glm::vec4 COLOR_BLUE = glm::vec4(0.6f, 0.6f, 1.0f, 1.0f);

enum { LIGHT0=0, LIGHT1=1, LIGHT2=2 };

class Render : public NonCopyable
{
    const float SCALE_INIT = 2.5f;
    const float SCALE_MIN = 0.2f;
    const float SCALE_MAX = 50.0f;
    const float SCALE_STEP = 0.05f;

    const std::string SHADERS_PATH = "shaders/";

    enum class projection { NONE, PERSPECTIVE, ORTHOGONAL, ORTHOGONAL_PARALLAX };

public:
    Render(Camera*);
    ~Render();

    Light& light(unsigned long index) { assert(index<m_lights.size()); return m_lights[index]; }
    const Light& light(unsigned long index) const { assert(index<m_lights.size()); return m_lights[index]; }

    void drawLightsPosition() const;
    Light& addLight(const glm::vec4& color, float ambient_factor = 0.6f);

    void setBaseScale(float scaleBase) { m_scaleBase = scaleBase; }
    void setZNear(float zNear) { m_zNear = zNear; }
    void setZFar(float zFar) { m_zFar = zFar; }

    float zNear() const { return m_zNear; }
    float zFar() const { return m_zFar; }

    int fps() const { return m_fps; }

    float scaleBase() const { return m_scaleBase; }
    const glm::ivec2& size() const { return m_size; }
    int width() const { return m_size.x; }
    int height() const { return m_size.y; }
    float time() const { return m_time; }

    void increaseScale();
    void decreaseScale();

    void setSize(int w, int h) { m_size = glm::vec2(w, h); glViewport(0, 0, w, h); }
    void setScaleBase(float scaleBase) { m_scaleBase = scaleBase;}

//    void increaseLightPos(int);
//    void decreaseLightPos(int);
//    void setLightPosition(const glm::vec3&, int);

    glm::vec3 lightDirectionFromWorldPosition(const glm::vec3&) const;

    void activateFbo(int, int, int);
    void deactivateFbo(int);

    void init(int, int);

    void applyPerspectiveProjection();
    void applyOrthogonalProjection();
    void applyOrthogonalProjection(float);
    void applyOrthogonalProjectionForHUD();

    BloomEffect& bloom() { return m_bloom; }
    const Fbo& lastFbo() const { return m_fbos[m_indexFboLastDeactivated]; }
    Fbo& fboBackGround() { return m_fboBackGround; }
    Fbo& fboFlatNormalMap() { return m_fboFlatNormalMap; }
    Fbo& fboFlatDiffuseMap() { return m_fboFlatDiffuseMap; }
    Fbo& fboScene() { return m_fboScene; }
    const Shaders& shaders() const { return m_shaders; }

    void clearColorAndDepthBuffers() const
    { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void draw(const Mesh&, const control::Material&, const glm::mat4&) const;

    void drawMesh(const Mesh&, const glm::mat4&) const;
    void drawMesh(const Mesh&, const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;

    GLuint drawDefferedFlatLight(GLuint, GLuint);

    void drawFlatNormalMap(const control::Material& material,
                           const glm::vec3& center,
                           float angle,
                           float scale = 1.0f) const;

    void drawFlatDiffuseMap(const control::Material& material,
                           const glm::vec3& center,
                           float angle,
                           float scale = 1.0f) const;

    void drawFlatWithLight(const control::Material& material,
                           const glm::vec3& center,
                           float angle,
                           float radius) const;

    void drawFlatWithLight(const control::Material& material,
                           const glm::mat4& modelMatrix,
                           float angle,
                           const glm::vec4& color = glm::vec4(1.0f)) const;

    void drawMeshWithPerlin(const Mesh&,
                            const control::Material&,
                            const glm::mat4&,
                            const glm::vec3& position,
                            const glm::vec3& size,
                            const glm::vec4& color = glm::vec4(1.0f)) const;

    void drawMeshWithOnlyPerlin(const Mesh&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawMesh_HUD(const Mesh&, const control::Material&, const glm::mat4&, const glm::vec4& color = glm::vec4(1.0f)) const;
    void drawMeshWithLight(const Mesh&, const control::Material&, const glm::mat4&) const;
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
    void drawScreenQuadTextured(GLuint) const;

    void drawParticles(const Mesh& mesh, const control::Material& material) const;
    void drawParticles(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawParticlesForHUD(const Mesh& mesh, const control::Material& material) const;
    void drawParticlesForHUD(const Mesh&, const control::Material&, const glm::mat4&) const;
    void drawBlinkingParticles(const Mesh&, const control::Material&) const;

    void drawLines(const Mesh& mesh) const;
    void drawAxis(const glm::mat4&) const;
    //void drawCollisionRadius(const glm::mat4&) const;
    void drawVector(const glm::vec3&, const glm::vec3&, float, float) const;
    void drawVector(const glm::vec3&, const glm::mat4&, float) const;

    void drawStarField(int, int, float, float) const;

    void update();

    glm::vec2 toWorldCoord(const glm::vec2&) const;
    glm::vec3 toWorldCoord(const glm::vec3&) const;
    void toScreenCoord(const glm::vec3&, glm::vec3&) const;
    Camera* camera() const { return m_camera; }

    control::Material* materialCollisionRadius() const { return m_materialCollisionRadius; }
    Mesh* quadMesh() const { return m_meshQuad; }

    void drawDebugCircle(const glm::vec3& center,
                         float radius,
                         const glm::vec4& color = glm::vec4(1.0f)) const;

    void drawCircle(const control::Material& material,
                    const glm::vec3& center,
                    float radius,
                    const glm::vec4& color = glm::vec4(1.0f)) const;

    void drawCircleWithPerlin(const control::Material& material,
                              const glm::vec3& center,
                              float radius,
                              const glm::vec4& color = glm::vec4(1.0f)) const;
private:
    projection m_activeProjection = projection::NONE;
    mutable Mesh::State m_activeStates = Mesh::State::NONE;

    float m_zNear = ZNEAR;
    float m_zFar = ZFAR;

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
    Mesh* m_meshCircle = nullptr;
    control::Material* m_materialCollisionRadius = nullptr;
    control::Material* m_materialPerlin = nullptr;
//    control::Material* m_materialNormalMap = nullptr;
//    control::Material* m_materialDemo = nullptr;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;
    glm::mat4 m_screenModelMatrix;
    glm::mat4 m_identityMatrix;

    // buffer rendering
    mutable glm::mat4 m_translateMatrix;
    mutable glm::mat4 m_rotateMatrix;
    mutable glm::mat4 m_scaleMatrix;
    mutable glm::mat4 m_modelMatrix;
    //

    ceti::pack<Light> m_lights;

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
    Fbo m_fboFlatNormalMap;
    Fbo m_fboFlatDiffuseMap;
    Fbo m_fboDifferedFlatLight;
    Fbo m_fboScene;

    int m_indexFboLastActivated = -1;
    int m_indexFboLastDeactivated = -1;

    BloomEffect m_bloom;
    Camera* m_camera = nullptr;

    bool __isLightActive(unsigned long) const;

    void __initAxisMesh();
    void __initPostEffects();
    void __makeShortCuts();

    void __updateProjectionViewMatrix();

    void __resizePostEffects(int, int);

    void __useProgram(GLint) const;

    void __updateFps();
    void __drawMesh(const Mesh&, bool use_alpha=false) const;

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



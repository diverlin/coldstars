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
#include <jeti/Screen.hpp>
#include <jeti/Material.hpp> // to be removed
#include <jeti/Shaders.hpp>
#include <jeti/ShaderLoader.hpp>
#include <jeti/GlErrorHelper.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// for ugly
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <meti/QuaternionUtils.hpp>
// for ugly

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <ceti/Logger.hpp>
#include <ceti/StringUtils.hpp>

namespace jeti {

Render::Render(Camera* camera)
    :
      m_screenModelMatrix(glm::scale(glm::vec3(1.0, 1.0, 1.0f)))
    , m_camera(camera)
{

}

Render::~Render() 
{
    delete m_meshQuad;
    delete m_meshAxis;
    delete m_meshCircle;
    delete m_materialCollisionRadius->model(); // TODO: make owning model flag, to delete model internally
    delete m_materialCollisionRadius;
}

void Render::drawLightsPosition() const
{
    for(const std::shared_ptr<Light>& light: m_lightsManager.lights()) {
        drawDebugCircle(light->position(), 20, light->diffuse());
    }
}

void Render::addLight(const LightPtr& light)
{
    m_lightsManager.add(light);
}

void Render::__enable_CULLFACE() const
{
    if (!glIsEnabled(GL_CULL_FACE)) {
        glEnable(GL_CULL_FACE);
    }
}

void Render::__disable_CULLFACE() const
{
    if (glIsEnabled(GL_CULL_FACE)) {
        glDisable(GL_CULL_FACE);
    }
}

void Render::__enable_ADDITIVE_BLEND() const
{
    if (!glIsEnabled(GL_BLEND)) {
        glEnable(GL_BLEND);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void Render::__enable_BLEND() const
{
    if (!glIsEnabled(GL_BLEND)) {
        glEnable(GL_BLEND);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::__disable_BLEND() const
{
    if (glIsEnabled(GL_BLEND)) {
        glDisable(GL_BLEND);
    }
}

void Render::__enable_DEPTH_TEST() const
{
    if (!glIsEnabled(GL_DEPTH_TEST)) {
        glEnable(GL_DEPTH_TEST);
    }
}

void Render::__disable_DEPTH_TEST() const
{
    if (glIsEnabled(GL_DEPTH_TEST)) {
        glDisable(GL_DEPTH_TEST);
    }
}

void Render::__enable_POINTSPRITE() const
{
    if (!glIsEnabled(GL_POINT_SPRITE)) {
        glEnable(GL_POINT_SPRITE);
    }
    if (!glIsEnabled(GL_PROGRAM_POINT_SIZE)) {
        glEnable(GL_PROGRAM_POINT_SIZE);
    }
}

void Render::__disable_POINTSPRITE() const
{
    if (glIsEnabled(GL_POINT_SPRITE)) {
        glDisable(GL_POINT_SPRITE);
    }
    if (glIsEnabled(GL_PROGRAM_POINT_SIZE)) {
        glDisable(GL_PROGRAM_POINT_SIZE);
    }
}

//void Render::setLightPosition(const glm::vec3& position, int index) {
//    light(index).position = position;
//}

//void Render::increaseLightPos(int index) {
//    light(index).position.z += 10.0f;
//}

//void Render::decreaseLightPos(int index) {
//    light(index).position.z -= 10.0f;
//}

void  Render::increaseScale()
{
    if (m_scaleBase < SCALE_MAX) {
        m_scaleBase += m_deltaScale;
    } else {
        m_scaleBase = SCALE_MAX;
    }
}

void Render::decreaseScale()
{
    if (m_scaleBase > SCALE_MIN) {
        m_scaleBase -= m_deltaScale;
    } else {
        m_scaleBase = SCALE_MIN;
    }
}

void Render::update() {
    m_camera->update();
    __updateFps();
    m_time += 0.01f;

    if (m_lightEmitterOn) {
        m_lightEmitter.resize(m_size.x, m_size.y);
        jeti::Light* newLight = m_lightEmitter.update(m_time);
        if (newLight) {
            addLight(LightPtr(newLight));
        }

    }
    m_lightsManager.update(m_time);
}

glm::vec2
Render::toWorldCoord(const glm::vec2& screen_coord) const {
    glm::vec2 world_coord(screen_coord);

    world_coord.x -= m_size.x/2;
    world_coord.y -= m_size.y/2;

    world_coord *= scaleBase();

    world_coord += meti::to_vec2(m_camera->position());

    return world_coord;
}

glm::vec3
Render::toWorldCoord(const glm::vec3& screen_coord) const {
    glm::vec3 world_coord(screen_coord);

    world_coord.x -= m_size.x/2;
    world_coord.y -= m_size.y/2;

    world_coord *= scaleBase();

    world_coord += m_camera->position();
    world_coord.z = ZDEFAULT;

    return world_coord;
}

void
Render::toScreenCoord(const glm::vec3& world_coord, glm::vec3& screen_coord) const {
    screen_coord = world_coord;

    screen_coord -= m_camera->position();

    screen_coord /= scaleBase();

    screen_coord.x += m_size.x/2;
    screen_coord.y += m_size.y/2;

    screen_coord.z = ZDEFAULT;
}


void Render::init(int w, int h)
{
    if (m_initialized)
        return;

    m_lastTime = std::chrono::steady_clock::now();

    glewInit();
    CHECK_OPENGL_ERRORS

            m_meshQuad = new Mesh;
    m_meshQuad->setStates(Mesh::State::QUAD);
    m_meshQuadAdditive = new Mesh;
    m_meshQuadAdditive->setStates(Mesh::State::QUAD_ADDITIVE);
    m_meshCircle = new Mesh(/*circle*/true);
    __initAxisMesh();

    m_size.x = w;
    m_size.y = h;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

    glShadeModel(GL_SMOOTH);

    applyOrthogonalProjection();

    m_shaders.screentexture   = compile_program(SHADERS_PATH+"screentexture.vert",     SHADERS_PATH+"screentexture.frag");
    m_shaders.basetexture     = compile_program(SHADERS_PATH+"basetexture.vert",       SHADERS_PATH+"basetexture.frag");
    m_shaders.texturewithperlin = compile_program(SHADERS_PATH+"texturewithperlin.vert", SHADERS_PATH+"texturewithperlin.frag");
    m_shaders.perlin          = compile_program(SHADERS_PATH+"perlin.vert",            SHADERS_PATH+"perlin.frag");
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
    m_shaders.particle_blink  = compile_program(SHADERS_PATH+"particle_blink.vert",    SHADERS_PATH+"particle_blink.frag");
    m_shaders.star            = compile_program(SHADERS_PATH+"base.vert",              SHADERS_PATH+"star.frag");
    m_shaders.starfield       = compile_program(SHADERS_PATH+"starfield.vert",         SHADERS_PATH+"starfield.frag");
    m_shaders.flatlight       = compile_program(SHADERS_PATH+"flatlight.vert",         SHADERS_PATH+"flatlight.frag");
    m_shaders.defferedflatlight = compile_program(SHADERS_PATH+"defferedflatlight.vert", SHADERS_PATH+"defferedflatlight.frag");

    checkProgramErrors(m_shaders.basetexture);
    checkProgramErrors(m_shaders.texturewithperlin);
    checkProgramErrors(m_shaders.basecolor);
    checkProgramErrors(m_shaders.black2alpha);
    checkProgramErrors(m_shaders.shockwave);
    checkProgramErrors(m_shaders.volumetriclight);
    checkProgramErrors(m_shaders.light);
    checkProgramErrors(m_shaders.light_normalmap);
    checkProgramErrors(m_shaders.blur);
    checkProgramErrors(m_shaders.extractbright);
    checkProgramErrors(m_shaders.combine);
    checkProgramErrors(m_shaders.multitexturing);
    checkProgramErrors(m_shaders.blank);
    checkProgramErrors(m_shaders.fogwarspark);
    checkProgramErrors(m_shaders.flash);
    checkProgramErrors(m_shaders.mask);
    checkProgramErrors(m_shaders.particle);
    checkProgramErrors(m_shaders.particle_blink);
    checkProgramErrors(m_shaders.star);
    checkProgramErrors(m_shaders.starfield);
    checkProgramErrors(m_shaders.flatlight);
    checkProgramErrors(m_shaders.defferedflatlight);

    __initPostEffects();
    __makeShortCuts();

    {
        auto model = new MaterialModel("data/other/radius.png");
        m_materialCollisionRadius = new control::Material(model);
    }

    {
        auto model = new MaterialModel("data/other/perlin.png");
        m_materialPerlin = new control::Material(model);
    }

    m_initialized = true;

    CHECK_OPENGL_ERRORS
}

void Render::__initAxisMesh()
{
    m_meshAxis = new Mesh;

    std::vector<glm::vec3> vertices;
    float r = 1.5f;
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(r, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, r, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
    vertices.push_back(glm::vec3(0.0, 0.0, r));

    std::vector<glm::vec4> colors;
    float m = 0.2f;
    float s = 0.2f;
    colors.push_back(glm::vec4(s, m, m, s));
    colors.push_back(glm::vec4(1.0, m, m, 1.0));
    colors.push_back(glm::vec4(m, s, m, s));
    colors.push_back(glm::vec4(m, 1.0, m, 1.0));
    colors.push_back(glm::vec4(m, m, s, s));
    colors.push_back(glm::vec4(m, m, 1.0, 1.0));

    float linesWidth = 2.0f;
    m_meshAxis->fillLineVertices(vertices, colors, linesWidth);
}

void Render::activateFbo(int index, int w, int h)
{
    if ( (index < 0) || (index >= m_fboNum) ) {
        throw std::runtime_error("wrong fbo index");
    }

    m_fbos[index].activate(w, h);
    m_indexFboLastActivated = index;
}

void Render::deactivateFbo(int index)
{
    if ((index < 0) || (index >= m_fboNum)) {
        throw std::runtime_error("wrong fbo index");
    }

    if (m_indexFboLastActivated != index) {
        throw std::runtime_error("you are trying to deactivate not active fbo");
    }
    
    m_fbos[index].deactivate();
    m_indexFboLastDeactivated = index;
}

void Render::__initPostEffects()
{
    m_fboBackGround.init();
    m_fboFlatNormalMap.init();
    m_fboFlatDiffuseMap.init();
    m_fboDifferedFlatLight.init();

    for (int i=0; i<m_fboNum; i++) {
        m_fbos[i].init();
    }

    m_bloom.Create(m_shaders.blur, m_shaders.extractbright, m_shaders.combine);
    __resizePostEffects(m_size.x, m_size.y);
}


void Render::__resizePostEffects(int w, int h)
{
    for (int i=0; i<m_fboNum; i++) {
        m_fbos[i].resize(w, h);
    }

    m_bloom.Resize(w, h);

    m_fboBackGround.resize(w, h);
    m_fboFlatNormalMap.resize(w, h);
    m_fboFlatDiffuseMap.resize(w, h);
    m_fboDifferedFlatLight.resize(w, h);
} 

void Render::__makeShortCuts()
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

void Render::applyPerspectiveProjection()
{        
    m_projectionMatrix = glm::perspective(90.0f, m_size.x/float(m_size.y), m_zNear, m_zFar);
    __updateProjectionViewMatrix();
}

/* used for parallax (bg), to decrease affection on scale by scaleFactor
 * */
void Render::applyOrthogonalProjection(float scaleFactor)
{
    m_scale = 1.0f + scaleFactor*m_scaleBase;
    __setOrthogonalProjection();
}

void Render::applyOrthogonalProjection()
{        
    m_scale = m_scaleBase;
    __setOrthogonalProjection();
}

void Render::applyOrthogonalProjectionForHUD()
{
    m_scale = 1.0f;
    __setOrthogonalProjection();
}

void Render::__setOrthogonalProjection() {
    m_projectionMatrix = glm::ortho(-m_size.x/2 * m_scale, m_size.x/2 * m_scale, -m_size.y/2 * m_scale, m_size.y/2 * m_scale, 0.0f/*m_zNear*/, m_zFar);
    __updateProjectionViewMatrix();
}

//void Render::composeViewMatrix(const glm::mat4& Vm)
//{
//    m_viewMatrix = Vm;
//    __updateProjectionViewMatrix();
//}

void Render::__updateProjectionViewMatrix()
{ 
    m_viewMatrix = glm::lookAt(m_camera->position(), m_camera->target(), m_camera->up());
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}


void Render::drawQuad(const control::Material& material, const glm::mat4& ModelMatrix, const glm::vec4& color) const
{
    drawMesh(*m_meshQuad, material, ModelMatrix, color);
}

void Render::drawQuadAdditive(const control::Material& material, const glm::mat4& ModelMatrix, const glm::vec4& color) const
{
    drawMesh(*m_meshQuadAdditive, material, ModelMatrix, color);
}

void Render::drawQuad_HUD(const ceti::Box2D& box, const control::Material& material) const
{
    // ugly start
    glm::vec2 pos = box.center();
    glm::mat4 TranslationMatrix = glm::translate(glm::vec3(pos.x, pos.y, 0.0f));

    //    glm::quat Qx, Qy, Qz;
    
    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z);

    //    glm::mat4 RotationMatrix = glm::toMat4(Qx*Qy*Qz);
    
    glm::vec2 size = box.size()*box.scale();
    glm::mat4 ScaleMatrix = glm::scale(glm::vec3(size.x, size.y, 1.0f));

    glm::mat4 ModelMatrix = TranslationMatrix /* * RotationMatrix */ * ScaleMatrix;
    // ugly end

    drawMesh_HUD(*m_meshQuad, material, ModelMatrix);
}

void Render::__drawMesh(const Mesh& mesh, bool use_alpha) const {
    // bug with transparent normal mesh (move states to material)
    //if (mesh.states() != m_activeStates) {
    switch(mesh.states()) {
    case Mesh::State::QUAD:
        __disable_POINTSPRITE();
        __enable_BLEND();
        __disable_DEPTH_TEST();
        __disable_CULLFACE();
        break;
    case Mesh::State::QUAD_ADDITIVE:
        __disable_POINTSPRITE();
        __enable_ADDITIVE_BLEND();
        __disable_DEPTH_TEST();
        __disable_CULLFACE();
        break;
    case Mesh::State::NORMAL:
        __disable_POINTSPRITE();
        if (use_alpha) {
            __enable_ADDITIVE_BLEND();
            __disable_DEPTH_TEST();
        } else {
            __disable_BLEND();
            __enable_DEPTH_TEST();
        }

        __enable_CULLFACE();
        break;
    case Mesh::State::PARTICLES:
        __enable_POINTSPRITE();
        __enable_ADDITIVE_BLEND();
        __disable_DEPTH_TEST();
        __disable_CULLFACE();
        break;
    case Mesh::State::LINES:
        __disable_POINTSPRITE();
        __disable_BLEND();
        __disable_DEPTH_TEST();
        __disable_CULLFACE();
        break;
    case Mesh::State::NONE:
        assert(false);
    }
    m_activeStates = mesh.states();
    //}

    mesh.draw();
}

void Render::drawMesh(const Mesh& mesh, const glm::mat4& modelMatrix) const
{
    __useProgram(m_shaders.basecolor);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basecolor, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basecolor, "u_ModelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        __drawMesh(mesh);
    }
}

void Render::drawMesh(const Mesh& mesh, const control::Material& material, const glm::mat4& modelMatrix, const glm::vec4& color) const
{
    __useProgram(m_shaders.basetexture);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_modelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(m_shaders.basetexture, "u_color"), 1, glm::value_ptr(color));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_texture"), 0);

        __drawMesh(mesh);
    }
}

void Render::drawFlatNormalMap(const control::Material& material,
                               const glm::vec3& center,
                               float angle,
                               float scale) const
{
    if (!material.model()->hasNormalMap()) {
        return;
    }

    m_translateMatrix = glm::translate(center);
    m_scaleMatrix = glm::scale(glm::vec3(scale*material.model()->w, scale*material.model()->h, 1.0f));
    m_rotateMatrix = glm::rotate(angle, meti::OZ);

    m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

    GLuint program = m_shaders.basetexture;
    __useProgram(program);
    {
        glUniformMatrix4fv(glGetUniformLocation(program, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "u_modelMatrix")         , 1, GL_FALSE, &m_modelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->normalmap);
        glUniform1i(glGetUniformLocation(program, "u_texture"), 0);

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawFlatDiffuseMap(const control::Material& material,
                                const glm::vec3& center,
                                float angle,
                                float scale) const
{
    m_translateMatrix = glm::translate(center);
    m_scaleMatrix = glm::scale(glm::vec3(scale*material.model()->w, scale*material.model()->h, 1.0f));
    m_rotateMatrix = glm::rotate(angle, meti::OZ);

    m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

    GLuint program = m_shaders.basetexture;
    __useProgram(program);
    {
        glUniformMatrix4fv(glGetUniformLocation(program, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "u_modelMatrix")         , 1, GL_FALSE, &m_modelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(program, "u_texture"), 0);

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawFlatWithLight(const control::Material& material,
                               const glm::vec3& center,
                               float angle,
                               float scale) const
{
    m_translateMatrix = glm::translate(center);
    m_scaleMatrix = glm::scale(glm::vec3(scale*material.model()->w, scale*material.model()->h, 1.0f));
    m_rotateMatrix = glm::rotate(angle, meti::OZ);

    m_modelMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

    ceti::pack<LightData> lightsdata = m_lightsManager.shiningTo(center);

    GLuint program = m_shaders.flatlight;
    // TODO: color must be taken from material model
    __useProgram(program);
    {
        glUniformMatrix4fv(glGetUniformLocation(program, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "u_modelMatrix")         , 1, GL_FALSE, &m_modelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(program, "u_light_ambient"), 1, glm::value_ptr(glm::vec4(0.4, 0.4, 0.4, 1.0)));

        int lights_num = int(lightsdata.size());
        //lights_num = 0;
        if (lights_num>=1) {
            const LightData& ldata = lightsdata.at(LIGHT0);
            const Light& light0 = *ldata.light;
            float light0_attenuation = light0.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light0_diffuse"), 1, glm::value_ptr(light0.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light0_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light0_attenuation"), light0_attenuation);
        }

        if (lights_num>=2) {
            const LightData& ldata = lightsdata.at(LIGHT1);
            const Light& light1 = *ldata.light;
            float light1_attenuation = light1.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light1_diffuse"), 1, glm::value_ptr(light1.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light1_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light1_attenuation"), light1_attenuation);
        }
        if (lights_num>=3) {
            const LightData& ldata = lightsdata.at(LIGHT2);
            const Light& light2 = *ldata.light;
            float light2_attenuation = light2.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light2_diffuse"), 1, glm::value_ptr(light2.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light2_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light2_attenuation"), light2_attenuation);
        }
        if (lights_num>=4) {
            const LightData& ldata = lightsdata.at(LIGHT3);
            const Light& light3 = *ldata.light;
            float light3_attenuation = light3.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light3_diffuse"), 1, glm::value_ptr(light3.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light3_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light3_attenuation"), light3_attenuation);
        }
        if (lights_num>=5) {
            const LightData& ldata = lightsdata.at(LIGHT4);
            const Light& light4 = *ldata.light;
            float light4_attenuation = light4.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light4_diffuse"), 1, glm::value_ptr(light4.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light4_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light4_attenuation"), light4_attenuation);
        }
        if (lights_num>=6) {
            const LightData& ldata = lightsdata.at(LIGHT5);
            const Light& light5 = *ldata.light;
            float light5_attenuation = light5.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light5_diffuse"), 1, glm::value_ptr(light5.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light5_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light5_attenuation"), light5_attenuation);
        }
        if (lights_num>=7) {
            const LightData& ldata = lightsdata.at(LIGHT6);
            const Light& light6 = *ldata.light;
            float light6_attenuation = light6.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light6_diffuse"), 1, glm::value_ptr(light6.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light6_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light6_attenuation"), light6_attenuation);
        }
        if (lights_num>=8) {
            const LightData& ldata = lightsdata.at(LIGHT7);
            const Light& light7 = *ldata.light;
            float light7_attenuation = light7.attenuationFactor(ldata.distance);

            glUniform4fv(glGetUniformLocation(program, "u_light7_diffuse"), 1, glm::value_ptr(light7.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light7_dir"), 1, glm::value_ptr(ldata.dir));
            glUniform1f(glGetUniformLocation(program, "u_light7_attenuation"), light7_attenuation);
        }

        glUniform1f(glGetUniformLocation(program, "u_angle"), -angle);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(program, "u_texture"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material.model()->normalmap);
        glUniform1i(glGetUniformLocation(program, "u_normalmap"), 1);

        __drawMesh(*m_meshQuad);
    }
}

//glm::vec3 Render::lightDirectionFromWorldPosition(const glm::vec3& worldPosition) const
//{
//    glm::vec3 cameraPos(m_camera->position());
//    glm::vec3 diff(worldPosition-cameraPos);
//    diff.z = worldPosition.z;
//    return glm::normalize(diff);
//}

float Render::screenScale() const
{
    return m_scale*m_size.y;
}

float Render::toScreenNorm(float val) const
{
    return val/screenScale();
}

float Render::screenRatio() const
{
    return m_size.y/float(m_size.x);
}

glm::vec3 Render::toScreenCoordNorm(const glm::vec3& v) const
{
    float factor = screenScale();
    float backupz = v.z;
    glm::vec3 result(v);
    result -= m_camera->position();
    result /= factor;
    result.x *= screenRatio();
    result.z = backupz;
    return result;
}

GLuint Render::drawDefferedFlatLight(GLuint diffuseScreenMap, GLuint normalScreenMap)
{
    m_fboDifferedFlatLight.activate();

    const std::vector<LightPtr>& lights = m_lightsManager.lights();

    int lights_num = lights.size();

    GLuint program = m_shaders.defferedflatlight;
    __useProgram(program);
    {
        glUniformMatrix4fv(glGetUniformLocation(program, "u_modelMatrix"), 1, GL_FALSE, &m_screenModelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(program, "u_light_ambient"), 1, glm::value_ptr(glm::vec4(0.4, 0.4, 0.4, 1.0)));

        glUniform1f(glGetUniformLocation(program, "u_screenRatio"), screenRatio());


        if (lights_num >= 1) {
            const Light& light0 = *lights.at(LIGHT0);
            glUniform4fv(glGetUniformLocation(program, "u_light0_diffuse"), 1, glm::value_ptr(light0.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light0_position"), 1, glm::value_ptr(toScreenCoordNorm(light0.position())));
            glUniform1f(glGetUniformLocation(program, "u_light0_radius"), toScreenNorm(light0.radius()));
        }
        if (lights_num >= 2) {
            const Light& light1 = *lights.at(LIGHT1);
            glUniform4fv(glGetUniformLocation(program, "u_light1_diffuse"), 1, glm::value_ptr(light1.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light1_position"), 1, glm::value_ptr(toScreenCoordNorm(light1.position())));
            glUniform1f(glGetUniformLocation(program, "u_light1_radius"), toScreenNorm(light1.radius()));
        }
        if (lights_num >= 3) {
            const Light& light2 = *lights.at(LIGHT2);
            glUniform4fv(glGetUniformLocation(program, "u_light2_diffuse"), 1, glm::value_ptr(light2.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light2_position"), 1, glm::value_ptr(toScreenCoordNorm(light2.position())));
            glUniform1f(glGetUniformLocation(program, "u_light2_radius"), toScreenNorm(light2.radius()));
        }
        if (lights_num >= 4) {
            const Light& light3 = *lights.at(LIGHT3);
            glUniform4fv(glGetUniformLocation(program, "u_light3_diffuse"), 1, glm::value_ptr(light3.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light3_position"), 1, glm::value_ptr(toScreenCoordNorm(light3.position())));
            glUniform1f(glGetUniformLocation(program, "u_light3_radius"), toScreenNorm(light3.radius()));
        }
        if (lights_num >= 5) {
            const Light& light4 = *lights.at(LIGHT4);
            glUniform4fv(glGetUniformLocation(program, "u_light4_diffuse"), 1, glm::value_ptr(light4.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light4_position"), 1, glm::value_ptr(toScreenCoordNorm(light4.position())));
            glUniform1f(glGetUniformLocation(program, "u_light4_radius"), toScreenNorm(light4.radius()));
        }
        if (lights_num >= 6) {
            const Light& light5 = *lights.at(LIGHT5);
            glUniform4fv(glGetUniformLocation(program, "u_light5_diffuse"), 1, glm::value_ptr(light5.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light5_position"), 1, glm::value_ptr(toScreenCoordNorm(light5.position())));
            glUniform1f(glGetUniformLocation(program, "u_light5_radius"), toScreenNorm(light5.radius()));
        }
        if (lights_num >= 7) {
            const Light& light6 = *lights.at(LIGHT6);
            glUniform4fv(glGetUniformLocation(program, "u_light6_diffuse"), 1, glm::value_ptr(light6.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light6_position"), 1, glm::value_ptr(toScreenCoordNorm(light6.position())));
            glUniform1f(glGetUniformLocation(program, "u_light6_radius"), toScreenNorm(light6.radius()));
        }
        if (lights_num >= 8) {
            const Light& light7 = *lights.at(LIGHT7);
            glUniform4fv(glGetUniformLocation(program, "u_light7_diffuse"), 1, glm::value_ptr(light7.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light7_position"), 1, glm::value_ptr(toScreenCoordNorm(light7.position())));
            glUniform1f(glGetUniformLocation(program, "u_light7_radius"), toScreenNorm(light7.radius()));
        }
        if (lights_num >= 9) {
            const Light& light8 = *lights.at(LIGHT8);
            glUniform4fv(glGetUniformLocation(program, "u_light8_diffuse"), 1, glm::value_ptr(light8.diffuse()));
            glUniform3fv(glGetUniformLocation(program, "u_light8_position"), 1, glm::value_ptr(toScreenCoordNorm(light8.position())));
            glUniform1f(glGetUniformLocation(program, "u_light8_radius"), toScreenNorm(light8.radius()));
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseScreenMap);
        glUniform1i(glGetUniformLocation(program, "u_texture"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalScreenMap);
        glUniform1i(glGetUniformLocation(program, "u_normalmap"), 1);

        __drawMesh(*m_meshQuad);
    }

    m_fboDifferedFlatLight.deactivate();

    return m_fboDifferedFlatLight.colorBuffer();
}

void Render::drawMeshWithPerlin(const Mesh& mesh,
                                const control::Material& material,
                                const glm::mat4& modelMatrix,
                                const glm::vec3& position,
                                const glm::vec3& size,
                                const glm::vec4& color) const
{
    __useProgram(m_shaders.texturewithperlin);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.texturewithperlin, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.texturewithperlin, "u_modelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(m_shaders.texturewithperlin, "u_color"), 1, glm::value_ptr(color));
        glUniform1f(glGetUniformLocation(m_shaders.texturewithperlin, "u_time"), m_time);

        glm::vec2 camera_pos(m_camera->position());
        glm::vec2 offset(1.0f/m_scale*(m_camera->position() - position));
        glUniform2fv(glGetUniformLocation(m_shaders.texturewithperlin, "u_offset"), 1, glm::value_ptr(offset));

        //        glUniform1f(glGetUniformLocation(m_shaders.texturewithperlin, "u_scale"), m_scale);
        //        glUniform2fv(glGetUniformLocation(m_shaders.texturewithperlin, "u_size"), 1, glm::value_ptr(glm::vec2(size)));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.texturewithperlin, "u_texture"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_materialPerlin->model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.texturewithperlin, "u_texturePerlin"), 1);

        __drawMesh(mesh);
    }
    glActiveTexture(GL_TEXTURE0);
}

void Render::drawMeshWithOnlyPerlin(const Mesh& mesh, const glm::mat4& modelMatrix, const glm::vec4& color) const
{
    __useProgram(m_shaders.perlin);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.perlin, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.perlin, "u_modelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(m_shaders.perlin, "u_color"), 1, glm::value_ptr(color));
        glUniform1f(glGetUniformLocation(m_shaders.perlin, "u_time"), m_time);

        glUniform1f(glGetUniformLocation(m_shaders.perlin, "u_scale"), m_scale);

        glm::vec2 camera_pos(m_camera->position());
        glUniform2fv(glGetUniformLocation(m_shaders.perlin, "u_cameraPos"), 1, glm::value_ptr(camera_pos));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_materialPerlin->model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.perlin, "u_texturePerlin"), 0);

        __drawMesh(mesh, /*use_alpha*/true);
    }
}

void Render::drawMesh_HUD(const Mesh& mesh, const control::Material& material, const glm::mat4& modelMatrix, const glm::vec4& color) const
{
    __useProgram(m_shaders.basetexture);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_modelMatrix")         , 1, GL_FALSE, &modelMatrix[0][0]);

        glUniform4fv(glGetUniformLocation(m_shaders.basetexture, "u_color"), 1, glm::value_ptr(color));
        glUniform1f(glGetUniformLocation(m_programLight,  "u_time"), m_time);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_texture"), 0);

        __drawMesh(mesh);
    }
}

void Render::draw(const Mesh& mesh, const control::Material& material, const glm::mat4& MM) const {
    //    if (material.model()->normalmap) {
    //        drawMeshLightNormalMap(mesh, material, MM);
    //    } else {
    drawMeshWithLight(mesh, material, MM);
    //    }
}

void Render::drawMeshWithLight(const Mesh& mesh, const control::Material& materialc, const glm::mat4& ModelMatrix) const
{
    if (mesh.isFlat()) {
        drawMesh(mesh, materialc, ModelMatrix);
        return;
    }

    float ambient_factor = 0.25;
    const glm::vec3& eye_pos = m_camera->position();
    const MaterialModel& material = *materialc.model();

    __useProgram(m_programLight);
    {
        glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(ModelMatrix)));

        glUniformMatrix4fv(m_programLightLocation_uProjectionViewMatrix, 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(m_programLightLocation_uModelMatrix         , 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix3fv(m_programLightLocation_uNormalMatrix        , 1, GL_FALSE, &NormalModelMatrix[0][0]);

        glUniform3fv(m_programLightLocation_uEyePos, 1, glm::value_ptr(eye_pos));

        const Light& light0 = *m_lightsManager.globalLight();
        glUniform3fv(glGetUniformLocation(m_programLight, "u_Light.position"), 1, glm::value_ptr(light0.position()));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.ambient"),  1, glm::value_ptr(light0.ambient()));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.diffuse"),  1, glm::value_ptr(light0.diffuse()));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Light.specular"), 1, glm::value_ptr(light0.specular()));
        glUniform3fv(glGetUniformLocation(m_programLight, "u_Light.attenuation"), 1, glm::value_ptr(light0.attenuation()));

        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.ambient"),  1, glm::value_ptr(material.ambient));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.diffuse"),  1, glm::value_ptr(material.diffuse));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.specular"), 1, glm::value_ptr(material.specular));
        glUniform4fv(glGetUniformLocation(m_programLight, "u_Material.emission"), 1, glm::value_ptr(material.emission));
        glUniform1f(glGetUniformLocation(m_programLight,  "u_Material.shininess"), material.shininess);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, materialc.model()->diffusemap);
        glUniform1i(m_programLightLocation_uTexture, 0);

        __drawMesh(mesh, material.use_alpha);
    }
}

void Render::drawMeshLightNormalMap(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{
    //float ambient_factor = 0.25f;
    const glm::vec3& eye_pos = m_camera->target();

    __useProgram(m_shaders.light_normalmap);
    {
        glm::mat3 NormalModelMatrix = glm::transpose(glm::mat3(glm::inverse(ModelMatrix)));

        glUniformMatrix4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.projectionView"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.model")         , 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Matrices.normal")        , 1, GL_FALSE, &NormalModelMatrix[0][0]);

        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_EyePos"), 1, glm::value_ptr(eye_pos));

        const Light& light0 = *m_lightsManager.globalLight();
        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.position"), 1, glm::value_ptr(light0.position()));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.ambient"),  1, glm::value_ptr(light0.ambient()));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.diffuse"),  1, glm::value_ptr(light0.diffuse()));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.specular"), 1, glm::value_ptr(light0.specular()));
        glUniform3fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Light.attenuation"), 1, glm::value_ptr(light0.attenuation()));

        const MaterialModel& material = *textureOb.model();
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.ambient"),  1, glm::value_ptr(material.ambient));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.diffuse"),  1, glm::value_ptr(material.diffuse));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.specular"), 1, glm::value_ptr(material.specular));
        glUniform4fv(glGetUniformLocation(m_shaders.light_normalmap, "u_Material.emission"), 1, glm::value_ptr(material.emission));
        glUniform1f(glGetUniformLocation(m_shaders.light_normalmap,  "u_Material.shininess"), material.shininess);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.light_normalmap, "u_Texture"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->normalmap);
        glUniform1i(glGetUniformLocation(m_shaders.light_normalmap, "u_Normalmap"), 1);

        __drawMesh(mesh);
    }
} 

void Render::drawMeshMultiTextured(const Mesh& mesh, const control::Material& textureOb, const glm::mat4& ModelMatrix) const
{	
    __useProgram(m_shaders.multitexturing);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.multitexturing, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.multitexturing, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.multitexturing, "Texture_0"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureOb.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.multitexturing, "Texture_1"), 1);

        glUniform2f(glGetUniformLocation(m_shaders.multitexturing, "displ"), textureOb.model()->texture_offset.x, textureOb.model()->texture_offset.y);

        __drawMesh(mesh);
    }
}  

void Render::drawStar(GLuint texture) const
{
    glm::vec2 offset(0.5f-m_camera->position().x/m_size.x/m_scaleBase, 0.5f-m_camera->position().y/m_size.y/m_scaleBase);

    __useProgram(m_shaders.star);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.star, "u_ModelMatrix"), 1, GL_FALSE, &m_screenModelMatrix[0][0]);

        if (texture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(glGetUniformLocation(m_shaders.particle, "u_texture"), 0);
        }

        glUniform1f(glGetUniformLocation(m_shaders.star, "u_time"), 3*m_time);
        glUniform1f(glGetUniformLocation(m_shaders.star, "u_sizeFactor"), 2*m_scaleBase);
        glUniform2fv(glGetUniformLocation(m_shaders.star, "u_resolution"), 1, glm::value_ptr(glm::vec2(m_size.x, m_size.y)));
        glUniform2fv(glGetUniformLocation(m_shaders.star, "u_worldPosition"), 1, glm::value_ptr(offset));

        __drawMesh(*m_meshQuad);
    }
}


void Render::drawPostEffectCombined(const std::vector<GLuint>& textures, int w, int h) const
{
    // ugly
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

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

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawPostEffectFogWar(GLuint texture, int w, int h, const glm::vec3& center, const glm::vec2& world_coord, float radius) const
{
    // ugly
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

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

        __drawMesh(*m_meshQuad);
    }
}


void Render::drawPostEffectShockWaves(GLuint scene_texture, int w, int h, int count, float center_array[10][2], float xyz_array[10][3], float time_array[10]) const
{
    // ugly
    //float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

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

        __drawMesh(*m_meshQuad);
    }
}



void Render::drawPostEffectExtractBright(GLuint scene_texture, int w, int h, float brightThreshold) const
{
    // ugly
    //float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __useProgram(m_shaders.extractbright);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.extractbright, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.extractbright, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, scene_texture);
        glUniform1i(glGetUniformLocation(m_shaders.extractbright, "source"), 0);

        glUniform1f(glGetUniformLocation(m_shaders.extractbright, "threshold"), brightThreshold);

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawPostEffectCombinedDebug(const std::vector<GLuint>& textures, int w, int h) const
{
    //float ratio = (float)h/w;
    unsigned int quad_num = textures.size();
    unsigned int quad_num_w = quad_num / 3;
    unsigned int quad_num_h = quad_num / 4;

    int size_w = w/quad_num_w;
    int size_h = h/quad_num_w;

    for (unsigned int i=0; i<quad_num_w; ++i) {
        for (unsigned int j=0; j<quad_num_h; ++j) {
            // ugly
            glm::mat4 TranslateMatrix = glm::translate(glm::vec3(size_w+i*size_w, size_h+j*size_h, SCREEN_QUAD_ZPOS));
            glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(size_w, size_h, 1.0f));
            glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
            // ugly

            __useProgram(m_shaders.basetexture); {
                glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_projectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(m_shaders.basetexture, "u_modelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[i+j]);
                glUniform1i(glGetUniformLocation(m_shaders.basetexture, "u_TextureScene"), 0);

                __drawMesh(*m_meshQuad);
            }
        }
    }
}

void Render::drawPostEffectVolumetricLight(const glm::vec2& world_coord, int w, int h)
{
    // ugly
    float scale = 1.0;
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __useProgram(m_shaders.volumetriclight);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.volumetriclight, "u_ProjectionMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.volumetriclight, "u_ModelMatrix")     , 1, GL_FALSE, &ModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bloom.GetFboFinal().colorBuffer());
        glUniform1i(glGetUniformLocation(m_shaders.volumetriclight, "FullSampler"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_bloom.GetTextureBlured());
        glUniform1i(glGetUniformLocation(m_shaders.volumetriclight, "BlurSampler"), 1);

        glUniform4f(glGetUniformLocation(m_shaders.volumetriclight, "sun_pos"), -world_coord.x/(w*scale), -world_coord.y/(h*scale), -100.0, 1.0);

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawPostEffectBlur(GLuint texture, int w, int h) const
{  
    // ugly
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

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
        
        __drawMesh(*m_meshQuad);
    }
}

void Render::drawScreenQuadTextured(GLuint texture) const
{
    GLuint program = m_shaders.screentexture;
    __useProgram(program);
    {
        glUniformMatrix4fv(glGetUniformLocation(program, "u_modelMatrix"), 1, GL_FALSE, &m_screenModelMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(program, "u_texture"), 0);

        __drawMesh(*m_meshQuad);
    }
}

void Render::drawParticles(const Mesh& mesh, const control::Material& material) const
{
    drawParticles(mesh, material, m_identityMatrix);
}

void Render::drawParticles(const Mesh& mesh, const control::Material& material, const glm::mat4& ModelMatrix) const
{
    __useProgram(m_shaders.particle);
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.particle, "uTexture_0"), 0);

        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ModelMatrix"),          1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform1f(glGetUniformLocation(m_shaders.particle, "u_scale"), m_scale);

        __drawMesh(mesh);
    }
}

void Render::drawParticlesForHUD(const Mesh& mesh, const control::Material& material) const
{
    drawParticlesForHUD(mesh, material, m_identityMatrix);
}

void Render::drawParticlesForHUD(const Mesh& mesh, const control::Material& material, const glm::mat4& ModelMatrix) const
{
    __useProgram(m_shaders.particle);
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.particle, "uTexture_0"), 0);

        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle, "u_ModelMatrix"),          1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform1f(glGetUniformLocation(m_shaders.particle, "u_scale"), m_scale);

        __drawMesh(mesh);
    }
}

void Render::drawBlinkingParticles(const Mesh& mesh, const control::Material& material) const
{
    __useProgram(m_shaders.particle_blink);
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.model()->diffusemap);
        glUniform1i(glGetUniformLocation(m_shaders.particle_blink, "uTexture_0"), 0);
        glUniform1f(glGetUniformLocation(m_shaders.particle_blink, "u_time"), m_time);

        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle_blink, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.particle_blink, "u_ModelMatrix"),          1, GL_FALSE, &m_identityMatrix[0][0]);

        glUniform1f(glGetUniformLocation(m_shaders.particle_blink, "u_scale"), m_scale);

        __drawMesh(mesh);
    }
}

void Render::drawStarField(int w, int h, float pos_x, float pos_y) const
{
    // ugly
    glm::mat4 TranslateMatrix = glm::translate(glm::vec3(w/2, h/2, SCREEN_QUAD_ZPOS));
    glm::mat4 ScaleMatrix     = glm::scale(glm::vec3(w/2, h/2, 1.0f));
    glm::mat4 ModelMatrix     = TranslateMatrix * ScaleMatrix;
    // ugly

    __useProgram(m_shaders.starfield);
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.starfield, "u_ProjectionViewMatrix"), 1, GL_FALSE, &m_projectionMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_shaders.starfield, "u_ModelMatrix")         , 1, GL_FALSE, &ModelMatrix[0][0]);

        glUniform2f(glGetUniformLocation(m_shaders.starfield, "resolution"), w, h);
        glUniform2f(glGetUniformLocation(m_shaders.starfield, "mouse"), pos_x, pos_y);
        glUniform1f(glGetUniformLocation(m_shaders.starfield, "time"), 1.0f);

        __drawMesh(*m_meshQuad);
    }
}

void Render::__useProgram(GLint program) const
{
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);
    if (id != program) {
        glUseProgram(program);
    }
}

void Render::drawAxis(const glm::mat4& modelMatrix) const
{
    //__useProgram(0);
    glLineWidth(m_meshAxis->linesWidth());
    drawMesh(*m_meshAxis, modelMatrix);
}

void Render::drawLines(const Mesh& mesh) const
{
    //__useProgram(0);
    glLineWidth(mesh.linesWidth());
    __drawMesh(mesh);
}

//void Render::drawCollisionRadius(const glm::mat4& modelMatrix) const
//{
//    drawQuad(*m_materialCollisionRadius, modelMatrix);
//}

void Render::drawVector(const glm::vec3& v, const glm::vec3& pos, float length, float width) const
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

void Render::drawVector(const glm::vec3& v, const glm::mat4& ModelMatrix, float width) const
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

void Render::__updateFps()
{
    const auto now_time = std::chrono::steady_clock::now();
    float milliseconds_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now_time-m_lastTime).count();
    if (milliseconds_diff > 1000.0f) {
        m_fps = m_framesCounter;
        m_framesCounter = 0;
        m_lastTime = now_time;
    } else {
        m_framesCounter++;
    }
}

void Render::drawDebugCircle(const glm::vec3& center,
                             float radius,
                             const glm::vec4& color) const
{
    drawCircle(*m_materialCollisionRadius, center, radius, color);
}

void Render::drawCircle(const control::Material& material,
                        const glm::vec3& center,
                        float radius,
                        const glm::vec4& color) const
{
    m_translateMatrix = glm::translate(center);
    m_scaleMatrix = glm::scale(glm::vec3(radius, radius, 1.0f));
    m_modelMatrix = m_translateMatrix * m_scaleMatrix;

    //__useProgram(0);
    //glLineWidth(m_meshCircle->linesWidth());
    //drawMesh(*m_meshCircle, *m_materialCollisionRadius, m_modelMatrix, color);
    drawMesh(*m_meshQuad, material, m_modelMatrix, color);
}

void Render::drawCircleWithPerlin(const control::Material& material,
                                  const glm::vec3& center,
                                  float radius,
                                  const glm::vec4& color) const
{
    m_translateMatrix = glm::translate(center);
    m_scaleMatrix = glm::scale(glm::vec3(radius, radius, 1.0f));
    m_modelMatrix = m_translateMatrix * m_scaleMatrix;

    //__useProgram(0);
    //glLineWidth(m_meshCircle->linesWidth());
    //drawMesh(*m_meshCircle, *m_materialCollisionRadius, m_modelMatrix, color);
    drawMeshWithPerlin(*m_meshQuad, material, m_modelMatrix, center, glm::vec3(radius, radius, 1.0f), color);
}

} // namespace jeti

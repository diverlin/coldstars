#include "openglwidget.hpp"

#include <glm/gtx/transform.hpp>

#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    m_camera = new jeti::Camera(1000);
    m_render = new jeti::Render(m_camera);
    m_modelScale = glm::vec3(500.0f);
}

OpenGLWidget::~OpenGLWidget()
{
    delete m_render;
    delete m_camera;
    delete m_mesh;
    delete m_material_model;
    delete m_material_control;
}

void OpenGLWidget::initializeGL()
{
    int w = 800;
    int h = 600;
    m_render->init(w, h);
    m_mesh = new jeti::Mesh("data/obj/vehicles/Anna_V_2.0_variations/anna_mod.obj");
    m_material_model = new jeti::model::Material("data/obj/vehicles/Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg");
    m_material_control = new jeti::control::Material(m_material_model);

    resizeGL(w, h);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    m_render->setSize(w, h);
    m_render->applyOrthogonalProjection();
}

void OpenGLWidget::paintGL()
{
    assert(isValid());
    m_render->clearColorAndDepthBuffers();
    if (m_useOrtho)
        m_render->applyOrthogonalProjection();
    else {
        m_render->applyPerspectiveProjection();
    }
    glm::mat4 scaleMatrix = glm::scale(m_modelScale);
    m_render->drawCollisionRadius(scaleMatrix);

    m_render->drawMeshLight(*m_mesh, *m_material_control, scaleMatrix);

    m_render->update();
    update();
}

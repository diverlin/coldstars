#include "openglwidget.hpp"

#include <glm/gtx/transform.hpp>

#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    m_render = new jeti::Render;
    m_camera = new jeti::Camera(m_render->zNear(), m_render->zFar());
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
    m_render->init(m_camera, w, h);
    m_mesh = new jeti::Mesh("data/obj/vehicles/Anna_V_2.0_variations/anna_mod.obj");
    m_material_model = new jeti::model::Material("data/obj/vehicles/Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg");
    m_material_control = new jeti::control::Material(m_material_model);

    resizeGL(w, h);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    m_render->setSize(w, h);
    m_render->applyOrthogonalProjection();

    setFixedSize(w, h);
}

void OpenGLWidget::paintGL()
{
    setFixedSize(800, 600);
    assert(isValid());
    qDebug()<<"gl size="<<size();
    m_render->clearColorAndDepthBuffers();
    m_render->applyOrthogonalProjection();
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(500.f, 500.f, 1.f));
    m_render->drawCollisionRadius(scaleMatrix);

    m_render->drawMeshLight(*m_mesh, *m_material_control, scaleMatrix);

    update();
}

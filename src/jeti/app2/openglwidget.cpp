#include "openglwidget.hpp"

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Base.hpp>

#include <glm/gtx/transform.hpp>

#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    m_camera = new jeti::Camera(1000);
    m_render = new jeti::Render(m_camera);
}

OpenGLWidget::~OpenGLWidget()
{
    delete m_render;
    delete m_camera;
    for (jeti::Base* object: m_objects) {
        delete object;
    }
    m_objects.clear();
}

void OpenGLWidget::initializeGL()
{
    int w = 800;
    int h = 600;
    m_render->init(w, h);

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
    m_render->applyOrthogonalProjection();

    for (jeti::Base* object: m_objects) {
            object->update();
            object->draw(*m_render);
            //m_render->drawCollisionRadius(object->modelMatrix());
            //m_render->drawMesh(*m_render->quadMesh(), object->modelMatrix());
    }
//    glm::mat4 scaleMatrix = glm::scale(glm::vec3(200.0f));
//    m_render->drawCollisionRadius(scaleMatrix);

//    scaleMatrix = glm::scale(glm::vec3(400.0f));
//    m_render->drawCollisionRadius(scaleMatrix);

    m_render->update();
    update();
}

void OpenGLWidget::add(jeti::Base* object) {
    m_objects.push_back(object);
}

void OpenGLWidget::take(jeti::Base*) {
    assert(false);
}

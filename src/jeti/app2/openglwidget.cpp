#include "openglwidget.hpp"

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>
#include <jeti/view/Base.hpp>
#include <jeti/view/Editable.hpp>

#include <glm/gtx/transform.hpp>

#include <QMouseEvent>
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
    for (jeti::view::Base* object: m_objects) {
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

    for (jeti::view::Base* object: m_objects) {
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

glm::vec2 OpenGLWidget::_cursorWidgetToWorldCoord(float x, float y) const
{
    //return glm::vec2(x /*- size().width()/2*/, y /*- size().height()/2*/);
    return m_render->toWorldCoord(glm::vec2(x,m_render->height()-y));
}

jeti::view::Base*
OpenGLWidget::_findClosest(const glm::vec2& cursorPos) const
{
    // pass 1: find intersected objects
    std::vector<jeti::view::Base*> m_intersected_objects;
    for(jeti::view::Base* object: m_objects) {
        if (object->isPointInsideShape(cursorPos)) {
            m_intersected_objects.push_back(object);
        }
    }

    // pass 2: collect distances among intersected
    std::vector<float> distances;
    for(jeti::view::Base* object: m_intersected_objects) {
        distances.push_back(object->distanceTo(cursorPos));
    }

    // pass 3: find shortest distance
    int index = -1;
    float min = 9999999.0f;
    for(int i=0; i<distances.size(); ++i) {
        if (distances[i] < min) {
            index = i;
            min = distances[i];
        }
    }

    // return result
    if (index != -1) {
        return m_intersected_objects[index];
    }

    return nullptr;
}

void OpenGLWidget::_trySelect(const glm::vec2& cursorPos)
{
    m_selectedObject = _findClosest(cursorPos);
    if (m_selectedObject) {
        jeti::view::Editable* baseEditable = static_cast<jeti::view::Editable*>(m_selectedObject);
        m_controlObject = baseEditable->collisionWithControls(cursorPos);
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    m_cursorPos = _cursorWidgetToWorldCoord(event->x(), event->y());
    if (m_selectedObject) {
        m_selectedObject->setPosition(m_cursorPos.x, m_cursorPos.y, 0);
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    m_cursorPos = _cursorWidgetToWorldCoord(event->x(), event->y());
    _trySelect(m_cursorPos);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_selectedObject) {
        m_selectedObject = nullptr;
    }
}

void OpenGLWidget::add(jeti::view::Base* object) {
    m_objects.push_back(object);
}

void OpenGLWidget::take(jeti::view::Base*) {
    assert(false);
}

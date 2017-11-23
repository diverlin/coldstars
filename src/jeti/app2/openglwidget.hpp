#pragma once

#include <jeti/MyGl.hpp> // must be called first

namespace jeti {
class Render;
class Camera;
namespace view {
class Base;
class Control;
} // namespace view
} // namespace jeti

#include <glm/glm.hpp>

#include <QtWidgets/QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void add(jeti::view::Base*);
    void take(jeti::view::Base*);

    void remove(jeti::view::Base*);
    void select(jeti::view::Base*);

    jeti::Render* render() const { return m_render; }

signals:
    void selectedObjectChanged(jeti::view::Base*);

protected:
    void initializeGL() override;
    void resizeGL(int, int) override;
    void paintGL() override;

    QSize minimumSizeHint() const override { return QSize(300, 300); }
    QSize sizeHint() const override { return QSize(500, 500); }

    void mouseMoveEvent(QMouseEvent*) override final;
    void mousePressEvent(QMouseEvent*) override final;
    void mouseReleaseEvent(QMouseEvent*) override final;

    glm::vec2 _cursorWidgetToWorldCoord(float, float) const;
    jeti::view::Base* _findClosest(const glm::vec2&) const;
    void _trySelect(const glm::vec2&);

private:
    glm::vec2 m_cursorPosPrev;
    glm::vec2 m_cursorPos;
    jeti::Render* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
    std::vector<jeti::view::Base*> m_objects;

    jeti::view::Base* m_selectedObject = nullptr;
    jeti::view::Control* m_controlObject = nullptr;

    void _resetSelection();
};

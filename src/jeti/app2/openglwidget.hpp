#pragma once

#include <jeti/MyGl.hpp> // must be called first

namespace jeti {
class Render;
class Camera;
class Base;
} // namespace jeti

#include <glm/glm.hpp>

#include <QtWidgets/QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void add(jeti::Base*);
    void take(jeti::Base*);

    jeti::Render* render() const { return m_render; }

protected:
    void initializeGL() override;
    void resizeGL(int, int) override;
    void paintGL() override;

    QSize minimumSizeHint() const override { return QSize(300, 300); }
    QSize sizeHint() const override { return QSize(500, 500); }

private:
    jeti::Render* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
    std::vector<jeti::Base*> m_objects;
};

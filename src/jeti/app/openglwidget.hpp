#pragma once

#include <jeti/MyGl.hpp> // must be called first

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Mesh.hpp>

#include <QtWidgets/QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void setUseOrtho(bool use_ortho) { m_useOrtho = use_ortho; }
    void setModelScale(const glm::vec3& scale) { m_modelScale = scale; }
    jeti::Render* render() const { return m_render; }

protected:
    void initializeGL() override;
    void resizeGL(int, int) override;
    void paintGL() override;

    QSize minimumSizeHint() const override { return QSize(300, 300); }
    QSize sizeHint() const override { return QSize(500, 500); }

private:
    bool m_useOrtho = false;

    glm::vec3 m_modelScale;
    jeti::Render* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
    jeti::Mesh* m_mesh = nullptr;
    jeti::model::Material* m_material_model = nullptr;
    jeti::control::Material* m_material_control = nullptr;
};
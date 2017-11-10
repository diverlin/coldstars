#include "openglwindow.hpp"

#include <QtGui/QGuiApplication>

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Mesh.hpp>

#include <glm/gtx/transform.hpp>

class DemoWindow : public OpenGLWindow
{
public:
    DemoWindow();

    void initialize() override;
    void render() override;

private:
    jeti::Render* m_render = nullptr;
    jeti::Camera* m_camera = nullptr;
    jeti::Mesh* m_mesh = nullptr;
    jeti::model::Material* m_material_model = nullptr;
    jeti::control::Material* m_material_control = nullptr;

    int m_frame = 0;
};

DemoWindow::DemoWindow()
    : m_frame(0)
{
    m_render = new jeti::Render;
    m_camera = new jeti::Camera(m_render->zNear(), m_render->zFar());
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    DemoWindow window;
    window.setFormat(format);
    window.resize(800, 600);
    window.show();

    return app.exec();
}

void DemoWindow::initialize()
{
    m_render->init(m_camera, 800, 600);
    m_mesh = new jeti::Mesh("data/obj/vehicles/Anna_V_2.0_variations/anna_mod.obj");
    m_material_model = new jeti::model::Material("data/obj/vehicles/Anna_V_2.0_variations/Anna_Textures/ship_hull12.jpg");
    m_material_control = new jeti::control::Material(m_material_model);
}

void DemoWindow::render()
{
    m_render->clearColorAndDepthBuffers();
    m_render->applyOrthogonalProjection();
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(500.f, 500.f, 1.f));
    m_render->drawCollisionRadius(scaleMatrix);

    m_render->drawMeshLight(*m_mesh, *m_material_control, scaleMatrix);

    ++m_frame;
}

#pragma once

#include <QMainWindow>

namespace qeti {
class ValueControlWidget;
class PointControlWidget;
} // namespace qeti

class OpenGLWidget;
class QBoxLayout;
class QCheckBox;

const QString KEY_USE_ORTHO_PROJECTION = "use_ortho";
const QString KEY_PROJECTION_ZNEAR = "projection.znear";
const QString KEY_PROJECTION_ZFAR = "projection.zfar";
const QString KEY_CAMERA_POSX = "camera.pos.x";
const QString KEY_CAMERA_POSY = "camera.pos.y";
const QString KEY_CAMERA_POSZ = "camera.pos.z";
const QString KEY_CAMERA_RADIUS = "camera.radius";
const QString KEY_MODEL_SCALEX = "model.scale.x";
const QString KEY_MODEL_SCALEY = "model.scale.y";
const QString KEY_MODEL_SCALEZ = "model.scale.z";
const QString KEY_LIGHT_POSX = "light.pos.x";
const QString KEY_LIGHT_POSY = "light.pos.y";
const QString KEY_LIGHT_POSZ = "light.pos.z";

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    int m_max = 5000;
    OpenGLWidget* m_glWidget = nullptr;

    QCheckBox* m_orthoProjCheckBox = nullptr;
    QCheckBox* m_perspProjCheckBox = nullptr;

    qeti::ValueControlWidget* m_zNearControlWidget = nullptr;
    qeti::ValueControlWidget* m_zFarControlWidget = nullptr;
    qeti::ValueControlWidget* m_cameraRadiusControlWidget = nullptr;

    qeti::PointControlWidget* m_cameraPositionWidget = nullptr;
    qeti::PointControlWidget* m_modelScaleWidget = nullptr;
    qeti::PointControlWidget* m_lightPositionWidget = nullptr;

    QBoxLayout* __create_mainLayout();
    OpenGLWidget* __create_glWidget() const;
    QWidget* __create_projectionSelectorWidget();
    QWidget* __create_projectionControlWidget();
    QWidget* __create_cameraControlWidget();
    QWidget* __create_modelScaleControlWidget();
    QWidget* __create_lightPositionControlWidget();

    void __setUseOrthoProjection(bool);
    void __setZNear(int);
    void __setZFar(int);
    void __setCameraPosition(const QVector3D&);
    void __setModelScale(const QVector3D&);
    void __setLightPosition(const QVector3D&);
    void __setCameraRadius(int);

    int __readKey(const QString&);
    void __saveKey(const QString&, int);
};



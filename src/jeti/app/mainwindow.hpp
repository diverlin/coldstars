#pragma once

#include <QtWidgets/QMainWindow>
#include <QFormLayout>

class OpenGLWidget;

namespace qeti {
class ValueControlWidget;
class PointControlWidget;
} // naemspace qeti

class QBoxLayout;

const QString KEY_PROJECTION_ZNEAR = "projection.znear";
const QString KEY_PROJECTION_ZFAR = "projection.zfar";
const QString KEY_CAMERA_POSX = "camera.x";
const QString KEY_CAMERA_POSY = "camera.y";
const QString KEY_CAMERA_POSZ = "camera.z";
const QString KEY_CAMERA_RADIUS = "camera.radius";

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    int m_max = 5000;
    OpenGLWidget* m_glWidget = nullptr;

    qeti::ValueControlWidget* m_zNearControlWidget = nullptr;
    qeti::ValueControlWidget* m_zFarControlWidget = nullptr;
    qeti::ValueControlWidget* m_cameraRadiusControlWidget = nullptr;

    qeti::PointControlWidget* m_cameraPositionWidget = nullptr;

    QBoxLayout* __create_mainLayout();
    OpenGLWidget* __create_glWidget() const;
    QWidget* __create_projectionControlWidget();
    QWidget* __create_cameraControlWidget();

    void __setZNear(int);
    void __setZFar(int);
    void __setCameraPosition(const QVector3D&);
    void __setCameraRadius(int);

    int __readKey(const QString&);
    void __saveKey(const QString&, int);
};



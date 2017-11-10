#pragma once

#include <QtWidgets/QMainWindow>

class QBoxLayout;

class OpenGLWidget;
class QLineEdit;
class QSlider;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    int m_max = 1000;
    int m_zNear = 0;
    int m_zFar = 0;
    OpenGLWidget* m_glWidget = nullptr;
//    QLineEdit* m_modelPosX = nullptr;
//    QLineEdit* m_modelPosY = nullptr;
//    QLineEdit* m_modelPosZ = nullptr;

//    QLineEdit* m_cameraPosX = nullptr;
//    QLineEdit* m_cameraPosY = nullptr;
//    QLineEdit* m_cameraPosZ = nullptr;

//    QLineEdit* m_cameraDirX = nullptr;
//    QLineEdit* m_cameraDirY = nullptr;
//    QLineEdit* m_cameraDirZ = nullptr;

    QLineEdit* m_zNearLineEdit = nullptr;
    QLineEdit* m_zFarLineEdit = nullptr;
    QSlider* m_zNearSlider = nullptr;
    QSlider* m_zFarSlider = nullptr;

    QBoxLayout* __create_mainLayout();
    OpenGLWidget* __create_glWidget() const;
    QWidget* __create_modelControlWIdget();
    QWidget* __create_projectionControlWidget();

    void __setZNear(int);
    void __setZFar(int);
};



#pragma once

#include <QtWidgets/QMainWindow>
#include <QFormLayout>

class OpenGLWidget;
class QLineEdit;
class QSlider;

class QFormLayout;
class QBoxLayout;

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    FormWidget(QWidget* parent = nullptr):QWidget(parent){
        m_layout = new QFormLayout(this);
        setLayout(m_layout);
    }
    ~FormWidget()=default;

    QFormLayout* layout() const { return m_layout; }

private:
    QFormLayout* m_layout = nullptr;
};


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
    //QWidget* __create_modelControlWIdget();
    QWidget* __create_projectionControlWidget();
    QWidget* __create_cameraControlWidget();

    void __setZNear(int);
    void __setZFar(int);
};



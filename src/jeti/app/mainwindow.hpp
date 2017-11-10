#pragma once

#include <QtWidgets/QMainWindow>

class OpenGLWidget;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    OpenGLWidget* m_glWidget = nullptr;
};



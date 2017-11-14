#pragma once

#include <QMainWindow>

namespace qeti {
class ValueControlWidget;
class PointControlWidget;
} // namespace qeti

class OpenGLWidget;
class QBoxLayout;
class QCheckBox;
class QTreeWidget;


namespace jeti {
class Mesh;
} // namespace jeti

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    int m_counter = 0;
    OpenGLWidget* m_glWidget = nullptr;
    QTreeWidget* m_nodeTree = nullptr;

    QBoxLayout* __create_mainLayout();
    OpenGLWidget* __create_glWidget() const;
    QTreeWidget* __create_nodeTreeWidget() const;

    void __create_object();

    jeti::Mesh* m_mesh = nullptr;
    jeti::Mesh* m_mesh2 = nullptr;
};



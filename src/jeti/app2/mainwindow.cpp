#include "mainwindow.hpp"
#include "openglwidget.hpp"

//#include <qeti/formwidget.hpp>
//#include <qeti/valuecontrolwidget.hpp>
//#include <qeti/pointcontrolwidget.hpp>

#include <jeti/Base.hpp>
#include <jeti/Render.hpp>

#include <QHBoxLayout>
//#include <QFormLayout>
//#include <QPushButton>
//#include <QLineEdit>
//#include <QSlider>
//#include <QLabel>
//#include <QIntValidator>
//#include <QVector3D>
//#include <QSettings>
//#include <QCheckBox>
//#include <QGroupBox>
//#include <QButtonGroup>
#include <QTreeWidget>

#include <QDebug>


MainWindow::MainWindow()
{
    // create
    QBoxLayout* mainLayout = __create_mainLayout();
    m_glWidget = __create_glWidget();
    m_nodeTree = __create_nodeTreeWidget();

    QWidget* topFrame = new QWidget;
    QWidget* topLeftFrame = new QWidget;
    QWidget* topRightFrame = new QWidget;
    QWidget* bottomFrame = new QWidget;
    QWidget* bottomLeftFrame = new QWidget;
    QWidget* bottomRightFrame = new QWidget;

    topFrame->setLayout(new QHBoxLayout);
    topLeftFrame->setLayout(new QVBoxLayout);
    topRightFrame->setLayout(new QVBoxLayout);
    bottomFrame->setLayout(new QHBoxLayout);
    bottomLeftFrame->setLayout(new QVBoxLayout);
    bottomRightFrame->setLayout(new QVBoxLayout);

    // mount
    topLeftFrame->layout()->addWidget(m_nodeTree);
    topRightFrame->layout()->addWidget(m_glWidget);

    topFrame->layout()->addWidget(topLeftFrame);
    topFrame->layout()->addWidget(topRightFrame);

    bottomFrame->layout()->addWidget(bottomLeftFrame);
    bottomFrame->layout()->addWidget(bottomRightFrame);

    mainLayout->addWidget(topFrame);
    mainLayout->addWidget(bottomFrame);

    // read settings and init ui
}

MainWindow::~MainWindow()
{

}

QBoxLayout*
MainWindow::__create_mainLayout() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    return layout;
}

OpenGLWidget*
MainWindow::__create_glWidget() const
{
    OpenGLWidget* widget = new OpenGLWidget;
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(2, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    widget->setFormat(format);
    return widget;
}

QTreeWidget*
MainWindow::__create_nodeTreeWidget() const
{
    QTreeWidget* widget = new QTreeWidget;
    return widget;
}


void MainWindow::__create_object() {
    jeti::Base* object = new jeti::Base(new jeti::Mesh, m_glWidget->render()->materialCollisionRadius());
    object->setScale(500.0f);
    m_glWidget->add(object);
}

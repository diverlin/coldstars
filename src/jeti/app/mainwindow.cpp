#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

MainWindow::MainWindow()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    m_glWidget = new OpenGLWidget(this);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(2, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    m_glWidget->setFormat(format);

    layout->addWidget(new QPushButton("push1"));
    layout->addWidget(m_glWidget);
    layout->addWidget(new QPushButton("push2"));
}

MainWindow::~MainWindow()
{

}



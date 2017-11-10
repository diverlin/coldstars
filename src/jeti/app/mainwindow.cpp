#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include "formwidget.hpp"
#include "controlwidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QIntValidator>

#include <QDebug>



namespace {
QWidget* widgets_to_row(const QList<QWidget*>& list) {
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();
    widget->setLayout(layout);
    for (QWidget* widget: list) {
        layout->addWidget(widget);
    }
    return widget;
}
QWidget* widgets_to_column(const QList<QWidget*>& list) {
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    widget->setLayout(layout);
    for (QWidget* widget: list) {
        layout->addWidget(widget);
    }
    return widget;
}

} // namespace

MainWindow::MainWindow()
{
    QBoxLayout* mainLayout = __create_mainLayout();
    m_glWidget = __create_glWidget();

///    mainLayout->addWidget(new QPushButton("push1"));
    mainLayout->addWidget(m_glWidget);
//    mainLayout->addWidget(new QPushButton("push2"));
    mainLayout->addWidget(__create_projectionControlWidget());

    __setZNear(300);
    __setZFar(1000);
}

MainWindow::~MainWindow()
{

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

QBoxLayout*
MainWindow::__create_mainLayout() {
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    return layout;
}

QWidget*
MainWindow::__create_projectionControlWidget() {
    qeti::FormWidget* form = new qeti::FormWidget();

    m_zNear = new qeti::ControlWidget(-m_max, m_max);
    m_zFar = new qeti::ControlWidget(-m_max, m_max);

    // connect
    connect(m_zNear, &qeti::ControlWidget::valueChanged, this, [this](int value) {
        __setZNear(value);
    });
    connect(m_zFar, &qeti::ControlWidget::valueChanged, this, [this](int value) {
        __setZFar(value);
    });

    form->layout()->addRow("z near:", m_zNear);
    form->layout()->addRow("z far:", m_zFar);

    return form;
}

QWidget*
MainWindow::__create_cameraControlWidget()
{
    qeti::FormWidget* form = new qeti::FormWidget();

    //QWidget* znear_row = widgets_to_row(QList<QWidget*>()<<m_zNearLineEdit<<m_zNearSlider);
}

void MainWindow::__setZNear(int value)
{
    m_zNear->setValue(value);
    m_glWidget->render()->setZNear(value);
}

void MainWindow::__setZFar(int value)
{
    m_zFar->setValue(value);
    m_glWidget->render()->setZFar(value);
}



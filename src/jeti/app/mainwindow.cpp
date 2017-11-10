#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include "qeti/formwidget.hpp"
#include "qeti/valuecontrolwidget.hpp"

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
    // create
    qeti::FormWidget* form = new qeti::FormWidget();
    m_zNearControlWIdget = new qeti::ValueControlWidget(-m_max, m_max);
    m_zFarControlWidget = new qeti::ValueControlWidget(-m_max, m_max);

    // connect
    connect(m_zNearControlWIdget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __setZNear(value);
    });
    connect(m_zFarControlWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __setZFar(value);
    });

    // mount
    form->layout()->addRow("z near:", m_zNearControlWIdget);
    form->layout()->addRow("z far:", m_zFarControlWidget);

    return form;
}

QWidget*
MainWindow::__create_cameraControlWidget()
{
    // create
    //qeti::FormWidget* form = new qeti::FormWidget();

    //QWidget* znear_row = widgets_to_row(QList<QWidget*>()<<m_zNearLineEdit<<m_zNearSlider);
}

void MainWindow::__setZNear(int value)
{
    m_zNearControlWIdget->setValue(value);
    m_glWidget->render()->setZNear(value);
}

void MainWindow::__setZFar(int value)
{
    m_zFarControlWidget->setValue(value);
    m_glWidget->render()->setZFar(value);
}



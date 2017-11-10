#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include "qeti/formwidget.hpp"
#include "qeti/valuecontrolwidget.hpp"
#include "qeti/pointcontrolwidget.hpp"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QIntValidator>
#include <QVector3D>
#include <QSettings>

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

glm::vec3 to_glmvec3(const QVector3D& v) {
    return glm::vec3(v.x(), v.y(), v.z());
}

} // namespace

MainWindow::MainWindow()
{
    QBoxLayout* mainLayout = __create_mainLayout();
    m_glWidget = __create_glWidget();

    mainLayout->addWidget(m_glWidget);
    mainLayout->addWidget(__create_projectionControlWidget());
    mainLayout->addWidget(__create_cameraControlWidget());

    __setZNear(__readKey(KEY_PROJECTION_ZNEAR));
    __setZFar(__readKey(KEY_PROJECTION_ZFAR));
    QVector3D v;
    v.setX(__readKey(KEY_CAMERA_POSX));
    v.setY(__readKey(KEY_CAMERA_POSY));
    v.setZ(__readKey(KEY_CAMERA_POSZ));
    __setCameraPosition(v);
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
    m_zNearControlWidget = new qeti::ValueControlWidget(-m_max, m_max);
    m_zFarControlWidget = new qeti::ValueControlWidget(-m_max, m_max);

    // connect
    connect(m_zNearControlWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __setZNear(value);
    });
    connect(m_zFarControlWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __setZFar(value);
    });

    // mount
    form->layout()->addRow("z near:", m_zNearControlWidget);
    form->layout()->addRow("z far:", m_zFarControlWidget);

    return form;
}

QWidget*
MainWindow::__create_cameraControlWidget()
{
    // create
    qeti::FormWidget* form = new qeti::FormWidget();
    m_cameraPositionWidget = new qeti::PointControlWidget(-m_max, m_max, this);

    // connect
    connect(m_cameraPositionWidget, &qeti::PointControlWidget::valueChanged, this, [this](const QVector3D& value) {
        __setCameraPosition(value);
    });

    // mount
    form->layout()->addRow("camera pos:", m_cameraPositionWidget);

    return form;
}

void MainWindow::__setZNear(int value)
{
    m_zNearControlWidget->setValue(value);
    m_glWidget->render()->setZNear(value);

    __saveKey(KEY_PROJECTION_ZNEAR, value);
}

void MainWindow::__setZFar(int value)
{
    m_zFarControlWidget->setValue(value);
    m_glWidget->render()->setZFar(value);

    __saveKey(KEY_PROJECTION_ZFAR, value);
}

void MainWindow::__setCameraPosition(const QVector3D& value)
{
    m_cameraPositionWidget->setValue(value);
    glm::vec3 v(to_glmvec3(value));
    qDebug()<<v.x<<" "<<v.y<<" "<<v.z;
    m_glWidget->render()->camera()->setPosition(v);

    __saveKey(KEY_CAMERA_POSX, v.x);
    __saveKey(KEY_CAMERA_POSY, v.y);
    __saveKey(KEY_CAMERA_POSZ, v.z);
}

int MainWindow::__readKey(const QString& key)
{
    QSettings settings;
    return settings.value(key, 0).toInt();
}

void MainWindow::__saveKey(const QString& key, int val)
{
    QSettings settings;
    settings.setValue(key, val);
}

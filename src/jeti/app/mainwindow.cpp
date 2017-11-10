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
#include <QCheckBox>
#include <QGroupBox>
#include <QButtonGroup>

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
    // create
    QBoxLayout* mainLayout = __create_mainLayout();
    m_glWidget = __create_glWidget();
    m_cameraRadiusControlWidget = new qeti::ValueControlWidget(0, m_max);
    connect(m_cameraRadiusControlWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __setCameraRadius(value);
    });

    // mount
    QWidget* widgetLeft = new QWidget;
    widgetLeft->setLayout(new QVBoxLayout);

    QWidget* widgetRight = new QWidget;
    QFormLayout* formLayout = new QFormLayout;
    widgetRight->setLayout(formLayout);

    widgetLeft->layout()->addWidget(m_glWidget);
    formLayout->addWidget(__create_projectionSelectorWidget());
    formLayout->addRow("proj:", __create_projectionControlWidget());
    formLayout->addRow("cam pos:", __create_cameraControlWidget());
    formLayout->addRow("cam rad:", m_cameraRadiusControlWidget);
    formLayout->addRow("model scale:", __create_modelScaleControlWidget());
    formLayout->addRow("light pos:", __create_lightPositionControlWidget());

    mainLayout->addWidget(widgetLeft);
    mainLayout->addWidget(widgetRight);

    // read settings and init ui
    __setUseOrthoProjection(__readKey(KEY_USE_ORTHO_PROJECTION));

    __setZNear(__readKey(KEY_PROJECTION_ZNEAR));
    __setZFar(__readKey(KEY_PROJECTION_ZFAR));

    QVector3D camera_pos;
    camera_pos.setX(__readKey(KEY_CAMERA_POSX));
    camera_pos.setY(__readKey(KEY_CAMERA_POSY));
    camera_pos.setZ(__readKey(KEY_CAMERA_POSZ));
    __setCameraPosition(camera_pos);

    QVector3D model_scale;
    model_scale.setX(__readKey(KEY_MODEL_SCALEX));
    model_scale.setY(__readKey(KEY_MODEL_SCALEY));
    model_scale.setZ(__readKey(KEY_MODEL_SCALEZ));
    __setModelScale(model_scale);

    QVector3D light_position;
    light_position.setX(__readKey(KEY_LIGHT_POSX));
    light_position.setY(__readKey(KEY_LIGHT_POSY));
    light_position.setZ(__readKey(KEY_LIGHT_POSZ));
    __setLightPosition(light_position);

    __setCameraRadius(__readKey(KEY_CAMERA_RADIUS));
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
MainWindow::__create_projectionSelectorWidget() {
    QGroupBox* widget = new QGroupBox(tr("Projection"));
    QHBoxLayout* layout = new QHBoxLayout;
    widget->setLayout(layout);

    m_orthoProjCheckBox = new QCheckBox("ortho");
    m_perspProjCheckBox = new QCheckBox("persp");

    layout->addWidget(m_perspProjCheckBox);
    layout->addWidget(m_orthoProjCheckBox);

    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(m_orthoProjCheckBox);
    group->addButton(m_perspProjCheckBox);

    connect(group, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
        [=](QAbstractButton* button){
        bool useOrtho = false;
        if (button == m_orthoProjCheckBox) {
            useOrtho = true;
        }
        if (button == m_perspProjCheckBox) {
            useOrtho = false;
        }
        __setUseOrthoProjection(useOrtho);
    });

//    layout->addStretch(1);
//    group->setCheckable(true);
//    group->setChecked(false);

    return widget;
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
    m_cameraPositionWidget = new qeti::PointControlWidget(-m_max, m_max, "", this);

    // connect
    connect(m_cameraPositionWidget, &qeti::PointControlWidget::valueChanged, this, [this](const QVector3D& value) {
        __setCameraPosition(value);
    });

    // mount
    return m_cameraPositionWidget;
}

QWidget*
MainWindow::__create_modelScaleControlWidget()
{
    // create
    m_modelScaleWidget = new qeti::PointControlWidget(1, m_max, "", this);

    // connect
    connect(m_modelScaleWidget, &qeti::PointControlWidget::valueChanged, this, [this](const QVector3D& value) {
        __setModelScale(value);
    });

    // mount
    return m_modelScaleWidget;
}

QWidget*
MainWindow::__create_lightPositionControlWidget()
{
    // create
    m_lightPositionWidget = new qeti::PointControlWidget(-m_max, m_max, "", this);

    // connect
    connect(m_lightPositionWidget, &qeti::PointControlWidget::valueChanged, this, [this](const QVector3D& value) {
        __setLightPosition(value);
    });

    // mount
    return m_lightPositionWidget;
}


void MainWindow::__setUseOrthoProjection(bool useOrtho)
{
    if (useOrtho && !m_orthoProjCheckBox->isChecked()) {
        m_orthoProjCheckBox->setChecked(true);
    }
    if (!useOrtho && !m_perspProjCheckBox->isChecked()) {
        m_perspProjCheckBox->setChecked(true);
    }
    m_glWidget->setUseOrtho(useOrtho);
    __saveKey(KEY_USE_ORTHO_PROJECTION, useOrtho);
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
    //qDebug()<<v.x<<" "<<v.y<<" "<<v.z;
    m_glWidget->render()->camera()->setPosition(v);

    __saveKey(KEY_CAMERA_POSX, v.x);
    __saveKey(KEY_CAMERA_POSY, v.y);
    __saveKey(KEY_CAMERA_POSZ, v.z);
}

void MainWindow::__setModelScale(const QVector3D& value)
{
    m_modelScaleWidget->setValue(value);
    glm::vec3 v(to_glmvec3(value));
    //qDebug()<<v.x<<" "<<v.y<<" "<<v.z;
    m_glWidget->setModelScale(v);

    __saveKey(KEY_MODEL_SCALEX, v.x);
    __saveKey(KEY_MODEL_SCALEY, v.y);
    __saveKey(KEY_MODEL_SCALEZ, v.z);
}

void MainWindow::__setLightPosition(const QVector3D& value)
{
    m_lightPositionWidget->setValue(value);
    glm::vec3 v(to_glmvec3(value));
    //qDebug()<<v.x<<" "<<v.y<<" "<<v.z;
    m_glWidget->render()->setLightPosition(v);

    __saveKey(KEY_LIGHT_POSX, v.x);
    __saveKey(KEY_LIGHT_POSY, v.y);
    __saveKey(KEY_LIGHT_POSZ, v.z);
}

void MainWindow::__setCameraRadius(int radius)
{
    m_glWidget->render()->camera()->setRadius(radius);
    __saveKey(KEY_CAMERA_RADIUS, radius);
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

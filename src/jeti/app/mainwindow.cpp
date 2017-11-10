#include "mainwindow.hpp"
#include "openglwidget.hpp"

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
    QWidget* frame = new QWidget();
    QFormLayout* layout = new QFormLayout();
    frame->setLayout(layout);

    m_zNearLineEdit = new QLineEdit;
    m_zNearLineEdit->setValidator(new QIntValidator(-m_max, m_max, this));
    m_zFarLineEdit = new QLineEdit;
    m_zFarLineEdit->setValidator(new QIntValidator(-m_max, m_max, this));
    m_zNearSlider = new QSlider(Qt::Horizontal);
    m_zNearSlider->setRange(-m_max, m_max);
    m_zFarSlider = new QSlider(Qt::Horizontal);
    m_zFarSlider->setRange(-m_max, m_max);

    // connect
    // sliders to lineedits
    connect(m_zNearSlider, &QSlider::valueChanged, this, [this]() {
        __setZNear(m_zNearSlider->value());
    });
    connect(m_zFarSlider, &QSlider::valueChanged, this, [this]() {
        __setZFar(m_zFarSlider->value());
    });
    // lineedits to sliders
    connect(m_zNearLineEdit, &QLineEdit::textChanged, this, [this]() {
        __setZNear(m_zNearLineEdit->text().toInt());
    });
    connect(m_zFarLineEdit, &QLineEdit::textChanged, this, [this]() {
        __setZFar(m_zFarLineEdit->text().toInt());
    });

    // stick
    QWidget* znear_row = widgets_to_row(QList<QWidget*>()<<m_zNearLineEdit<<m_zNearSlider);
    QWidget* zfar_row = widgets_to_row(QList<QWidget*>()<<m_zFarLineEdit<<m_zFarSlider);

    layout->addRow("z near:", znear_row);
    layout->addRow("z far:", zfar_row);

    return frame;
}

void MainWindow::__setZNear(int val)
{
    m_zNear = val;
    QString zNearText = QString::number(val);
    if (m_zNearLineEdit->text() != zNearText) {
        m_zNearLineEdit->setText(zNearText);
    }
    if (m_zNearSlider->value() != val) {
        m_zNearSlider->setValue(val);
    }
    m_glWidget->render()->setZNear(val);
}

void MainWindow::__setZFar(int val)
{
    m_zFar = val;
    QString zFarText = QString::number(val);
    if (m_zFarLineEdit->text() != zFarText) {
        m_zFarLineEdit->setText(zFarText);
    }
    if (m_zFarSlider->value() != val) {
        m_zFarSlider->setValue(val);
    }
    m_glWidget->render()->setZFar(val);
}



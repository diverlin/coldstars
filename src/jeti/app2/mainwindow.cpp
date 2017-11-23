#include "mainwindow.hpp"
#include "openglwidget.hpp"

//#include <qeti/formwidget.hpp>
//#include <qeti/valuecontrolwidget.hpp>
//#include <qeti/pointcontrolwidget.hpp>

#include <jeti/view/Editable.hpp>
#include <jeti/Render.hpp>

#include <meti/RandUtils.hpp>

#include <QHBoxLayout>
#include <QPushButton>
#include <QTreeWidget>

#include <QDebug>


MainWindow::MainWindow()
{
    srand(time(NULL));

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
    QPushButton* add = new QPushButton(tr("Create Obj"));
    bottomLeftFrame->layout()->addWidget(add);
    connect(add, &QPushButton::clicked, this, [this](bool) {
        __create_object();
    });

    QPushButton* del = new QPushButton(tr("Delete Obj"));
    bottomLeftFrame->layout()->addWidget(del);
    connect(del, &QPushButton::clicked, this, [this](bool) {
        __delete_object();
    });
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    for (int i=0; i<10; ++i) {
        __create_object();
    }
}

QBoxLayout*
MainWindow::__create_mainLayout() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout();
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

    connect(widget, &OpenGLWidget::selectedObjectChanged, this, &MainWindow::__slot_changeCurrentItem);

    return widget;
}

QTreeWidget*
MainWindow::__create_nodeTreeWidget() const
{
    QTreeWidget* widget = new QTreeWidget;

    // connection
    connect(widget, &QTreeWidget::currentItemChanged, this, &MainWindow::__slot_onCurrentItemChanged);

    return widget;
}


void MainWindow::__create_object() {
    if (!m_mesh) {
        m_mesh = new jeti::Mesh;
    }
    if (!m_mesh2) { // some bug, the obj with such mesh is not rendered
        m_mesh2 = new jeti::Mesh;
    }

    qDebug()<<"__create_object";

    m_counter++;
    jeti::control::Material* material = new jeti::control::Material(m_glWidget->render()->materialCollisionRadius()->model());
    jeti::view::Editable* object = new jeti::view::Editable(m_mesh, material);
    float size = meti::rand::gen_float(30.0f, 60.0f);
    object->setSize(size, size, 1.0f);

    object->setPosition(meti::rand::gen_vec3xy(200.f));
    m_glWidget->add(object);

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, "object");
    m_nodeTree->addTopLevelItem(item);

    m_itemsobjects_map.insert(std::make_pair(item, object));
}

void MainWindow::__delete_object() {
    QTreeWidgetItem* currentItem = m_nodeTree->currentItem();
    if (!currentItem) {
        return;
    }

    std::map<QTreeWidgetItem*, jeti::view::Base*>::iterator it = m_itemsobjects_map.find(currentItem);
    if (it == m_itemsobjects_map.end()) {
        return;
    }
    m_nodeTree->removeItemWidget(currentItem, m_nodeTree->currentColumn());
    jeti::view::Base* object = it->second;
    m_glWidget->remove(object);

    m_itemsobjects_map.erase(it);

    delete currentItem;
    delete object;
}


void MainWindow::__slot_onCurrentItemChanged(QTreeWidgetItem* curr, QTreeWidgetItem* prev)
{
    m_glWidget->select(m_itemsobjects_map[curr]);
}

void MainWindow::__slot_changeCurrentItem(jeti::view::Base* object)
{
    for(std::map<QTreeWidgetItem*, jeti::view::Base*>::iterator it = m_itemsobjects_map.begin(); it != m_itemsobjects_map.end(); ++it) {
        if (it->second == object) {
            m_nodeTree->setCurrentItem(it->first);
            return;
        }
    }
}

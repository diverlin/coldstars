#pragma once

#include <QMainWindow>

#include <map>

//namespace qeti {
//class ValueControlWidget;
//class PointControlWidget;
//} // namespace qeti

class OpenGLWidget;
class QBoxLayout;
class QCheckBox;
class QTreeWidget;
class QTreeWidgetItem;


namespace jeti {
class Mesh;
namespace view {
class Base;
} // namespace view
} // namespace jeti

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

    void init();

private:
    int m_counter = 0;
    OpenGLWidget* m_glWidget = nullptr;
    QTreeWidget* m_nodeTree = nullptr;

    QBoxLayout* __create_mainLayout();
    OpenGLWidget* __create_glWidget() const;
    QTreeWidget* __create_nodeTreeWidget() const;

    jeti::Mesh* m_mesh = nullptr;
    jeti::Mesh* m_mesh2 = nullptr;

    std::map<QTreeWidgetItem*, jeti::view::Base*> m_itemsobjects_map;

    void __create_object();
    void __delete_object();

private slots:
    void __slot_onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);
    void __slot_changeCurrentItem(jeti::view::Base*);
};



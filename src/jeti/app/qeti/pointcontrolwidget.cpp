#include "pointcontrolwidget.hpp"
#include "valuecontrolwidget.hpp"

#include <QVBoxLayout>
#include <QDebug>

namespace qeti {

PointControlWidget::PointControlWidget(int min, int max, QWidget* parent)
    :
      QWidget(parent)
{
    // create
    m_controlXWidget = new qeti::ValueControlWidget(min, max, this);
    m_controlYWidget = new qeti::ValueControlWidget(min, max, this);
    m_controlZWidget = new qeti::ValueControlWidget(min, max, this);

    // connect
    connect(m_controlXWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __slot_setX(value);
    });
    connect(m_controlYWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __slot_setY(value);
    });
    connect(m_controlZWidget, &qeti::ValueControlWidget::valueChanged, this, [this](int value) {
        __slot_setZ(value);
    });

    // mount
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_controlXWidget);
    layout->addWidget(m_controlYWidget);
    layout->addWidget(m_controlZWidget);
    setLayout(layout);
}

void PointControlWidget::setValue(const QVector3D& v) {
    __set(v.x(), v.y(), v.z());
}

void PointControlWidget::__set(int x, int y, int z)
{
    bool was_changed = false;
    if (m_position.x() != x) {
        m_position.setX(x);
        m_controlXWidget->setValue(x);
        was_changed = true;
    }
    if (m_position.y() != y) {
        m_position.setX(y);
        m_controlYWidget->setValue(y);
        was_changed = true;
    }
    if (m_position.z() != z) {
        m_position.setX(z);
        m_controlZWidget->setValue(z);
        was_changed = true;
    }

    if (was_changed) {
        emit valueChanged(m_position);
    }
}

void PointControlWidget::__slot_setX(int x)
{
    qDebug()<<"__slot_setX(int x)";
    if (m_position.x() == x) {
        return;
    }
    m_position.setX(x);
    m_controlXWidget->setValue(x);
    emit valueChanged(m_position);
}

void PointControlWidget::__slot_setY(int y)
{
    if (m_position.y() == y) {
        return;
    }
    m_position.setY(y);
    m_controlYWidget->setValue(y);
    emit valueChanged(m_position);
}

void PointControlWidget::__slot_setZ(int z)
{
    if (m_position.z() == z) {
        return;
    }
    m_position.setZ(z);
    m_controlZWidget->setValue(z);
    emit valueChanged(m_position);
}

} // namespace qeti

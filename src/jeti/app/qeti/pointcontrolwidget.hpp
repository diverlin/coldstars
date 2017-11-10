#pragma once

#include <QWidget>
#include <QVector3D>

namespace qeti {

class ValueControlWidget;

class PointControlWidget : public QWidget
{
    Q_OBJECT
public:
    PointControlWidget(int min, int max, QWidget* parent = nullptr);
    ~PointControlWidget()=default;

    void setValue(const QVector3D&);

    QVector3D valueX() { return m_position; }

private slots:
    void __slot_setX(int x);
    void __slot_setY(int y);
    void __slot_setZ(int z);

signals:
    void valueChanged(QVector3D);

private:
    QVector3D m_position;

    qeti::ValueControlWidget* m_controlXWidget = nullptr;
    qeti::ValueControlWidget* m_controlYWidget = nullptr;
    qeti::ValueControlWidget* m_controlZWidget = nullptr;

    void __set(int x, int y, int z);
};

} // namespace qeti

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

    void set(const QVector3D&);
    void set(int x, int y, int z);

signals:
    void valueChanged(int, int, int);
    void valueChanged(QVector3D);

private:
    QVector3D m_point;

    qeti::ValueControlWidget* m_controlXWidget = nullptr;
    qeti::ValueControlWidget* m_controlYWidget = nullptr;
    qeti::ValueControlWidget* m_controlZWidget = nullptr;
};

} // namespace qeti

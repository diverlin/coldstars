#pragma once

#include <QWidget>

class QLineEdit;
class QSlider;
class QSpinBox;

namespace qeti {

class ValueControlWidget: public QWidget
{
    Q_OBJECT
public:
    ValueControlWidget(int min, int max, const QString& label="", QWidget* parent = nullptr);
    ~ValueControlWidget()=default;

    int value() const { return m_value; }

    void setValue(int value);

private slots:
    void __slot_setValue(int value);

signals:
    void valueChanged(int value);

private:
    int m_value = 0;
    QLineEdit* m_lineEdit = nullptr;
    QSlider* m_slider = nullptr;
    QSpinBox* m_spinBox = nullptr;
};

} // namespace qeti



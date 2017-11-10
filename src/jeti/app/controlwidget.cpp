#include "controlwidget.hpp"

#include <QSlider>
#include <QLineEdit>
#include <QIntValidator>
#include <QHBoxLayout>

namespace qeti {

ControlWidget::ControlWidget(int min, int max, QWidget* parent):QWidget(parent) {
    m_lineEdit = new QLineEdit;
    m_lineEdit->setValidator(new QIntValidator(min, max, this));

    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(min, max);

    connect(m_slider, &QSlider::valueChanged, this, [this](int value) {
        __slot_setValue(value);
    });
    connect(m_lineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        __slot_setValue(text.toInt());
    });

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_slider);
    setLayout(layout);
}

void ControlWidget::__slot_setValue(int value) {
    setValue(value);
}

void ControlWidget::setValue(int value)
{
    if (m_value == value) {
        return;
    }

    m_value = value;
    QString valueText = QString::number(value);
    if (m_lineEdit->text() != valueText) {
        m_lineEdit->setText(valueText);
    }
    if (m_slider->value() != value) {
        m_slider->setValue(value);
    }

    emit valueChanged(value);
}

} // namespace qeti

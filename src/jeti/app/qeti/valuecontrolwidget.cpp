#include "valuecontrolwidget.hpp"

#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QIntValidator>
#include <QHBoxLayout>

namespace qeti {

ValueControlWidget::ValueControlWidget(int min, int max, const QString& label, QWidget* parent)
    :
      QWidget(parent)
{
    // create
    m_lineEdit = new QLineEdit;
    m_lineEdit->setValidator(new QIntValidator(min, max, this));
    m_lineEdit->setText(QString::number(m_value));

    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(min, max);
    m_slider->setValue(m_value);

    // connect
    connect(m_slider, &QSlider::valueChanged, this, [this](int value) {
        __slot_setValue(value);
    });
    connect(m_lineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        __slot_setValue(text.toInt());
    });

    // mount
    QHBoxLayout* layout = new QHBoxLayout();
    if (!label.isEmpty()) {
        layout->addWidget(new QLabel(label));
    }
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_slider);
    setLayout(layout);
}

void ValueControlWidget::__slot_setValue(int value) {
    setValue(value);
}

void ValueControlWidget::setValue(int value)
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

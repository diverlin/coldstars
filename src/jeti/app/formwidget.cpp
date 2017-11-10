#include "formwidget.hpp"

#include <QFormLayout>

namespace qeti {

FormWidget::FormWidget(QWidget* parent)
    :
      QWidget(parent)
{
    m_layout = new QFormLayout(this);
    setLayout(m_layout);
}

} // namespace qeti

#pragma once

#include <QWidget>

class QFormLayout;

namespace qeti {

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    FormWidget(QWidget* parent = nullptr);
    ~FormWidget()=default;

    QFormLayout* layout() const { return m_layout; }

private:
    QFormLayout* m_layout = nullptr;
};

} // namespace qeti

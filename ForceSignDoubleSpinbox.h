#ifndef DOUBLESPINBOXADAPTED_H
#define DOUBLESPINBOXADAPTED_H

#include <QDoubleSpinBox>

class ForceSignDoubleSpinbox: public QDoubleSpinBox
{
public:
    using QDoubleSpinBox::QDoubleSpinBox;
    QString textFromValue(double value) const override
    {
        // Adapt the display of text to always show sign (+ or -)
        QString text = QDoubleSpinBox::textFromValue(value);
        if(value > 0)
            text.prepend(QChar('+'));
        return text;
    }
};

#endif // DOUBLESPINBOXADAPTED_H

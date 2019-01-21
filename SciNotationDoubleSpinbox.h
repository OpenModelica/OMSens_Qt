#ifndef SCINOTDOUBLESPINBOX_H
#define SCINOTDOUBLESPINBOX_H

#include <QObject>
#include <QDoubleSpinBox>

class SciNotationDoubleSpinbox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit SciNotationDoubleSpinbox(QWidget *parent = 0) : QDoubleSpinBox(parent) {}

    // Change the way we read the user input
    double valueFromText(const QString & text) const
    {
        double numFromStr = text.toDouble(); return numFromStr; }

    // Change the way we show the internal number
    QString textFromValue(double value) const
    {
        return QString::number(value, 'E', 6);
    }

    // Change the way we validate user input (if validate => valueFromText)
    QValidator::State validate(QString &text, int&) const
    {

        // Try to convert the string to double
        bool ok;
        text.toDouble(&ok);
        // See if it's a valid Double
        QValidator::State validationState;
        if(ok)
        {
            // If string conversion was valid, set as ascceptable
            validationState = QValidator::Acceptable;

        }
        else
        {
            // If string conversion was invalid, set as invalid
            validationState = QValidator::Invalid;
        }
        return validationState;
    }



signals:

public slots:
};

#endif // SCINOTDOUBLESPINBOX_H

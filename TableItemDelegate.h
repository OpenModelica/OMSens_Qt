#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H

#include <QStyledItemDelegate>

class TableItemDelegate : public QStyledItemDelegate
{
   Q_OBJECT
public:

   TableItemDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {}

   QString displayText(const QVariant & value, const QLocale & locale) const
   {
       QString text;
       switch (value.userType()) {
       case QVariant::Double:
           text = QString::number(value.toDouble(), 'G', 8);
           break;
       default:
           // If it's not a double, use Qt's default
           text = QStyledItemDelegate::displayText(value,locale);
           break;
       }
       return text;
   }
};

#endif // TABLEITEMDELEGATE_H

#include "HelpTab.h"

#include <QLabel>
#include <QFormLayout>

HelpTab::HelpTab(QString description, QWidget *parent) : QWidget(parent)
{
    // Save description
    mDescription = new QLabel(description, this);
    mDescription->setWordWrap(true);

    // Layout
    QFormLayout *mainLayout = new QFormLayout(this);
    // Description
    mainLayout->addRow(mDescription);
    setLayout(mainLayout);
}

#include "HelpTab.h"

#include <QLabel>
#include <QFormLayout>

HelpTab::HelpTab(QString description, QWidget *parent) : QWidget(parent)
{
    // Save description
    mDescription = new QLabel(description);
    mDescription->setWordWrap(true);

    // Layout
    QFormLayout *mainLayout = new QFormLayout;
    // Description
    mainLayout->addRow(mDescription);
    setLayout(mainLayout);
}

#include "HelpBrowser.h"

#include <QHBoxLayout>

HelpBrowser::HelpBrowser(const QString &textPath, QWidget *parent)
    : QDialog(parent)
{

    // Initialize text browser
    textBrowser = new QTextBrowser;
    textBrowser->setSource(textPath);


    // Layout
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(textBrowser);
    setLayout(pMainLayout);

    // Window attributes
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumHeight(900);
    setMinimumWidth(800);
}

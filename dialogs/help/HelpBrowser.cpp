#include "HelpBrowser.h"

#include <QHBoxLayout>

HelpBrowser::HelpBrowser(const QString &textPath, QWidget *parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    textBrowser = new QTextBrowser;

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(textBrowser);
    setLayout(pMainLayout);

    textBrowser->setSource(textPath);
}

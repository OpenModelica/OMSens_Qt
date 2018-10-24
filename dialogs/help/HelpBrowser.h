#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QDialog>
#include <QTextBrowser>

class HelpBrowser : public QDialog
{
    Q_OBJECT

public:
    HelpBrowser(const QString &textPath, QWidget *parent = 0);
private slots:

private:
    // GUI
    QTextBrowser *textBrowser;
};

#endif // HELPBROWSER_H

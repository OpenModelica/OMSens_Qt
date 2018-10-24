#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QObject>
#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>

class HelpBrowser : public QWidget
{
    Q_OBJECT

public:
    HelpBrowser(const QString &path, const QString &page,
                QWidget *parent = 0);

    static void showPage(const QString &page);

private slots:
    void updateWindowTitle();

private:
    QTextBrowser *textBrowser;
    QPushButton *homeButton;
    QPushButton *backButton;
    QPushButton *closeButton;
};

#endif // HELPBROWSER_H

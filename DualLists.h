#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class DualLists : public QWidget
{
    Q_OBJECT

public:
    // Constructors
    explicit DualLists(QWidget *parent = 0);
    // Lists manipulation (adding for now. We don't need deletion or other things for now)
    void addItemToLeftList(QString itemString);
    void addItemToRightList(QString itemString);
    // Getters
    QList<QListWidgetItem *> itemsOnRightList();

private:
    // Members
    //   Lists
    QListWidget *mpLeftList;
    QListWidget *mpRightList;
    //   Buttons
    QPushButton *mpMoveOneRightBtn;
    QPushButton *mpMoveAllRightBtn;
    QPushButton *mpMoveOneLeftBtn;
    QPushButton *mpMoveAllLeftBtn;
    //   Lists of buttons
    QVector<QPushButton*> mpLeftToRightBtns;
    QVector<QPushButton*> mpRightToLeftBtns;
    //   Layouts
    QHBoxLayout *mpMainLayout;
    QVBoxLayout *mpBtnsLayout;

    // General auxs
    void moveItemInIndexFromListToList(int itemIndex,QListWidget *fromList,QListWidget *toList,QVector<QPushButton*> fromListButtons);
    void moveAllItemsFromListToList(QListWidget *fromList,QListWidget *toList,QVector<QPushButton*> fromListButtons);
    // Constructor auxs
    void initializeMembers();
    void setupConnections();
    void organizeLayout();


private slots:
    void moveOneItemRight();
    void moveOneItemLeft();
    void enableLeftToRightBtns();
    void enableRightToLeftBtns();
    void moveAllItemsRight();
    void moveAllItemsLeft();
    void updateBtnsStatus();
};

#endif // MAINWINDOW_H

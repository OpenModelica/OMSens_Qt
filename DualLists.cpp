#include "DualLists.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>

DualLists::DualLists(QWidget *parent) :
    QWidget(parent)
{
    initializeMembers();
    organizeLayout();
    setupConnections();
}

// Constructor aux funcs
void DualLists::initializeMembers()
{
    // Initialize lists
    mpLeftList = new QListWidget;
    mpRightList = new QListWidget;
    //Enable sorting on both lists
    mpLeftList->setSortingEnabled(true);
    mpRightList->setSortingEnabled(true);

    // Initialize buttons
    mpMoveOneRightBtn = new QPushButton(">", this);
    mpMoveAllRightBtn = new QPushButton(">>", this);
    mpMoveOneLeftBtn = new QPushButton("<", this);
    mpMoveAllLeftBtn = new QPushButton("<<", this);
    // Disable all buttons until an item on a list is clicked
    mpMoveOneRightBtn->setEnabled(false);
    mpMoveAllRightBtn->setEnabled(false);
    mpMoveOneLeftBtn->setEnabled(false);
    mpMoveAllLeftBtn->setEnabled(false);
    // Initialize lists of buttons of similar use
    mpLeftToRightBtns << mpMoveOneRightBtn << mpMoveAllRightBtn;
    mpRightToLeftBtns << mpMoveOneLeftBtn << mpMoveAllLeftBtn;
}

void DualLists::organizeLayout()
{
    // Main layout that will contain widgets and sublayouts
    QHBoxLayout *mpMainLayout = new QHBoxLayout(this);

    // First add the list on the left
    mpMainLayout->addWidget(mpLeftList);

    // Buttons sublayout in the middle
    QVBoxLayout *mpBtnsLayout = new QVBoxLayout(this);
    mpBtnsLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mpBtnsLayout->addWidget(mpMoveOneRightBtn);
    mpBtnsLayout->addWidget(mpMoveAllRightBtn);
    mpBtnsLayout->addWidget(mpMoveOneLeftBtn);
    mpBtnsLayout->addWidget(mpMoveAllLeftBtn);
    mpBtnsLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add the buttons in the middle
    mpMainLayout->addLayout(mpBtnsLayout);

    // Add the list on the right
    mpMainLayout->addWidget(mpRightList);
}

void DualLists::setupConnections()
{
    // Enable buttons when item selected
    connect(mpLeftList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(enableLeftToRightBtns()));
    connect(mpRightList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(enableRightToLeftBtns()));
    // Move items when buttons pressed
    connect(mpMoveOneRightBtn, SIGNAL(clicked()), this, SLOT(moveOneItemRight()));
    connect(mpMoveAllRightBtn, SIGNAL(clicked()), this, SLOT(moveAllItemsRight()));
    connect(mpMoveOneLeftBtn, SIGNAL(clicked()), this, SLOT(moveOneItemLeft()));
    connect(mpMoveAllLeftBtn, SIGNAL(clicked()), this, SLOT(moveAllItemsLeft()));
}

// Private functions
void DualLists::moveItemInIndexFromListToList(int itemIndex,QListWidget *fromList,QListWidget *toList,QVector<QPushButton*> fromListButtons)
{
    // Remove item from "fromList" and get its pointer
    QListWidgetItem *itemToMove = fromList->takeItem(itemIndex);
    // Add item to "toList"  at the last position
    int toListPos = toList->count();
    toList->insertItem(toListPos, itemToMove);

    //Check if the sending list is empty after taking items out of it
    if(fromList->count() == 0)
    {
        // Disable the buttons if list empty
        foreach (QPushButton *pMoveButton, fromListButtons)
        {
        pMoveButton->setEnabled(false);
        }
    }
}

void DualLists::moveAllItemsFromListToList(QListWidget *fromList,QListWidget *toList,QVector<QPushButton*> fromListButtons)
{
       while (fromList->count()>0) {
         int pos=0;
         DualLists::moveItemInIndexFromListToList(pos,fromList,toList, fromListButtons);
    }
}


// Slots
void DualLists::moveOneItemRight()
{
    //Move selected item from left list to right list
    int currentRow = mpLeftList->currentRow();
    DualLists::moveItemInIndexFromListToList(currentRow,mpLeftList,mpRightList, mpLeftToRightBtns);
}
void DualLists::moveOneItemLeft()
{
    //Move selected item from right list to left list
    int currentRow = mpRightList->currentRow();
    DualLists::moveItemInIndexFromListToList(currentRow,mpRightList,mpLeftList, mpRightToLeftBtns);
}

void DualLists::enableLeftToRightBtns()
{
    foreach (QPushButton *pMoveButton, mpLeftToRightBtns)
    {
    pMoveButton->setEnabled(true);
    }
}

void DualLists::enableRightToLeftBtns()
{
    foreach (QPushButton *pMoveButton, mpRightToLeftBtns)
    {
    pMoveButton->setEnabled(true);
    }
}

void DualLists::moveAllItemsRight()
{
    //Move all items from left list to right list
    DualLists::moveAllItemsFromListToList(mpLeftList,mpRightList, mpLeftToRightBtns);
}
void DualLists::moveAllItemsLeft()
{
    //Move all items from right list to left list
    DualLists::moveAllItemsFromListToList(mpRightList,mpLeftList,mpRightToLeftBtns);
}

void DualLists::updateBtnsStatus()
{
    // Status bools
    bool leftListHasItemSelected =mpLeftList->selectedItems().isEmpty();
    bool rightListHasItemSelected =mpRightList->selectedItems().isEmpty();
    // "From left list" buttons
    mpMoveOneLeftBtn->setEnabled(leftListHasItemSelected);
    mpMoveAllLeftBtn->setEnabled(leftListHasItemSelected);
    // "Move all" buttons
    mpMoveOneRightBtn->setEnabled(rightListHasItemSelected);
    mpMoveAllRightBtn->setEnabled(rightListHasItemSelected);

}

// Public functions

void DualLists::addItemToLeftList(QString itemString)
{
    mpLeftList->addItem(itemString);
}

void DualLists::addItemToRightList(QString itemString)
{
    mpRightList->addItem(itemString);
}

QList<QListWidgetItem*> DualLists::itemsOnRightList()
{
    QList<QListWidgetItem*> items;
    for(int i_item=0; i_item<mpRightList->count(); i_item++)
    {
        items.append(mpRightList->item(i_item));
    }
    return items;
}

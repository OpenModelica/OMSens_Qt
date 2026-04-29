/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2026, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF AGPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.8.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GNU AGPL
 * VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs:
 * http://www.openmodelica.org or
 * https://github.com/OpenModelica/ or
 * http://www.ida.liu.se/projects/OpenModelica,
 * and in the OpenModelica distribution.
 *
 * GNU AGPL version 3 is obtained from:
 * https://www.gnu.org/licenses/licenses.html#GPL
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

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

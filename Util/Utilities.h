/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2014, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */
/*
 * @author Adeel Asghar <adeel.asghar@liu.se>
 */

#include <QApplication>
#include <QSplashScreen>
#include <QMdiArea>
#include <QLineEdit>
#include <QThread>
#include <QToolButton>
#include <QComboBox>
#include <QPushButton>
#include <QFile>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVariant>
#include <QDebug>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QProcess>
#include <QSettings>
#include <QFileIconProvider>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollArea>
#include <QScrollBar>
#include <QGenericMatrix>

#ifndef UTILITIES_H
#define UTILITIES_H
//QUEDAN:
class Label : public QLabel
{
public:
  Label(QWidget *parent = 0, Qt::WindowFlags flags = 0);
  Label(const QString &text, QWidget *parent = 0, Qt::WindowFlags flags = 0);
  Qt::TextElideMode elideMode() const {return mElideMode;}
  void setElideMode(Qt::TextElideMode elideMode) {mElideMode = elideMode;}
  virtual QSize minimumSizeHint() const;
  virtual QSize sizeHint() const;
  void setText(const QString &text);
private:
  Qt::TextElideMode mElideMode;
  QString mText;
protected:
  virtual void resizeEvent(QResizeEvent *event);
};
namespace Utilities {

  //QUEDAN:
  Label* getHeadingLabel(QString heading);
  QFrame* getHeadingLine();
  // QUEDAN^

} // namespace Utilities
// QUEDAN^

#endif // UTILITIES_H

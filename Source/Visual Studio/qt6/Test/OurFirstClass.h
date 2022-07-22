#pragma once

#include <MyForm.h>
#include <ProzesseQT.h>

#include <QtWidgets/QMainWindow>
#include "ui_OurFirstClass.h"

#include <QLabel>

class OurFirstClass : public QMainWindow
{
    Q_OBJECT

public:
    OurFirstClass(QWidget *parent = Q_NULLPTR);

private:
    Ui::OurFirstClassClass ui;
    QLabel* statusLabel;
    TProcessQT proc;
    TMyForm frm;
private slots:
   void PersonNewEvent(void);
   void PersonEditEvent(void);
   void EmployeeNewEvent(void);
   void EmployeeEditEvent(void);
   void PersonListEvent(void);
   void RollDiceEvent(void);
   void WorkEvent(void);

};

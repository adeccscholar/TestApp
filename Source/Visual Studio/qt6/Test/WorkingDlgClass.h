#pragma once

#include "Prozesse.h"
#include <QDialog>
#include "ui_WorkingDlgClass.h"

class WorkingDlgClass : public QDialog
{
    Q_OBJECT

public:
    WorkingDlgClass(TProcess& proc, QWidget *parent = Q_NULLPTR);
    ~WorkingDlgClass();

private:
    Ui::WorkingDlgClass ui;

    TProcess& process;
    TMyForm   frm;

private slots:
   void SelectEvent(void);
   void StartEvent(void);
};

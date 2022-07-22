#include "WorkingDlgClass.h"

WorkingDlgClass::WorkingDlgClass(TProcess& proc, QWidget *parent)
  : process(proc), QDialog(parent)
{
    ui.setupUi(this);
    frm.Set(this, false);

    connect(ui.btnSelect, SIGNAL(clicked()), this, SLOT(SelectEvent()));
    connect(ui.btnStart,  SIGNAL(clicked()), this, SLOT(StartEvent()));
    connect(ui.btnClose,  SIGNAL(clicked()), this, SLOT(close()));
}

WorkingDlgClass::~WorkingDlgClass()
{
}

void WorkingDlgClass::SelectEvent(void) {
   process.SelectWithFileDlg(frm);
   }

void WorkingDlgClass::StartEvent(void) {
   //ui.lvData->setUpdatesEnabled(false);
   process.WorkingWith(frm);
   //ui.lvData->setUpdatesEnabled(true);
   }
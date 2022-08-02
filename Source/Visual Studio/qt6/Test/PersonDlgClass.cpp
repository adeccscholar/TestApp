#include "PersonDlgClass.h"

PersonDlgClass::PersonDlgClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.btnOk,     &QPushButton::clicked,       this, &QDialog::accept);
    connect(ui.btnCancel, &QPushButton::clicked,       this, &QDialog::reject);
    connect(ui.edtSalary, &QLineEdit::editingFinished, this, &PersonDlgClass::SalaryEditChanged);
    
}

PersonDlgClass::~PersonDlgClass()
{
}


void PersonDlgClass::SalaryEditChanged(void) { 
   return;
   }
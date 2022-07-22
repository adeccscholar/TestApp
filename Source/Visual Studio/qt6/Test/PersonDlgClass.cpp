#include "PersonDlgClass.h"

PersonDlgClass::PersonDlgClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

PersonDlgClass::~PersonDlgClass()
{
}

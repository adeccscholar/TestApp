#include "PersonListClass.h"

PersonListClass::PersonListClass(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(accept()));
}

PersonListClass::~PersonListClass()
{
}

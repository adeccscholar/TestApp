#pragma once

#include <QDialog>
#include "ui_PersonListClass.h"

class PersonListClass : public QDialog
{
    Q_OBJECT

public:
    PersonListClass(QWidget *parent = Q_NULLPTR);
    ~PersonListClass();

private:
    Ui::PersonListClass ui;
};

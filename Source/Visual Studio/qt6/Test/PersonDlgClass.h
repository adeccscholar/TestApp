#pragma once

#include <QDialog>
#include "ui_PersonDlgClass.h"

class PersonDlgClass : public QDialog
{
    Q_OBJECT

public:
    PersonDlgClass(QWidget *parent = Q_NULLPTR);
    ~PersonDlgClass();

private:
    Ui::PersonDlgClass ui;

private slots:
    void SalaryEditChanged(void);
};

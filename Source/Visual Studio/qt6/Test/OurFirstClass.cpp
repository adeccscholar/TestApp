#include "OurFirstClass.h"
#include "PersonDlgClass.h"
#include "pugixml.hpp"

#include <QFile>

#include <iostream>
#include <iterator>
#include <algorithm>

TStreamWrapper<Narrow> old_cout(std::cout), old_cerr(std::cerr), old_clog(std::clog);


OurFirstClass::OurFirstClass(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.statusBar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    statusLabel = new QLabel(this);
    statusLabel->setObjectName("sbMain");
    statusLabel->setText("sbMain");
    ui.statusBar->addPermanentWidget(statusLabel);
    frm.Set(this, false);

    QFile form_data(":/data/LocalizeFirstApp.xml");
    form_data.open(QFile::ReadOnly |  QIODevice::Text);
    QByteArray data = form_data.readAll();
    std::istringstream ins(data.toStdString());
    proc.Read(ins);
    proc.InitMainForm(frm);

    /*
    std::vector<std::string> vecTest = { "Test1 ", "Test 2", "noch ein Test", "4. Test", "letzter Test", "jetzt wirklich" };
    std::ostream mys(new ListBoxStreamBuf<Narrow>(ui.listWidget));
    std::copy(vecTest.begin(), vecTest.end(), std::ostream_iterator<std::string>(mys, "\n"));
    std::copy(vecTest.begin(), vecTest.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    */
    connect(ui.btnPersonNew,    SIGNAL(clicked()), this, SLOT(PersonNewEvent()));
    connect(ui.btnPersonEdit,   SIGNAL(clicked()), this, SLOT(PersonEditEvent()));
    connect(ui.btnEmployeeNew,  SIGNAL(clicked()), this, SLOT(EmployeeNewEvent()));
    connect(ui.btnEmployeeEdit, SIGNAL(clicked()), this, SLOT(EmployeeEditEvent()));
    connect(ui.btnPersonList,   SIGNAL(clicked()), this, SLOT(PersonListEvent()));
    connect(ui.btnRollDice,     SIGNAL(clicked()), this, SLOT(RollDiceEvent()));
    connect(ui.btnWork,         SIGNAL(clicked()), this, SLOT(WorkEvent()));
    connect(ui.btnClose,        SIGNAL(clicked()), this, SLOT(close()));

}


/*
TMyForm frm(new PersonDlgClass(), true);
mapFormsDictionary forms;
read("D:\\Test\\LocalizeFirstApp.xml", forms);
InitForm(frm, "frmAddress", forms);
InitForm(frm, "frmPerson", forms);
InitForm(frm, "frmBanking", forms);
InitForm(frm, "frmEmployee", forms);
frm.ShowModal();
//control(forms);
*/


void OurFirstClass::PersonNewEvent(void) {
   proc.PersonNew();
   }

void OurFirstClass::PersonEditEvent(void) {
   TPerson person;
   proc.CreatePerson(person);
   proc.PersonEdit(person);
   }

void OurFirstClass::EmployeeNewEvent(void) {
   proc.EmployeeNew();
   }

void OurFirstClass::EmployeeEditEvent(void) {
   TDepartment department;
   TEmployee   employee;
   proc.CreateEmployee(department, employee);
   proc.EmployeeEdit(employee);
   }

void OurFirstClass::PersonListEvent(void) {
   try {
      proc.ShowPersonList();
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler:" << std::endl
         << ex.what() << std::endl;
      }
   }

void OurFirstClass::RollDiceEvent(void) {
   try {
      proc.Roll_Dices(frm);
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler:" << std::endl
         << ex.what() << std::endl;
      }
   }

void OurFirstClass::WorkEvent(void) {
   try {
      proc.WorkingWithFileDlg();
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler:" << std::endl
         << ex.what() << std::endl;
      }
   }
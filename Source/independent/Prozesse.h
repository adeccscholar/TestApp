//---------------------------------------------------------------------------

#ifndef ProzesseH
#define ProzesseH
//---------------------------------------------------------------------------

#include "MyForm.h"
#include <iostream>
#include <string>
#include <tuple>
#include <locale>

/*
class TAddress;
class TBankingAccount;
class TPerson;
class TDepartment;
class TEmployee;
*/
#include "PersonData.h"
#include "Data.h"

#include "FileDlgProcesses.h"

class TProcess;

class TMyDirectoryForm {
   private:
      static std::vector<tplList<Narrow>> address_captions;
      std::ostream d_out;
      TStreamWrapper<Latin> wrapper;
      TProcess* process;
   public:
      TMyDirectoryForm(TProcess *proc) : d_out(std::cout.rdbuf()), process(proc), wrapper(d_out) { }
      TMyDirectoryForm(TMyDirectoryForm const&) = delete;
      virtual ~TMyDirectoryForm(void) { wrapper.Reset(); }

      void InitForm(TMyForm&);

      std::ostream& stream(void) { return d_out; }
   };

class TMyPersonListForm {
   private:
      static std::vector<tplList<Narrow>> person_list_captions;
      std::ostream d_out;
      TStreamWrapper<Narrow> wrapper;
      TProcess* process;
   public:
      TMyPersonListForm(TProcess* proc) : d_out(std::cout.rdbuf()), process(proc), wrapper(d_out) { }
      TMyPersonListForm(TMyPersonListForm const& ref) = delete;
      virtual ~TMyPersonListForm(void) {  wrapper.Reset(); }

      void InitForm(TMyForm&);
      std::ostream& stream(void) { return d_out; }
};


class TMyAddressForm {
   private:
      TProcess* process;
   public:
      TMyAddressForm(TProcess* proc) : process(proc) { }
      TMyAddressForm(TMyAddressForm const&) = delete;
      virtual ~TMyAddressForm(void) = default;

      void InitForm(TMyForm&);
      void ToForm(TMyForm&, TAddress const&);
      bool FromForm(TMyForm& frm, TAddress& address);
};

class TMyBankingForm {
   private:
      TProcess* process;
   public:
      TMyBankingForm(TProcess* proc) : process(proc) { }
      TMyBankingForm(TMyBankingForm const&) = delete;
      virtual ~TMyBankingForm(void) = default;

      void InitForm(TMyForm&);
      void ToForm(TMyForm&, TBankingAccount const&);
      bool FromForm(TMyForm& frm, TBankingAccount& banking);

};

class TMyPersonForm {
   private:
       static vecRepVals Salutations;
       bool   boActive = false;
       TMyAddressForm address_form;
       TProcess* process;
   public:
       TMyPersonForm(TProcess* proc) : process(proc), address_form(proc) { }
       TMyPersonForm(TMyPersonForm const&) = delete;
       virtual ~TMyPersonForm(void) { };

	   void InitForm(TMyForm&);

	   void ToForm(TMyForm&, TPerson const&);
       bool FromForm(TMyForm& frm, TPerson& person);

       TMyAddressForm const& AddressForm(void) const { return address_form; }
       TMyAddressForm & AddressForm(void) { return address_form; }

       bool Active(void) const { return boActive; }
       bool Active(bool newVal) { return boActive = newVal; }
   };

class TMyEmployeeForm : public TMyPersonForm {
   private:
      static vecRepVals Departments;
      TMyBankingForm banking_form;
      TProcess* process;
   public:
      TMyEmployeeForm(TProcess* proc) : process(proc), banking_form(proc), TMyPersonForm(proc) { }
      TMyEmployeeForm(TMyEmployeeForm const&) = delete;
      virtual ~TMyEmployeeForm(void) { }

      void InitForm(TMyForm&);
      bool FromForm(TMyForm& frm, TEmployee& employee);
	  void ToForm(TMyForm&, TEmployee const&);

      TMyBankingForm const& BankingForm(void) const { return banking_form; }
      TMyBankingForm &      BankingForm(void) { return banking_form; }

      std::tuple<bool, std::string> EnterSalary(TMyForm& frm);
      std::tuple<bool, std::string> ExitSalary(TMyForm& frm);
      std::tuple<bool, std::string> CheckSocialSecurityNumber(TMyForm& frm);

   };

class TProcess {
	private:
       static TStreamWrapper<Narrow> old_cout, old_cerr, old_clog;
       static std::locale myLoc;
       static std::vector<std::function<void(TData&, std::string_view const&)>> funcs_read_f;

       mapFormsDictionary form_data;
       mapLists<Narrow>   list_data;
       mapReposAll        repo_data;

       TMyPersonForm      person_form;
       TMyEmployeeForm    employee_form;
       TMyPersonListForm  person_list_form;
       TMyDirectoryForm   directory_form;

       myData vec_data;
       itData it_data;

       TFileDlgProcess   proc_filedlg;
	public:
       TProcess(void) : directory_form(this), person_form(this), employee_form(this), 
                        person_list_form(this) { }
       TProcess(TProcess const& ref) = delete;
       virtual ~TProcess(void) { }

       void StartProcess(std::ostream& form_data_file);

       std::tuple<bool, TPerson> PersonNew(void);
       bool PersonEdit(TPerson&);

       std::tuple<bool, TEmployee> EmployeeNew(void);
       bool EmployeeEdit(TEmployee&);

       void ShowPersonList(void);
       void Roll_Dices(TMyForm&);

       void InitMainForm(TMyForm&);
       void CloseMainForm(TMyForm&);

       mapFormsDictionary const& DataForms(void) const { return form_data; }
       mapFormsDictionary &      DataForms(void) { return form_data; }

       TMyPersonForm const&      PersonForm(void) const { return person_form; }
       TMyPersonForm &           PersonForm(void) { return person_form; }

       TMyEmployeeForm const&    EmployeeForm(void) const { return employee_form; }
       TMyEmployeeForm &         EmployeeForm(void) { return employee_form; }

       TMyPersonListForm const&  PersonListForm(void) const { return person_list_form; }
       TMyPersonListForm &       PersonListForm(void)  { return person_list_form; }

       TMyDirectoryForm  const&  DirectoryForm(void) const { return directory_form; }
       TMyDirectoryForm  &       DirectoryForm(void) { return directory_form; }

       TFileDlgProcess   &       FileDlgProcess(void) { return proc_filedlg; };
       void  WorkingWithFileDlg(void);
       void  SelectWithFileDlg(TMyForm& caller_frm);
       void  WorkingWith(TMyForm& caller_frm);

       void Read(std::string const& strFileName);
       void WorkwithData(void);
       void OutputData(std::ostream&);

       void CreatePerson(TPerson& person);
       void  CreateEmployee(TDepartment& department, TEmployee& employee);


       virtual TMyForm CreatePersonForm(void)     = 0;
       virtual TMyForm CreateEmployeeForm(void)   = 0;
       virtual TMyForm CreatePersonListForm(void) = 0;
       virtual TMyForm CreateDirectoryForm(void)  = 0;
       virtual TMyForm CreateFileDialog(void)     = 0;

       void Read(std::istream& filestream) { Read(filestream, form_data, list_data, repo_data); }
       bool InitForm(TMyForm& frm, std::string const& form_name) { return InitForm(frm, form_name, form_data); }
       vecList<Narrow> const& GetCaptions(std::string const& list_name) { return GetCaptions(list_name, list_data); }
       vecRepVals const& GetRepository(std::string const& repo_name) { return GetRepository(repo_name, repo_data); }

       // Statische Methoden zur Verallgemeinerung
       static void              Read(std::istream& filestream, mapFormsDictionary& formsDictionary, mapLists<Narrow>& lists, mapReposAll& repos);
       static bool              InitForm(TMyForm& frm, std::string const& form_name, mapFormsDictionary const& formsDictionary);
       static vecList<Narrow> const& GetCaptions(std::string const& list_name, mapLists<Narrow> const& lists);
       static vecRepVals const& GetRepository(std::string const& repo_name, mapReposAll const& repos);
};

#endif



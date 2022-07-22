//---------------------------------------------------------------------------
// Hallo neue unabhängige Welt
#include "Prozesse.h"
#include "MyStream.h"
#include "MyTools.h"
#include "Business.h"

#include "pugixml.hpp"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <codecvt>

using myRules = TBusinessRules;

//---------------------------------------------------------------------------

vecRepVals TMyPersonForm::Salutations = {
                                     { "Herr",      1 },
                                     { "Frau",      2 },
                                     { "Diverse",   3 },
                                     { "unbekannt", 9 }
                                   };

vecRepVals TMyEmployeeForm::Departments = {
                                     { "Buchhaltung",       1 },
                                     { "Controlling",       2 },
                                     { "Personal",          3 },
                                     { "Marketing",         4 },
                                     { "EDV",               5 },
                                     { "Einkauf",           6 },
                                     { "Produktion 1",      7 },
                                     { "Produktion 2",      8 },
                                     { "Verkauf",           9 },
                                     { "Unterstützung",    10 },
                                     { "Produktionshilfe", 11 }
                                   };

std::vector<tplList<Narrow>> TMyPersonListForm::person_list_captions = {
         { "Anrede",  120, EMyAlignmentType::left  },
         { "Vorname", 200, EMyAlignmentType::left  },
         { "Name",    200, EMyAlignmentType::left  },
         { "Alter",   110, EMyAlignmentType::right }
         };


std::vector<tplList<Narrow>> TMyDirectoryForm::address_captions = {
    { "PLZ",         150, EMyAlignmentType::center },
    { "Ort",         250, EMyAlignmentType::left },
    { "Stadtbezirk", 250, EMyAlignmentType::left },
    { "Straße",      250, EMyAlignmentType::left },
    { "Nummer",      150, EMyAlignmentType::right },
    { "Entfernung",  200, EMyAlignmentType::right },
    { "Winkel",      200, EMyAlignmentType::right }
   };

std::vector<std::function<void(TData&, std::string_view const&)>> TProcess::funcs_read_f = {
      [](TData& data, std::string_view const& val) { data.City(val); },
      [](TData& data, std::string_view const& val) { data.Street(val); },
      [](TData& data, std::string_view const& val) { data.StreetNumber(val); },
      [](TData& data, std::string_view const& val) { data.ZipCode(val); },
      [](TData& data, std::string_view const& val) { data.Urban_Unit(val); },
      [](TData& data, std::string_view const& val) { data.Old_Unit(val); },
      [](TData& data, std::string_view const& val) { data.District(val); },
      [](TData& data, std::string_view const& val) { data.Latitude(val); },
      [](TData& data, std::string_view const& val) { data.Longitude(val); },
      [](TData& data, std::string_view const& val) { throw std::runtime_error("file corruped"); }
   };

struct TMyNum : public std::numpunct<char> {
	char_type   do_decimal_point () const { return ','; }
	char_type   do_thousands_sep () const { return '.'; }
	string_type do_truename ()      const { return "ja"; }
	string_type do_falsename ()     const { return "nein"; }
	std::string do_grouping ()      const { return "\3";	}
   };

struct TMyNumW : public std::numpunct<wchar_t> {
	char_type   do_decimal_point () const { return L','; }
	char_type   do_thousands_sep () const { return L'.'; }
	string_type do_truename ()      const { return L"ja"; }
	string_type do_falsename ()     const { return L"nein"; }
	std::string do_grouping ()      const { return "\3";	}
   };

TMyNum newNumPunct;
TMyNumW newNumPunctW;
std::locale TProcess::myLoc;

TStreamWrapper<Narrow> TProcess::old_cout(std::cout);
TStreamWrapper<Narrow> TProcess::old_cerr(std::cerr);
TStreamWrapper<Narrow> TProcess::old_clog(std::clog);

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TProcess::StartProcess(std::ostream& form_data_file) {

   }

void TProcess::Read(std::istream& filestream, mapFormsDictionary& formsDictionary, mapLists<Narrow>& lists, mapReposAll& repos) {
   auto error_message = [](pugi::xml_parse_result const& result) {
      std::cerr << "XML parsed with errors\n";
      std::cerr << "Error description: " << result.description() << "\n";
      std::cerr << "Error offset: " << result.offset
         << " (error at [" << result.offset << "]\n\n";
   };

   formsDictionary.clear();
   pugi::xml_document doc;
   pugi::xml_parse_result result = doc.load(filestream, pugi::parse_default | pugi::parse_fragment, pugi::encoding_latin1);
   if (!result) error_message(result);

   pugi::xml_node forms = doc.find_node([](pugi::xml_node& node) { return strcmp(node.name(), "forms") == 0; });
   if (forms) {
      for (pugi::xml_node form : forms.children("form")) {
         std::string strFormName = form.attribute("name").value();
         tplFormData        formdata;
         std::get<0>(formdata) = { form.child("caption").child_value(), form.attribute("id").as_int() };

         for (pugi::xml_node comp : form.child("components").children("component")) {
            tplFormElements elements;
            std::get<0>(elements) = comp.attribute("name").value();
            std::get<1>(elements) = static_cast<EMyFrameworkType>(comp.attribute("type").as_int());
            std::get<2>(elements) = static_cast<EMyAlignmentType>(comp.attribute("alignment").as_int());
            std::get<3>(elements) = comp.child("text").child_value();
            std::get<4>(elements) = comp.child("hint").child_value();
            std::get<5>(elements) = comp.attribute("id").as_int();
            std::get<1>(formdata).emplace_back(std::forward<tplFormElements>(elements));
         }
         formsDictionary.insert({ strFormName, formdata });
      }
   }


   pugi::xml_node node_lists = doc.find_node([](pugi::xml_node& node) { return strcmp(node.name(), "lists") == 0; });
   if (node_lists) {
      for (pugi::xml_node child : node_lists.children("list")) {
         std::string strListName = child.attribute("name").value();
         vecList<Narrow> entries;
         for (pugi::xml_node item : child.child("cols").children("col")) {
            tplList<Narrow> elements;
            std::get<0>(elements) = item.attribute("name").value();
            std::get<1>(elements) = item.attribute("width").as_int();
            std::get<2>(elements) = static_cast<EMyAlignmentType>(item.attribute("alignment").as_int());
            entries.push_back(elements);
            }
         lists.insert({ strListName, entries });
         }
      }


   pugi::xml_node node_repos = doc.find_node([](pugi::xml_node& node) { return strcmp(node.name(), "repositories") == 0; });
   if (node_repos) {
      for (pugi::xml_node child : node_repos.children()) {
         std::string strRepoName = child.attribute("name").value();
         vecRepVals entries;
         for (pugi::xml_node item : child.child("items").children("item")) {
            tplRepVal elements;
            std::get<0>(elements) = item.attribute("name").value();
            std::get<1>(elements) = item.attribute("ID").as_int();
            entries.push_back(elements);
            }
         repos.insert({ strRepoName, entries } );
         }
      }
}


bool TProcess::InitForm(TMyForm& frm, std::string const& form_name, mapFormsDictionary const& formsDictionary) {
   if (auto it = formsDictionary.find(form_name); it != formsDictionary.end()) {
      try {
         auto const& [info, vecData] = it->second;
         frm.SetCaption(std::get<0>(info));
         std::for_each(vecData.cbegin(), vecData.cend(), [&frm](auto const& data) {
            switch (std::get<1>(data)) {
            case EMyFrameworkType::label:
               frm.Set<EMyFrameworkType::label>(std::get<0>(data), std::get<3>(data));
               break;
            case EMyFrameworkType::edit:
               frm.Set<EMyFrameworkType::edit>(std::get<0>(data), std::get<3>(data));
               frm.Alignment<EMyFrameworkType::edit>(std::get<0>(data), std::get<2>(data));
               break;
            case EMyFrameworkType::button:
               frm.Set<EMyFrameworkType::button>(std::get<0>(data), std::get<3>(data));
               break;
            case EMyFrameworkType::groupbox:
               frm.Set<EMyFrameworkType::groupbox>(std::get<0>(data), std::get<3>(data));
               break;
            case EMyFrameworkType::checkbox:
               frm.Set<EMyFrameworkType::checkbox>(std::get<0>(data), std::get<3>(data));
               break;
            }
            });
         }
      catch (std::exception& ex) {
         std::cerr << "Fehler beim Initialisieren des Formulars \"" << form_name << "\":" << std::endl
            << ex.what() << std::endl;
         }

      }
   else {
      std::cerr << "Das Formular mit dem Namen \"" << form_name << "\" wurde im Dictionary nicht gefunden." << std::endl;
      return false;
      }
   return true;
   }

vecList<Narrow> const& TProcess::GetCaptions(std::string const& list_name, mapLists<Narrow> const& lists) {
   if (auto it = lists.find(list_name); it != lists.end()) {
      return it->second;
   }
   else {
      std::cerr << "Die Überschriften für die Liste \"" << list_name << "\" wurden nicht gefunden." << std::endl;
      throw std::runtime_error("Liste nicht gefunden");
   }
}

vecRepVals const& TProcess::GetRepository(std::string const& repo_name, mapReposAll const& repos) {
   if (auto it = repos.find(repo_name); it != repos.end()) {
      return it->second;
      }
   else {
      std::cerr << "Das Repository \"" << repo_name << "\" wurde nicht gefunden." << std::endl;
      throw std::runtime_error("repository nicht gefunden");
      }
   }

//---------------------------------------------------------------------------
void TProcess::InitMainForm(TMyForm& frm) {
   std::ios_base::sync_with_stdio(false);
   myLoc = std::locale(std::locale(std::locale("de_DE"), &newNumPunct), &newNumPunctW);
   frm.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cout, "memOutput");
   frm.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cerr, "memError");
   frm.GetAsStream<Narrow, EMyFrameworkType::statusbar>(old_clog, "sbMain");

   for(auto stream : { &std::cout, &std::cerr, &std::clog } ) {
      stream->imbue(myLoc);
      stream->setf(std::ios::fixed);
      }

   if (!InitForm(frm, "frmMain")) {
      frm.SetCaption("Testanwendung für Programmieren mit C++");
      frm.Alignment<EMyFrameworkType::edit>("edtValues", EMyAlignmentType::right);
      frm.Set<EMyFrameworkType::edit>("edtValues", "");

      frm.Set<EMyFrameworkType::button>("btnPersonNew", "Person neuanlegen ...");
      frm.Set<EMyFrameworkType::button>("btnPersonEdit", "Person bearbeiten ...");
      frm.Set<EMyFrameworkType::button>("btnEmployeeNew", "Angestellter anlegen ...");
      frm.Set<EMyFrameworkType::button>("btnEmployeeEdit", "Angestellter bearbeiten ...");
      frm.Set<EMyFrameworkType::button>("btnPersonList", "Personenliste ...");
      frm.Set<EMyFrameworkType::button>("btnRollDice", "Würfeln ...");
      frm.Set<EMyFrameworkType::button>("btnWork", "Bearbeiten ...");
      frm.Set<EMyFrameworkType::button>("btnClose", "Schließen");

      std::clog << "bereit" << std::endl;
      }
   }

//---------------------------------------------------------------------------
void TProcess::CloseMainForm(TMyForm& frm) {
   old_cout.SafeReset();
   old_cerr.SafeReset();
   old_clog.SafeReset();
   }

//---------------------------------------------------------------------------
std::tuple<bool, TPerson> TProcess::PersonNew(void) {
   TPerson person;
   try {
	  TMyWait wait;
      auto frm = CreatePersonForm();
      PersonForm().InitForm(frm);
	  //frm.SetCaption("neue Person eingeben");
	  //frm.Set<EMyFrameworkType::button>("btnOk", "Einfügen");

	  if(EMyRetResults iRet = frm.ShowModal(); iRet == EMyRetResults::ok) {

		 PersonForm().FromForm(frm, person);
         std::cout << person << std::endl;
         std::clog << "neue Person eingegben" << std::endl;
         }
      else {
         std::clog << "Eingabe abgebrochen" << std::endl;
         return std::make_tuple(false, person);
         }
	  }
   catch (std::exception& ex) {
	  std::cerr << "Fehler beim Erzeugen einer neuen Person" << std::endl
	            << ex.what() << std::endl << std::endl;
      std::clog << ex.what() << std::endl;
      return std::make_tuple(false, person);
	  }
   return std::make_tuple(true, person);
   }

//---------------------------------------------------------------------------
bool TProcess::PersonEdit(TPerson& person) {
   try {
	  TMyWait wait;

      auto frm = CreatePersonForm();
      PersonForm().InitForm(frm);
	  //frm.SetCaption("Person bearbeiten");
	  //frm.Set<EMyFrameworkType::button>("btnOk", "Speichern");

      PersonForm().ToForm(frm, person);

	  if(EMyRetResults iRet = frm.ShowModal(); iRet == EMyRetResults::ok) {
         PersonForm().FromForm(frm, person);
         std::cout << person << std::endl;
         std::clog << "Person eingegeben" << std::endl;
         }
      else {
         std::clog << "Personeneingabe abgebrochen" << std::endl;
         return false;
		 }
	  }
   catch (std::exception& ex) {
	  std::cerr << "Fehler beim Bearbeiten einer neuen Person" << std::endl
	            << ex.what() << std::endl << std::endl;
      std::clog << ex.what() << std::endl;
      return false;
	  }
   return true;
   }

//---------------------------------------------------------------------------
std::tuple<bool, TEmployee> TProcess::EmployeeNew(void) {
   TEmployee employee;
   try {
	  TMyWait wait;

      auto frm = CreateEmployeeForm();
      EmployeeForm().InitForm(frm);
	  //frm.SetCaption("neuen Angestellter eingeben ...");
	  //frm.Set<EMyFrameworkType::button>("btnOk", "Einfügen");

      if(EMyRetResults iRet = frm.ShowModal(); iRet == EMyRetResults::ok) {
         EmployeeForm().FromForm(frm, employee);
		 std::cout << employee << std::endl;
		 std::clog << "neuer Angestellter gespeichert" << std::endl;
		 }
      else {
         std::clog << "abgebrochen" << std::endl;
         return std::make_tuple(false, employee);
         }
	  }
   catch (std::exception& ex) {
	  std::cerr << "Fehler beim Erzeugen eines neuen Angestellten" << std::endl
	            << ex.what() << std::endl << std::endl;
      std::clog << ex.what() << std::endl;
      return std::make_tuple(false, employee);
	  }
   return std::make_tuple(true, employee);
   }

//---------------------------------------------------------------------------
bool TProcess::EmployeeEdit(TEmployee& employee) {
   try {
      TMyWait wait;
      auto form = CreateEmployeeForm();
      EmployeeForm().InitForm(form);
	  //form.SetCaption("Angestellten bearbeiten ...");
	  //form.Set<EMyFrameworkType::button>("btnOk", "Speichern");

      EmployeeForm().ToForm(form, employee);

      if(EMyRetResults iRet = form.ShowModal(); iRet == EMyRetResults::ok) {
         EmployeeForm().FromForm(form, employee);
         std::cout << employee << std::endl;
         std::clog << "Angestellter geändert" << std::endl;
         }
      else {
         std::clog << "abgebrochen" << std::endl;
         return false;
         }
	  }
   catch (std::exception& ex) {
	  std::cerr << "Fehler beim Bearbeiten eines Angestellten" << std::endl
	            << ex.what() << std::endl << std::endl;
      std::clog << ex.what() << std::endl;
      return false;
	  }
   return true;
   }

//---------------------------------------------------------------------------
void TProcess::CreatePerson(TPerson& person) {
   int iVal = 2;
   if (auto rep = repo_data.find("Salutations"); rep != repo_data.end()) {
      if (auto elem = std::find_if(rep->second.begin(), rep->second.end(), [&iVal](auto val) { return std::get<1>(val) == iVal;  }); elem != rep->second.end()) {
         person.Salutation(std::get<0>(*elem));
         }
      }
   person.FirstName("Maxi");
   person.Name("Mustermann");

   person.Address().ZipCode("10000");
   person.Address().City("Berlin");
   person.Address().Street("Testergasse");
   person.Address().StreetNumber("5");
   // 13.08.1963
   }

//---------------------------------------------------------------------------
void TProcess::CreateEmployee(TDepartment& department, TEmployee& employee) {
   department.Description("Marketing");
   CreatePerson(employee);

   employee.BankingAccount().BankName("Berliner Volksbank");
   employee.BankingAccount().IBANNumber("DE16100900000529819374");
   employee.BankingAccount().BIC("BEVODEBB");
   employee.BankingAccount().AccountHolder("Max Mustermann");

   employee.Department(&department);
   employee.JobDescription("Key Accounter");
   employee.Salary(std::make_optional(3346.0) );
   employee.TaxNumber("31/576/13579");
   employee.SocialSecurityNumber("04 130863 M 33 8");
   employee.Active(true);
   }

//---------------------------------------------------------------------------
void TProcess::Roll_Dices(TMyForm& frm) {
   int iValues = 100;
   try {
      auto values = frm.GetEditAs<int, true>("edtValues");
      if(values) {
         TBusinessRules::roll_the_dice(std::cout, *values, 6);
         std::clog << "fertig ;-)" << std::endl;
         std::cerr << "Würfeln mit 6 Werten " << *values << " mal." << std::endl;
         }
      else {
         std::cerr << "Keine Anzahl von Werten eingegeben." << std::endl;
         std::clog << "Keine Werte zum Würfeln eingeben." << std::endl;
         }
      }
   catch(std::exception &ex) {
      std::cerr << "Fehler beim Würfeln." << std::endl
                << ex.what() << std::endl;
      std::clog << "Fehler beim Würfeln." << std::endl;
      }
   }

//---------------------------------------------------------------------------
void TProcess::ShowPersonList(void) {
   using tplPerson = std::tuple<std::string, std::string, std::string, int>;
   static std::vector<tplPerson> PersonList = {
      tplPerson { "Frau", "Lisa", "Meyer", 30 },
      tplPerson { "Herr", "Fred", "Feuerstein", 42 },
      tplPerson { "Herr", "Max", "Mustermann", 51 },
      tplPerson { "Frau", "Julia", "Lepkowski", 31 },
      tplPerson { "Frau", "Eve", "Herrmann", 38 },
      tplPerson { "Herr", "Roland", "Wolf", 56 },
      tplPerson { "Frau", "Cornelia", "Cianfarini", 32 },
      tplPerson { "Frau", "Simone", "Steffen", 41 },
      tplPerson { "Herr", "Gerd", "Krause", 45 },
      tplPerson { "Frau", "Anette", "Steiff", 27 },
      tplPerson { "Frau", "Marta", "Lehmann", 57 },
      tplPerson { "Herr", "Max", "Heise", 61 },
      tplPerson { "Herr", "Matthias", "Fehse", 29 },
      tplPerson { "Frau", "Christel", "Haase", 58 },
      tplPerson { "Herr", "Günter", "Brunner", 41 },
      tplPerson { "Herr", "Hans- Jürgen", "Fritsche", 49 },
      tplPerson { "Herr", "Ernst", "Hesse", 60 },
      tplPerson { "Herr", "Detlef", "Karstens", 57 },
      tplPerson { "Frau", "Edith", "Senger", 46 },
      tplPerson { "Herr", "Frank", "Heusinger", 34 },
      tplPerson { "Herr", "Richard", "Koch", 55 }
      };
   try {
      TMyWait wait;
      auto form = CreatePersonListForm();
      PersonListForm().InitForm(form);
      char tab = '\t';
      for(auto person : PersonList) {
         PersonListForm().stream()
              << std::get<0>(person) << tab << std::get<1>(person) << tab
              << std::get<2>(person) << tab << std::get<3>(person) << std::endl;
         }
      form.ShowModal();
	  }
   catch (std::exception& ex) {
	  std::cerr << "Fehler beim Anzeigen der Personenliste" << std::endl
	            << ex.what() << std::endl << std::endl;
      std::clog << ex.what() << std::endl;
	  }
   return;
   }


void TProcess::Read(std::string const& strFileName) {
   std::ifstream ifs(strFileName);
   if (!ifs.is_open()) {
      std::ostringstream os;
      os << "error while opeining file \"" << strFileName << "\"" << std::endl;
      throw std::runtime_error(os.str().c_str());
      }
   std::stringstream strStream;
   strStream << ifs.rdbuf();
   ifs.close();
   //#if !defined __BORLANDC__
   std::string old_buffer = strStream.str();
   std::string_view test(old_buffer);
   //#else
   //std::string_view test(strStream.str().begin(), strStream.str().end());
   //#endif
   vec_data.reserve(std::count(test.begin(), test.end(), '\n'));
   size_t start_pos = 0, end_pos = 0;
   size_t iPos = 0, iEnd;
   int iCount;
   TData data;
   while ((end_pos = test.find('\n', start_pos)) != std::string_view::npos) {
      iPos = start_pos;
      iCount = 0;
      do {
         iEnd = test.find(";", iPos);
         if (iEnd > end_pos) iEnd = end_pos;
         funcs_read_f[iCount++](data, test.substr(iPos, iEnd - iPos));
         if (iEnd != end_pos) iPos = iEnd + 1;
      } while (iEnd != end_pos);
      vec_data.emplace_back(std::move(data));
      start_pos = end_pos + 1;
   }
   return;
   }

void TProcess::WorkwithData(void) {
   std::pair<double, double> point = std::make_pair(52.520803, 13.40945); // Berlin, television tower
   int iDistance = 1000;
   auto func_start = std::chrono::high_resolution_clock::now();
   CalculateFor(vec_data.begin(), vec_data.end(), point);
   auto func_ende = std::chrono::high_resolution_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cerr << "Berechnung der Distance in " << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;
   func_start = std::chrono::high_resolution_clock::now();
   it_data = std::partition(std::execution::par, vec_data.begin(), vec_data.end(), [iDistance](TData const& val) { return val.Distance() < iDistance; });
   func_ende = std::chrono::high_resolution_clock::now();
   time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cerr << "Umverteilen in " << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;
   func_start = std::chrono::high_resolution_clock::now();
   std::sort(std::execution::par, vec_data.begin(), it_data, [](auto const& a, auto const& b) {
      return a.Distance() == b.Distance() ? a.Angle() < b.Angle() : a.Distance() < b.Distance();
      });
   func_ende = std::chrono::high_resolution_clock::now();
   time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cerr << "Sortieren in " << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;
   }

void TProcess::OutputData(std::ostream& out) {

   static constexpr auto convert = [](std::string const& source, const std::locale& loc) -> std::string {
      // UTF-8 to wstring
      //std::wstring_convert<std::codecvt_utf8<wchar_t>> wconv;
      //std::wstring wstr = wconv.from_bytes(source.c_str());
      std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvtUtf8{ new std::codecvt_byname<wchar_t, char, std::mbstate_t>("de_De") };
      std::wstring wstr = cvtUtf8.from_bytes(source.c_str());
      // wstring to string
      std::vector<char> buf(wstr.size());
      std::use_facet<std::ctype<wchar_t>>(loc).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());
      return std::string(buf.data(), buf.size());
      };

   // convert(val.Street(), std::locale(".1252"))
   auto countvals = std::distance(vec_data.begin(), it_data);
   auto func_start = std::chrono::high_resolution_clock::now();
   std::for_each(vec_data.begin(), it_data, [&out](auto& val) {
      out << val.ZipCode() << '\t' << val.City() << '\t' << val.District() << '\t' 
          << val.Street() << '\t' << val.StreetNumber() << '\t'
          //<< std::setprecision(9) << val.Latitude() << ";" << std::setprecision(9) << val.Longitude() << ";"
          //<< std::setprecision(3) << val.Distance() << 't' << std::setprecision(3) << val.Angle() 
          << TMyTools::double_to_string_fmt(val.Distance(), 3) << '\t' << TMyTools::double_to_string_fmt(val.Angle(), 3)
          << std::endl;
      });
   auto func_ende = std::chrono::high_resolution_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
   std::cerr << "Ausgeben von " << countvals << " Zeilen in " << std::setprecision(3) << time / 1000.0 << " ms" << std::endl;
}


void TProcess::WorkingWithFileDlg(void) {
   try {
      TStreamWrapper<Narrow> old_cerr_dlg(std::cerr);
      auto form = CreateDirectoryForm();
      DirectoryForm().InitForm(form);
      // irgendwas mit einem ostream
      form.Set<EMyFrameworkType::edit>(  "edtFile",   "D:\\Abfall");
      form.GetAsStream<Narrow, EMyFrameworkType::memo>(old_cerr_dlg, "memError");
      form.ShowModal();
      }
   catch(std::exception& ex) {
      std::cerr << "Fehler beim Aufruf des Formulars:" << std::endl
                << ex.what() << std::endl;
      }
   }

void TProcess::SelectWithFileDlg(TMyForm& caller_frm) {
   std::optional<std::string> strRetPath = {};
   bool boRetVal   = false;
   try {
      auto form = CreateFileDialog();
      FileDlgProcess().InitFileDlg(form);
      auto path = caller_frm.Get<EMyFrameworkType::edit, std::string>("edtFile");
      if(path) {
         FileDlgProcess().SetFileOrDirectory(form, *path);
         if(form.ShowModal() == EMyRetResults::ok) {
            caller_frm.Set<EMyFrameworkType::edit>("edtFile", FileDlgProcess().GetFileOrDirectory(form));
            }
         else {
            std::cerr << "Auswahl abgebrochen." << std::endl;
            }
         }
      else {
         std::cerr << "Der Pfad ist nicht gefüllt." << std::endl;
         }
      }
   catch(std::exception& ex) {
      std::cerr << "Fehler beim Öffnen des Datei- Dialoges:" << std::endl
                << ex.what() << std::endl;
      }
   }

void TProcess::WorkingWith(TMyForm& caller_frm) {
   // !!! Baustelle
   try {
      TMyWait wait;
      auto strFile = caller_frm.Get<EMyFrameworkType::edit, std::string>("edtFile");
      if (strFile) {
         vec_data.clear();
         vec_data.shrink_to_fit();
         auto func_start = std::chrono::high_resolution_clock::now();
         Read(*strFile);
         auto func_ende  = std::chrono::high_resolution_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::microseconds>(func_ende - func_start).count();
         std::cerr << "Lesen der Datei in " << std::setprecision(3) << time/1000.0 << " ms" << std::endl;
         WorkwithData();
         OutputData(DirectoryForm().stream());
         }
      else {
         std::cerr << "Fehler beim Verarbeiten:" << std::endl
                   << "Keine Datendatei ausgewählt." << std::endl;

         }
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler beim Verarbeiten:" << std::endl
                << ex.what() << std::endl;
      }
   }




void TMyDirectoryForm::InitForm(TMyForm& frm) {
   if (process) {
      address_captions = process->GetCaptions("address_list");
      }

   frm.GetAsStream<Latin, EMyFrameworkType::listview>(wrapper, "lvData", address_captions);
   if (!process || !process->InitForm(frm, "frmWork")) {
      frm.SetCaption("Formular zum Verarbeiten der Daten ...");
      frm.Set<EMyFrameworkType::label>("lblFile", "Datendatei:");
      frm.Set<EMyFrameworkType::edit>("edtFile", "");
      frm.Set<EMyFrameworkType::button>("btnSelect", "Auswahl ...");
      frm.Set<EMyFrameworkType::button>("btnStart", "Auswertung");
      frm.Set<EMyFrameworkType::button>("btnClose", "Schließen");
      }
   }

//---------------------------------------------------------------------------
void TMyPersonListForm::InitForm(TMyForm& frm) {
   if (process) {
      person_list_captions = process->GetCaptions("person_list");
      }

   frm.GetAsStream<Narrow, EMyFrameworkType::listview>(wrapper, "lvPersons", person_list_captions);
   if (!process || !process->InitForm(frm, "frmPersonList")) {
      //frm.SetCaption("Personen anzeigen ...");
      //frm.Set<EMyFrameworkType::button>("btnOk", "Speichern");
      }
   }

//---------------------------------------------------------------------------
//  Implementierung von TMyAddressForm
//---------------------------------------------------------------------------
void TMyAddressForm::InitForm(TMyForm& frm) {
   if (!process || !process->InitForm(frm, "frmAddress")) {
      frm.Set<EMyFrameworkType::groupbox>("grpAddress", "Adresse");
      frm.Set<EMyFrameworkType::label>("lblZipCodeCity", "PLZ / Ort");
      frm.Set<EMyFrameworkType::label>("lblStreetExtension", "Straße / Nummer:");
      frm.Set<EMyFrameworkType::edit>("edtZipCode", "");
      frm.Set<EMyFrameworkType::edit>("edtCity", "");
      frm.Set<EMyFrameworkType::edit>("edtStreet", "");
      frm.Set<EMyFrameworkType::edit>("edtStreetNumber", "");
      }
   }

//---------------------------------------------------------------------------
void TMyAddressForm::ToForm(TMyForm& frm, TAddress const& address) {
   frm.Set<EMyFrameworkType::edit>("edtZipCode",      address.ZipCode());
   frm.Set<EMyFrameworkType::edit>("edtCity",         address.City());
   frm.Set<EMyFrameworkType::edit>("edtStreet",       address.Street());
   frm.Set<EMyFrameworkType::edit>("edtStreetNumber", address.StreetNumber());
   }

//---------------------------------------------------------------------------
bool TMyAddressForm::FromForm(TMyForm& frm, TAddress& address) {
   address.ZipCode(frm.GetEditAs<std::string>("edtZipCode"));
   address.City(frm.GetEditAs<std::string>("edtCity"));
   address.Street(frm.GetEditAs<std::string>("edtStreet"));
   address.StreetNumber(frm.GetEditAs<std::string>("edtStreetNumber"));
   return true;
   }

//---------------------------------------------------------------------------
//  Implementierung von TMyAddressForm
//---------------------------------------------------------------------------

void TMyBankingForm::InitForm(TMyForm& frm) {
   if (!process || !process->InitForm(frm, "frmBanking")) {
      frm.Set<EMyFrameworkType::groupbox>("grpBankingAccount", "Bankverbindung");
      frm.Set<EMyFrameworkType::label>("lblBankName", "Name der Bank:");
      frm.Set<EMyFrameworkType::label>("lblIBANNumber", "IBAN:");
      frm.Set<EMyFrameworkType::label>("lblBIC", "BIC:");
      frm.Set<EMyFrameworkType::label>("lblAccountHolder", "Kontoinhaber:");
      frm.Set<EMyFrameworkType::edit>("edtBankName", "");
      frm.Set<EMyFrameworkType::edit>("edtIBANNumber", "");
      frm.Set<EMyFrameworkType::edit>("edtBIC", "");
      frm.Set<EMyFrameworkType::edit>("edtAccountHolder", "");
      }
   }

//---------------------------------------------------------------------------
void TMyBankingForm::ToForm(TMyForm& frm, TBankingAccount const& banking) {
   frm.Set<EMyFrameworkType::edit>("edtBankName",      banking.BankName());
   frm.Set<EMyFrameworkType::edit>("edtIBANNumber",    banking.IBANNumber());
   frm.Set<EMyFrameworkType::edit>("edtBIC",           banking.BIC());
   frm.Set<EMyFrameworkType::edit>("edtAccountHolder", banking.AccountHolder());
   }

//---------------------------------------------------------------------------
bool TMyBankingForm::FromForm(TMyForm& frm, TBankingAccount& banking) {
   banking.BankName(frm.GetEditAs<std::string>("edtBankName"));
   banking.IBANNumber(frm.GetEditAs<std::string>("edtIBANNumber"));
   banking.BIC(frm.GetEditAs<std::string>("edtBIC"));
   banking.AccountHolder(frm.GetEditAs<std::string>("edtAccountHolder"));
   return true;
   }


//---------------------------------------------------------------------------
// Implementierung von TMyPersonForm
//---------------------------------------------------------------------------

void TMyPersonForm::InitForm(TMyForm& frm) {
   frm.Visible<EMyFrameworkType::groupbox>("grpBankingAccount", false);
   frm.Visible<EMyFrameworkType::groupbox>("grpEmployee", false);

   AddressForm().InitForm(frm);

   if (process) {

      Salutations = process->GetRepository("Salutations");
      }
   frm.InitCombobox("cbxSalutation", Salutations);

   if (!process || !process->InitForm(frm, "frmPerson")) {
      frm.SetCaption("Personendatendialog");
      frm.Set<EMyFrameworkType::groupbox>("grpPerson", "Persondaten");

      frm.Set<EMyFrameworkType::combobox>("cbxSalutation", std::optional<std::string> { });

      frm.Set<EMyFrameworkType::label>("lblSalutation", "Anrede:");
      frm.Set<EMyFrameworkType::label>("lblFirstName", "Vorname:");
      frm.Set<EMyFrameworkType::label>("lblName", "Name:");
      frm.Set<EMyFrameworkType::edit>("edtFirstName", "");
      frm.Set<EMyFrameworkType::edit>("edtName", "");

      frm.Set<EMyFrameworkType::button>("btnOk", "Bestätigen");
      frm.Set<EMyFrameworkType::button>("btnCancel", "Abbrechen");
      }

    boActive = true;
   }


//---------------------------------------------------------------------------
void TMyPersonForm::ToForm(TMyForm& frm, TPerson const& person) {
   frm.Set<EMyFrameworkType::combobox>("cbxSalutation", person.Salutation());
   frm.Set<EMyFrameworkType::edit>("edtFirstName",      person.FirstName());
   frm.Set<EMyFrameworkType::edit>("edtName",           person.Name());
   AddressForm().ToForm(frm, person.Address());
   }

//---------------------------------------------------------------------------
bool TMyPersonForm::FromForm(TMyForm& frm, TPerson& person) {
   try {
	  person.Salutation(frm.GetComboBoxAs<std::string>("cbxSalutation"));
	  person.FirstName(frm.GetEditAs<std::string>("edtFirstName"));
	  person.Name(frm.GetEditAs<std::string>("edtName"));
      AddressForm().FromForm(frm, person.Address());
	  }
   catch(std::exception &ex) {
      std::cerr << "Error in FromForm(TPerson&)" << std::endl
                << ex.what() << std::endl;
	  return false;
	  }
   return true;
   }


//---------------------------------------------------------------------------
void TMyEmployeeForm::InitForm(TMyForm& frm) {
    TMyPersonForm::InitForm(frm);

    if (process) {
       Departments = process->GetRepository("Departments");
    }

    frm.InitCombobox("cbxDepartment", Departments);

    frm.Visible<EMyFrameworkType::groupbox>("grpBankingAccount", true);
    frm.Visible<EMyFrameworkType::groupbox>("grpEmployee", true);

    BankingForm().InitForm(frm);

    if (!process || !process->InitForm(frm, "frmEmployee")) {
       frm.Set<EMyFrameworkType::groupbox>("grpEmployee", "Angestellter");
       frm.Set<EMyFrameworkType::label>("lblDepartment", "Abteilung:");
       frm.Set<EMyFrameworkType::label>("lblJobDescription", "Beschreibung:");
       frm.Set<EMyFrameworkType::label>("lblSalary", "Gehalt:");
       frm.Set<EMyFrameworkType::label>("lblTaxNumber", "Steuernummer:");
       frm.Set<EMyFrameworkType::label>("lblSocialSecurityNumber", "Versicherungsnummer:");
       frm.Set<EMyFrameworkType::edit>("edtJobDescription", "");
       frm.Set<EMyFrameworkType::edit>("edtSalary", "");
       frm.Set<EMyFrameworkType::edit>("edtTaxNumber", "");
       frm.Set<EMyFrameworkType::edit>("edtSocialSecurityNumber", "");
       frm.Set<EMyFrameworkType::combobox>("cbxDepartment", std::optional<std::string> { });

       frm.Set<EMyFrameworkType::checkbox>("chkActive", "Aktiv");
       frm.Set<EMyFrameworkType::checkbox>("chkActive", false);

       frm.Alignment<EMyFrameworkType::edit>("edtSalary", EMyAlignmentType::right);
       }
    //boActive = true;
   }

//---------------------------------------------------------------------------
void TMyEmployeeForm::ToForm(TMyForm& frm, TEmployee const& employee) {
	TMyPersonForm::ToForm(frm, employee);
    BankingForm().ToForm(frm, employee.BankingAccount());

	frm.Set<EMyFrameworkType::edit>("edtJobDescription",       employee.JobDescription());
	frm.Set<EMyFrameworkType::edit>("edtSalary",               employee.Salary(), -1, 2);
	frm.Set<EMyFrameworkType::edit>("edtTaxNumber",            employee.TaxNumber());
	frm.Set<EMyFrameworkType::edit>("edtSocialSecurityNumber", employee.SocialSecurityNumber());
	frm.Set<EMyFrameworkType::checkbox>("chkActive",           employee.Active());
	frm.Set<EMyFrameworkType::combobox>("cbxDepartment",       employee.Department()->Description());
    }


//---------------------------------------------------------------------------
bool TMyEmployeeForm::FromForm(TMyForm& frm, TEmployee& employee) {
   if(TMyPersonForm::FromForm(frm, employee)) {
      BankingForm().FromForm(frm, employee.BankingAccount());
      employee.JobDescription(frm.GetEditAs<std::string>("edtJobDescription"));
      employee.Salary(frm.GetEditAs<double, true>("edtSalary"));
      employee.TaxNumber(frm.GetEditAs<std::string>("edtTaxNumber"));
      employee.Active(frm.GetCheckBoxAs<bool>("chkActive"));

      std::string strNumber = frm.GetEditAs<std::string>("edtSocialSecurityNumber");
      strNumber = myRules::CheckSocialSecurityNumber(std::forward<std::string>(strNumber));
      employee.SocialSecurityNumber(strNumber);

       //employee.Department()->Description(frm.GetComboBoxAs<std::string>("cbxDepartment"));
       // Department suchen und zuordnen fehlt hier
      }
   return true;
   }


std::tuple<bool, std::string> TMyEmployeeForm::EnterSalary(TMyForm& frm) {
   if(!Active()) return std::make_tuple<bool, std::string>(false, "events running");
   try {
      Active(false);
      auto src = frm.GetEditAs<std::string, true>("edtSalary");
      if(src) {
         std::string strVal = TMyTools::integral_double_clean_Thousand(std::forward<std::string>(*src));
         frm.Set<EMyFrameworkType::edit>("edtSalary", strVal);
         }
      //frm.Alignment<EMyFrameworkType::edit>("edtSalary", EMyAlignmentType::left);
      }
   catch(std::exception &ex) {
      std::cerr << ex.what() << std::endl;
      return std::make_tuple<bool, std::string>(false, ex.what());
      }
   Active(true);
   return std::make_tuple<bool, std::string>(true, "event without problems");
   }

std::tuple<bool, std::string> TMyEmployeeForm::ExitSalary(TMyForm& frm) {
   if(!Active()) return std::make_tuple<bool, std::string>(false, "events running");
   try {
      Active(false);
      auto src = frm.GetEditAs<double, true>("edtSalary");
      if(src) {
         frm.Set<EMyFrameworkType::edit>("edtSalary", src, -1, 2);
         }
      //frm.Alignment<EMyFrameworkType::edit>("edtSalary", EMyAlignmentType::right);
      }
   catch(std::exception &ex) {
      std::cerr << ex.what() << std::endl;
      return std::make_tuple<bool, std::string>(false, ex.what());
      }
   Active(true);
   return std::make_tuple<bool, std::string>(true, "event without problems");
   }

//---------------------------------------------------------------------------
std::tuple<bool, std::string> TMyEmployeeForm::CheckSocialSecurityNumber(TMyForm& frm) {
   std::optional<std::string> strNumber;
   frm.GetEdit("edtSocialSecurityNumber", strNumber);
   if(!strNumber) return std::make_tuple<bool, std::string>(true, "field with SocialSecurityNumber is empty!");
   else {
      try {
         strNumber = myRules::CheckSocialSecurityNumber(std::forward<std::string>(*strNumber));
         }
      catch(std::exception &ex) {
         std::cerr << "Fehler im Formular " << frm.FormName() << " im Feld edtSocialSecurityNumber" << std::endl
                   << ex.what() << std::endl;
         return std::make_tuple<bool, std::string>(false, ex.what());
         }
      }
   frm.Set<EMyFrameworkType::edit>("edtSocialSecurityNumber", strNumber);
   return std::make_tuple<bool, std::string>(true, "field with SocialSecurityNumber is correct filled");
   }







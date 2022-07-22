//---------------------------------------------------------------------------

#ifndef ProzesseVCLH
#define ProzesseVCLH

#include "MyForm.h"
#include "Prozesse.h"
//---------------------------------------------------------------------------

class TProcessVCL : public TProcess {
   public:
      TProcessVCL(void);
      TProcessVCL(TProcessVCL const&) = delete;
      virtual ~TProcessVCL(void);

      virtual TMyForm CreatePersonForm(void);
      virtual TMyForm CreateEmployeeForm(void);
      virtual TMyForm CreatePersonListForm(void);

      virtual TMyForm CreateDirectoryForm(void);
      virtual TMyForm CreateFileDialog(void);
   };

#endif

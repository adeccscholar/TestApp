//---------------------------------------------------------------------------

#ifndef ProzesseFMXH
#define ProzesseFMXH
//---------------------------------------------------------------------------

#include "MyForm.h"
#include "Prozesse.h"
//---------------------------------------------------------------------------

class TProcessFMX : public TProcess {
   public:
      TProcessFMX(void);
      TProcessFMX(TProcessFMX const&) = delete;
      virtual ~TProcessFMX(void);

      virtual TMyForm CreatePersonForm(void);
      virtual TMyForm CreateEmployeeForm(void);

      virtual TMyForm CreatePersonListForm(void);

      virtual TMyForm CreateDirectoryForm(void);
      virtual TMyForm CreateFileDialog(void);
   };

#endif

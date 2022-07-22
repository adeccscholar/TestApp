#pragma once

#include <Prozesse.h>
#include <MyForm.h>

class TProcessQT : public TProcess {
public:
   TProcessQT(void);
   TProcessQT(TProcessQT const&) = delete;
   virtual ~TProcessQT(void);

   virtual TMyForm CreatePersonForm(void);
   virtual TMyForm CreateEmployeeForm(void);
   virtual TMyForm CreatePersonListForm(void);

   virtual TMyForm CreateDirectoryForm(void);
   virtual TMyForm CreateFileDialog(void);
};

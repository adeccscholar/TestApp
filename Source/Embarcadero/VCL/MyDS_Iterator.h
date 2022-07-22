#ifndef MyDS_IteratorH
#define MyDS_IteratorH

#include <Vcl.StdCtrls.hpp>

#include <iterator>
#include <string>
#include <cstddef>

struct my_dslist_iterator {
   using iterator_category = std::input_iterator_tag;
   using value_type        = std::string;
   using difference_type   = std::ptrdiff_t;
   using reference         = const value_type&;
   using pointer           = const value_type*;

   my_dslist_iterator() { }

   my_dslist_iterator(System::Classes::TStrings* para) {
      theText = para;
      start_pos = 0;
      ++* this;
      }

   my_dslist_iterator& operator = (System::Classes::TStrings* para) {
      theText   = para;
      start_pos = 0;
      return *this;
      }

   my_dslist_iterator& operator = (my_dslist_iterator const& ref) {
      theText = ref.theText;
      start_pos = ref.start_pos;
      theLine   = ref.theLine;
      return *this;
      }

   reference operator*() const { return theLine; }
   pointer   operator->() const { return &theLine; }

   my_dslist_iterator& operator++() {
      if(theText) {
         if(start_pos < theText->Count) {
            theLine = AnsiString(theText->Strings[start_pos++]).c_str();
            }
         else {
            theText = nullptr;
            }
         }
      return *this;
      }

   my_dslist_iterator operator++(int) {
       auto copy(*this);
       ++* this;
       return copy;
      }


   friend bool operator == (const my_dslist_iterator& x, const my_dslist_iterator& y) {
      return x.theText == y.theText;
      }


   friend bool operator != (const my_dslist_iterator& x, const my_dslist_iterator& y) {
      return !(x == y);
      }

   private:
      System::Classes::TStrings* theText   = nullptr;
      std::string                theLine;
      size_t                     start_pos = 0;

};

struct my_dslist {
   my_dslist(System::Classes::TStrings* para) { theText = para; }
   my_dslist(my_dslist const& ref) { theText = ref.theText; }

   my_dslist_iterator begin() const { return my_dslist_iterator(theText); }
   my_dslist_iterator end()  const  { return my_dslist_iterator(); }

   private:
      System::Classes::TStrings* theText;
   };

#endif

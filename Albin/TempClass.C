#include <TObject.h>
#include <iostream>



class TempClass : public TObject
{
	public:
	Int_t year;
	Int_t month;
	Int_t day;
	Int_t hour;
	
	Double_t temp;
	string qual;
};

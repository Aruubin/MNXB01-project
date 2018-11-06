#include <iostream>
#include "TempClass.C"

void classtest();

void classtest()
{
	TempClass measurement;
	measurement.year=1923;
	std::cout<< measurement.year<<endl;
}

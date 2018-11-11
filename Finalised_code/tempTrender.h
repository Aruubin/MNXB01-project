#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>

class tempTrender {
	public:
	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

	private:
	Int_t startYear;
	Int_t endYear;
	Int_t numberOfYears;
	static const Int_t maxNumberOfYears = 100;
	Double_t yearSum[maxNumberOfYears]; //Total sum of temperature
	Double_t yearCount[maxNumberOfYears]; //Total number of temperature counts in a year.
	Double_t yearAvg[maxNumberOfYears]; // Average for each year.
	Double_t meanYearAvg; // Mean of the average yearly temperature.
};

#endif

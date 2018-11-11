//Here we will include the files used for our tasks and call them

#include "ReadVisby.C"
#include "emil.C"

void project(){
	
	Visby_hist(5); //Here the investigation of coastal versus inland climate is done.
					//In this case, the investigated month is May
					
	each_day(1961); //Here the plotting of the mean temperature for each day of a year
					//is performed. Changing the input value of the function each_day()
					//produces a plot of the temperatures that year.
}

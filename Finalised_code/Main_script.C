//Here we will include the files used for our tasks and call them

#include "ReadVisby.C"
#include "emil.C"
#include "tempTrender.cpp"
//#include "SaeidRootFinal.C"

void project(){
					
	//Simply uncomment the function for which you wish to view a histogram of

	//each_day(1961); //Here the plotting of the mean temperature for each day of a year
					//is performed. Changing the input value of the function each_day()
					//produces a plot of the temperatures that year.
	
	/*string pathToFile = "../datasets/smhi-opendata_Lund.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	t.tempPerYear(2050); 
	*/
					
	//Visby_hist(5); //Here the investigation of coastal versus inland climate is done.
					//In this case, the investigated month is May
	
	//SaeidRootFinal(); //Sadly, this at the moment does not compile
}
					


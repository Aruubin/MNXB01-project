#include "tempTrender.h"
#include <string>

void project() {
	string pathToFile = "../datasets/smhi-opendata_Lund.csv"; //Put the path to your data file here
	//string  pathToFile = "test_data.csv";
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
}

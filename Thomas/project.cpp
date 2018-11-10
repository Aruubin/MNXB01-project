#include "tempTrender.h"
#include <string>

void project() {
	string pathToFile = "../datasets/smhi-opendata_Lund.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	t.tempPerYear(2050); 
}

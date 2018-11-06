#include <iostream>
#include <fstream>

using namespace std;


#include <TF1.h>  
#include <TH1.h> 
#include <TStyle.h>
#include <TMath.h> 
#include <TCanvas.h>

void Visby_analysis();

void Visby_analysis()
{	//open the datafile for Visby measurements
	ifstream file("smhi-opendata_Visby.csv");
	
	//need to specify the structure of data after looking at the raw datafile
	//All information in datafile:
	double_t Temp= 0;
	int_t Year = 0;
	int_t Month = 0;
	int_t Day = 0;
	string helpString;
	int_t Hour = 0;
	int_t min;
	int_t sec;
	string Quality;
	
	
	//Get useful data: In a while-loop
	while(file>>Year>>helpString>>Month>>helpString>>Day>>helpString>>Hour>>helpString>>min>>helpString>>sec>>helpString>>Temp>>helpString>>Quality){
		//Insert data into measurement objects
	}
	
	//For chosen measrements, data objects to group their properties
	//Create class for measurements, and use #include "ClassName.h"
	//Store class objects in a ROOT tree 
	
	
	
	//Make histogram for drawing
	//TH1D* hTemp = new TH1D("hTemp", "Name/description; x-axis; y-axis",0,0,0)
	
	
	
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <numeric>
#include "trimData.C" //File with function trim() that executes bash script
//trimData.sh that cuts the dataset I've chosen to not contain any text.

using namespace std;

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void each_day(Int_t year){

	Int_t dayCounter = 1;
	Int_t dayCounter1 = -1;
	string strReadYear;
	string strMonth;
	string strDay;
	string strHour;
	string strMinute;
	string strSecond;
	string strTemp;
	
	Int_t readYear = -1;
	Int_t month = -1;
	Int_t day = -1;
	Int_t hour = -1;
	Int_t minute = -1;
	Int_t second = -1;
	Double_t temp = -1.0;
	
	vector<double> Templist;
	vector<double> avgList;
	string Ymd = "placeholder";
	string ymd = "datestring";
	Double_t avgTemp = 0.0;
	Double_t lastTemp = 0.0;
	Int_t lastDay = -1;
	
	string helpString; //help variable
	
	//create histogram that I will fill with data values
	TH1D* hDat = new TH1D("hDat", "; Day of year; Temperature [#circC]", 
			  366, 0, 366);

	trim(); //calling of function trim() that creates a new textfile
	//Lund.csv without any text in it.
	
	ifstream file("Lund.csv");
	
	while(file){
			
		//using getline to extract each variable as a string
		getline(file, strReadYear, '-');
		getline(file, strMonth, '-');
		getline(file, strDay, ';');
		getline(file, strHour, ':');
		getline(file, strMinute, ':');
		getline(file, strSecond, ';');
		getline(file, strTemp, '\n');
		  
		//object from the class stringstream 
		//making strReadYear into an integer readYear
		//integers declared in the beginning of document
		stringstream str1(strReadYear); 
		str1 >> readYear;
				
		//converting strMonth into an integer month
		stringstream str2(strMonth);
		str2 >> month;
				
		//converting strDay into an integer day
		stringstream str3(strDay);
		str3 >> day;
				
		//converting strHour into an integer hour
		stringstream str4(strHour);
		str4 >> hour;
				
		//converting strMinute into an integer minute
		stringstream str5(strMinute);
		str5 >> minute;
				
		//converting strSecond into an integer second
		stringstream str6(strSecond);
		str6 >> second;
				
		//converting strTemp into a double temp
		stringstream str7(strTemp);
		str7 >> temp;
		
		//if the entered year is the same as the year being read of the file, enter if statement
		if(year==readYear){	

			ymd = strReadYear + strMonth + strDay;
			
			//if the date being read is the same as the previous read date, enter if statement
			if(ymd==Ymd){
				Templist.push_back(temp); //temperatures of the same day is added to a list
			}
			
			//when the next date is read enter else where the average temperature for the previous
			//day is calculated and the list of temparatures is cleared and to which the current
			//date's temperature is added.
			else{
				avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
				Int_t len = Templist.size();
				
				for(Int_t i = 0; i < len; ++i){
					avgList.push_back(pow((Templist[i]-avgTemp), 2.0));
				}
				Templist.clear();
				Templist.push_back(temp);
				
				if(len != 0){
					
					hDat->SetBinContent(dayCounter, avgTemp);
					hDat->SetBinError(dayCounter, sqrt((1./len)*accumulate(avgList.begin(), avgList.end(), 0.0)));
					avgList.clear();
					dayCounter++;
				}
			}
			Ymd = ymd;
		}
	}
	
	file.close();
	
	//calculate avgTemp for the last read date
	avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
	for(unsigned int i = 0; i < Templist.size(); ++i){
		avgList.push_back(pow((Templist[i]-avgTemp), 2.0));
	}
	hDat->SetBinContent(dayCounter, avgTemp);
	hDat->SetBinError(dayCounter, sqrt((1./Templist.size())*accumulate(avgList.begin(), avgList.end(), 0.0)));
	TCanvas* c2 = new TCanvas("c2", "TempEachDay", 1920, 1080);
	hDat->SetLineWidth(2.5);
	hDat->Draw();

}



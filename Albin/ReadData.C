#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <numeric>

#include "Data_trimming.C"

using namespace std;

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void each_day(Int_t year){
	
	Int_t yearCount = 0; //counter
	string strReadYear;
	string strMonth;
	string strDay;
	string strHour;
	string strMinute;
	string strSecond;
	string strTemp;
	string quality;
	
	Int_t readYear = -1;
	Int_t month = -1;
	Int_t day = -1;
	Int_t hour = -1;
	Int_t minute = -1;
	Int_t second = -1;
	Double_t temp = -1.0;
	
	list<double> Templist;
	string Ymd = "placeholder";
	
	string helpString; //help variable
	
	TH1D* hTemp = new TH1D("hTemp", "Temperature as Visby; temperature [deg]; Counts", 
			1000, 0, 40);
	
	usebash();

	ifstream file("nicedata.csv");
	
	while(file){
			
		//using getline to extract each variable as a string
		getline(file, strReadYear, '-');
		getline(file, strMonth, '-');
		getline(file, strDay, ';');
		getline(file, strHour, ':');
		getline(file, strMinute, ':');
		getline(file, strSecond, ';');
		getline(file, strTemp, '\n');
		  
		// object from the class stringstream 
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
		
		if(readYear == year and month==7){
			//For measurements of the same day, the average temperature is added to the histogram
			string ymd = strReadYear + strMonth + strDay;
			
			//First gives a -nan due to the list first being empty. Nothing prompts the final avg for day 31 to be calculated
			if(ymd==Ymd){Templist.push_back(temp);}
			
			else{
				Double_t avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
				hTemp->Fill(avgTemp);
				Int_t len = Templist.size();
				Templist.clear();
				Templist.push_back(temp);
				cout<<day-1<<endl;
				cout<<avgTemp<<endl;
				cout<<len<<endl<<endl;
			}
			Ymd=ymd;
			
			
		}
	
	}
	
	file.close();
}



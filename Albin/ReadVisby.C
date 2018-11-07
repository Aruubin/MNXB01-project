#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <numeric>

#include "DataTrimVisby.C"
#include "DataTrimBoras.C"

using namespace std;

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRint.h>
#include <THStack.h>

void Visby_hist(){
	
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
	string ymd = "Datestring";
	Double_t avgTemp = 0;
	Double_t lastTemp = 0;
	
	string helpString; //help variable
	
	TH1D* hVisby = new TH1D("hTemp", "Temperature at Visby; temperature [deg]; Counts", 
			1000, 0, 40);
	
	trimVisby();

	ifstream file("trimmedVisby.csv");
	
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
		
		if(month==7){
			//For measurements of the same day, the average temperature is added to the histogram
			ymd = strReadYear + strMonth + strDay;
			
			//Nothing prompts the final avg for day 31 to be calculated
			if(ymd==Ymd){Templist.push_back(temp);}
			
			else{
				avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
				Int_t len = Templist.size();
				Templist.clear();
				Templist.push_back(temp);
				if(len != 0){
					hVisby->Fill(avgTemp);
				}
			}
			Ymd=ymd;
			lastTemp=temp;
			
		}
	
	}
	//calculate and print avgTemp for the last investigated day
	avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
	hVisby->Fill(avgTemp);
	
	
	file.close();
	
	
	Int_t yearCountB = 0; //counter
	string strReadYearB;
	string strMonthB;
	string strDayB;
	string strHourB;
	string strMinuteB;
	string strSecondB;
	string strTempB;
	string qualityB;
	
	Int_t readYearB = -1;
	Int_t monthB = -1;
	Int_t dayB = -1;
	Int_t hourB = -1;
	Int_t minuteB = -1;
	Int_t secondB = -1;
	Double_t tempB = -1.0;
	
	list<double> TemplistB;
	string YmdB = "placeholder";
	string ymdB = "Datestring";
	Double_t avgTempB = 0;
	Double_t lastTempB = 0;
	
	string helpStringB; //help variable
	
	TH1D* hBoras = new TH1D("hTemp", "Temperature at Boras; temperature [deg]; Counts", 
			1000, 0, 40);
	
	trimBoras();

	ifstream fileB("trimmedBoras.csv");
	
	while(fileB){
			
		//using getline to extract each variable as a string
		getline(fileB, strReadYearB, '-');
		getline(fileB, strMonthB, '-');
		getline(fileB, strDayB, ';');
		getline(fileB, strHourB, ':');
		getline(fileB, strMinuteB, ':');
		getline(fileB, strSecondB, ';');
		getline(fileB, strTempB, '\n');
		  
		// object from the class stringstream 
		//making strReadYear into an integer readYear
		//integers declared in the beginning of document
		stringstream str1(strReadYearB); 
		str1 >> readYearB;
				
		//converting strMonth into an integer month
		stringstream str2(strMonthB);
		str2 >> monthB;
				
		//converting strDay into an integer day
		stringstream str3(strDayB);
		str3 >> dayB;
				
		//converting strHour into an integer hour
		stringstream str4(strHourB);
		str4 >> hourB;
				
		//converting strMinute into an integer minute
		stringstream str5(strMinuteB);
		str5 >> minuteB;
				
		//converting strSecond into an integer second
		stringstream str6(strSecondB);
		str6 >> secondB;
				
		//converting strTemp into a double temp
		stringstream str7(strTempB);
		str7 >> tempB;
		
		if(monthB==7){
			//For measurements of the same day, the average temperature is added to the histogram
			ymdB = strReadYearB + strMonthB + strDayB;
			
			//Nothing prompts the final avg for day 31 to be calculated
			if(ymdB==YmdB){TemplistB.push_back(tempB);}
			
			else{
				avgTempB=accumulate(TemplistB.begin(), TemplistB.end(), 0.0)/(TemplistB.size());
				Int_t lenB = TemplistB.size();
				TemplistB.clear();
				TemplistB.push_back(tempB);
				if(lenB != 0){
					hBoras->Fill(avgTempB);
				}
			}
			YmdB=ymdB;
			lastTempB=tempB;
			
		}
	
	}
	//calculate and print avgTemp for the last investigated day
	avgTempB=accumulate(TemplistB.begin(), TemplistB.end(), 0.0)/(TemplistB.size());
	hBoras->Fill(avgTempB);
	
	
	file.close();
	
	//Cannot print both histograms neatly at the same time
	//FIX IT!!
	THStack *hs = new THStack("hs","");
	hVisby->SetFillColor(kRed);
	hs->Add(hVisby);
	hBoras->SetFillColor(kGreen);
	hs->Add(hBoras);
	
	TCanvas* cs = new TCanvas("cs","cs",10,10,700,900);
	cs->cd(2); hs->Draw("nostack"); 
	
}



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <numeric>

#include "DataTrimBoras.C"

using namespace std;

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void Boras_hist(){
	
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

	ifstream file("trimmedBoras.csv");
	
	while(file){
			
		//using getline to extract each variable as a string
		getline(file, strReadYearB, '-');
		getline(file, strMonthB, '-');
		getline(file, strDayB, ';');
		getline(file, strHourB, ':');
		getline(file, strMinuteB, ':');
		getline(file, strSecondB, ';');
		getline(file, strTempB, '\n');
		  
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
	
	TCanvas* c2 = new TCanvas("c2", "Boras histogram", 900, 600);
	
	hBoras->SetMinimum(0);
	hBoras->Draw();
	
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <numeric>

#include "DataTrimVisby.C"
#include "DataTrimBoras.C"

using namespace std;

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h> 
#include <TRint.h>
#include <THStack.h>
#include <TLegend.h>


void Visby_hist(Int_t ChosenMonth){
	
	//Values will be extracted as a string
	string strReadYear;
	string strMonth;
	string strDay;
	string strHour;
	string strMinute;
	string strSecond;
	string strTemp;
	string quality;
	
	//Values will then be converted to useful integers and doubles
	Int_t readYear = -1;
	Int_t month = -1;
	Int_t day = -1;
	Int_t hour = -1;
	Int_t minute = -1;
	Int_t second = -1;
	Double_t temp = -1.0;
	
	//These are to be used in calculating the average temperature over a day
	list<double> Templist;
	string Ymd = "placeholder";
	string ymd = "Datestring";
	Double_t avgTemp = 0;
	Double_t lastTemp = 0;
	
	
	TH1D* hVisby = new TH1D("hTemp", "Temperature at Visby; Temperature [#circC]; Counts", 
			400, -10, 30);
	
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
		
		if(month==ChosenMonth){
			//For measurements of the same date, the average temperature is added to the histogram
			ymd = strReadYear + strMonth + strDay;
			
			//Note that nothing here prompts the final avg for the last investigated day to be calculated
			//This is insted done after the file is done reading
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
	//Here the avgTemp for the last investigated day is calculated and printed
	avgTemp=accumulate(Templist.begin(), Templist.end(), 0.0)/(Templist.size());
	hVisby->Fill(avgTemp);
	
	
	file.close();
	
	
	//Here the same as for the Visby measurements is done for measurements taken at Boras
	//This is so that the two histograms can be plotted together for comparison
	
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
	
	
	TH1D* hBoras = new TH1D("hTempB", "Temperature at Boras; temperature [deg]; Counts", 
			400, -10, 30);
	
	trimBoras();

	ifstream fileB("trimmedBoras.csv");
	
	while(fileB){
			
		getline(fileB, strReadYearB, '-');
		getline(fileB, strMonthB, '-');
		getline(fileB, strDayB, ';');
		getline(fileB, strHourB, ':');
		getline(fileB, strMinuteB, ':');
		getline(fileB, strSecondB, ';');
		getline(fileB, strTempB, '\n');
		  

		stringstream str1(strReadYearB); 
		str1 >> readYearB;
				
				
		stringstream str2(strMonthB);
		str2 >> monthB;
				
	
		stringstream str3(strDayB);
		str3 >> dayB;
				
	
		stringstream str4(strHourB);
		str4 >> hourB;
				
	
		stringstream str5(strMinuteB);
		str5 >> minuteB;
				
		
		stringstream str6(strSecondB);
		str6 >> secondB;
				
	
		stringstream str7(strTempB);
		str7 >> tempB;
		
		if(monthB==ChosenMonth){
		
			ymdB = strReadYearB + strMonthB + strDayB;
			
			
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
	
	avgTempB=accumulate(TemplistB.begin(), TemplistB.end(), 0.0)/(TemplistB.size());
	hBoras->Fill(avgTempB);
	
	
	file.close();
	
	//Use the plot modification given in the skeleton code in order to make the figure neat
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetTitleSize(0.05, "x"); 
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetLabelSize(0.05, "x");
	gStyle->SetLabelSize(0.05, "y");
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.16);
	
	//In order to compare the two histograms, they are printed on the same canvas
	TCanvas* cVis = new TCanvas("cVis","Visby", 1500, 800);
	hVisby->SetLineColor(2);
	hBoras->SetLineColor(4);
	hVisby->Draw();
	hBoras->Draw("SAME");
	
	//To make the comparison more clear, gaussian fits of the two temperature distributions are done
	TF1* fitVisby = new TF1("fitVisby","gaus");
	TF1* fitBoras = new TF1("fitBoras","gaus");
	fitBoras->SetLineColor(3);
	fitBoras->SetLineWidth(3);
	fitVisby->SetLineColor(1);
	fitVisby->SetLineWidth(3);
	hVisby->Fit(fitVisby);
	hBoras->Fit(fitBoras);
	
	TLegend* legend = new TLegend(0.1,0.7,0.48,0.9);
	legend->SetHeader("Comparison of temperatures at Visby & Boras");
	legend->AddEntry(hVisby,"Average temperatures at Visby for May month","l");
	legend->AddEntry(hBoras,"Average day temperatures at Boras for May month","l");
	legend->AddEntry(fitVisby,"Gaussian fit for the Visby temperature","l");
	legend->AddEntry(fitBoras,"Gaussian fit for the Boras temperature","l");
	legend->Draw();
	
}



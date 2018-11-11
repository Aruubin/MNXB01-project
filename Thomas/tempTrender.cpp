#include <fstream>
#include <iostream>

using namespace std;

#include "tempTrender.h"
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TGraph.h>
#include <THStack.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>

tempTrender::tempTrender(string filePath) {
	startYear = -1;
	endYear = -1;
	numberOfYears = -1;
	
	for(Int_t i = 0; i < maxNumberOfYears; i++)
	{
		yearSum[i] = 0.0;
		yearCount[i] = 0;
	}
	
	ifstream file(filePath.c_str());
	string helpString;
	
	//The first number of strings without data is skipped.
	while(file >> helpString)
	{
		if (helpString.find("UTC") != string::npos) 
		{
			break;
		}
		
	}
	
	while(file >> helpString)
	{ 
		//Datapoints have atleast a length of 25. Sorting out the rest.
		if (helpString.length()>24)
		{
			//First two characters in the data string should be 19 or 20. Sorting out the rest.
			string firstTwo = helpString.substr(0,2);
			if (firstTwo == "19" || firstTwo == "20")
			{	
				//Cutting out the wanted strings.
				string dateStr = helpString.substr(0,10);
				string yearStr = helpString.substr(0,4);
				string hourStr = helpString.substr(11,2);
				string restStr = helpString.substr(20);
				
				//Using 'find' to get the temperature string, that has varying length. 
				Int_t semicolon_pos = restStr.find(";");
				string tempStr = restStr.substr(0,semicolon_pos); 
				string qualityStr = restStr.substr(semicolon_pos+1,1);
				
				//The bad data is sorted out.
				if(qualityStr == "G")
				{	//Only data from 06.00 and 18.00 is used, since they are the only every dataset have.
					if(hourStr == "06" || hourStr == "18")
					{
						//Converting strings intro int and float.
						Int_t year;
						Float_t temp;
						sscanf(yearStr.c_str(), "%d", &year);
						sscanf(tempStr.c_str(), "%f", &temp);
						
						//Asigning startYear and endYear to the first and last completed year.
						if (startYear == -1 && dateStr.find("-01-01") == 4)
						{
							startYear = year;
						}
						if (dateStr.find("-12-31") == 4)
						{
							endYear = year;
						}
						if (startYear != -1)
						{
							Int_t pos = year-startYear;
							yearSum[pos] += temp;
							yearCount[pos] += 1;
						}
					}
				}	
			}
		} 
	}
	numberOfYears = endYear - startYear + 1;
	
	Double_t sumAvg = 0.0;
	//Calculating the average yearly temperature.
	for(Int_t i = 0; i < numberOfYears; i++)
	{
		yearAvg[i] = yearSum[i]/yearCount[i];
		sumAvg += yearAvg[i];
	}
	//Calculating the mean average yearly temperature.
	meanYearAvg = sumAvg/numberOfYears;
	file.close();
}

void tempTrender::tempPerYear(int yearToExtrapolate) //Make a histogram of average temperature per year, then fit and extrapolate to the given year
{
	//Creates a histogram of the yearly average temperature. Should be drawn furthest back in plot.
	TH1D* hYearAvg = new TH1D("yearAvgHist","Average yearlly temperature in Lund", numberOfYears, startYear, endYear+1);
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		hYearAvg->Fill(startYear+i, yearAvg[i]);
	}
	
	//Histogram with the mean yearly temperature. Constant. In the middle in the plot.
	TH1D* hMeanAvg = new TH1D("meanAvg","Mean temperature over a year in Lund", numberOfYears, startYear, endYear+1);
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		hMeanAvg->Fill(startYear+i, meanYearAvg);
	}
	
	//Histogram with either mean yearly average or the yearly averge if lower. Should be drawn in the front.
	TH1D* hWhite = new TH1D("white","filling in colour", numberOfYears, startYear, endYear+1);
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		Double_t value = meanYearAvg;
		if (yearAvg[i]<value)
		{
			value =yearAvg[i];
		}
		hWhite->Fill(startYear+i, value);
	}
	
	//Creates a graph of the mean of the closes 5 years, including itself.
	TGraph* gFiveMean = new TGraph();
	for (Int_t bin = 3; bin < numberOfYears-1; bin++)
	{
		Double_t y_value = (hYearAvg->GetBinContent(bin-2) + hYearAvg->GetBinContent(bin-1) +
		hYearAvg->GetBinContent(bin) + hYearAvg->GetBinContent(bin+1) + hYearAvg->GetBinContent(bin+2))/5.0;

		gFiveMean->SetPoint(gFiveMean->GetN() ,hYearAvg->GetBinCenter(bin), y_value);
	}
	
	
	//Fits an arctan function with arctan(0) at 1987. 
	TF1* fitFunc = new TF1("fitFunc", "[0]+[1]*atan(x-1987) ", startYear, endYear+1);
	hYearAvg->Fit(fitFunc);
	
	cout << "Year "<< yearToExtrapolate << endl << "Calculated temperature: " <<
	  fitFunc->Eval(yearToExtrapolate) << endl;
	  
	//Adds a box with names. 
	TLegend* legend = new TLegend(0.2, 0.775, 0.4, 0.925);
	legend->SetHeader("Yearly average temperature of Lund");
	legend->AddEntry(fitFunc, "A fitted arctan function");
	legend->AddEntry(gFiveMean, "Moving average over 5 years");
	
	//Creates an canvas
	TCanvas* c3 = new TCanvas("c3", "Year average", 900, 600);
	
	//Plotting settings.
	hYearAvg->SetFillColor(2); //Red
	hMeanAvg->SetFillColor(4); //Blue
	hWhite->SetFillColor(10); //White
	THStack *thstack = new THStack("thstack", "Lunds yearly temperature");
	thstack->Add(hYearAvg);
	thstack->Add(hMeanAvg);
	thstack->Add(hWhite);
	thstack->SetMinimum(3.0);
	thstack->Draw("nostack");
	thstack->GetXaxis()->SetTitle("Year");
	thstack->GetYaxis()->SetTitle("Average Temperature [#circC]");
	gFiveMean->SetLineWidth(3);
	gFiveMean->Draw("SAME C");
	fitFunc->SetLineColor(8);
	fitFunc->SetLineWidth(3);
	fitFunc->Draw("SAME C");
	legend->Draw();
	c3->SaveAs("yearAvg_Lund.png");
}

#include <fstream>
#include <iostream>

using namespace std;

#include "tempTrender.h"
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TGraph.h>
#include <THStack.h>

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
	
	//Below the first number of lines with text in the file is removed.
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
			string firstTwo = helpString.substr(0,2);
			if (firstTwo == "19" || firstTwo == "20")
			{	
				//Cutting out the wanted values.
				string dateStr = helpString.substr(0,10);
				string yearStr = helpString.substr(0,4);
				string hourStr = helpString.substr(11,2);
				string restStr = helpString.substr(20);

				Int_t semicolon_pos = restStr.find(";");
				string tempStr = restStr.substr(0,semicolon_pos); 
				string qualityStr = restStr.substr(semicolon_pos+1,1);
				
				//Only the values 
				if(qualityStr == "G")
				{
					if(hourStr == "06" || hourStr == "18")
					{
						Int_t year;
						Float_t temp;
						sscanf(yearStr.c_str(), "%d", &year);
						sscanf(tempStr.c_str(), "%f", &temp);
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
						
						//cout << "Year: " << year << " Temp: " << temp << endl;
					}
				}	
			}
		} 
	}
	numberOfYears = endYear - startYear + 1;
	
	Double_t sumAvg = 0.0;
	
	for(Int_t i = 0; i < numberOfYears; i++)
	{
		yearAvg[i] = yearSum[i]/yearCount[i];
		sumAvg += yearAvg[i];
	}
	meanYearAvg = sumAvg/numberOfYears;
	//cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	//cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
	
	file.close();
}

void tempTrender::tempPerYear(int yearToExtrapolate) //Make a histogram of average temperature per year, then fit and extrapolate to the given year
{
	
	TH1D* hYearAvg = new TH1D("yearAvgHist","Average yearlly temperature in Lund", numberOfYears, startYear, endYear+1);
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		//cout << startYear+i<<" , " << yearAvg[i]<< endl;
		hYearAvg->Fill(startYear+i, yearAvg[i]);
		//hYearAvg->SetBinContent(hYearAvg->FindBin(startYear+i),yearAvg[i]);
	}
	hYearAvg->SetFillColor(2); //Red
	
	
	TH1D* hMeanAvg = new TH1D("meanAvg","Mean temperature over a year in Lund", numberOfYears, startYear, endYear+1);
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		hMeanAvg->Fill(startYear+i, meanYearAvg);
	}
	hMeanAvg->SetFillColor(4); //blue
	
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
	hWhite->SetFillColor(10); //White
	
	THStack *thstack = new THStack("thstack", "");
	thstack->Add(hYearAvg);
	thstack->Add(hMeanAvg);
	thstack->Add(hWhite);
	thstack->SetMinimum(5.5);
	thstack->Draw("nostack");
	
	/*
	Double_t x[100], y[100];
	for (Int_t i = 0; i<numberOfYears;i++)
	{
		x[i]=startYear+i;
		y[i]=yearAvg[i];
	}
	TGraph* gr = new TGraph(numberOfYears, x, y);
	gr->SetFillColor(38);
	gr->Draw("AB");
	
	TGraph* gYearAvg = new TGraph();
	
	//TH1D* hYearAvg = new TH1D("yearAvgHist","Average yearlly temperature in Lund",numberOfYears, startYear, endYear);
	
	for (Int_t i = 0; i < numberOfYears ; i++)
	//{
		gYearAvg->Expand(i+1,100);
		gYearAvg->SetPoint(i,startYear+i,yearAvg[i]);
		
	}
	gYearAvg->Draw("Same C");
	*/
}

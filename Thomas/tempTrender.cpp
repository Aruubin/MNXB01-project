#include <fstream>
#include <iostream>

using namespace std;

#include "tempTrender.h"

tempTrender::tempTrender(string filePath) {
	const Int_t startYear = 1961;
	const Int_t endYear = 2014;
	const Int_t numberOfYears = endYear-startYear+1;
	Double_t yearSum[numberOfYears];
	Int_t yearCount[numberOfYears];
	
	for(Int_t i = 0; i < numberOfYears; i++)
	{
		yearSum[i] = 0.0;
		yearCount[i] = 0;
	}
	
	ifstream file(filePath.c_str());
	string helpString;
	while(file >> helpString)
	{
		if (helpString.find("UTC") != string::npos) 
		{
			break;
		}
		
	}
	
	while(file >> helpString)
	{ 
		
		if (helpString.length()>24)
		{
			string firstTwo = helpString.substr(0,2);
			if (firstTwo == "19" || firstTwo == "20")
			{	
				string dateStr = helpString.substr(0,10);
				string yearStr = helpString.substr(0,4);
				string hourStr = helpString.substr(11,2);
				string restStr = helpString.substr(20);

				Int_t semicolon_pos = restStr.find(";");
				string tempStr = restStr.substr(0,semicolon_pos); 
				string qualityStr = restStr.substr(semicolon_pos+1,1);
				if(qualityStr == "G")
				{
					if(hourStr == "06" || hourStr == "18")
					{
						Int_t year;
						Float_t temp;
						sscanf(yearStr.c_str(), "%d", &year);
						sscanf(tempStr.c_str(), "%f", &temp);
						if (year >= startYear && year <= endYear)
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
	
	Double_t yearAvg[numberOfYears];
	for(Int_t i = 0; i < numberOfYears; i++)
	{
		yearAvg[i] = yearSum[i]/yearCount[i];
		
	}
	
	for (Int_t i = 0; i<numberOfYears; i++)
	{
		cout << yearAvg[i] << endl;
	}
	
	//cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	//cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
	file.close();
}

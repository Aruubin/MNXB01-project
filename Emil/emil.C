#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
	
	string helpString; //help variable
	string helpString1;
	
	//open input file
	//ifstream infile("smhi_opendata_Lund.csv");
	
	//ofstream file("example.csv");
	
	//char c;
	//Int_t line_no = 1;
	//while(infile.get(c)){
		
	//	if(line_no > 12){
	//		file << c;
	//	}
		
	//	if(&c == "\n"){
	//		line_no = line_no + 1;
	//		cout << "new line" << endl;
	//	}
	//}
	
	//file.close();
	
	//infile.close();
	
	ifstream file("smhitest.csv");
	
	while(file >> helpString){
	// >> month >> helpString >> day >> helpString >> hour >> helpString >> minute >> helpString >> second >> helpString >> temp >> helpString >> quality
	//while(!file.eof()){
	
	//use stoi to convert strings to integers
		
		getline(file, strReadYear, '-');
		getline(file, strMonth, '-');
		getline(file, strDay, ';');
		getline(file, strHour, ':');
		getline(file, strMinute, ':');
		getline(file, strSecond, ';');
		getline(file, strTemp, ';');
		//getline(file, quality, '\n');
		
		readYear = atoi(strMonth);
		
		//cout << "\n";
		//cout << "\n" << strReadYear << "-" << strMonth << "-"	<< strDay << endl;
		//cout << strHour << ":" << strMinute << ":" << strSecond << endl;
		//cout << temp << endl;
		//cout << quality << endl;
		
		cout << readYear << endl;
		
	//	cout << "hello1" << endl;
		
	//	if(readYear == year){
	//		cout << "hello" << endl;
	//	}
		if(file){
			yearCount ++;
		}
		
		//string cool = "1961-01-01";
		
		//if(file >> cool){
			//break;}
	}
	
	file.close();
}


